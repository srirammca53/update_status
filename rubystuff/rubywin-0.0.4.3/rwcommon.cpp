/*----------------------------------
  rwcommon.cpp
  $Date: 2001/08/16 12:50:40 $
  $Revision: 1.7 $
  Copyright (C) 2000 Masaki Suketa
------------------------------------*/
#include <windows.h>
#include <stdio.h>
#include <string.h>
#include <string>
#include <ctype.h>
#include <sys/stat.h>

#if defined(__CYGWIN__)
#include <sys/cygwin.h>
#endif

#include "rwcommon.h"
using namespace std;

void GetModuleFileFolder(
    char *pFolder
    ) {
    GetModuleFileName(NULL, pFolder, MAX_PATH);
    char *p = strrchr(pFolder, '\\');
    *p = '\0';
}

void GetRWLibFullPath(
    char * fullpath,
    const char * libname
    ) {
    char path[MAX_PATH];
    GetModuleFileFolder(path);
    sprintf(fullpath, "%s\\%s\\%s",
            path, RUBYWIN_LIB, libname);
}

bool IsFileExist(
    const char *fname
    ) {
    FILE *fp = fopen(fname, "r");
    if(!fp) {
        return false;
    }
    fclose(fp);
    return true;
}

static string getlongfname(
    const string & fname,
    const string & dir
    ) {
    string fpath = dir + '\\' + fname;
    string longname = dir;
    WIN32_FIND_DATA data;
    HANDLE h = FindFirstFile(fpath.c_str(), &data);
    if (h != INVALID_HANDLE_VALUE) {
        FindClose(h);
        longname = dir + '\\' +  data.cFileName;
    }
    return longname;
}

string getlongpath(
    const string & path
    ) {
    string::size_type lpos = path.find_first_of('\\', 0);
    if (lpos == string::npos) {
        return path;
    }
    string longpath = path.substr(0, 2);
    string p;
    lpos = path.find_first_of('\\', 3);
    string::size_type fpos = 3;
    while (lpos != string::npos) {
        p = path.substr(fpos, lpos-fpos);
        longpath = getlongfname(p, longpath);
        fpos = lpos + 1;
        lpos = path.find_first_of('\\', fpos);
    }
    p = path.substr(fpos);
    longpath = getlongfname(p, longpath);
    return longpath;
}

bool get_file_version_info(
    const char * file,
    string & version,
    string & copyright
    ) {
    DWORD dummy;
    version = "???";
    copyright = "???";
    DWORD infosize=GetFileVersionInfoSize(const_cast<char *>(file), &dummy);
    if (infosize == 0) {
        return false;
    }
    char* p=new char [infosize];
    if (GetFileVersionInfo(const_cast<char *>(file), 0, infosize, p) == 0) {
        delete [] p;
        return false;
    }
    DWORD *q;
    UINT bufsize=sizeof q;
    if (VerQueryValue(p, "\\VarFileInfo\\Translation", (void**)&q, &bufsize) == 0) {
        delete [] p;
        return false;
    }
    char buf[128];
    sprintf(buf, "\\StringFileInfo\\%04X%04X\\FileVersion", LOWORD(*q), HIWORD(*q));
    char *value;
    bufsize=sizeof value;
    if (VerQueryValue(p, buf, (void**)&value, &bufsize) == 0) {
        delete [] p;
        return false;
    }
    version = value;

    sprintf(buf, "\\StringFileInfo\\%04X%04X\\LegalCopyright", LOWORD(*q), HIWORD(*q));
    if (VerQueryValue(p, buf, (void**)&value, &bufsize) == 0) {
        delete [] p;
        return false;
    }
    copyright = value;
    delete [] p;
    return true;
}

int get_file_size(
    const char *file
    ) {
    struct stat st;
    memset(&st, 0, sizeof(struct stat));
    stat(file, &st);
    return st.st_size;
}

string convert_dirsep(
    const char * path
    ) {
    string s = path;
#if defined(__CYGWIN__)
    char newpath[MAX_PATH + 1];
    cygwin_conv_to_posix_path(path, newpath);
    s = newpath;
#endif
    return s;
}

static string::size_type skip_win_drive_letter(
    const string str,
    const string pause,
    string::size_type file_first,
    string::size_type file_last
    ) {
    if(str.size() > file_first + 2) {
        if (str[file_first + 1] == ':' && str[file_first + 2] == '\\') {
            return str.find_first_of(pause, file_first + 2);
        }
    }
    return file_last;
}

static string::size_type file_from_tagstr(
    const string tagstr,
    const string pause,
    string & filename
    ) {
    string::size_type file_first = tagstr.find_first_not_of(pause);
    if (file_first == string::npos) {
        return string::npos;
    }
    string::size_type file_last = tagstr.find_first_of(pause, file_first);
    file_last = skip_win_drive_letter(tagstr, pause, file_first, file_last);
    if (file_last == string::npos) {
        return string::npos;
    }
    filename = tagstr.substr(file_first, file_last-file_first);
    return file_first;
}

static string::size_type line_from_tagstr(
    const string tagstr,
    const string pause,
    int & line,
    string::size_type first
    ) {
    string::size_type line_first = tagstr.find_first_not_of(pause, first);
    if (line_first == string::npos) {
        return string::npos;
    }
    string::size_type line_last = tagstr.find_first_of(pause, line_first);
    if (line_last == string::npos) {
        return string::npos;
    }

    for (string::size_type i = line_first; i < line_last; i ++) {
        if (!isdigit(tagstr[i])) {
            return string::npos;
        }
    }

    line = atoi(tagstr.substr(line_first, line_last - line_first).c_str());
    return line_first;
}

bool parse_tagstr(
    const string & str,
    string & filename,
    int & line
    ) {

    const string pause = ": \t\r\n()[]";
    string::size_type filepos = file_from_tagstr(str, pause, filename); 
    if (filepos == string::npos) {
        return false;
    }
    if (line_from_tagstr(str, pause, line, filepos + filename.size())== string::npos) {
        return false;
    }
    return true;
}

void MESSAGE (
    const char *file,
    const long line,
    const char *msg
    ) {
    string str;
    char szline[32];
    sprintf(szline, " (%ld) ", line);
    str = file;
    str += szline;
    str += msg;
    MessageBox(NULL, str.c_str(), "RubyWin", MB_OK);
}

void MESSAGE (
    const char *file,
    const long line,
    const char *name,
    const int num
    ) {
    char sznum[32];
    sprintf(sznum, "%d", num);
    MESSAGE(file, line, name, sznum);
}

void MESSAGE(
    const char *file,
    const long line,
    const char *name,
    const char *val
    ) {
    string msg = name;
    msg += " = ";
    msg += val;
    MESSAGE(file, line, msg.c_str());
}

void MESSAGE(
    const char *file,
    const long line,
    const char *name,
    const string &val
    ) {
    MESSAGE(file, line, name, val.c_str());
    }

 
