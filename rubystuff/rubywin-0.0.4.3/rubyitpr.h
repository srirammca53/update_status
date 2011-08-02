/*----------------------------------
  rubyitpr.h
  $Date: 2001/07/01 08:37:13 $
  Copyright (C) 2000 Masaki Suketa
------------------------------------*/
#ifndef RUBYITPR_H
#define RUBYITPR_H
#include <string>
#include "ruby.h"

using namespace std;

class RubyITPR {
public:
    RubyITPR(){};
    void init();
    const char *version_string(){
        return m_pversion;
    }
    ~RubyITPR() {
        delete [] m_pversion;
    }
    int run_file(const char *file, const char *fname);
    int run_file_with_argv(const char *file, const char *fname, const char* argv);
    int check_syntax(const char *file, const char *fname);
private:
    void init_rb_argv0();
    void reset_error();
    VALUE set_end_file_object_to_data(const char* file);
    void load_rwini();
    void chdir_dirname(const char* file);
    int  load_protect(const char* fname, int wrap=1);
    void reset_argv(const char *argv);
    void argv_push_files(const char *argv);
    void clear_argv();
    string create_error_msg(const char *file, const char *fname);
    void report_error(const char *file, const char *fname);
    void get_version_string();
    char * m_pversion;
};

#endif
