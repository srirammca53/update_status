/*--------------------------------------
  redit.cpp
  $Date: 2003/01/13 02:56:20 $
  $Revision: 1.13 $
  Copyright (C) 1999-2003 Masaki Suketa
 ---------------------------------------*/
#include <windows.h>
#include <richedit.h>
#include <Scintilla.h>
#include <SciLexer.h>
#include "rubywin.h"
#include "redit.h"
#include "docwin.h"
#include "resource.h"
#include "rwcommon.h"
#include "dismscwarn.h"

extern RubyWin theRubyWin;
WNDPROC OrgRichEditProc;

static BOOL IsStartKeyWord(
    const string & str,
    const char *key
    ) {
    string::size_type pos = str.find_first_not_of(" ");
    if (pos != string::npos) {
        pos = 0;
    }
    pos = str.find(key, pos);
    if (pos != string::npos) {
        int n = pos + strlen(key);
        char c = str[n];
        if (c == ' ' ||
            c == '(' ||
            c == '\0' ||
            c == '\n' ||
            c == '\r') {
            return TRUE;
        }
    }
    return FALSE;
}

static BOOL IsFinishKeyWord(
    const string & str,
    const char * key
    ) {
    string::size_type pos = str.find_last_not_of(" \n\r");
    if (pos == string::npos) {
        return FALSE;
    }
    int len = strlen(key);
    pos = pos - len + 1;
    if (pos < 0) {
        return FALSE;
    }
    pos = str.find(key, pos);
    if (pos == string::npos) {
        return FALSE;
    }
    return TRUE;
}

void REDIT::SetCharFormat(
    CHARFORMAT *pfm
    ) {
    SendMessage(m_hwnd, SCI_STYLESETFONT, STYLE_DEFAULT, (LPARAM)pfm->szFaceName);
    for (int style = 0; style <= STYLE_MAX; style++) {
        SendMessage(m_hwnd, SCI_STYLESETFONT, style, (LPARAM)pfm->szFaceName);
        SendMessage(m_hwnd, SCI_STYLESETSIZE, style, (LPARAM)(pfm->yHeight/20));
        SendMessage(m_hwnd, SCI_STYLESETFORE, style,
                    (LPARAM)(theRubyWin.ReditProperty().textColor[0].color));
        SendMessage(m_hwnd, SCI_STYLESETCHARACTERSET, style, (LPARAM)pfm->bCharSet);
    }
    SetForeColor();
    SendMessage(m_hwnd, SCI_SETCODEPAGE, SC_CP_UTF8, 0);
}

void REDIT::SetStyleSetBack(
    COLORREF cr
    ) {
    for (int style = 0; style <= STYLE_MAX; style++) {
    	SendMessage(m_hwnd, SCI_STYLESETBACK, style, cr);
    }
}

void REDIT::ConsoleWrite(
    int len,
    const char *p
    ) {
    SendMessage(m_hwnd, SCI_ADDTEXT, len, reinterpret_cast<LPARAM>(p));
    SendMessage(m_hwnd, EM_SCROLLCARET, 0, 0);
}

LRESULT REDIT::GotoLine(
    int line
    ) {
    return SendMessage(m_hwnd, SCI_GOTOLINE, line-1, 0);
}

LRESULT REDIT::GotoPos(
    int pos
    ) {
    return SendMessage(m_hwnd, SCI_GOTOPOS, pos, 0);
}

LRESULT REDIT::GetSel(
    CHARRANGE *pcr
    ) {
    return SendMessage(m_hwnd, EM_EXGETSEL, 0, reinterpret_cast<LPARAM>(pcr));
}

LRESULT REDIT::SetSel(
    CHARRANGE *pcr
    ) {
    return SendMessage(m_hwnd, EM_EXSETSEL, 0, reinterpret_cast<LPARAM>(pcr));
}

LRESULT REDIT::ReplaceSel(
    const char *str
    ) {
    return SendMessage(m_hwnd, EM_REPLACESEL, 0, reinterpret_cast<LPARAM>(str));
}

