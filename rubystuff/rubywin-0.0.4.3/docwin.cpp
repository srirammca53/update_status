/*----------------------------------------
  docwin.cpp
  $Date: 2001/08/18 07:07:14 $
  $Revision: 1.7 $
  Copyright (C) 2000 - 2001 Masaki Suketa
 ----------------------------------------*/

#include <windows.h>
#include <richedit.h>
#include <stdio.h>
#include <Scintilla.h>
#include "judge_jcode.h"
#include "rwuconv.h"
#include "rwcommon.h"
#include "docwin.h"
#include "reditprop.h"
#include "rubywin.h"
#include "resource.h"
#include "filedlg.h"
#include "argvdlg.h"
#include "finddlg.h"
#include "redit.h"
#include "dismscwarn.h"

extern RubyWin theRubyWin;

static void CreateTempFileName(
    char * ptmpfname
    ) {
    char path[MAX_PATH];
    GetModuleFileName(NULL, path, sizeof(path));
    char *p = strrchr(path, '\\');
    *p = '\0';
    char fname[MAX_PATH];
    GetTempFileName(path, "rw", 0, fname);
    strcpy(ptmpfname, fname);
}

DocWin::DocWin(unsigned char jcode){
    m_filecode = jcode;
    m_fullpath[0] = '\0';
    m_pConsole = NULL;
    m_cs_hfactor = 0.5;
}

BOOL DocWin::InitInstance(
    HINSTANCE hInstance
    ) {

    WNDCLASS wndclass;
    wndclass.style          =CS_HREDRAW | CS_VREDRAW;
    wndclass.lpfnWndProc    =DocWin::StWndProc;
    wndclass.cbClsExtra     =0;
    wndclass.cbWndExtra     =sizeof(DocWin*);
    wndclass.hInstance      =hInstance;
    wndclass.hIcon          =LoadIcon(hInstance, "RUBYICON");
    wndclass.hCursor        =LoadCursor(NULL, IDC_ARROW);
    wndclass.hbrBackground  =(HBRUSH)GetStockObject(WHITE_BRUSH);
    wndclass.lpszMenuName   =NULL;
    wndclass.lpszClassName  ="DocWin";

    return RegisterClass(&wndclass);
}

LRESULT CALLBACK DocWin::StWndProc(
    HWND hwnd,
    UINT msg,
    WPARAM wParam,
    LPARAM lParam
    ) {
    DocWin * pWin = reinterpret_cast<DocWin *>(GetWindowLong(hwnd, 0));
    if(pWin == 0) {
        if (msg == WM_CREATE) {
            CREATESTRUCT *pcs = reinterpret_cast<CREATESTRUCT *>(lParam);
            MDICREATESTRUCT *pmcs =
                reinterpret_cast<MDICREATESTRUCT *>(pcs->lpCreateParams);
            pWin = reinterpret_cast<DocWin *>(pmcs->lParam);
            SetWindowLong(hwnd, 0, reinterpret_cast<LONG>(pWin));
            return pWin->WndProc(hwnd, msg, wParam, lParam);
        }
        else {
            return DefMDIChildProc(hwnd, msg, wParam, lParam);
        }
    }
    else {
        if (msg == WM_MDIDESTROY) {
            delete pWin;
            SetWindowLong(hwnd, 0, 0);
            return DefMDIChildProc(hwnd, msg, wParam, lParam);
        }
        return pWin->WndProc(hwnd, msg, wParam, lParam);
    }
}

HWND DocWin::Create(
    HINSTANCE hInstance,
    HWND hClient,
    const char *str
    ) {
    static MDICREATESTRUCT mdic;
    mdic.szClass = "DocWin";
    mdic.szTitle = str;
    mdic.hOwner = hInstance;
    mdic.x = CW_USEDEFAULT;
    mdic.y = CW_USEDEFAULT;
    mdic.cx = CW_USEDEFAULT;
    mdic.cy = CW_USEDEFAULT;
    mdic.style = 0;
    mdic.lParam = reinterpret_cast<LPARAM>(this);
    return reinterpret_cast<HWND>(SendMessage(hClient, WM_MDICREATE, 0,(LPARAM)&mdic));
}

HWND DocWin::Create(
    HINSTANCE hInstance,
    HWND hClient,
    long id
    ) {
    char szTitle[16];
    sprintf(szTitle, "Ruby%ld", id);
    return Create(hInstance, hClient, szTitle);
}

void DocWin::CreateSplitConsole(
    int nCmdShow
    ) {
    if (!m_pConsole) {
        m_pConsole = REDIT::CreateEdit(m_hwnd, EDIT_SPLIT_CONSOLE);
    } else {
        m_pConsole->SetFocus();
    }
    m_pConsole->Show(nCmdShow);
    ResizeChildWindows();
}

