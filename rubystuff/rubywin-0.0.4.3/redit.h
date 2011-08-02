/*----------------------------------------
  redit.h
  $Date: 2002/07/27 14:08:50 $
  $Revision: 1.9 $
  Copyright (C) 2000 - 2001 Masaki Suketa
 -----------------------------------------*/
#ifndef REDIT_H
#define REDIT_H
#include <richedit.h>
#include <string>
#include "reditprop.h"

using namespace std;

const int INDENT_SIZE = 2;

enum EDITTYPE {
    EDIT_IRB,
    EDIT_CONSOLE,
    EDIT_SPLIT_CONSOLE,
    EDIT_BUFFER
};

struct GETS_INFO {
    GETS_INFO() {
        nCurPos = 0;
        IsReadGets = FALSE;
    }
    int  nCurPos;
    BOOL IsReadGets;
    string str;
};

struct INDENT_INFO {
    INDENT_INFO() {
        size = 0;
    }
    string str_pre;
    int size;
};

class REDIT {
public:
    REDIT(){m_isShown = true; m_hwnd = NULL;}
    static REDIT* CreateEdit(HWND hwnd, EDITTYPE type);
    static LRESULT CALLBACK HookProc(HWND, UINT, WPARAM, LPARAM);
    LRESULT CALLBACK ReadInputLine();
    void SetCharFormat(CHARFORMAT * pfm);
    void SetStyleSetBack(COLORREF cr);
    void ConsoleWrite(int len, const char *p);
    LRESULT GotoLine(int line);
    LRESULT GotoPos(int pos);
    LRESULT GetSel(CHARRANGE *pcr);
    LRESULT SetSel(CHARRANGE *pcr);
    int  GetLength();
    BOOL CanUndo();
    BOOL CanPaste();
    LRESULT Undo();
    LRESULT Copy();
    LRESULT Cut();
    LRESULT Paste();
    LRESULT SelectAll();
    LRESULT Delete();
    LRESULT ScrollCaret();
    LRESULT Colourise(int start, int end);
    LRESULT SetEOL(int eol_mode);
    LRESULT SetIndent(int width);
    LRESULT SetLexer(int lexer);
    LRESULT ReplaceSel(const char *str);
    int FindText(int flg, FINDTEXTEX *ft);
    BOOL IsModified();
    LRESULT SetSavePoint();
    LRESULT GetSelText(char *p);
    LRESULT EmptyUndoBuffer();
    LRESULT AddText(int len, char *p);
    LRESULT GetTextRange(TEXTRANGE *ptr);
    int LineFromChar(int pos);

    BOOL CanRedo();
    LRESULT Redo();
    LRESULT DisplayLineNumber(BOOL doDisplay);
    BOOL IsDisplayLineNumber();
    void Resize(int top, int width, int height);
    void Resize(const int left, const int top, const int width, const int height);
    void SetFocus() { ::SetFocus(m_hwnd); }
    BOOL ToggleShow();
    BOOL Show(int nCmdShow);
    bool IsShown() const {return m_isShown;}
    EDITTYPE EditType() const {return m_edittype;}

private:
    void SetHook(EDITTYPE type);
    LRESULT CALLBACK WmChar(WPARAM, LPARAM);
    LRESULT CALLBACK WmLButtonDblclk(WPARAM, LPARAM);
    LRESULT CALLBACK WmContextMenu(WPARAM, LPARAM);
    LRESULT CALLBACK WmCommand(WPARAM, LPARAM);
    LRESULT CALLBACK WmSize(WPARAM, LPARAM);
    BOOL TagJumpFromCurrentLine();
    LRESULT CALLBACK ConsoleWmChar(WPARAM, LPARAM);
    LRESULT CALLBACK BufferWmChar(WPARAM, LPARAM);
    void SetEditProperty(REDIT_PROPERTY *pedprop);
    void SetForeColor();
    LRESULT SetKeywords(const char * keywords);
    void AutoIndent(int nLine);
    BOOL IsNeedIndent(const string & str);
    void SetIndent(int nLine, const string & indent);
    int GetPrevNoEmptyLine(int nLine);
    string GetStrFromLine(int nLine);
    int CalcIndentSize(const string &str, const string &pre);

    int GetCurrentLine() {return (int)SendMessage(m_hwnd, EM_LINEFROMCHAR, (WPARAM)-1, 0);}

    void EmulateGetsEndOfLine(char * p);

    GETS_INFO m_gets;
    INDENT_INFO m_indent;
    EDITTYPE m_edittype;
    HWND m_hwnd;
    bool m_isShown;
};

#endif