int REDIT::FindText(
    int flg,
    FINDTEXTEX *ft
    ) {
    return SendMessage(m_hwnd, EM_FINDTEXTEX, flg, reinterpret_cast<LPARAM>(ft));
}
    
int REDIT::GetLength() {
    return SendMessage(m_hwnd, SCI_GETLENGTH, 0, 0);
}

BOOL REDIT::CanUndo() {
    return SendMessage(m_hwnd, SCI_CANUNDO, 0, 0);
}

BOOL REDIT::CanPaste() {
    return SendMessage(m_hwnd, SCI_CANPASTE, 0, 0);
}

LRESULT REDIT::Undo() {
    return SendMessage(m_hwnd, SCI_UNDO, 0, 0);
}

LRESULT REDIT::Copy() {
    return SendMessage(m_hwnd, SCI_COPY, 0, 0);
}
LRESULT REDIT::Cut() {
    return SendMessage(m_hwnd, SCI_CUT, 0, 0);
}
LRESULT REDIT::Paste() {
    return SendMessage(m_hwnd, SCI_PASTE, 0, 0);
}
LRESULT REDIT::SelectAll() {
    return SendMessage(m_hwnd, SCI_SELECTALL, 0, 0);
}

LRESULT REDIT::Delete() {
/*
    return SendMessage(m_hwnd, EM_REPLACESEL, (WPARAM)TRUE, (LPARAM)"");
*/
    return SendMessage(m_hwnd, SCI_CLEAR, (WPARAM)TRUE, (LPARAM)"");
}

LRESULT REDIT::ScrollCaret() {
    return SendMessage(m_hwnd, SCI_SCROLLCARET, 0, 0);
}

LRESULT REDIT::Colourise(int start, int end) {
    return SendMessage(m_hwnd, SCI_COLOURISE, start, end);
}

LRESULT REDIT::SetEOL(int eol_code) {
    return SendMessage(m_hwnd, SCI_SETEOLMODE, eol_code, 0);
}

LRESULT REDIT::SetIndent(int width) {
    return SendMessage(m_hwnd, SCI_SETINDENT, width, 0);
}

LRESULT REDIT::SetLexer(int lexer) {
    return SendMessage(m_hwnd, SCI_SETLEXER, lexer, 0);
}

BOOL REDIT::IsModified() {
    return SendMessage(m_hwnd, SCI_GETMODIFY, 0, 0);
}

LRESULT REDIT::SetSavePoint() {
    return SendMessage(m_hwnd, SCI_SETSAVEPOINT, 0, 0);
}

LRESULT REDIT::GetSelText(
    char * p
    ) {
    return SendMessage(m_hwnd, EM_GETSELTEXT, 0, reinterpret_cast<LPARAM>(p));
}

LRESULT REDIT::EmptyUndoBuffer() {
    return SendMessage(m_hwnd, EM_EMPTYUNDOBUFFER, 0, 0);
}

LRESULT REDIT::AddText(
    int len,
    char *p
    ) {
    return SendMessage(m_hwnd, SCI_ADDTEXT, len, reinterpret_cast<LPARAM>(p));
}

int REDIT::LineFromChar(
    int pos
    ) {
    return SendMessage(m_hwnd, EM_EXLINEFROMCHAR, 0, pos);
}

LRESULT REDIT::GetTextRange(
    TEXTRANGE *ptr
    ) {
    return SendMessage(m_hwnd, EM_GETTEXTRANGE, 0, reinterpret_cast<LPARAM>(ptr));
}


//--- Scintilla original function ---
BOOL REDIT::CanRedo() {
    return SendMessage(m_hwnd, SCI_CANREDO, 0, 0);
}

LRESULT REDIT::Redo() {
    return SendMessage(m_hwnd, SCI_REDO, 0, 0);
}

LRESULT REDIT::DisplayLineNumber(
    BOOL doDisplay
    ) {
    int width = 0;
    if (doDisplay) {
        width = 60;
    }
    return SendMessage(m_hwnd, SCI_SETMARGINWIDTHN, 0, width);
}

BOOL REDIT::IsDisplayLineNumber() {
    return SendMessage(m_hwnd, SCI_GETMARGINWIDTHN, 0, 0) > 0;
}

