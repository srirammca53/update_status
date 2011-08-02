/*----------------------------------
  textcolordlg.h
  $Date: 2001/06/24 08:58:21 $
  Copyright (C) 2001 Masaki Suketa
 -----------------------------------*/
#ifndef TEXTCOLORDLG_H
#define TEXTCOLORDLG_H

#include "dlgbase.h"
#include "reditprop.h"

class TEXTCOLORDLG :public DLGBASE {
public:
    TEXTCOLORDLG();
    virtual ~TEXTCOLORDLG(){}
protected:
    LRESULT CALLBACK DlgProc(UINT msg, WPARAM wParam, LPARAM lParam);
private:
    BOOL WmCommand(WPARAM wParam, LPARAM lParam);
    BOOL WmInitDialog(WPARAM wParam, LPARAM lParam);
    BOOL IdOK(WPARAM wParam, LPARAM lParam);
    BOOL IdcPbTextcolor(WPARAM wParam, LPARAM lParam);
    vector<COLORREF> m_ColorSample;
    vector<HWND> m_hColorSample;
};

#endif