void DocWin::ResizeEdit(
    int console_height
    ) {

    RECT rc;
    GetClientRect(m_hwnd, &rc);
    m_pEdit->Resize(0, rc.right - rc.left, 
                    ((rc.bottom - rc.top) - console_height));
    m_cs_hfactor = (double)console_height / (double)(rc.bottom - rc.top);
}

void DocWin::OpenFile(
    HWND hwnd,
    const char *fullpath
    ) {
    strcpy(m_fullpath, fullpath);
    ReadFile(hwnd, fullpath);
    SetWindowText(hwnd, fullpath);
    theRubyWin.UpdateRecentFiles(fullpath);
}

void DocWin::GotoLine(
    HWND hwnd,
    int line
    ) {
    m_pEdit->GotoLine(line);
}

void DocWin::ResizeChildWindows() {
    RECT rc;
    GetClientRect(m_hwnd, &rc);
    int width = rc.right - rc.left;
    if(m_pConsole && m_pConsole->IsShown()) {
	int c_height = static_cast<int>((rc.bottom - rc.top) * m_cs_hfactor);
	int e_height = (rc.bottom - rc.top) - c_height;
        m_pEdit->Resize(0, width, e_height);
        int cxdelta = GetSystemMetrics(SM_CXSIZEFRAME);
	int cydelta = GetSystemMetrics(SM_CYSIZEFRAME);
	int left = 0 - cxdelta;
        m_pConsole->Resize(left, e_height, 
                           width + 2 * cxdelta, c_height + cydelta);
    }
    else {
        m_pEdit->Resize(0, width, rc.bottom - rc.top);
    }
}

LRESULT CALLBACK DocWin::WndProc(
    HWND hwnd,
    UINT msg, 
    WPARAM wParam, 
    LPARAM lParam
    ) {
    switch(msg) {
    case WM_CREATE:
        return WmCreate(hwnd, wParam, lParam);
    case WM_SIZE:
        return WmSize(hwnd, wParam, lParam);
    case WM_CLOSE:
        return WmClose(hwnd, wParam, lParam);
    case WM_MDIACTIVATE:
        return WmMDIActivate(hwnd, wParam, lParam);
    case WM_INITMENUPOPUP:
        return WmInitMenuPopup(hwnd, wParam, lParam);
    case WM_COMMAND:
        return WmCommand(hwnd, wParam, lParam);
    }
    return DefMDIChildProc(hwnd, msg, wParam, lParam);
}

LRESULT CALLBACK DocWin::WmCreate(
    HWND hwnd,
    WPARAM wParam,
    LPARAM lParam
    ) {
    m_hwnd = hwnd;
    char szTitle[MAX_PATH];
    GetWindowText(hwnd, szTitle, MAX_PATH);
    if(strcmp(szTitle, CONSOLE) == 0 ||
       strcmp(szTitle, IRB) == 0 ) {
        m_pEdit = REDIT::CreateEdit(hwnd, EDIT_CONSOLE);
    }
    else {
        m_pEdit = REDIT::CreateEdit(hwnd, EDIT_BUFFER);
    }
    return 0;
}

LRESULT CALLBACK DocWin::WmSize(
    HWND hwnd,
    WPARAM wParam,
    LPARAM lParam
    ) {
    ResizeChildWindows();
    return DefMDIChildProc(hwnd, WM_SIZE, wParam, lParam);
}

LRESULT CALLBACK DocWin::WmClose(
    HWND hwnd,
    WPARAM wParam,
    LPARAM lParam
    ) {
    if (IsDocSaved(hwnd, wParam, lParam) == FALSE) {
        if(m_fullpath[0] != '\0') {
            theRubyWin.UpdateRecentFiles(m_fullpath);
        }
        return 0;
    }
    if(m_fullpath[0] != '\0') {
        theRubyWin.UpdateRecentFiles(m_fullpath);
    }
    return ::DefMDIChildProc(hwnd, WM_CLOSE, wParam, lParam);
}

LRESULT CALLBACK DocWin::WmMDIActivate(
    HWND hwnd,
    WPARAM wParam,
    LPARAM lParam
    ) {
    theRubyWin.DrawMenu(lParam == (LPARAM)hwnd);
    SetFocus(GetWindow(hwnd, GW_CHILD));
    return 0;
}

