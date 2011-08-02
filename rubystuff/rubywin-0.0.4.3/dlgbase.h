/*----------------------------------
  dlgbase.h
  $Date: 2001/04/15 05:43:37 $
  Copyright (C) 2000 Masaki Suketa
 -----------------------------------*/
#ifndef DLGBASE_H
#define DLGBASE_H

#include <string>

using namespace std;
class DLGBASE {
public:
    DLGBASE(const char *pResourceName);
    virtual ~DLGBASE();
    int Open(HWND hwnd, HINSTANCE hInst);
    static  LRESULT CALLBACK TDlgProc(
        HWND hDlgWnd, UINT msg,
        WPARAM wParam, LPARAM lParam
    );
    void SetFont(DWORD dwCharSet, const char *pFaceName);
protected:
    virtual LRESULT CALLBACK DlgProc(UINT msg, WPARAM wParam, LPARAM lParam);
    void SetHWND(HWND hwnd) {m_hwnd = hwnd;}
    HWND ToHwnd(int id) {return GetDlgItem(m_hwnd, id);}
    HWND m_hwnd;
    HFONT m_hFont;
    string m_resource;
};

#endif
