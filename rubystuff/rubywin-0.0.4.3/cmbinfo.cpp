/*----------------------------------
  cmbinfo.cpp
  $Date: 2001/04/15 05:43:37 $
  Copyright (C) 2000 Masaki Suketa
 -----------------------------------*/

#include <algorithm>
#include "cmbinfo.h"

using namespace std;

void CMBINFO::AddItem(
    const char *str
    ) {
    m_last_str = str;
    deque<string>::iterator i = find(m_str_list.begin(), m_str_list.end(), str);
    if (i == m_str_list.end()) {
        m_str_list.push_front(m_last_str);
    }
}

BOOL CMBINFO::SetComboBox(
    HWND hCombo
    ) {
    deque<string>::iterator i = m_str_list.begin();
    while (i != m_str_list.end()) {
        SendMessage(hCombo, CB_ADDSTRING, 0, (LPARAM)((*i).c_str()));
        i++;
    }
    if (m_last_str.size() > 0) {
        SetWindowText(hCombo, m_last_str.c_str());
        return TRUE;
    }
    return FALSE;
}
