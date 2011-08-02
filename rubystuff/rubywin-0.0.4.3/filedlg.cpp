/*----------------------------------
  filedlg.cpp
  $Date: 2001/04/15 05:43:37 $
  Copyright (C) 2000 Masaki Suketa
 -----------------------------------*/
#include <windows.h>
#include "string.h"
#include "filedlg.h"

BOOL ShowOpenFileDlg(
    HWND hwnd,
    char *title,
    char *fullpath,
    char *fname
    ) {
    OPENFILENAME ofn;
    memset(&ofn, 0, sizeof(OPENFILENAME));
    ofn.lStructSize = sizeof(OPENFILENAME);
    ofn.hwndOwner = hwnd;
    ofn.lpstrFilter = "All Files(*.*)\0*.*\0\0";
    ofn.lpstrFile = fullpath;
    ofn.nMaxFile = MAX_PATH;
    ofn.lpstrFileTitle = fname;
    ofn.nMaxFileTitle = MAX_PATH;
    ofn.Flags = OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;
    ofn.lpstrTitle = title;
    return GetOpenFileName(&ofn);
}

BOOL ShowSaveFileDlg(
    HWND hwnd,
    char *title,
    char *fullpath,
    char *fname
    ) {
    OPENFILENAME ofn;
    memset(&ofn, 0, sizeof(OPENFILENAME));
    ofn.lStructSize = sizeof(OPENFILENAME);
    ofn.hwndOwner = hwnd;
    ofn.lpstrFilter = "All Files(*.*)\0*.*\0\0";
    ofn.lpstrFile = fullpath;
    ofn.nMaxFile = MAX_PATH;
    ofn.lpstrFileTitle = fname;
    ofn.nMaxFileTitle = MAX_PATH;
    ofn.Flags = OFN_OVERWRITEPROMPT | OFN_HIDEREADONLY;
    ofn.lpstrTitle = title;
    return GetSaveFileName(&ofn);
}