void REDIT::Resize(
    const int left,
    const int top,
    const int width,
    const int height
    ) {
    MoveWindow(m_hwnd, left, top, width, height, TRUE);
}

void REDIT::Resize(
    int top,
    int width,
    int height
    ) {
    MoveWindow(m_hwnd, 0, top, width, height, TRUE);
}

BOOL REDIT::ToggleShow() {
    int nCmdShow = m_isShown? SW_HIDE : SW_SHOW;
    m_isShown = !m_isShown;
    return ShowWindow(m_hwnd, nCmdShow);
}

BOOL REDIT::Show(int nCmdShow) {
    m_isShown = (nCmdShow == SW_HIDE)? false : true;
    return ShowWindow(m_hwnd, nCmdShow);
}

REDIT* REDIT::CreateEdit(
    HWND hwnd,
    EDITTYPE type
    ) {
    DWORD style = WS_CHILD | WS_VISIBLE | WS_BORDER |
                  WS_VSCROLL | WS_HSCROLL |
                  ES_AUTOVSCROLL | ES_AUTOHSCROLL |
                  ES_MULTILINE | ES_WANTRETURN;
    if (type == EDIT_SPLIT_CONSOLE) {
        style = style | WS_THICKFRAME;
    }
    HWND hEdit =
        CreateWindowEx(WS_EX_CLIENTEDGE,
                       "Scintilla",
                       "",
                       style,
                       0, 0, 0, 0,
                       hwnd,
                       (HMENU)1,
                       theRubyWin.hInstance(),
                       NULL);
    REDIT * pREdit = new REDIT;
    pREdit->m_hwnd = hEdit;
    pREdit->SetHook(type);
    REDIT_PROPERTY &edprop = theRubyWin.ReditProperty();
    pREdit->SetEditProperty(&edprop);
    return pREdit;
}

void REDIT::SetHook(
    EDITTYPE type
    ) {
    m_edittype = type;
    if (m_edittype == EDIT_BUFFER) {
        SetIndent(2);
        SetLexer(SCLEX_RUBY);
    }
    OrgRichEditProc = (WNDPROC)GetWindowLong(m_hwnd, GWL_WNDPROC);
    SetWindowLong(m_hwnd, GWL_WNDPROC, (LONG)&REDIT::HookProc);
    SetWindowLong(m_hwnd, GWL_USERDATA, reinterpret_cast<LONG>(this));
}

LRESULT CALLBACK REDIT::ReadInputLine() {
    m_gets.nCurPos = GetWindowTextLength(m_hwnd);
    m_gets.IsReadGets = TRUE;
    MSG msg;
    while (m_gets.IsReadGets == TRUE) {
        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)){
            if (msg.message == WM_QUIT){
                break;
            }
            else {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }
        }
    }
    return reinterpret_cast<LRESULT>(m_gets.str.c_str());
}

LRESULT CALLBACK REDIT::HookProc(
    HWND hwnd,
    UINT msg,
    WPARAM wParam,
    LPARAM lParam
    ) {
    REDIT * pRedit = reinterpret_cast<REDIT*>(GetWindowLong(hwnd, GWL_USERDATA));
    if (pRedit == 0) {
        return CallWindowProc(OrgRichEditProc, hwnd, msg, wParam, lParam);
    }
    switch(msg) {
    case WM_CHAR:
        return pRedit->WmChar(wParam, lParam);
    case WM_CONTEXTMENU:
        return pRedit->WmContextMenu(wParam, lParam);
    case WM_INITMENUPOPUP:
        return SendMessage(GetParent(hwnd), WM_INITMENUPOPUP, wParam, lParam);
    case WM_LBUTTONDBLCLK:
        return pRedit->WmLButtonDblclk(wParam, lParam);
    case WM_COMMAND:
        return pRedit->WmCommand(wParam, lParam);
    case WM_SIZE:
        return pRedit->WmSize(wParam, lParam);
    case WM_DESTROY:
        delete pRedit;
        SetWindowLong(hwnd, GWL_USERDATA, 0);
        break;
    }
    return CallWindowProc(OrgRichEditProc, hwnd, msg, wParam, lParam);
}

