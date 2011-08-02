/*--------------------------------------
  rwclass.cpp
  $Date: 2003/01/11 11:40:28 $
  Copyright (C) 2000-2001 Masaki Suketa
----------------------------------------*/
#include <windows.h>
#include "judge_jcode.h"
#include "rubywin.h"
#include "rwclass.h"
#include "rwcommon.h"
#include "ruby.h"
#include "dismscwarn.h"

/* Redefine RUBY_METHOD_FUNC for VC6.0(C++) Compatibility */
#ifdef RUBY_METHOD_FUNC
#undef RUBY_METHOD_FUNC
#endif

#ifndef ANYARGS
#define ANYARGS void
#endif
#define RUBY_METHOD_FUNC(func) (reinterpret_cast<VALUE(*)(ANYARGS)>(func))

VALUE rb_cRW_CONSOLE;
VALUE rb_mRW_IO_EMULATE;
VALUE rb_eRW_DUMMY_ERROR;
VALUE rb_cRubyWin;
VALUE rb_cRW_Buffer;

bool is_call_ruby_gets = false;

extern RubyWin theRubyWin;

static VALUE rubywin_s_set_auto_judge_jcode(
    VALUE self,
    VALUE val
    ) {
    switch (TYPE(val)) {
    case T_NIL:
    case T_FALSE:
        theRubyWin.set_auto_judge_jcode(FALSE);
        break;
    default:
        theRubyWin.set_auto_judge_jcode(TRUE);
        break;
    }
    return val;
}

static VALUE rubywin_s_get_auto_judge_jcode(
    VALUE self
    ) {
    if (theRubyWin.get_auto_judge_jcode()) {
        return Qtrue;
    }
    return Qfalse;
}

static VALUE rw_buffer_s_set_def_fileio_code(
    VALUE self,
    VALUE code
    ) {
    Check_Type(code, T_STRING);
    theRubyWin.set_def_fileio_code(STR2CSTR(code));
    return code;
}

static VALUE rw_buffer_s_get_def_fileio_code(
    VALUE self
    ) {
    switch(theRubyWin.get_def_fileio_code()) {
    case JP_UTF8:
        return rb_str_new2("UTF8");
    case JP_SJIS:
        return rb_str_new2("SJIS");
    case JP_EUC:
        return rb_str_new2("EUC");
    case JP_JIS:
        return rb_str_new2("JIS");
    default:
        return rb_str_new2("UTF8");
    }
    return rb_str_new2("NONE");
}

static VALUE rw_console_f_write(
    VALUE self,
    VALUE str
    ) {
    const char *p;
    if (TYPE(str) != T_STRING)
        str = rb_obj_as_string(str);
    if (RSTRING(str)->len == 0) return INT2FIX(0);
    p = RSTRING(str)->ptr;
    theRubyWin.console_f_write(p);
    return INT2FIX(RSTRING(str)->len);
}

static VALUE rw_console_f_gets(
    VALUE self
    ) {
    const char *p = theRubyWin.console_f_gets();
    VALUE str = rb_str_new2(p);
    rb_lastline_set(str);
    return str;
}

static VALUE rw_console_f_missing(
    int argc,
    VALUE *argv,
    VALUE self
    ) {
    return self;
}

static VALUE rw_io_emulate_f_p(
    int argc,
    VALUE *argv,
    VALUE self
    ) {
    int i;
    VALUE default_rs = rb_str_new2("\r\n");
    VALUE str = rb_str_new("", 0);
    for (i = 0; i < argc; i++) {
        rb_str_concat(str, rb_obj_as_string(rb_inspect(argv[i])));
        rb_str_concat(str, default_rs);
    }
    theRubyWin.console_f_write(RSTRING(str)->ptr);
    return Qnil;
}

static VALUE rw_io_emulate_f_putc(
    VALUE self,
    VALUE ch
    ) {
    int c = NUM2CHR(ch);
    char buf[16];
    sprintf(buf, "%c", c);
    theRubyWin.console_f_write(buf);
    return ch;
}

static VALUE rw_io_emulate_f_gets(
    VALUE self
    ) {
    if (is_call_ruby_gets) {
        return rb_gets();
    }
    else {
        return rw_console_f_gets(self);
    }
}

static VALUE rw_f_exit(
    VALUE argc,
    VALUE *argv,
    VALUE obj
    ) {
    rb_raise(rb_eRW_DUMMY_ERROR, "");
    return Qnil;
}

void set_call_org_gets(
    bool b
    ) {
    is_call_ruby_gets = b;
}

void Init_rubywin() {
    set_call_org_gets(false);
    rb_cRubyWin = rb_define_class("RubyWin", rb_cObject);
    rb_define_singleton_method(rb_cRubyWin, "auto_judge_jcode=",
                               RUBY_METHOD_FUNC(rubywin_s_set_auto_judge_jcode), 1);
    rb_define_singleton_method(rb_cRubyWin, "auto_judge_jcode?",
                               RUBY_METHOD_FUNC(rubywin_s_get_auto_judge_jcode), 0);

    rb_cRW_Buffer = rb_define_class_under(rb_cRubyWin, "Buffer", rb_cObject);
    rb_define_singleton_method(rb_cRW_Buffer, "default_fileio_code=",
                               RUBY_METHOD_FUNC(rw_buffer_s_set_def_fileio_code), 1);
    rb_define_singleton_method(rb_cRW_Buffer, "default_fileio_code",
                               RUBY_METHOD_FUNC(rw_buffer_s_get_def_fileio_code), 0);
                               
    rb_cRW_CONSOLE = rb_define_class("RW_CONSOLE", rb_cObject);

    rb_define_method(rb_cRW_CONSOLE, "write",
                     RUBY_METHOD_FUNC(rw_console_f_write), 1);
    rb_define_method(rb_cRW_CONSOLE, "gets" ,
                     RUBY_METHOD_FUNC(rw_console_f_gets), 0);
    rb_define_method(rb_cRW_CONSOLE, "method_missing",
                     RUBY_METHOD_FUNC(rw_console_f_missing), -1);
    rb_mRW_IO_EMULATE = rb_define_module("RW_IO_EMULATE");
    rb_define_module_function(rb_mRW_IO_EMULATE, "gets",
                              RUBY_METHOD_FUNC(rw_io_emulate_f_gets), 0);
    rb_define_module_function(rb_mRW_IO_EMULATE, "p",
                              RUBY_METHOD_FUNC(rw_io_emulate_f_p), -1);
    rb_define_module_function(rb_mRW_IO_EMULATE, "putc",
                              RUBY_METHOD_FUNC(rw_io_emulate_f_putc), 1);
    rb_eRW_DUMMY_ERROR = rb_define_class(RW_DUMMY_ERROR,
                                         rb_eStandardError);
    rb_define_global_function("exit", RUBY_METHOD_FUNC(rw_f_exit), -1);

    rb_eval_string("$> = RW_CONSOLE.new");
    rb_eval_string("include RW_IO_EMULATE");
    rb_eval_string("STDOUT = $>");
    rb_eval_string("STDERR = $>");
    rb_eval_string("STDIN = $>");
    rb_eval_string("$stdout = $>");
    rb_eval_string("$stderr = $>");
    rb_eval_string("$stdin = $>");
}
