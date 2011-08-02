/*----------------------------------------
  textcolordlg.cpp
  $Date: 2001/08/12 04:16:28 $
  Copyright (C) 2001 Masaki Suketa
 -----------------------------------------*/
#include <windows.h>

#include <string>
#include "rwcommon.h"
#include "resource.h"
#include "textcolordlg.h"
#include "rubywin.h"
#include "dismscwarn.h"
using namespace std;
extern RubyWin theRubyWin;

static const string SAMPLE_STRING = "AaBb12";

TEXTCOLORDLG::TEXTCOLORDLG():
    DLGBASE("TEXTCOLORDLG")
    {
    vector<TEXTCOLOR>::iterator t = theRubyWin.ReditProperty().textColor.begin();
    vector<TEXTCOLOR>::iterator end = theRubyWin.ReditProperty().textColor.end();
    for(; t != end; t++) {
        m_ColorSample.push_back(t->color);
    }
}

LRESULT CALLBACK TEXTCOLORDLG::DlgProc(
    UINT msg,
    WPARAM wParam,
    LPARAM lParam
    ) {
    switch(msg) {
    case WM_INITDIALOG:
        return WmInitDialog(wParam, lParam);
    case WM_COMMAND:
        return WmCommand(wParam, lParam);
    default:
        return FALSE;
    }
    return TRUE;
}

BOOL TEXTCOLORDLG::WmInitDialog(
    WPARAM wParam,
    LPARAM lParam
    ) {
    vector<COLORREF>::iterator c = m_ColorSample.begin();
    for(int i = 0; c != m_ColorSample.end(); c++, i++) {
        HWND hwnd   = CreateWindowEx(0, "Scintilla", "",
                                     WS_CHILD | WS_VISIBLE | ES_READONLY,
                                     0, 15 + 26 * i, 80, 16,
                                     m_hwnd,  0,  theRubyWin.hInstance(), NULL);
        SendMessage(hwnd, SCI_ADDTEXT, SAMPLE_STRING.size(),
                    reinterpret_cast<LPARAM>(SAMPLE_STRING.c_str()));
        SendMessage(hwnd, SCI_SETREADONLY, 1, 0);
        SendMessage(hwnd, SCI_STYLESETFORE, 0, (LPARAM)(*c));
        m_hColorSample.push_back(hwnd);
    }
    return FALSE;
}

BOOL TEXTCOLORDLG::WmCommand(
    WPARAM wParam,
    LPARAM lParam
    ) {
    switch(LOWORD(wParam)) {
    case IDOK:
        return IdOK(wParam, lParam);
    case IDCANCEL:
        EndDialog(m_hwnd, IDCANCEL);
	return TRUE;
    case IDC_PB_TEXTCOLOR_DEFAULT:
    case IDC_PB_TEXTCOLOR_COMMENT:
    case IDC_PB_TEXTCOLOR_NUMBER:
    case IDC_PB_TEXTCOLOR_STRING:
    case IDC_PB_TEXTCOLOR_SSTRING:
    case IDC_PB_TEXTCOLOR_KEYWORD:
    case IDC_PB_TEXTCOLOR_CLASSNAME:
    case IDC_PB_TEXTCOLOR_METHOD:
    case IDC_PB_TEXTCOLOR_OPERATOR:
        return IdcPbTextcolor(wParam, lParam);
    }
    return FALSE;
}

BOOL TEXTCOLORDLG::IdOK(
    WPARAM wParam,
    LPARAM lParam
    ) {
    vector<COLORREF>::iterator c = m_ColorSample.begin();
    for(int i = 0; c != m_ColorSample.end(); c++, i++) {
        theRubyWin.ReditProperty().textColor[i].color = *c;
    }
    
    EndDialog(m_hwnd, IDOK);
    return TRUE;
}

BOOL TEXTCOLORDLG::IdcPbTextcolor(
    WPARAM wParam, LPARAM lParam
    ) {
    CHOOSECOLOR cc;
    static DWORD dwCustColors[16];
    const int id = LOWORD(wParam) - IDC_PB_TEXTCOLOR_DEFAULT;
    memset(&cc, 0, sizeof(CHOOSECOLOR));
    cc.lStructSize = sizeof(CHOOSECOLOR);
    cc.hwndOwner = m_hwnd;
    cc.lpCustColors = dwCustColors;
    cc.rgbResult = m_ColorSample[id];
    cc.Flags = CC_RGBINIT;
    if (ChooseColor(&cc)) {
        m_ColorSample[id] = cc.rgbResult;
        SendMessage(m_hColorSample[id], SCI_STYLESETFORE, 0, cc.rgbResult);
    }
    return TRUE;
}