LRESULT CALLBACK REDIT::WmChar(
    WPARAM wParam,
    LPARAM lParam
    ) {
    switch(m_edittype) {
    case EDIT_IRB:
    case EDIT_CONSOLE:
    case EDIT_SPLIT_CONSOLE:
        return ConsoleWmChar(wParam, lParam);
    case EDIT_BUFFER:
        return BufferWmChar(wParam, lParam);
    }
    return CallWindowProc(OrgRichEditProc, m_hwnd, WM_CHAR, wParam, lParam);
}

LRESULT CALLBACK REDIT::WmContextMenu(
    WPARAM wParam,
    LPARAM lParam
    ) {
    POINT pt;
    pt.x = (LOWORD(lParam));
    pt.y = (HIWORD(lParam));
    HMENU hmenu = LoadMenu(theRubyWin.hInstance(), "RUBYWINCONTEXTMENU");
    HMENU hSubmenu = GetSubMenu(hmenu, 0);
    TrackPopupMenu(hSubmenu, TPM_LEFTALIGN, pt.x, pt.y, 0, m_hwnd, NULL);
    DestroyMenu(hmenu);
    return 0;
}

LRESULT CALLBACK REDIT::WmCommand(
    WPARAM wParam,
    LPARAM lParam
    ) {
    if(IDM_UNDO <= LOWORD(wParam) && LOWORD(wParam) <= IDM_REDO ||
       IDM_EVAL_BUFFER <= LOWORD(wParam) && LOWORD(wParam) <= IDM_CHECK_SYNTAX) {
        return SendMessage(GetParent(m_hwnd), WM_COMMAND, wParam, lParam);
    }
    return 0;
}

LRESULT CALLBACK REDIT::WmLButtonDblclk(
    WPARAM wParam,
    LPARAM lParam
    ) {
    switch(m_edittype) {
    case EDIT_CONSOLE:
    case EDIT_SPLIT_CONSOLE:
        if (TagJumpFromCurrentLine()) {
            return 0;
        }
        break;
    default:
    	// do nothing.
    	break;
    }
    return CallWindowProc(OrgRichEditProc, m_hwnd, WM_LBUTTONDBLCLK, wParam, lParam);
}

LRESULT CALLBACK REDIT::WmSize(
    WPARAM wParam,
    LPARAM lParam
    ) {
    DocWin * pDoc = reinterpret_cast<DocWin *>(GetWindowLong(GetParent(m_hwnd), 0));
    if (pDoc) {
        if (m_edittype == EDIT_SPLIT_CONSOLE) {
	    RECT rc;
	    GetWindowRect(m_hwnd, &rc);
	    int cydelta = GetSystemMetrics(SM_CYSIZEFRAME);
    	    pDoc->ResizeEdit(rc.bottom - rc.top - cydelta);
	}
    }
    return CallWindowProc(OrgRichEditProc, m_hwnd, WM_SIZE, wParam, lParam);
}

BOOL REDIT::TagJumpFromCurrentLine() {
    string str = GetStrFromLine(GetCurrentLine());
    string fname;
    int line = 0;
    if (parse_tagstr(str, fname, line)) {
	theRubyWin.TagJump(fname.c_str(), line);
	return TRUE;
    }
    return FALSE;
}

LRESULT CALLBACK REDIT::ConsoleWmChar(
    WPARAM wParam,
    LPARAM lParam
    ) {
    if ((UINT)wParam == VK_RETURN && m_gets.IsReadGets == TRUE) {
        TEXTRANGE tr;
        tr.chrg.cpMin = m_gets.nCurPos;
        tr.chrg.cpMax = GetWindowTextLength(m_hwnd);
        int len = tr.chrg.cpMax - tr.chrg.cpMin + 1;
        tr.lpstrText = new char[len + 1];
        SendMessage(m_hwnd, EM_GETTEXTRANGE, 0, (LPARAM)(&tr));
        EmulateGetsEndOfLine(tr.lpstrText);
        m_gets.str = tr.lpstrText;
        delete [] tr.lpstrText;
        m_gets.IsReadGets = FALSE;
    }
    return CallWindowProc(OrgRichEditProc, m_hwnd, WM_CHAR, wParam, lParam);
}