LRESULT CALLBACK DocWin::WmInitMenuPopup(
    HWND hwnd,
    WPARAM wParam,
    LPARAM lParam
    ) {
    HMENU hMenu = (HMENU)wParam;
    CHARRANGE cr;
    m_pEdit->GetSel(&cr);
    if(cr.cpMin == cr.cpMax) {
        EnableMenuItem(hMenu, IDM_CUT, MF_GRAYED | MF_BYCOMMAND);
        EnableMenuItem(hMenu, IDM_COPY, MF_GRAYED | MF_BYCOMMAND);
        EnableMenuItem(hMenu, IDM_DELETE, MF_GRAYED | MF_BYCOMMAND);
        EnableMenuItem(hMenu, IDM_EVAL_SELECT, MF_GRAYED | MF_BYCOMMAND);
    }
    else {
        EnableMenuItem(hMenu, IDM_CUT, MF_ENABLED | MF_BYCOMMAND);
        EnableMenuItem(hMenu, IDM_COPY, MF_ENABLED | MF_BYCOMMAND);
        EnableMenuItem(hMenu, IDM_DELETE, MF_ENABLED | MF_BYCOMMAND);
        EnableMenuItem(hMenu, IDM_EVAL_SELECT, MF_ENABLED | MF_BYCOMMAND);
    }
    char szTitle[MAX_PATH];
    GetWindowText(hwnd, szTitle, MAX_PATH);
    int n = m_pEdit->GetLength();
    if (n == 0 || strcmp(szTitle, CONSOLE) == 0 || strcmp(szTitle, IRB) == 0){
        EnableMenuItem(hMenu, IDM_EVAL_BUFFER, MF_GRAYED | MF_BYCOMMAND);
        EnableMenuItem(hMenu, IDM_EVAL_WITH_ARGV, MF_GRAYED | MF_BYCOMMAND);
        EnableMenuItem(hMenu, IDM_CHECK_SYNTAX, MF_GRAYED | MF_BYCOMMAND);
    }
    else {
        EnableMenuItem(hMenu, IDM_EVAL_BUFFER, MF_ENABLED | MF_BYCOMMAND);
        EnableMenuItem(hMenu, IDM_EVAL_WITH_ARGV, MF_ENABLED | MF_BYCOMMAND);
        EnableMenuItem(hMenu, IDM_CHECK_SYNTAX, MF_ENABLED | MF_BYCOMMAND);
    }
    if (n == 0) {
        EnableMenuItem(hMenu, IDM_FIND, MF_GRAYED | MF_BYCOMMAND);
        EnableMenuItem(hMenu, IDM_REPLACE, MF_GRAYED | MF_BYCOMMAND);
    }
    else {
        EnableMenuItem(hMenu, IDM_FIND, MF_ENABLED | MF_BYCOMMAND);
        EnableMenuItem(hMenu, IDM_REPLACE, MF_ENABLED | MF_BYCOMMAND);
    }
    if (strcmp(theRubyWin.GetFindInfo().LastFindStr(), "") == 0) {
        EnableMenuItem(hMenu, IDM_FIND_NEXT, MF_GRAYED | MF_BYCOMMAND);
        EnableMenuItem(hMenu, IDM_REPLACE_NEXT, MF_GRAYED | MF_BYCOMMAND);
    }
    else {
        EnableMenuItem(hMenu, IDM_FIND_NEXT, MF_ENABLED | MF_BYCOMMAND);
        EnableMenuItem(hMenu, IDM_REPLACE_NEXT, MF_ENABLED | MF_BYCOMMAND);
    }
    if(m_pEdit->CanUndo()) {
        EnableMenuItem(hMenu, IDM_UNDO, MF_ENABLED | MF_BYCOMMAND);
    }
    else {
        EnableMenuItem(hMenu, IDM_UNDO, MF_GRAYED | MF_BYCOMMAND);
    }

    if(m_pEdit->CanRedo()) {
        EnableMenuItem(hMenu, IDM_REDO, MF_ENABLED | MF_BYCOMMAND);
    }
    else {
        EnableMenuItem(hMenu, IDM_REDO, MF_GRAYED | MF_BYCOMMAND);
    }
        
    if(m_pEdit->CanPaste()) {
        EnableMenuItem(hMenu, IDM_PASTE, MF_ENABLED | MF_BYCOMMAND);
    }
    else {
        EnableMenuItem(hMenu, IDM_PASTE, MF_GRAYED | MF_BYCOMMAND);
    }
    if (m_pEdit->IsDisplayLineNumber()) {
        CheckMenuItem(hMenu, IDM_VIEW_LINE, MF_BYCOMMAND | MF_CHECKED);
    }
    else {
        CheckMenuItem(hMenu, IDM_VIEW_LINE, MF_BYCOMMAND | MF_UNCHECKED);
    }

    if (m_pEdit->EditType() == EDIT_BUFFER) {
       EnableMenuItem(hMenu, IDM_SPLIT_CONSOLE, MF_ENABLED | MF_BYCOMMAND);
       if (m_pConsole && m_pConsole->IsShown()) {
           CheckMenuItem(hMenu, IDM_SPLIT_CONSOLE,
                         MF_BYCOMMAND | MF_ENABLED | MF_CHECKED);
       }
       else {
           CheckMenuItem(hMenu, IDM_SPLIT_CONSOLE, 
                         MF_BYCOMMAND | MF_ENABLED | MF_UNCHECKED);
       }
    }
    else {
        CheckMenuItem(hMenu, IDM_SPLIT_CONSOLE, 
                      MF_BYCOMMAND | MF_ENABLED | MF_UNCHECKED);
        EnableMenuItem(hMenu, IDM_SPLIT_CONSOLE, 
	               MF_BYCOMMAND | MF_GRAYED);
    }
    return 0;
}

