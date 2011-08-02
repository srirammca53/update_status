/*----------------------------------
  filedlg.h
  $Date: 2001/04/15 05:43:37 $
  Copyright (C) 2000 Masaki Suketa
 -----------------------------------*/
#ifndef FILE_DLG_H
#define FILE_DLG_H
BOOL ShowOpenFileDlg(HWND hwnd, char *str, char *fullpath, char *fname);
BOOL ShowSaveFileDlg(HWND hwnd, char *str, char *fullpath, char *fname);
#endif
