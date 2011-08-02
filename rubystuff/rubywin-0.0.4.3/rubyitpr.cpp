/*----------------------------------
  rubyitpr.cpp
  $Date: 2002/07/27 14:08:50 $
  $Revision: 1.7 $
  Copyright (C) 2000 Masaki Suketa
------------------------------------*/
#include <string>
#include <stdio.h>
#include <windows.h>
#include <ruby.h>
#include <node.h>
#include "rubyitpr.h"
#include "rwclass.h"
#include "rubywin.h"
#include "rwcommon.h"
#include "dismscwarn.h"

extern "C" int st_lookup(struct st_table *, char *, char **);

using namespace std;
extern RubyWin theRubyWin;

char err[] = "if /\\w+:[0-9]+:/ =~ $!.to_s \n \"#{$!.to_s}(#{$!.type.inspect.to_s})\"; \n else \n \"#{$@[0].to_s}: #{$!.to_s}(#{$!.type.inspect.to_s})\"; \n end \n ";

char errat[] = "'\n\n' + $@.collect{|i| '    from ' + i}.join('\n')";

void RubyITPR::init() {
    
#if defined(NT)
    static int dummyargc(0);
    static char** vec;
    NtInitialize(&dummyargc, &vec);
#endif
    ruby_init();
    init_rb_argv0();
    ruby_init_loadpath();
    get_version_string();
    Init_rubywin();
    load_rwini();
    reset_error();
}

void RubyITPR::get_version_string() {

    VALUE s = rb_eval_string("RUBY_VERSION + ' (' + RUBY_RELEASE_DATE + ') [' + RUBY_PLATFORM + ']'");
    m_pversion = new char [RSTRING(s)->len + 1];
    strcpy(m_pversion, STR2CSTR(s));
}

int  RubyITPR::load_protect(
    const char* fname,
    int wrap
    ) {

    VALUE f = rb_str_new2(fname);
    int state = 0;
    ruby_script(const_cast<char*>(fname));
    rb_load_protect(f, wrap, &state);
    return state;
}

void RubyITPR::load_rwini() {
    char szPath[MAX_PATH];
    GetRWLibFullPath(szPath, "rwinit.rb");
    if (IsFileExist(szPath)) {
        int state = load_protect(szPath, 0);
        if (state) {
            string msg = create_error_msg(szPath, "rwinit.rb");
            MessageBox(NULL, msg.c_str(), "RubyWin", MB_OK);
        }
    }
}

void RubyITPR::chdir_dirname(
    const char* file
    ) {
    string path = file;
    string::size_type pos = path.find_last_of('\\');
    if (pos != string::npos) {
        path = path.substr(0, pos);
        SetCurrentDirectory(path.c_str());
    }
}

void RubyITPR::clear_argv() {
    set_call_org_gets(false);
    rb_funcall(rb_argv, rb_intern("clear"), 0);
}

void RubyITPR::init_rb_argv0() {
    char path[MAX_PATH];
    memset(&path, 0, MAX_PATH);
    GetModuleFileName(NULL, path, sizeof(path));
    rb_argv0 = rb_str_new2(path);
}

void RubyITPR::reset_error() {
    rb_eval_string("$! = nil;");
}

VALUE RubyITPR::set_end_file_object_to_data(
    const char *fname
    ) {
    VALUE f = rb_file_open(fname, "r");
    VALUE line;
    int __end__seen = 0;
    while (!NIL_P(line = rb_io_gets(f))) {
        char *pb = RSTRING(line)->ptr;
        if (strncmp(pb, "__END__", 7) == 0 &&
            (RSTRING(line)->len == 7 || pb[7] == '\n' || pb[7] == '\r')) {
            __end__seen = 1;
            break;
        }
    }
    if (__end__seen) {
        ID data = rb_intern("DATA");
        if (st_lookup(RCLASS(rb_cObject)->iv_tbl, (char *)data, 0)) {
            rb_mod_remove_const(rb_cObject, rb_str_new2("DATA"));
        }
        rb_define_global_const("DATA", f);
   }
   return f;
}

void RubyITPR::argv_push_files(
    const char *wild_card
    ) {
    
    WIN32_FIND_DATA fd;
    HANDLE fh;
    if ((fh = FindFirstFile (wild_card, &fd)) == INVALID_HANDLE_VALUE) {
        return;
    }
    do {
        set_call_org_gets(true);
        rb_ary_push(rb_argv, rb_tainted_str_new2(fd.cFileName));
    } while(FindNextFile(fh, &fd));
}

void RubyITPR::reset_argv(
    const char *str_arg
    ) {
    clear_argv();
    int len = strlen(str_arg);
    char *pBuf = new char[len + 1];
    strcpy(pBuf, str_arg);

    char* ptok = strtok(pBuf, " ");
    while(ptok != NULL) {
        char *p = ptok;
        bool is_wild_card = false;
        while (*p != '\0') {
            if (*p == '*' || *p == '?') {
                argv_push_files(ptok);
                is_wild_card = true;
                break;
            }
            p++;
        }
        if (is_wild_card == false) {
            set_call_org_gets(true);
            rb_ary_push(rb_argv, rb_tainted_str_new2(ptok));
        }
        ptok = strtok(NULL, " ");
    }
    delete [] pBuf;
}

string RubyITPR::create_error_msg(
    const char *file,
    const char *fname
    ) {
    VALUE v = rb_eval_string(err);
    VALUE at = rb_eval_string(errat);
    rb_str_concat(v, at);
    string msg;

    char *p = strstr(STR2CSTR(v), RW_DUMMY_ERROR);
    if(p) return msg;

    int size = RSTRING(v)->len;
    p = new char[size+1];
    strncpy(p, RSTRING(v)->ptr, size);
    p[size] = '\0';
    msg = "\r\n";
    msg += p;
    if (strcmp(file, fname) == 0) {
        delete [] p;
        return msg + "\r\n";
    }
    string::size_type pos = msg.find(file);
    string::size_type len = strlen(file);
    while (pos != string::npos) {
        msg.replace(pos, len, fname);
        pos = msg.find(file);
    }
    msg += "\r\n";
    delete [] p;
    return msg;
}

void RubyITPR::report_error(
    const char *file,
    const char *fname
    ) {
    string msg = create_error_msg(file, fname);
    if (msg != "") {
        theRubyWin.console_f_write(msg.c_str());
    }
    reset_error();
}

int RubyITPR::run_file(
    const char *file,
    const char *fname
    ) {
    chdir_dirname(fname);
    VALUE f = set_end_file_object_to_data(file);
    string s = convert_dirsep(file);
    int state = load_protect(s.c_str(), 0);
    ruby_script((char*)fname);
    rb_io_close(f);
    if (state) {
        report_error(s.c_str(), fname);
    }
    return state;
}

int RubyITPR::run_file_with_argv(
    const char *file,
    const char *fname,
    const char *argv
    ) {
    reset_argv(argv);
    int state = run_file(file, fname);
    clear_argv();
    return state;
}

int RubyITPR::check_syntax(
    const char *fname,
    const char *title
    ) {
    int state = 0;
    VALUE f = rb_file_open(fname, "r");
    if (rb_compile_file(title, f, 1)) {
        theRubyWin.console_f_write("\nSyntax OK\n");
    }
    else {
        ruby_nerrs = 0;
        state = run_file(fname, title);
    }
    rb_io_close(f);
    return state;
}