LRESULT CALLBACK DocWin::WmCommand(
    HWND hwnd,
    WPARAM wParam,
    LPARAM lParam
    ) {
    switch(LOWORD(wParam)) {
    case IDM_SAVE:
        return IdmSave(hwnd, wParam, lParam);
    case IDM_SAVE_AS:
        return IdmSaveAs(hwnd, wParam, lParam);
    case IDM_UNDO:
        return IdmUndo(hwnd, wParam, lParam);
    case IDM_REDO:
        return IdmRedo(hwnd, wParam, lParam);
    case IDM_COPY:
        return IdmCopy(hwnd, wParam, lParam);
    case IDM_CUT:
        return IdmCut(hwnd, wParam, lParam);
    case IDM_PASTE:
        return IdmPaste(hwnd, wParam, lParam);
    case IDM_SELECT_ALL:
        return IdmSelectAll(hwnd, wParam, lParam);
    case IDM_DELETE:
        return IdmDelete(hwnd, wParam, lParam);
    case IDM_FIND:
        return IdmFind(hwnd, wParam, lParam);
    case IDM_FIND_NEXT:
        return IdmFindNext(hwnd, wParam, lParam);
    case IDM_REPLACE:
        return IdmReplace(hwnd, wParam, lParam);
    case IDM_REPLACE_NEXT:
        return IdmReplaceNext(hwnd, wParam, lParam);
    case IDM_EVAL_BUFFER:
        return IdmEvalBuffer(hwnd, wParam, lParam);
    case IDM_EVAL_WITH_ARGV:
        return IdmEvalWithArgv(hwnd, wParam, lParam);
    case IDM_EVAL_SELECT:
        return IdmEvalSelect(hwnd, wParam, lParam);
    case IDM_CHECK_SYNTAX:
        return IdmCheckSyntax(hwnd, wParam, lParam);
    case IDM_SPLIT_CONSOLE:
        return IdmSplitConsole(hwnd, wParam, lParam);
    case CMD_SAVED:
        return CmdSaved(hwnd, wParam, lParam);
    case CMD_UNSAVE:
        return !CmdSaved(hwnd, wParam, lParam);
    case CMD_CONSOLE_GETS:
        return CmdConsoleGets(hwnd, wParam, lParam);
    case CMD_SPLIT_CONSOLE_GETS:
        return CmdSplitConsoleGets(hwnd, wParam, lParam);
    case CMD_SETCHARFORMAT:
        return CmdSetCharFormat(hwnd, wParam, lParam);
    case CMD_SETBACKCOLOR:
        return CmdSetBackColor(hwnd, wParam, lParam);
    case CMD_SETVIEWLINE:
        return CmdSetViewLine(hwnd, wParam, lParam);
    case CMD_CONSOLE_WRITE:
        return CmdConsoleWrite(hwnd, wParam, lParam);
    case CMD_SPLIT_CONSOLE_WRITE:
        return CmdSplitConsoleWrite(hwnd, wParam, lParam);
    }
    return DefMDIChildProc(hwnd, WM_COMMAND, wParam, lParam);
}

LRESULT CALLBACK DocWin::IdmSave(
    HWND hwnd,
    WPARAM wParam,
    LPARAM lParam
    ) {
    SaveDoc(hwnd);
    return 0;
}

LRESULT CALLBACK DocWin::IdmSaveAs(
    HWND hwnd,
    WPARAM wParam,
    LPARAM lParam
    ) {
    SaveAsDoc(hwnd);
    return 0;
}

LRESULT CALLBACK DocWin::IdmUndo(
    HWND hwnd,
    WPARAM wParam,
    LPARAM lParam
    ) {
    m_pEdit->Undo();
    return 0;
}

LRESULT CALLBACK DocWin::IdmRedo(
    HWND hwnd,
    WPARAM wParam,
    LPARAM lParam
    ) {
    m_pEdit->Redo();
    return 0;
}

LRESULT CALLBACK DocWin::IdmCopy(
    HWND hwnd,
    WPARAM wParam,
    LPARAM lParam
    ) {
    m_pEdit->Copy();
    return 0;
}

LRESULT CALLBACK DocWin::IdmCut(
    HWND hwnd,
    WPARAM wParam,
    LPARAM lParam
    ) {
    m_pEdit->Cut();
    return 0;
}