LRESULT CALLBACK REDIT::BufferWmChar(
    WPARAM wParam,
    LPARAM lParam
    ) {
    Colourise(0, -1);
    int nCurLine = -1;
    if ((UINT)wParam == VK_RETURN) {
        CallWindowProc(OrgRichEditProc, m_hwnd, WM_CHAR, wParam, lParam);
        nCurLine = GetCurrentLine();
        AutoIndent(nCurLine);
        return 0;
    }
    else if ((UINT)wParam == VK_TAB) {
        nCurLine = GetCurrentLine();
        AutoIndent(nCurLine);
        return 0;
    }
    return CallWindowProc(OrgRichEditProc, m_hwnd, WM_CHAR, wParam, lParam);
}

void REDIT::SetEditProperty(
    REDIT_PROPERTY *pedprop
    ) {
    if (pedprop->cfm.cbSize > 0) {
        SetCharFormat(&pedprop->cfm);
    }
    SetStyleSetBack(pedprop->backColor);
    SetKeywords(pedprop->keywords.c_str());
    DisplayLineNumber(pedprop->isDisplayLineNumber);
}

void REDIT::SetForeColor() {
    vector<TEXTCOLOR>::iterator i = theRubyWin.ReditProperty().textColor.begin();
    vector<TEXTCOLOR>::iterator end = theRubyWin.ReditProperty().textColor.end();
    for (; i != end; i++) {
        SendMessage(m_hwnd, SCI_STYLESETFORE, i->id, (LPARAM)(i->color));
    }
}

LRESULT REDIT::SetKeywords(
    const char * keywords
    ) {
    return SendMessage(m_hwnd, SCI_SETKEYWORDS, 0, reinterpret_cast<LPARAM>(keywords));
}

void REDIT::AutoIndent(
    int nLine
    ) {
    int nPreLine = GetPrevNoEmptyLine(nLine);
    string str = GetStrFromLine(nLine);
    string pre = GetStrFromLine(nPreLine);
    if (nPreLine > -1) {
        if (IsNeedIndent(pre) == TRUE) {
            AutoIndent(nPreLine);
            pre = GetStrFromLine(nPreLine);
        }
    }
    int size = CalcIndentSize(str, pre);
    string s;
    if (size > 0) {
        string s1(size, ' ');
        s = s1;
    }
    SetIndent(nLine, s);
}

void REDIT::SetIndent(
    int nLine,
    const string & indent
    ) {
    string str = GetStrFromLine(nLine);
    int m = 0;
    string::size_type pos = str.find_first_not_of(" \t");
    if (string::npos != pos) {
        m = pos;
    }
    
    int i = (int)SendMessage(m_hwnd, EM_LINEINDEX, (WPARAM)nLine, 0);
    CHARRANGE cr;
    cr.cpMin = i;
    cr.cpMax = i + m;
    SendMessage(m_hwnd, EM_EXSETSEL, 0, (LPARAM)&cr);
    SendMessage(m_hwnd, EM_REPLACESEL, (WPARAM)TRUE, (LPARAM)indent.c_str());
    cr.cpMin = cr.cpMax = i + indent.size();
    SendMessage(m_hwnd, EM_EXSETSEL, 0, (LPARAM)&cr);
}

BOOL REDIT::IsNeedIndent(
    const string & str
    ) {
    const int size = 9;
    char key[size][16]
        = {"else", "elsif", "end"   , "ensure", "rescue",
           "when", "}"    , "=begin", "=end"};

    for(int j = 0; j < size; j++) {
        if(IsStartKeyWord(str, key[j]) == TRUE) {
            return TRUE;
        }
    }
    return FALSE;
}

