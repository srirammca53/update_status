/*---------------------------------
  rwwinbase.cpp
  $Date: 2001/04/15 05:43:37 $
  Copyright (C) 2000 Masaki Suketa
-----------------------------------*/
#include <windows.h>
#include "rwwinbase.h"

BOOL RWWinbase::Register(
    HINSTANCE hInstance,
    LPCTSTR   szClassName,
    HBRUSH    hbrBack
    ) {

    WNDCLASS wndclass;
    wndclass.style          =CS_HREDRAW | CS_VREDRAW;
    wndclass.lpfnWndProc    =RWWinbase::StWndProc;
    wndclass.cbClsExtra     =0;
    wndclass.cbWndExtra     =sizeof(RWWinbase*);
    wndclass.hInstance      =hInstance;
    wndclass.hIcon          =LoadIcon(hInstance, "RUBYICON");
    wndclass.hCursor        =LoadCursor(NULL, IDC_ARROW);
    wndclass.hbrBackground  =hbrBack;
    wndclass.lpszMenuName   =NULL;
    wndclass.lpszClassName  =szClassName;

    return RegisterClass(&wndclass);
}

LRESULT CALLBACK RWWinbase::StWndProc(
    HWND hWnd,
    UINT msg,
    WPARAM wParam,
    LPARAM lParam
    ) {
    RWWinbase *pWin = reinterpret_cast<RWWinbase *>(GetWindowLong(hWnd, 0));
    if(pWin == 0) {
        if (msg == WM_CREATE) {
            LPCREATESTRUCT pcs = reinterpret_cast<LPCREATESTRUCT>(lParam);
            pWin = reinterpret_cast<RWWinbase *>(pcs->lpCreateParams);
            pWin->SetHWND(hWnd);
            SetWindowLong(hWnd, 0, reinterpret_cast<LONG>(pWin));
            return pWin->WndProc(msg, wParam, lParam);
        }
        else {
            return DefWindowProc(hWnd, msg, wParam, lParam);
        }
    }
    else {
        return pWin->WndProc(msg, wParam, lParam);
    }
}

LRESULT CALLBACK RWWinbase::WndProc(
    UINT msg,
    WPARAM wParam,
    LPARAM lParam
    ) {
    return DefWindowProc(m_hwnd, msg, wParam, lParam);
}

