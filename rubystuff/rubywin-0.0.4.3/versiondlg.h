/*---------------------------------
  versiondlg.h
  $Revision: 1.2 $
  $Date: 2001/09/16 11:09:50 $
  Copyright (C) 2001 Masaki Suketa
 ----------------------------------*/

#ifndef VERSIONDLG_H
#define VERSIONDLG_H

#include <string>

using namespace std;

class VersionDLG {
public:
    VersionDLG() {m_version = "Ruby ";}
    int Open(HWND hWnd, HINSTANCE hInst);
    static  LRESULT CALLBACK DlgProc(
        HWND hDlgWnd, UINT msg,
        WPARAM wParam, LPARAM lParam
    );
    BOOL InitDialog(WPARAM wParam, LPARAM lParam);
    BOOL Command(WPARAM wParam, LPARAM lParam);
    void SetHWND(HWND hDlgWnd) {m_hwnd = hDlgWnd;}
    void SetVersionInfo(const char *p) {m_version += p;}
private:
    HWND m_hwnd;
    string m_version;
};
#endif