int REDIT::CalcIndentSize(
    const string &str,
    const string &pre
    ){
    const int size1 = 12;
    char type1[size1][16] = {
        "BEGIN", "END", "begin" , "case"  , "class",
        "def"  , "for", "if"    , "module", "unless",
        "until", "while"
        };

    const int size2 = 5;
    char type2[size2][16] = {
        "else", "elsif", "ensure", "rescue", "when"}; 
    const int size5 = 4;
    char type5[size5][16]
        = {"|", "{", "[", "do"};

    int nstr = 0;
    string::size_type pos = str.find_first_not_of(' ');
    if (pos != string::npos) {
        nstr = pos;
    }
    int npre = 0;
    pos = pre.find_first_not_of(' ');
    if (pos != string::npos) {
        npre = pos;
    }

    if (pre[npre] == '\0' || pre[npre] == '\n' || pre[npre] == '\r') {
        return 0;
    }
    if (IsStartKeyWord(str, "=begin")) {
        return 0;
    }
    else if(IsStartKeyWord(str, "=end")) {
        return 0;
    }
    if (IsStartKeyWord(pre, "=end")) {
        return nstr;
    }
    int j = 0;
    
    const int size6 = 10;
    char type6[size6*2][16] = {	
        "case"  , "when",
        "when"  , "when",
        "if"    , "else",
        "if"    , "elsif",
        "elsif" , "else",
        "rescue", "rescue",
        "rescue", "ensure",
        "rescue", "end",
        "else",   "end",
        "ensure", "end"	
        };
    const int last = size6*2;
    for(j = 0; j < last; j+=2) {
        if( IsStartKeyWord(pre, type6[j]) == TRUE &&
            IsStartKeyWord(str, type6[j+1]) == TRUE ) {
            return npre;
        }
    }


    const int size3 = 3;
    char type3[size3][16]
        = {"end", "}", "]"};
    for(j = 0; j < size3; j++) {
        if(IsStartKeyWord(str, type3[j]) == TRUE) {
            npre -= theRubyWin.indent_size();
            if(npre < 0) npre = 0;
            return npre;
        }
    }
    
    for(j = 0; j < size2; j++) {
        if(IsStartKeyWord(str, type2[j]) == TRUE) {
            npre -= theRubyWin.indent_size();
            if(npre < 0) npre = 0;
            return npre;
        }
    }
    
    for(j = 0; j < size1; j++) {
        if(IsStartKeyWord(pre, type1[j]) == TRUE) {
            return npre + theRubyWin.indent_size();
        }
    }
    
    for(j = 0; j < size2; j++) {
        if(IsStartKeyWord(pre, type2[j]) == TRUE) {
            npre += theRubyWin.indent_size();
            if(npre < 0) npre = 0;
            return npre;
        }
    }
    for(j = 0; j < size5; j++) {
        if(IsFinishKeyWord(pre, type5[j]) == TRUE) {
            npre += theRubyWin.indent_size();
            return npre;
        }
    }

    return npre;
}

int REDIT::GetPrevNoEmptyLine(
    int nLine
    ) {
    int line = nLine - 1;
    string str;
    for(; line > -1; line--) {
        str = GetStrFromLine(line);
        string::size_type pos = str.find_first_not_of(" \r\n");
        if (pos != string::npos) {
            return line;
        }
    }
    return -1;
}

string REDIT::GetStrFromLine(
    int nLine
    ) {
    string str = "";
    if (nLine < 0) {
        return str;
    }
    int idx = (int)SendMessage(m_hwnd, EM_LINEINDEX, (WPARAM)nLine, 0);
    if (idx == -1)
        return str;
    WORD size = (WORD)SendMessage(m_hwnd, SCI_GETLENGTH, (WPARAM)idx, 0);
    if (size <= 0)
        return str;
    char *p = new char[size +sizeof(WORD)+ 1];
    *(WORD*)p = size + sizeof(WORD);
    WORD ncb = (WORD)SendMessage(m_hwnd, SCI_GETLINE, (WPARAM)nLine, (LPARAM)p);
    if (ncb <= 0) {
        delete [] p;
        return str;
    }
    p[ncb] = '\0';
    str = p;
    delete [] p;
    return str;
}

void REDIT::EmulateGetsEndOfLine(
    char * pline
    ) {
    int last = strlen(pline);
    if (last > 1 && 
        pline[last - 1] == '\n' && pline[last - 2] == '\r') {
        pline[last - 2] = '\n';
	pline[last - 1] = '\0';
    }
}
