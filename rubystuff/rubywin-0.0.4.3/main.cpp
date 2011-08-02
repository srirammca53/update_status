/*----------------------------------
  main.cpp
  $Date: 2001/08/12 04:16:28 $
  Copyright (C) 2000 Masaki Suketa
------------------------------------*/
#include <windows.h>
#include "rubywin.h"
#include "dismscwarn.h"

RubyWin theRubyWin;

int WINAPI WinMain(
    HINSTANCE hInstance,
    HINSTANCE hPrevInst,
    LPSTR lpszCmdLine,
    int nCmdShow
    ){

    if (!theRubyWin.InitInstance(hInstance)) {
        return FALSE;
    }
    return theRubyWin.Run(lpszCmdLine, nCmdShow);

}

