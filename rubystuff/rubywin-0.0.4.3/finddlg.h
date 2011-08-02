/*----------------------------------------
  finddlg.h
  $Date: 2001/06/17 12:43:29 $
  Copyright (C) 2000 - 2001 Masaki Suketa
 ----------------------------------------*/
#ifndef FINDDLG_H
#define FINDDLG_H

#include <string>
#include "dlgbase.h"
#include "findinfo.h"

using namespace std;

class FINDDLG :public DLGBASE{
public:
    FINDDLG(FindInfo & findinfo, const char *pResourceName);
    virtual ~FINDDLG(){}
    const char *FindStr() {return m_find_str.c_str();}
    const char *ReplStr() {return m_repl_str.c_str();}
    const UINT SearchFlg() {return m_search_flg;}
protected:
    LRESULT CALLBACK DlgProc(UINT msg, WPARAM wParam, LPARAM lParam);
private:
    BOOL WmCommand(WPARAM wParam, LPARAM lParam);
    BOOL WmInitDialog(WPARAM wParam, LPARAM lParam);
    BOOL WmSetFont(WPARAM wParam, LPARAM lParam);
    BOOL IdOK(WPARAM wParam, LPARAM lParam);
    BOOL IdcCmbFindStr(WPARAM wParam, LPARAM lParam);
    void GetInputData(int nID, string & str);
    BOOL m_is_repl;
    UINT m_search_flg;
    string m_find_str;
    string m_repl_str;
    FindInfo & m_findinfo;
};

#endif
