/*----------------------------------------
  finddlg.cpp
  $Date: 2001/08/12 04:16:28 $
  Copyright (C) 2000 - 2001 Masaki Suketa
 ------------------------------------------*/
#include <windows.h>
#include <string.h>
#include <stdio.h>
#include "resource.h"
#include "finddlg.h"
#include "rubywin.h"
#include "rwcommon.h"
#include "dismscwarn.h"

using namespace std;

extern RubyWin theRubyWin;

FINDDLG::FINDDLG(
    FindInfo & findinfo,
    const char *pResourceName
    ):
    DLGBASE(pResourceName),
    m_findinfo(findinfo)
    {
    if (strcmp(pResourceName, "FINDDLG") == 0) {
        m_is_repl = FALSE;
    }
    else {
        m_is_repl = TRUE;
    }
    m_search_flg = 0;
}

LRESULT CALLBACK FINDDLG::DlgProc(
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

BOOL FINDDLG::WmInitDialog(
    WPARAM wParam,
    LPARAM lParam
    ) {
    if (m_hFont) {
        SendMessage(m_hwnd, WM_SETFONT, (WPARAM)m_hFont, MAKELPARAM(TRUE, 0));
    }

    m_search_flg = m_findinfo.SearchFlg();
    if (m_search_flg & FR_MATCHCASE) {
        CheckDlgButton(m_hwnd, IDC_CHK_MATCH_CASE, BST_CHECKED);
    }
    if (m_search_flg & FR_WHOLEWORD) {
        CheckDlgButton(m_hwnd, IDC_CHK_WHOLE_WORD, BST_CHECKED);
    }

    if (!m_findinfo.SetCmbFindStr(ToHwnd(IDC_CMB_FIND_STR))) {
        EnableWindow(ToHwnd(IDOK), FALSE);
    }
    if (m_is_repl) {
        m_findinfo.SetCmbReplStr(ToHwnd(IDC_CMB_REPL_STR));
    }
    return FALSE;
}

BOOL FINDDLG::WmSetFont(
    WPARAM wParam,
    LPARAM lParam
    ) {
    SendMessage(ToHwnd(IDC_CMB_FIND_STR), WM_SETFONT, wParam, lParam);
    if (m_is_repl) {
        SendMessage(ToHwnd(IDC_CMB_REPL_STR), WM_SETFONT, wParam, lParam);
    }
    return FALSE;
}

BOOL FINDDLG::WmCommand(
    WPARAM wParam,
    LPARAM lParam
    ) {
    switch(LOWORD(wParam)) {
    case IDOK:
        return IdOK(wParam, lParam);
    case IDCANCEL:
        EndDialog(m_hwnd, IDCANCEL);
	return TRUE;
    case IDC_CMB_FIND_STR:
        return IdcCmbFindStr(wParam, lParam);
    case IDC_CMB_REPL_STR:
        return IdcCmbFindStr(wParam, lParam);
    }
    return FALSE;
}

BOOL FINDDLG::IdOK(
    WPARAM wParam,
    LPARAM lParam
    ) {
    GetInputData(IDC_CMB_FIND_STR, m_find_str);
    m_findinfo.AddFindStr(m_find_str.c_str());

    if (m_is_repl) {
        GetInputData(IDC_CMB_REPL_STR, m_repl_str);
        m_findinfo.AddReplStr(m_repl_str.c_str());
    }

    m_search_flg = 0;
    if(IsDlgButtonChecked(m_hwnd, IDC_CHK_MATCH_CASE)) {
        m_search_flg |= FR_MATCHCASE;
    }
    if (IsDlgButtonChecked(m_hwnd, IDC_CHK_WHOLE_WORD)) {
        m_search_flg |= FR_WHOLEWORD;
    }
    m_findinfo.SetSearchFlg(m_search_flg);

    EndDialog(m_hwnd, IDOK);
    return TRUE;
}

BOOL FINDDLG::IdcCmbFindStr(
    WPARAM wParam,
    LPARAM lParam
    ) {
    if (HIWORD(wParam) == CBN_EDITCHANGE) {
        HWND hFindStr = ToHwnd(IDC_CMB_FIND_STR);
        int nFLen = GetWindowTextLength(hFindStr);
        EnableWindow(ToHwnd(IDOK), (nFLen > 0));
    }
    return TRUE;
}

void FINDDLG::GetInputData(
    int nID,
    string & str
    ) {
    HWND hwnd = ToHwnd(nID);
    int nLen = GetWindowTextLength(hwnd);
    char *p = new char[nLen + 1];
    GetWindowText(hwnd, p, nLen + 1);
    str = p;
    delete [] p;
}
