/*----------------------------------
  dlgbase.cpp
  $Date: 2001/08/12 04:16:28 $
  Copyright (C) 2000 Masaki Suketa
 -----------------------------------*/
#include <windows.h>
#include "resource.h"
#include "dlgbase.h"

DLGBASE::DLGBASE(
    const char *pResourceName
    ):
    m_resource(pResourceName)
    {
    m_hFont = NULL;
    m_hwnd = NULL;
}

DLGBASE::~DLGBASE() {
    if (m_hFont) {
        DeleteObject(m_hFont);
    }
}

void DLGBASE::SetFont(
    DWORD dwCharSet,
    const char *pFaceName
    ) {
    m_hFont = CreateFont(0, 0, 0, 0, FW_REGULAR,
                         FALSE, FALSE, FALSE,
                         dwCharSet,
                         OUT_DEFAULT_PRECIS,
                         CLIP_DEFAULT_PRECIS,
                         PROOF_QUALITY,
                         FIXED_PITCH | FF_MODERN,
                         pFaceName);
}
        
int DLGBASE::Open(
    HWND hWndParent,
    HINSTANCE hInst
    ) {
    return DialogBoxParam(hInst, m_resource.c_str(), hWndParent,
                          reinterpret_cast<DLGPROC>(DLGBASE::TDlgProc),
                          reinterpret_cast<LPARAM>(this));
}

LRESULT CALLBACK DLGBASE::TDlgProc(
    HWND hDlgWnd,
    UINT msg,
    WPARAM wParam,
    LPARAM lParam
    ) {
    DLGBASE * pDlg = reinterpret_cast<DLGBASE *>(GetWindowLong(hDlgWnd, DWL_USER));
    switch(msg) {
    case WM_INITDIALOG:
        pDlg = reinterpret_cast<DLGBASE*>(lParam);
        SetWindowLong(hDlgWnd, DWL_USER, reinterpret_cast<LPARAM>(pDlg));
        pDlg->SetHWND(hDlgWnd);
        return pDlg->DlgProc(msg, wParam, lParam);
    default:
        if(pDlg) {
            return pDlg->DlgProc(msg, wParam, lParam);
        }
        return FALSE;
    }
    return TRUE;
}

LRESULT CALLBACK DLGBASE::DlgProc(
    UINT msg,
    WPARAM wParam,
    LPARAM lParam
    ) {
    return FALSE;
}
