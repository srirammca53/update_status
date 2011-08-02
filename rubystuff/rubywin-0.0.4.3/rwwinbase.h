/*---------------------------------
  rwwinbase.h
  $Date: 2001/04/15 05:43:37 $
  Copyright (C) 2000 Masaki Suketa
-----------------------------------*/
#ifndef RWWINBASE_H
#define RWWINBASE_H
class RWWinbase {
public:
    RWWinbase() {m_hwnd = 0;}
    virtual ~RWWinbase() {}
    static BOOL Register(
        HINSTANCE hInstance,
        LPCTSTR   lpszClassName,
        HBRUSH    hBrush
        );
    static LRESULT CALLBACK StWndProc(
        HWND hWnd,
        UINT msg,
        WPARAM wParam,
        LPARAM lParam
        );
    virtual LRESULT CALLBACK WndProc(UINT msg, WPARAM wParam, LPARAM lParam);
    void SetHWND(HWND hwnd) {m_hwnd = hwnd;}
protected:
    HWND m_hwnd;
    HMENU m_hMenu;
};

#endif

