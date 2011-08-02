/*----------------------------------
  versiondlg.cpp
  $Date: 2001/04/15 05:43:37 $
  Copyright (C) 2000 Masaki Suketa
------------------------------------*/
#include <windows.h>
#include "version.h"
#include "resource.h"

#include "rwcommon.h"
#include "versiondlg.h"

static VersionDLG *pDlg;

int VersionDLG::Open(
    HWND hWndParent,
    HINSTANCE hInst
    ) {
    return DialogBoxParam(hInst, "VERSIONDLG", hWndParent,
                          (DLGPROC)VersionDLG::DlgProc,
                          (LPARAM)this);
}

LRESULT CALLBACK VersionDLG::DlgProc(
    HWND hDlgWnd,
    UINT msg,
    WPARAM wParam,
    LPARAM lParam
    ) {
    switch(msg) {
    case WM_INITDIALOG:
        pDlg = (VersionDLG*)lParam;
        pDlg->SetHWND(hDlgWnd);
        return pDlg->InitDialog(wParam, lParam);
    case WM_COMMAND:
        return pDlg->Command(wParam, lParam);
    default:
        return FALSE;
    }
    return TRUE;
}

BOOL VersionDLG::InitDialog(
    WPARAM wParam,
    LPARAM lParam
    ) {
    string rw_version = "RubyWin ";
    rw_version += RUBYWIN_VERSION;
    SetWindowText(GetDlgItem(m_hwnd, IDC_ST_RUBYWIN_VERSION), rw_version.c_str());
    SetWindowText(GetDlgItem(m_hwnd, IDC_ST_RUBY_VERSION), m_version.c_str());
    string str_ruby_copyright = "Copyright (C) 1993-";
    str_ruby_copyright += m_version.substr(12, 4);
    str_ruby_copyright += " Yukihiro Matsumoto";
    SetWindowText(GetDlgItem(m_hwnd, IDC_ST_RUBY_COPYRIGHT),
                  str_ruby_copyright.c_str());
    string version, copyright;

    get_file_version_info("SciLexer.dll", version, copyright);
    string str_scilexer_version = "Scintilla " + version;
    SetWindowText(GetDlgItem(m_hwnd, IDC_ST_SCILEXER_VERSION),
                  str_scilexer_version.c_str());
    SetWindowText(GetDlgItem(m_hwnd, IDC_ST_SCILEXER_COPYRIGHT),
                  copyright.c_str());
    return FALSE;
}

BOOL VersionDLG::Command(
    WPARAM wParam,
    LPARAM lParam
    ) {
    switch(LOWORD(wParam)) {
    case IDOK:
        EndDialog(m_hwnd, IDOK);
        return TRUE;
    case IDCANCEL:
        EndDialog(m_hwnd, IDCANCEL);
	return TRUE;
    }
    return FALSE;
}
