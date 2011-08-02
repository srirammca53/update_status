/*----------------------------------
  cmbinfo.h
  $Date: 2002/07/27 14:08:50 $
  Copyright (C) 2000 Masaki Suketa
 -----------------------------------*/
#ifndef CMBINFO_H
#define CMBINFO_H
#include <string>
#include <deque>
#include <windows.h>
using namespace std;

class CMBINFO {
public:
    CMBINFO(){}
    ~CMBINFO(){}
    void AddItem(const char * str);
    BOOL SetComboBox(HWND hCombo);
    const char* LastItem(){return m_last_str.c_str();}
private:
    deque<string> m_str_list;
    string m_last_str;
};

#endif