LRESULT CALLBACK DocWin::IdmPaste(
    HWND hwnd,
    WPARAM wParam,
    LPARAM lParam
    ) {
    m_pEdit->Paste();
    return 0;
}

LRESULT CALLBACK DocWin::IdmSelectAll(
    HWND hwnd,
    WPARAM wParam,
    LPARAM lParam
    ) {
    m_pEdit->SelectAll();
    return 0;
}

LRESULT CALLBACK DocWin::IdmDelete(
    HWND hwnd,
    WPARAM wParam,
    LPARAM lParam
    ) {
    m_pEdit->Delete();
    return 0;
}

LRESULT CALLBACK DocWin::IdmFind(
    HWND hwnd,
    WPARAM wParam,
    LPARAM lParam
    ) {
    FINDDLG finddlg(theRubyWin.GetFindInfo(), "FINDDLG");
    CHARFORMAT & cfm = theRubyWin.CharFormat();
    if (cfm.cbSize) {
        finddlg.SetFont(cfm.bCharSet, cfm.szFaceName);
    }
    if (finddlg.Open(hwnd, theRubyWin.hInstance()) == IDOK) {
        FindStr(finddlg.FindStr(), finddlg.SearchFlg(), IDM_FIND_NEXT);
    }
    SetFocus(GetWindow(hwnd, GW_CHILD));
    return 0;
}

LRESULT CALLBACK DocWin::IdmFindNext(
    HWND hwnd,
    WPARAM wParam,
    LPARAM lParam
    ) {
    FindInfo & fi = theRubyWin.GetFindInfo();
    FindStr(fi.LastFindStr(), fi.SearchFlg(), IDM_FIND_NEXT);
    SetFocus(GetWindow(hwnd, GW_CHILD));
    return 0;
}

LRESULT CALLBACK DocWin::IdmReplace(
    HWND hwnd,
    WPARAM wParam,
    LPARAM lParam
    ) {
    FINDDLG repldlg(theRubyWin.GetFindInfo(), "REPLDLG");
    CHARFORMAT & cfm = theRubyWin.CharFormat();
    if (cfm.cbSize) {
        repldlg.SetFont(cfm.bCharSet, cfm.szFaceName);
    }
    if (repldlg.Open(hwnd, theRubyWin.hInstance()) == IDOK) {
        if (FindStr(repldlg.FindStr(), repldlg.SearchFlg(), IDM_FIND_NEXT)) {
            ReplStr(repldlg.ReplStr());
        }
    }
    SetFocus(GetWindow(hwnd, GW_CHILD));
    return 0;
}

LRESULT CALLBACK DocWin::IdmReplaceNext(
    HWND hwnd,
    WPARAM wParam,
    LPARAM lParam
    ) {
    FindInfo & fi = theRubyWin.GetFindInfo();
    if (FindStr(fi.LastFindStr(), fi.SearchFlg(), IDM_FIND_NEXT)) {
        ReplStr(fi.LastReplStr());
    }
    SetFocus(GetWindow(hwnd, GW_CHILD));
    return 0;
}

LRESULT CALLBACK DocWin::IdmEvalBuffer(
    HWND hwnd,
    WPARAM wParam,
    LPARAM lParam
    ) {

    char szTitle[MAX_PATH + 1];
    GetWindowText(hwnd, szTitle, MAX_PATH);

    char tmpfname[MAX_PATH + 1];
    CreateTempFileName(tmpfname);
    WriteFile(hwnd, tmpfname, m_filecode);
    int state = theRubyWin.run_file(tmpfname, szTitle, 
                                    IOBUF_SPLIT_CONSOLE, m_hwnd);
    DeleteFile(tmpfname);
    if (!state) {
        SetFocus(hwnd);
    }
    return 0;
}

LRESULT CALLBACK DocWin::IdmEvalWithArgv(
    HWND hwnd,
    WPARAM wParam,
    LPARAM lParam
    ) {
    ARGVDLG argvdlg(theRubyWin.GetArgvInfo());
    CHARFORMAT & cfm = theRubyWin.CharFormat();
    if (cfm.cbSize) {
        argvdlg.SetFont(cfm.bCharSet, cfm.szFaceName);
    }
    if (argvdlg.Open(hwnd, theRubyWin.hInstance()) == IDOK) {
        char szTitle[MAX_PATH];
        GetWindowText(hwnd, szTitle, MAX_PATH);

        char tmpfname[MAX_PATH];
        CreateTempFileName(tmpfname);

        WriteFile(hwnd, tmpfname, m_filecode);
        int state = theRubyWin.run_file_with_argv(tmpfname, szTitle, 
                                                  argvdlg.Argv(), 
                                                  IOBUF_SPLIT_CONSOLE,
                                                  m_hwnd);
        DeleteFile(tmpfname);
        if (!state) {
            SetFocus(hwnd);
        }
    }
    return 0;
}

