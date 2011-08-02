/*----------------------------------
  rwcommon.h
  $Date: 2001/08/16 12:50:40 $
  $Revision: 1.7 $
  Copyright (C) 2000 Masaki Suketa
------------------------------------*/
#ifndef RWCOMMON_H
#define RWCOMMON_H

#include <string>

using namespace std;

const char * const RUBYWIN_LIB = "rwlib";
void GetModuleFileFolder(char *folder);
void GetRWLibFullPath(char * fullpath, const char * libname);
bool IsFileExist(const char * fname);
string getlongpath(const string & path);
bool get_file_version_info(const char * file, string & version, string & copyright);
int get_file_size(const char * file);
string convert_dirsep(const char * path);
bool parse_tagstr(const string & str, string & filename, int & line);

void MESSAGE(const char * file, const long line, const char *msg);
void MESSAGE(const char * file, const long line, 
             const char * name, const int id);
void MESSAGE(const char * file, const long line, 
             const char * name, const char *val);
void MESSAGE(const char * file, const long line,
             const char * name, const string &val);
#define DOUT(msg) MESSAGE(__FILE__, __LINE__, #msg, (msg))

#endif
