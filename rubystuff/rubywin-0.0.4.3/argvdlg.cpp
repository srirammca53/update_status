/*----------------------------------
  argvdlg.cpp
  $Revision: 1.3 $
  $Date: 2001/09/16 11:10:32 $
  Copyright (C) 2000 Masaki Suketa
 -----------------------------------*/
#include <windows.h>
#include <string.h>
#include <stdio.h>
#include "resource.h"
#include "argvdlg.h"
#include "rubywin.h"
#include "dismscwarn.h"

extern RubyWin theRubyWin;

ARGVDLG::ARGVDLG(
    CMBINFO & argvinfo
    ):
    DLGBASE("ARGVDLG"),
    m_argvinfo(argvinfo)
    {
}

LRESULT CALLBACK ARGVDLG::DlgProc(
    UINT msg,
    WPARAM wParam,
    LPARAM lParam
    ) {
    switch(msg) {
    case WM_INITDIALOG:
        return WmInitDialog(wParam, lParam);
    case WM_SETFONT:
        return WmSetFont(wParam, lParam);
    case WM_COMMAND:
        return WmCommand(wParam, lParam);
    default:
        return FALSE;
    }
    return TRUE;
}

BOOL ARGVDLG::WmInitDialog(
    WPARAM wParam,
    LPARAM lParam
    ) {
    if (m_hFont) {
        SendMessage(m_hwnd, WM_SETFONT, (WPARAM)m_hFont, MAKELPARAM(TRUE, 0));
    }
    if (!m_argvinfo.SetComboBox(ToHwnd(IDC_CMB_ARGV))) {
        EnableWindow(ToHwnd(IDOK), FALSE);
    }
    return FALSE;
}

BOOL ARGVDLG::WmSetFont(
    WPARAM wParam,
    LPARAM lParam
    ) {
    SendMessage(ToHwnd(IDC_CMB_ARGV), WM_SETFONT, wParam, lParam);
    return FALSE;
}

BOOL ARGVDLG::WmCommand(
    WPARAM wParam,
    LPARAM lParam
    ) {
    switch(LOWORD(wParam)) {
    case IDOK:
        return IdOK(wParam, lParam);
    case IDCANCEL:
        EndDialog(m_hwnd, IDCANCEL);
	return TRUE;
    case IDC_CMB_ARGV:
        return IdcCmbArgv(wParam, lParam);
    }
    return FALSE;
}

BOOL ARGVDLG::IdOK(
    WPARAM wParam,
    LPARAM lParam
    ) {
    HWND hArgv = ToHwnd(IDC_CMB_ARGV);
    int nLen = GetWindowTextLength(hArgv);
    char *p = new char[nLen + 1];
    GetWindowText(hArgv, p, nLen + 1);
    m_str_argv = p;
    delete [] p;
    m_argvinfo.AddItem(m_str_argv.c_str());
    EndDialog(m_hwnd, IDOK);
    return TRUE;
}

BOOL ARGVDLG::IdcCmbArgv(
    WPARAM wParam,
    LPARAM lParam
    ) {
    if (HIWORD(wParam) == CBN_EDITCHANGE) {
        HWND hArgv = ToHwnd(IDC_CMB_ARGV);
        int nLen = GetWindowTextLength(hArgv);
        EnableWindow(ToHwnd(IDOK), (nLen > 0));
    }
    return TRUE;
}