LRESULT CALLBACK DocWin::IdmEvalSelect(
    HWND hwnd,
    WPARAM wParam,
    LPARAM lParam
    ) {

    char szTitle[MAX_PATH];
    GetWindowText(hwnd, szTitle, MAX_PATH);

    char tmpfname[MAX_PATH];
    CreateTempFileName(tmpfname);

    WriteSelectionFile(hwnd, tmpfname);
    int state = theRubyWin.run_file(tmpfname, szTitle, 
                                    IOBUF_SPLIT_CONSOLE, m_hwnd);
    DeleteFile(tmpfname);
    if (!state) {
        SetFocus(hwnd);
    }
    return 0;
}

LRESULT CALLBACK DocWin::IdmCheckSyntax(
    HWND hwnd,
    WPARAM wParam,
    LPARAM lParam
    ) {
    char szTitle[MAX_PATH + 1];
    GetWindowText(hwnd, szTitle, MAX_PATH);
    char tmpfile[MAX_PATH + 1];
    CreateTempFileName(tmpfile);
    WriteFile(hwnd, tmpfile, m_filecode);
    int state = theRubyWin.check_syntax(tmpfile, szTitle,
                                        IOBUF_SPLIT_CONSOLE, m_hwnd);
    DeleteFile(tmpfile);
    if (!state) {
        SetFocus(hwnd);
    }
    return 0;
}

LRESULT CALLBACK DocWin::IdmSplitConsole(
    HWND hwnd,
    WPARAM wParam,
    LPARAM lParam
    ) {
    if(m_pConsole) {
        m_pConsole->ToggleShow();
    } else {
        CreateSplitConsole(SW_SHOW);
    }
    ResizeChildWindows();
    return 0;
}

LRESULT CALLBACK DocWin::CmdSaved(
    HWND hwnd,
    WPARAM wParam,
    LPARAM lParam
    ) {
    return IsDocSaved(hwnd, wParam, lParam);
}

LRESULT CALLBACK DocWin::CmdConsoleGets(
    HWND hwnd,
    WPARAM wParam,
    LPARAM lParam
    ) {
    return m_pEdit->ReadInputLine();
}

LRESULT CALLBACK DocWin::CmdSplitConsoleGets(
    HWND hwnd,
    WPARAM wParam,
    LPARAM lParam
    ) {
    CreateSplitConsole(SW_SHOW);
    return m_pConsole->ReadInputLine();
}

LRESULT CALLBACK DocWin::CmdSetCharFormat(
    HWND hwnd,
    WPARAM wParam,
    LPARAM lParam
    ){
    CHARFORMAT *pfm = reinterpret_cast<CHARFORMAT*>(lParam);
    m_pEdit->SetCharFormat(pfm);
    if(m_pConsole) {
        m_pConsole->SetCharFormat(pfm);
    }
    return 0;
}

LRESULT CALLBACK DocWin::CmdSetBackColor(
    HWND hwnd,
    WPARAM wParam,
    LPARAM lParam
    ) {
    COLORREF *pColor = reinterpret_cast<COLORREF*>(lParam);
    m_pEdit->SetStyleSetBack(*pColor);
    if(m_pConsole) {
        m_pConsole->SetStyleSetBack(*pColor);
    }
    return 0;
}

LRESULT CALLBACK DocWin::CmdSetViewLine(
    HWND hwnd,
    WPARAM wParam,
    LPARAM lParam
    ) {
    m_pEdit->DisplayLineNumber(lParam);
    if(m_pConsole) {
        m_pConsole->DisplayLineNumber(lParam);
    }

    return 0;
}

void DocWin::ConsoleWrite(
    REDIT *pREdit,
    LPARAM lParam
    ) {
    UString u;
    char * p = reinterpret_cast<char *>(lParam);
    int len = strlen(p);
    if (convert_to_utf8(p, len, &u) > 0) {
        pREdit->ConsoleWrite(u.len, (char *)u.str);
        UStr_free(&u);
    }
    else {
        pREdit->ConsoleWrite(len, p);
    }
}

LRESULT CALLBACK DocWin::CmdConsoleWrite(
    HWND hwnd,
    WPARAM wParam,
    LPARAM lParam
    ) {
    ConsoleWrite(m_pEdit, lParam);
    return 0;
}

LRESULT CALLBACK DocWin::CmdSplitConsoleWrite(
    HWND hwnd,
    WPARAM wParam,
    LPARAM lParam
    ) {
    CreateSplitConsole(SW_SHOW);
    ConsoleWrite(m_pConsole, lParam);
    return 0;
}

