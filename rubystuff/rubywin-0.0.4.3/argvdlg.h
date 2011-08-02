/*----------------------------------
  argvdlg.h
  $Revision: 1.2 $
  $Date: 2001/09/16 11:11:07 $
  Copyright (C) 2000 Masaki Suketa
 -----------------------------------*/
#ifndef ARGVDLG_H
#define ARGVDLG_H

#include <string>

#include "dlgbase.h"
#include "cmbinfo.h"

using namespace std;

class ARGVDLG :public DLGBASE{
public:
    ARGVDLG(CMBINFO& argvinfo);
    virtual ~ARGVDLG(){}
    const char *Argv() {return m_str_argv.c_str();}
protected:
    LRESULT CALLBACK DlgProc(UINT msg, WPARAM wParam, LPARAM lParam);
private:
    BOOL WmCommand(WPARAM wParam, LPARAM lParam);
    BOOL WmInitDialog(WPARAM wParam, LPARAM lParam);
    BOOL WmSetFont(WPARAM wParam, LPARAM lParam);
    BOOL IdOK(WPARAM wParam, LPARAM lParam);
    BOOL IdcCmbArgv(WPARAM wParam, LPARAM lParam);
    string m_str_argv;
    CMBINFO & m_argvinfo;
};

#endif
