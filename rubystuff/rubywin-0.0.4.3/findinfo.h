/*----------------------------------
  findinfo.h
  $Date: 2001/04/15 05:43:37 $
  Copyright (C) 2000 Masaki Suketa
 -----------------------------------*/
#ifndef FINDINFO_H
#define FINDINFO_H

#include <windows.h>
#include "cmbinfo.h"

class FindInfo {
public:
    FindInfo(){}
    void SetSearchFlg(UINT search_flg) {m_search_flg = search_flg;}
    UINT SearchFlg() {return m_search_flg;}
    BOOL SetCmbFindStr(HWND hCmb) {return m_find_str.SetComboBox(hCmb);}
    BOOL SetCmbReplStr(HWND hCmb) {return m_repl_str.SetComboBox(hCmb);}
    const char* LastFindStr() {return m_find_str.LastItem();}
    const char* LastReplStr() {return m_repl_str.LastItem();}
    void AddFindStr(const char* str) {m_find_str.AddItem(str);}
    void AddReplStr(const char* str) {m_repl_str.AddItem(str);}
private:
    UINT m_search_flg;
    CMBINFO m_find_str;
    CMBINFO m_repl_str;
};

#endif