BOOL DocWin::IsDocSaved(
    HWND hwnd,
    WPARAM wParam,
    LPARAM lParam
    ) {
    if(m_pEdit->IsModified()) {
        char msg[MAX_PATH + 100];
        char fullpath[MAX_PATH]; fullpath[0] = '\0';
        GetWindowText(hwnd, fullpath, MAX_PATH);
        strcpy(msg, "Save changes to ");
        strcat(msg, fullpath);
        strcat(msg, " ?");
        int answer = MessageBox(hwnd, msg, "RubyWin", MB_YESNOCANCEL);
        switch(answer) {
        case IDYES:
            return SaveDoc(hwnd);
        case IDNO:
            return TRUE;
        case IDCANCEL:
            return FALSE;
        }
    }
    return TRUE;
}

BOOL DocWin::SaveDoc(
    HWND hwnd
    ) {
    if(m_fullpath[0] == '\0') {
        return SaveAsDoc(hwnd);
    } else {
        if (WriteFile(hwnd, m_fullpath, m_filecode)) {
            m_pEdit->SetSavePoint();
        }
    }
    return TRUE;
}

BOOL DocWin::SaveAsDoc(
    HWND hwnd
    ) {
    char fullpath[MAX_PATH];
    memset(&fullpath, 0, MAX_PATH);
    strcpy(fullpath, m_fullpath);
    if (ShowSaveFileDlg(hwnd, fullpath)) {
        if (WriteFile(hwnd, fullpath, m_filecode)) {
            char szText[MAX_PATH];
            GetWindowText(hwnd, szText, MAX_PATH);
            if(strcmp(szText, CONSOLE) != 0 && strcmp(szText, IRB) != 0) {
                SetWindowText(hwnd, fullpath);
                strcpy(m_fullpath, fullpath);
            }
            m_pEdit->SetSavePoint();
            return TRUE;
        }
    }
    return FALSE;
}

BOOL DocWin::WriteFile(
    HWND hwnd,
    const char *fullpath,
    unsigned char jcode
    ) {
    FILE *fp = fopen(fullpath, "wb");
    if(!fp) {
        MessageBox(hwnd, "Fail to open file!!!", "RubyWin", MB_OK | MB_ICONERROR);
        return FALSE;
    }
    int nlen = m_pEdit->GetLength();
    char *pdata = new char[nlen + 1];
    TEXTRANGE tr;
    if(pdata) {
        tr.chrg.cpMin = 0;
        tr.chrg.cpMax = nlen;
        tr.lpstrText = pdata;
        m_pEdit->GetTextRange(&tr);
        pdata[nlen] = '\0';
        UString u;
        if(utf8_convert_to(pdata, jcode, &u) > 0) {
            fwrite(u.str, u.len, 1, fp);
            UStr_free(&u);
        }
        else {
            fwrite(pdata, nlen, 1, fp);
        }
        delete [] pdata;
    }
    else {
        char data[blockSize + 1];
        for (int i = 0; i < nlen; i += blockSize) {
            int writeSize = nlen - i;
            if (writeSize > blockSize) {
                writeSize = blockSize;
            }
            tr.chrg.cpMin = i;
            tr.chrg.cpMax = writeSize + i;
            tr.lpstrText = data;
            m_pEdit->GetTextRange(&tr);
            fwrite(data, writeSize, 1, fp);
        }
    }
    fclose(fp);
    return TRUE;
}

void DocWin::WriteSelectionFile(
    HWND hwnd,
    const char *fname
    ) {
    CHARRANGE cr;
    m_pEdit->GetSel(&cr);
    int len = cr.cpMax - cr.cpMin + 1;
    char * p = new char[len + 1];
    m_pEdit->GetSelText(p);
    int l = m_pEdit->LineFromChar(cr.cpMin);
    string msg;
    for(int i = 0; i < l; i++) {
        msg += "\r\n";
    }
    msg += p;
    FILE *fp = fopen(fname, "wb");
    if(!fp) {
        MessageBox(hwnd, "Fail to open file!!!", "RubyWin", MB_OK | MB_ICONERROR);
        return;
    }
    fwrite(msg.c_str(), msg.length(), 1, fp);
    fclose(fp);
}

