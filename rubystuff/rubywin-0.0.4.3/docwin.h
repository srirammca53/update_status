/*-----------------------------------------
   docwin.h
   $Date: 2001/08/16 12:47:21 $
   $Revision: 1.4 $
   Copyright (C) 2000 - 2001 Masaki Suketa
 ------------------------------------------*/
#ifndef DOCWIN_H
#define DOCWIN_H
#include <string>
#include "rwwinbase.h"
#include "ustring.h"
#include "redit.h"

using namespace std;

#define UNKNOWN_EOL -1

const int blockSize = 131072;

class RubyWin;
class DocWin {
public:
    DocWin(unsigned char jcode);
    static BOOL InitInstance(HINSTANCE hInstance);
    static LRESULT CALLBACK StWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
    HWND Create(HINSTANCE hInstance, HWND hClient, long id);
    HWND Create(HINSTANCE hInstance, HWND hClient, const char *pTitle);
    void ResizeEdit(int);
    void OpenFile(HWND hwnd, const char *pfullpath);
    void GotoLine(HWND hwnd, int line);
    LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
    const char * FullPath() {return m_fullpath;}
private:
    LRESULT CALLBACK WmCreate(HWND hwnd, WPARAM wParam, LPARAM lParam);
    LRESULT CALLBACK WmSize(HWND hwnd, WPARAM wParam, LPARAM lParam);
    LRESULT CALLBACK WmClose(HWND hwnd, WPARAM wParam, LPARAM lParam);
    LRESULT CALLBACK WmMDIActivate(HWND hwnd, WPARAM wParam, LPARAM lParam);
    LRESULT CALLBACK WmInitMenuPopup(HWND hwnd, WPARAM wParam, LPARAM lParam);
    LRESULT CALLBACK WmCommand(HWND hwnd, WPARAM wParam, LPARAM lParam);

    LRESULT CALLBACK IdmSave(HWND hwnd, WPARAM wParam, LPARAM lParam);
    LRESULT CALLBACK IdmSaveAs(HWND hwnd, WPARAM wParam, LPARAM lParam);

    LRESULT CALLBACK IdmUndo(HWND hwnd, WPARAM wParam, LPARAM lParam);
    LRESULT CALLBACK IdmRedo(HWND hwnd, WPARAM wParam, LPARAM lParam);
    LRESULT CALLBACK IdmCopy(HWND hwnd, WPARAM wParam, LPARAM lParam);
    LRESULT CALLBACK IdmCut(HWND hwnd, WPARAM wParam, LPARAM lParam);
    LRESULT CALLBACK IdmPaste(HWND hwnd, WPARAM wParam, LPARAM lParam);
    LRESULT CALLBACK IdmSelectAll(HWND hwnd, WPARAM wParam, LPARAM lParam);
    LRESULT CALLBACK IdmDelete(HWND hwnd, WPARAM wParam, LPARAM lParam);

    LRESULT CALLBACK IdmFind(HWND hwnd, WPARAM wParam, LPARAM lParam);
    LRESULT CALLBACK IdmFindNext(HWND hwnd, WPARAM wParam, LPARAM lParam);
    LRESULT CALLBACK IdmReplace(HWND hwnd, WPARAM wParam, LPARAM lParam);
    LRESULT CALLBACK IdmReplaceNext(HWND hwnd, WPARAM wParam, LPARAM lParam);

    LRESULT CALLBACK IdmEvalBuffer(HWND hwnd, WPARAM wParam, LPARAM lParam);
    LRESULT CALLBACK IdmEvalWithArgv(HWND hwnd, WPARAM wParam, LPARAM lParam);
    LRESULT CALLBACK IdmEvalSelect(HWND hwnd, WPARAM wParam, LPARAM lParam);
    LRESULT CALLBACK IdmCheckSyntax(HWND hwnd, WPARAM wParam, LPARAM lParam);
    LRESULT CALLBACK IdmSplitConsole(HWND hwnd, WPARAM wParam, LPARAM lParam);

    LRESULT CALLBACK CmdSaved(HWND hwnd, WPARAM wParam, LPARAM lParam);
    LRESULT CALLBACK CmdConsoleGets(HWND hwnd, WPARAM wParam, LPARAM lParam);
    LRESULT CALLBACK CmdSplitConsoleGets(HWND hwnd, WPARAM wParam, LPARAM lParam);
    LRESULT CALLBACK CmdSetCharFormat(HWND hwnd, WPARAM wParam, LPARAM lParam);
    LRESULT CALLBACK CmdSetBackColor(HWND hwnd, WPARAM wParam, LPARAM lParam);
    LRESULT CALLBACK CmdSetViewLine(HWND hwnd, WPARAM wParam, LPARAM lParam);
    LRESULT CALLBACK CmdConsoleWrite(HWND hwnd, WPARAM wParam, LPARAM lParam);
    LRESULT CALLBACK CmdSplitConsoleWrite(HWND hwnd, WPARAM wParam, LPARAM lParam);
    void ResizeChildWindows();
    void CreateSplitConsole(int nCmdShow);
    BOOL IsDocSaved(HWND hwnd, WPARAM wParam, LPARAM lParam);
    BOOL SaveDoc(HWND hwnd);
    BOOL SaveAsDoc(HWND hwnd);
    BOOL ShowSaveFileDlg(HWND hwnd, char *pfullpath);
    void ReadFile(HWND hwnd, const char *fullpath);
    BOOL WriteFile(HWND hwnd, const char *fullpath, unsigned char jcode);
    void WriteSelectionFile(HWND hwnd, const char *fullpath);
    void ConsoleWrite(REDIT *pRedit, LPARAM lParam);
    static DWORD CALLBACK ReadProc(DWORD dwCookie, LPBYTE pbBuf, LONG cb, LONG *pcb);
    static DWORD CALLBACK WriteProc(DWORD dwCookie, LPBYTE pbBuf, LONG cb, LONG *pcb);
    BOOL FindStr(const char* str, UINT search_flg, int nDirection);
    void ReplStr(const char* str);
    void set_filecode(const char* str, int len);
    int convert_to_utf8(const char* str, int len, UString * u);
    int utf8_convert_to(const char* str, unsigned char jcode, UString *u);
    int get_eol_code(const char* str);
    char m_fullpath[MAX_PATH];
    unsigned char m_filecode;
    HWND m_hwnd;
    REDIT *m_pEdit;
    REDIT *m_pConsole;
    double m_cs_hfactor;
};

#endif