void DocWin::ReadFile(
    HWND hwnd,
    const char *file
    ) {
    int size = get_file_size(file);
    FILE *fp = fopen(file, "rb");
    int eol_code = UNKNOWN_EOL;
    if (fp) {
        char *pbuf = new char[size + 1];
        int len = 0;
	if(pbuf) {
            len = fread(pbuf, 1, size + 1, fp);
	    pbuf[len] = '\0';
	    if((eol_code = get_eol_code(pbuf)) != UNKNOWN_EOL) {
	        m_pEdit->SetEOL(eol_code);
	    }
            set_filecode(pbuf, len);
            UString u;
            if (convert_to_utf8(pbuf, len, &u) > 0) {
                m_pEdit->AddText(u.len, (char *)u.str);
                UStr_free(&u);
            }
            else {
                m_pEdit->AddText(len, pbuf);
            }
	    delete [] pbuf;
	}
	else{
            char buf[blockSize];
            len = fread(buf, 1, sizeof(buf), fp);
            while(len > 0){
	        get_eol_code(buf);
		if (eol_code != UNKNOWN_EOL) {
	            if((eol_code = get_eol_code(buf)) != UNKNOWN_EOL) {
	                m_pEdit->SetEOL(eol_code);
	            }
		}
                m_pEdit->AddText(len, buf);
                len = fread(buf, 1, sizeof(buf), fp);
            }
	}
        fclose(fp);
        m_pEdit->SetSavePoint();
        m_pEdit->EmptyUndoBuffer();
        m_pEdit->GotoPos(0);
    }
}

DWORD CALLBACK DocWin::ReadProc(
    DWORD dwCookie,
    LPBYTE pbBuf,
    LONG cb,
    LONG *pcb
    ) {
    ::ReadFile((HANDLE)dwCookie, pbBuf, cb, (LPDWORD)pcb, NULL);
    return 0;
}

BOOL DocWin::ShowSaveFileDlg(
    HWND hwnd,
    char *pfullpath
    ) {
    char fname[MAX_PATH];
    fname[0] = '\0';
    if(pfullpath[0] != '\0') {
        char *p = strrchr(pfullpath, '\\');
        if(p) {
            p++;
            strcpy(fname, p);
        }
        else strcpy(fname, pfullpath);
    }
    return ::ShowSaveFileDlg(hwnd, "Save As", pfullpath, fname);
}

BOOL DocWin::FindStr(
    const char* str,
    UINT search_flg,
    int nDirection
    ) {
    FINDTEXTEX ft;
    CHARRANGE cr;
    m_pEdit->GetSel(&cr);
    ft.chrg.cpMin = cr.cpMax;
    ft.chrg.cpMax = m_pEdit->GetLength();
    ft.lpstrText = const_cast<char *>(str);
    int npos = -1;
    if ((npos = m_pEdit->FindText(search_flg, &ft)) == -1) {
        ft.chrg.cpMin = 0;
        ft.chrg.cpMax = cr.cpMin;
        npos = m_pEdit->FindText(search_flg, &ft);
    }
    if (npos > -1) {
        m_pEdit->SetSel(&ft.chrgText);
        m_pEdit->ScrollCaret();
        return TRUE;
    }
    MessageBeep(MB_OK);
    return FALSE;
}

void DocWin::ReplStr(
    const char *str
    ) {
    CHARRANGE cr;
    m_pEdit->GetSel(&cr);
    m_pEdit->ReplaceSel(str);
    cr.cpMax = cr.cpMin + strlen(str);
    m_pEdit->SetSel(&cr);
}

void DocWin::set_filecode(
    const char *str,
    int len
    ) {
    if (theRubyWin.get_auto_judge_jcode()) {
        int ubig = 0;
        m_filecode = judge_jcode(&m_filecode, &ubig,
                                 (const unsigned char*)str, len);
    }
}

int DocWin::convert_to_utf8(
    const char *str,
    int len,
    UString * u
    ) {
    if (!theRubyWin.get_auto_judge_jcode()) {
        return 0;
    }

    unsigned char code = theRubyWin.get_def_fileio_code();
    int ubig = 0;
    code = judge_jcode(&code, &ubig, (const unsigned char*)str, len);
    switch(code) {
    case JP_SJIS:
        return sjistou8((const unsigned char*)str, u);
    case JP_EUC:
        return euctou8((const unsigned char*)str, u);
    case JP_JIS:
        return jistou8((const unsigned char*)str, u);
    default:
        return 0;
    }
    return 0;
}

int DocWin::utf8_convert_to(
    const char* u,
    unsigned char jcode,
    UString *out
    ) {
    if (jcode == JP_UTF8) {
        return 0;
    }
    switch(jcode) {
    case JP_SJIS:
        return u8tosjis((const unsigned char*)u, out);
    case JP_EUC:
        return u8toeuc((const unsigned char*)u, out);
    case JP_JIS:
        return u8tojis((const unsigned char*)u, out);
    default:
        return 0;
    }
    return 0;
}

int DocWin::get_eol_code(
    const char *str
    ) {
    char *p = strchr(str, '\r');
    if (p) {
         p++;
         if (*p == '\n') {
            return SC_EOL_CRLF;
	 } else {
	    return SC_EOL_CR;
	 }
    } else {
       p = strchr(str, '\n');
       if (p) {
	    return SC_EOL_LF;
       }
    }
    return UNKNOWN_EOL;
}
