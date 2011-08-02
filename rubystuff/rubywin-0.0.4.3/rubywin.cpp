/*----------------------------------------
  rubywin.cpp
  $Date: 2001/08/18 07:09:24 $
  $Revision: 1.7 $
  Copyright (C) 2000 - 2001 Masaki Suketa
------------------------------------------*/
#include <windows.h>
#include <richedit.h>
#include <commctrl.h>
#include <string>
#include <algorithm>
#include <sstream>
#include <Scintilla.h>
#include <ruby.h>
#include <node.h>
#include "judge_jcode.h"
#include "resource.h"
#include "docwin.h"
#include "rubywin.h"
#include "versiondlg.h"
#include "filedlg.h"
#include "textcolordlg.h"
#include "rwcommon.h"
#include "property.h"
#include "dismscwarn.h"

using namespace std;

char *szClassName = "RubyWin";

WNDPROC OrgClientWndProc;

static LRESULT CALLBACK ClientWndHookProc(
    HWND hwnd,
    UINT msg,
    WPARAM wParam,
    LPARAM lParam
    ) {
    extern RubyWin theRubyWin;
    switch(msg) {
    case WM_DROPFILES:
        theRubyWin.OpenDropFiles(reinterpret_cast<HDROP>(wParam));
        return 0;
    }
    return CallWindowProc(OrgClientWndProc, hwnd, msg, wParam, lParam);
}

RubyWin::RubyWin() {
    m_doc_id = 0;
    m_status = RUN_NOTHING;
    m_iobuf = IOBUF_CONSOLE;
    m_running_doc_hwnd = NULL;
    m_auto_judge_jcode = FALSE;
    m_def_fileio_code = JP_UTF8;
    m_max_recent_files = MAX_RECENT_FILES;
    memset(&m_cfm, 0, sizeof(CHARFORMAT));
}

BOOL RubyWin::InitInstance(
    HINSTANCE hInstance
    ) {
    m_hInstance = hInstance;
    BOOL ret = Register(hInstance, szClassName,
                        reinterpret_cast<HBRUSH>(COLOR_APPWORKSPACE + 1));
    if (!ret) return ret;
    ret = DocWin::InitInstance(hInstance);
    LoadMenus();
    m_hAccel = LoadAccelerators(hInstance, "RUBYWINACCEL");
    return ret;
}

int RubyWin::Run(
    const char *szCmdLine,
    int nCmdShow
    ) {
    m_pcmdline = szCmdLine;
    m_Ruby.init();
    CreateWnd();
    ShowWindow(m_hwnd, nCmdShow);
    UpdateWindow(m_hwnd);
    return MessageLoop();
}

void RubyWin::DrawMenu(
    BOOL isActivate
    ) {
    if (isActivate) {
        SendMessage(m_hClient, WM_MDISETMENU,
                    reinterpret_cast<WPARAM>(m_hMenuDoc), 
                    reinterpret_cast<LPARAM>(m_hMenuDocWnd));
    }
    else {
        SendMessage(m_hClient, WM_MDISETMENU,
                    reinterpret_cast<WPARAM>(m_hMenu), 
                    reinterpret_cast<LPARAM>(m_hMenuWnd));
    }

    DrawMenuBar(m_hwnd);
}

void RubyWin::TagJump(
    const char * fname,
    int line
    ) {
    HWND hwnd = NULL;
    if (IsOpenedMDIChild(fname)) {
        hwnd = reinterpret_cast<HWND>(SendMessage(m_hClient, WM_MDIGETACTIVE, 0, 0));
    }
    else {
        hwnd = Open(fname);
    }
    DocWin * pDoc = reinterpret_cast<DocWin *>(GetWindowLong(hwnd, 0));
    pDoc->GotoLine(hwnd, line);
}

void RubyWin::OpenDropFiles(
    HDROP hDrop
    ) {
    UINT nFiles = DragQueryFile(hDrop, 0xFFFFFFFF, NULL, 0);
    char szFileName[MAX_PATH];
    for (UINT i = 0; i < nFiles; i++) {
        DragQueryFile(hDrop, i, szFileName, sizeof(szFileName));
        Open(szFileName);
    }
    DragFinish(hDrop);
}

void RubyWin::UpdateRecentFiles(
    const char *file
    ) {
    DeleteMenuRecentFiles();
    string v = file;
    m_recent_files.erase(remove(m_recent_files.begin(), m_recent_files.end(), v), m_recent_files.end());
    if (m_recent_files.size() >= m_max_recent_files) {
        m_recent_files.pop_back();
    }
    m_recent_files.push_front(v);
    InsertMenuRecentFiles();
}

void RubyWin::DeleteMenuRecentFiles() {
    HMENU hMenu = GetSubMenu(m_hMenu, 0);
    HMENU hMenuDoc = GetSubMenu(m_hMenuDoc, 0);
    for(unsigned int i = 0; i < m_recent_files.size(); i++) {
        DeleteMenu(hMenu, POS_SEP_RWMENU_EXIT, MF_BYPOSITION);
        DeleteMenu(hMenuDoc, POS_SEP_DOCMENU_EXIT, MF_BYPOSITION);
        DrawMenuBar(m_hwnd);
    }
    if (m_recent_files.size() > 0) {
        DeleteMenu(hMenu, POS_SEP_RWMENU_EXIT, MF_BYPOSITION);
        DeleteMenu(hMenuDoc, POS_SEP_DOCMENU_EXIT, MF_BYPOSITION);
        DrawMenuBar(m_hwnd);
    }
}

void RubyWin::InsertMenuRecentFiles() {
    MENUITEMINFO mii;
    memset(&mii, 0, sizeof(MENUITEMINFO));
    mii.cbSize = sizeof(MENUITEMINFO);
    mii.fMask = MIIM_TYPE | MIIM_ID; 
    mii.fType = MFT_STRING;
    HMENU hMenu = GetSubMenu(m_hMenu, 0);
    HMENU hMenuDoc = GetSubMenu(m_hMenuDoc, 0);
    int j = 0;

    deque<string>::iterator i = m_recent_files.begin();
    for(j = 0; i != m_recent_files.end(); i++, j++) {
        mii.wID = IDM_OPEN_RECENT_FILE + j;
        mii.dwTypeData = const_cast<char *>(i->c_str());
	mii.cch = i->size();
        InsertMenuItem(hMenu, POS_SEP_RWMENU_EXIT + j, TRUE, &mii);
        InsertMenuItem(hMenuDoc, POS_SEP_DOCMENU_EXIT + j, TRUE, &mii);
    }
    if (m_recent_files.size() > 0) {
        mii.fType = MFT_SEPARATOR;
        InsertMenuItem(hMenu, POS_SEP_RWMENU_EXIT + j, TRUE, &mii);
        InsertMenuItem(hMenuDoc, POS_SEP_DOCMENU_EXIT + j, TRUE, &mii);
    }
}

LRESULT CALLBACK RubyWin::WndProc(
    UINT msg,
    WPARAM wParam,
    LPARAM lParam
    ) {
    switch(msg) {
    case WM_CREATE:
        return WmCreate(wParam, lParam);
    case WM_CLOSE:
        return WmClose(wParam, lParam);
    case WM_DESTROY:
        return WmDestroy(wParam, lParam);
    case WM_INITMENUPOPUP:
        return WmInitMenuPopup(wParam, lParam);
    case WM_DROPFILES:
        return WmDropFiles(wParam, lParam);
    case WM_SIZE:
        return WmSize(wParam, lParam);
    case WM_ACTIVATE:
        return WmActivate(wParam, lParam);
    case WM_COMMAND:
        return WmCommand(wParam, lParam);
    default:
        return DefFrameProc(m_hwnd, m_hClient, msg, wParam, lParam);
    }
    return 0;
}

int RubyWin::MessageLoop() {
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        if (!TranslateMDISysAccel(m_hClient, &msg) &&
            !TranslateAccelerator(m_hwnd, m_hAccel, &msg)) {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }
    return msg.wParam;
}

void RubyWin::CreateWnd() {
    LoadLib();
    CreateWindow(szClassName,
                 szClassName,
                 WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN,
                 CW_USEDEFAULT,
                 CW_USEDEFAULT,
                 CW_USEDEFAULT,
                 CW_USEDEFAULT,
                 NULL,
                 m_hMenu,
                 m_hInstance,
                 reinterpret_cast<LPSTR>(this));
}

void RubyWin::LoadMenus() {
    m_hMenu = LoadMenu(m_hInstance, "RUBYWINMENU");
    m_hMenuWnd = GetSubMenu(m_hMenu, 0);
    m_hMenuDoc = LoadMenu(m_hInstance, "RUBYWINDOCMENU");
    m_hMenuDocWnd = GetSubMenu(m_hMenuDoc, INDEX_IDM_WINDOW);
}

LRESULT CALLBACK RubyWin::WmCreate(
    WPARAM wParam,
    LPARAM lParam
    ) {
    CLIENTCREATESTRUCT ccs;
    ccs.hWindowMenu = m_hMenuWnd;
    ccs.idFirstChild = IDM_FIRSTCHILD;
    m_hClient = CreateWindow(
        "MDICLIENT",
        NULL,
        WS_CHILD | WS_VISIBLE | WS_CLIPCHILDREN,
        0, 0, 0, 0,
        m_hwnd,
        (HMENU)1,
        m_hInstance,
        (LPSTR)&ccs);
    InitCommonControls();
    CreateToolbar();
    LoadInitFile();
    OrgClientWndProc = (WNDPROC)GetWindowLong(m_hClient, GWL_WNDPROC);
    SetWindowLong(m_hClient, GWL_WNDPROC, (LONG)&ClientWndHookProc);
    DragAcceptFiles(m_hwnd, TRUE);
    DragAcceptFiles(m_hClient, TRUE);
InsertMenuRecentFiles();
    return 0;
}

LRESULT CALLBACK RubyWin::WmClose(
    WPARAM wParam,
    LPARAM lParam
    ) {
    BOOL isAllSaved = TRUE;
    EnumChildWindows(m_hClient, &RubyWin::DocSavedProc, (LPARAM)(&isAllSaved));
    if (isAllSaved) {
        EnumChildWindows(m_hClient, &RubyWin::CloseProc, 0);
    }
    if (GetWindow(m_hClient, GW_CHILD)) {
        return 0;
    }
    return DefFrameProc(m_hwnd, m_hClient, WM_CLOSE, wParam, lParam);
}

LRESULT CALLBACK RubyWin::WmDestroy(
    WPARAM,
    LPARAM
    ) {
    FreeLib();
    StoreInitFile();
    PostQuitMessage(0);
    return 0;
}

LRESULT CALLBACK RubyWin::WmInitMenuPopup(
    WPARAM wParam,
    LPARAM lParam
    ) {
    HWND hwnd = (HWND)SendMessage(m_hClient, WM_MDIGETACTIVE, 0, 0);
    if (IsWindow(hwnd)) {
        SendMessage(hwnd, WM_INITMENUPOPUP, wParam, lParam);
    }
    HMENU hMenu = (HMENU)wParam;
    if (m_status == RUN_RUBY) {
        EnableMenuItem(hMenu, IDM_EVAL_BUFFER, MF_GRAYED | MF_BYCOMMAND);
        EnableMenuItem(hMenu, IDM_EVAL_SELECT, MF_GRAYED | MF_BYCOMMAND);
        EnableMenuItem(hMenu, IDM_EVAL_WITH_ARGV, MF_GRAYED | MF_BYCOMMAND);
        EnableMenuItem(hMenu, IDM_CHECK_SYNTAX, MF_GRAYED | MF_BYCOMMAND);
        EnableMenuItem(hMenu, IDM_IRB, MF_GRAYED | MF_BYCOMMAND);
        EnableMenuItem(hMenu, IDM_RUN_FILE, MF_GRAYED | MF_BYCOMMAND);
    }
    else {
        EnableMenuItem(hMenu, IDM_IRB, MF_ENABLED | MF_BYCOMMAND);
        EnableMenuItem(hMenu, IDM_RUN_FILE, MF_ENABLED | MF_BYCOMMAND);
    }
    return 0;
}

LRESULT CALLBACK RubyWin::WmDropFiles(
    WPARAM wParam,
    LPARAM lParam
    ) {
    OpenDropFiles(reinterpret_cast<HDROP>(wParam));
    return 0;
}

LRESULT CALLBACK RubyWin::WmSize(
    WPARAM wParam,
    LPARAM lParam
    ) {
    RECT ClRect, TbRect;
    SendMessage(m_hToolbar, TB_AUTOSIZE, 0, 0);
    GetClientRect(m_hwnd, &ClRect);
    GetWindowRect(m_hToolbar, &TbRect);
    UINT uTop = TbRect.bottom - TbRect.top;
    UINT uBottom = ClRect.bottom - uTop;
    MoveWindow(m_hClient, 0, uTop, ClRect.right, uBottom, TRUE);
    OpenFileSpecifiedByCmdLine();
    if (m_doc_id == 0) {
        CreateDocWin();
    }
    return 0;
}

LRESULT CALLBACK RubyWin::WmActivate(
    WPARAM wParam,
    LPARAM lParam
    ) {
    HWND hwnd = (HWND)SendMessage(m_hClient, WM_MDIGETACTIVE, 0, 0);
    if (hwnd) {
        SetFocus(GetWindow(hwnd, GW_CHILD));
    }
    return 0;
}

LRESULT CALLBACK RubyWin::WmCommand(
    WPARAM wParam,
    LPARAM lParam
    ) {
if (IDM_OPEN_RECENT_FILE <= LOWORD(wParam) && LOWORD(wParam) < IDM_UNDO) {
return IdmOpenRecentFile(wParam, lParam);
}
    switch(LOWORD(wParam)) {
    case IDM_NEW:
        return IdmNew(wParam, lParam);
    case IDM_OPEN:
        return IdmOpen(wParam, lParam);
    case IDM_CLOSE:
        return IdmClose(wParam, lParam);
    case IDM_EXIT:
        return IdmExit(wParam, lParam);
    case IDM_CONSOLE:
        return IdmConsole(wParam, lParam);
    case IDM_TILE_HORI:
        return IdmTileHori(wParam, lParam);
    case IDM_TILE_VERT:
        return IdmTileVert(wParam, lParam);
    case IDM_RUN_FILE:
        return IdmRunFile(wParam, lParam);
    case IDM_IRB:
        return IdmIRB(wParam, lParam);
    case IDM_FONT:
        return IdmFont(wParam, lParam);
    case IDM_SET_TEXT_COLOR:
        return IdmSetTextColor(wParam, lParam);
    case IDM_SET_BACK_COLOR:
        return IdmSetBackColor(wParam, lParam);
    case IDM_VIEW_LINE:
        return IdmViewLine(wParam, lParam);
    case IDM_CASCADE:
        return IdmCascade(wParam, lParam);
    case IDM_ARRANGE:
        return IdmArrange(wParam, lParam);
    case IDM_VERSION:
        return IdmVersion(wParam, lParam);
    default:
        return DefaultCommand(wParam, lParam);
    }
    return 1;
}

LRESULT CALLBACK RubyWin::IdmNew(
    WPARAM wParam,
    LPARAM lParam
    ) {
    CreateDocWin();
    return 0;
}

LRESULT CALLBACK RubyWin::IdmOpen(
    WPARAM wParam,
    LPARAM lParam
    ) {
    char fullpath[MAX_PATH];
    memset(&fullpath, 0, sizeof(fullpath));
    char fname[MAX_PATH];
    memset(&fname, 0, sizeof(fname));
    if (ShowOpenFileDlg(m_hwnd, "Open File", fullpath, fname)) {
        Open(fullpath);
    }
    return 0;
}

LRESULT CALLBACK RubyWin::IdmClose(
    WPARAM wParam,
    LPARAM lParam
    ) {
    HWND hwnd = (HWND)SendMessage(m_hClient, WM_MDIGETACTIVE, 0, 0);
    if (hwnd) {
        if (SendMessage(hwnd, WM_COMMAND, CMD_SAVED, 0)) {
            CloseProc(hwnd, 0);
        }
    }
    return 0;
}

LRESULT CALLBACK RubyWin::IdmExit(
    WPARAM wParam,
    LPARAM lParam
    ) {
    SendMessage(m_hwnd, WM_CLOSE, wParam, lParam);
    return 0;
}

LRESULT CALLBACK RubyWin::IdmRunFile(
    WPARAM wParam,
    LPARAM lParam
    ) {
    char fullpath[MAX_PATH]; fullpath[0] = '\0';
    char fname[MAX_PATH]; fname[0] = '\0';
    if (ShowOpenFileDlg(m_hwnd, "Run Ruby File", fullpath, fname)) {
        run_file(fullpath, fullpath, IOBUF_CONSOLE);
    }
    return 0;
}

LRESULT CALLBACK RubyWin::IdmIRB(
    WPARAM wParam,
    LPARAM lParam
    ) {
    char szPath[MAX_PATH];
    szPath[0] = '\0';
    GetRWLibFullPath(szPath, "rwirb.rb");
    if (!IsFileExist(szPath)) {
        char szMsg[MAX_PATH + 30];
        sprintf(szMsg, "File Not Found:\r\n%s", szPath);
        MessageBox(NULL, szMsg, "RubyWin", MB_OK | MB_ICONEXCLAMATION);
        return 0;
    }
    OpenMDIChild(IRB);
    run_file(szPath, szPath, IOBUF_IRB);
    return 0;
}

LRESULT CALLBACK RubyWin::IdmConsole(
    WPARAM wParam,
    LPARAM lParam
    ) {
    OpenMDIChild(CONSOLE);
    return 0;
}

LRESULT CALLBACK RubyWin::IdmFont(
    WPARAM wParam,
    LPARAM lParam
    ) {
    HWND hwnd = (HWND)SendMessage(m_hClient, WM_MDIGETACTIVE, 0, 0);
    HWND hREdit = GetWindow(hwnd, GW_CHILD);
    LOGFONT lf;
    memset(&lf, 0, sizeof(LOGFONT));
    CharFormat2LogFont(&m_edprop.cfm, &lf, hREdit);
    CHOOSEFONT cf;
    memset (&cf, 0, sizeof(CHOOSEFONT));
    if (m_edprop.cfm.cbSize) {
        cf.rgbColors = m_edprop.cfm.crTextColor;
    }
    cf.lStructSize = sizeof(CHOOSEFONT);
    cf.hwndOwner = hREdit;
    cf.lpLogFont = &lf;
    cf.Flags = CF_SCREENFONTS | CF_INITTOLOGFONTSTRUCT | CF_EFFECTS;
    if (ChooseFont(&cf)) {
        m_edprop.cfm.cbSize = sizeof(CHARFORMAT);
        m_edprop.cfm.yHeight = 2 * cf.iPointSize;
        m_edprop.cfm.crTextColor = cf.rgbColors;
        LogFont2CharFormat(&lf);
        EnumChildWindows(m_hClient, &RubyWin::SetFontProc, (LPARAM)(&m_edprop.cfm));
    }
    SetFocus(hREdit);
    return 0;
}

LRESULT CALLBACK RubyWin::IdmSetTextColor(
    WPARAM wParam,
    LPARAM lParam
    ) {
    TEXTCOLORDLG textcolordlg;
    if (textcolordlg.Open(m_hwnd, m_hInstance) == IDOK) {
        EnumChildWindows(m_hClient, &RubyWin::SetFontProc, (LPARAM)(&m_edprop.cfm));
    }
    return 0;
}

LRESULT CALLBACK RubyWin::IdmSetBackColor(
    WPARAM wParam,
    LPARAM lParam
    ) {
    HWND hwnd = (HWND)SendMessage(m_hClient, WM_MDIGETACTIVE, 0, 0);
    HWND hREdit = GetWindow(hwnd, GW_CHILD);

    CHOOSECOLOR cc;
    static DWORD dwCustColors[16];

    memset(&cc, 0, sizeof(CHOOSECOLOR));
    cc.lStructSize = sizeof(CHOOSECOLOR);
    cc.hwndOwner = hwnd;
    cc.lpCustColors = dwCustColors;
    cc.rgbResult = m_edprop.backColor;
    cc.Flags = CC_RGBINIT;
    if (ChooseColor(&cc)) {
        m_edprop.backColor = cc.rgbResult;
        EnumChildWindows(m_hClient, &RubyWin::SetBackColorProc, (LPARAM)(&m_edprop.backColor));
    }
    SetFocus(hREdit);
    return 0;
}

LRESULT CALLBACK RubyWin::IdmViewLine(
    WPARAM wParam,
    LPARAM lParam
    ) {
    HWND hwnd = (HWND)SendMessage(m_hClient, WM_MDIGETACTIVE, 0, 0);
    HWND hREdit = GetWindow(hwnd, GW_CHILD);
    m_edprop.isDisplayLineNumber = !m_edprop.isDisplayLineNumber;
    EnumChildWindows(m_hClient, &RubyWin::SetViewLineProc, (LPARAM)(m_edprop.isDisplayLineNumber));

    SetFocus(hREdit);
    return 0;
}

LRESULT CALLBACK RubyWin::IdmTileHori(
    WPARAM wParam,
    LPARAM lParam
    ) {
    SendMessage(m_hClient, WM_MDITILE, MDITILE_HORIZONTAL, 0);
    return 0;
}

LRESULT CALLBACK RubyWin::IdmTileVert(
    WPARAM wParam,
    LPARAM lParam
    ) {
    SendMessage(m_hClient, WM_MDITILE, MDITILE_VERTICAL, 0);
    return 0;
}

LRESULT CALLBACK RubyWin::IdmCascade(
    WPARAM wParam,
    LPARAM lParam
    ) {
    SendMessage(m_hClient, WM_MDICASCADE, 0, 0);
    return 0;
}

LRESULT CALLBACK RubyWin::IdmArrange(
    WPARAM wParam,
    LPARAM lParam
    ) {
    SendMessage(m_hClient, WM_MDIICONARRANGE, 0, 0);
    return 0;
}

LRESULT CALLBACK RubyWin::IdmVersion(
    WPARAM wParam,
    LPARAM lParam
    ) {
    VersionDLG dlg;
    dlg.SetVersionInfo(m_Ruby.version_string());
    dlg.Open(m_hwnd, m_hInstance);
    return 0;
}

LRESULT CALLBACK RubyWin::IdmOpenRecentFile(
    WPARAM wParam,
    LPARAM lParam
    ) {
    int id = LOWORD(wParam) - IDM_OPEN_RECENT_FILE;
    Open(m_recent_files[id].c_str());
    return 0;
}

LRESULT CALLBACK RubyWin::DefaultCommand(
    WPARAM wParam,
    LPARAM lParam
    ) {
    HWND hChild = (HWND)SendMessage(m_hClient, WM_MDIGETACTIVE, 0, 0);
    if(IsWindow(hChild)) {
        SendMessage(hChild, WM_COMMAND, wParam, lParam);
    }
    return DefFrameProc(m_hwnd, m_hClient, WM_COMMAND, wParam, lParam);
}

DocWin * RubyWin::CreateDocWin() {
    m_doc_id++;
    DocWin *pDocWin = new DocWin(m_def_fileio_code);
    if (pDocWin) {
        pDocWin->Create(m_hInstance, m_hClient, m_doc_id);
    }
    return pDocWin;
}

void RubyWin::CreateToolbar() {
    const int tbsize = 12;
    TBBUTTON tb[tbsize];
    for (int i = 0; i < tbsize; i++) {
        tb[i].fsStyle = TBSTYLE_BUTTON;
        tb[i].fsState = TBSTATE_ENABLED;
        tb[i].dwData = 0;
        tb[i].iString = 0;
    }

    tb[0].iBitmap = STD_FILENEW;
    tb[0].idCommand = IDM_NEW;

    tb[1].iBitmap = STD_FILEOPEN;
    tb[1].idCommand = IDM_OPEN;

    tb[2].iBitmap = STD_FILESAVE;
    tb[2].idCommand = IDM_SAVE;

    tb[3].fsStyle = TBSTYLE_SEP;
    tb[3].iBitmap = 0;
    tb[3].idCommand = 0;
    
    tb[4].iBitmap = STD_UNDO;
    tb[4].idCommand = IDM_UNDO;

    tb[5].iBitmap = STD_REDOW;
    tb[5].idCommand = IDM_REDO;

    tb[6].iBitmap = STD_CUT;
    tb[6].idCommand = IDM_CUT;

    tb[7].iBitmap = STD_COPY;
    tb[7].idCommand = IDM_COPY;

    tb[8].iBitmap = STD_PASTE;
    tb[8].idCommand = IDM_PASTE;

    tb[9].fsStyle = TBSTYLE_SEP;
    tb[9].iBitmap = 0;
    tb[9].idCommand = 0;

    tb[10].iBitmap = STD_FIND;
    tb[10].idCommand = IDM_FIND;

    tb[11].iBitmap = STD_REPLACE;
    tb[11].idCommand = IDM_REPLACE;

    m_hToolbar = CreateToolbarEx(m_hwnd,
                                 WS_VISIBLE|WS_CHILD|TBSTYLE_BUTTON,
                                 ID_TOOLBAR,
                                 tbsize,
                                 HINST_COMMCTRL,
                                 IDB_STD_SMALL_COLOR,
                                 tb,
                                 tbsize,
                                 0,0,16,15,sizeof(TBBUTTON));

}

HWND RubyWin::Open(
    const char *fname
    ) {
    if (!IsOpened(fname)) {
        DocWin *pDocWin = CreateDocWin();
        HWND hwnd = (HWND)SendMessage(m_hClient, WM_MDIGETACTIVE, 0, 0);
        pDocWin->OpenFile(hwnd, fname);
    }
    return (HWND)SendMessage(m_hClient, WM_MDIGETACTIVE, 0, 0);
}

void RubyWin::OpenFileSpecifiedByCmdLine() {
    if (m_pcmdline && *m_pcmdline != '\0') {
        string s = m_pcmdline;
        string::size_type lpos = s.find_first_of(" ");
        string::size_type fpos = 0;
        string path, longpath;
        while (lpos != string::npos) {
            path = s.substr(fpos, lpos-fpos);
            longpath = getlongpath(path);
            Open(longpath.c_str());
            fpos = lpos + 1;
            lpos = s.find_first_of(" ", fpos);
        }
        path = s.substr(fpos);
        longpath = getlongpath(path);
        Open(longpath.c_str());
    }
}

HWND RubyWin::OpenMDIChild(
    const char * pTitle
    ) {
    if (!IsOpenedMDIChild(pTitle)) {
        DocWin * pDocWin = new DocWin(m_def_fileio_code);
        pDocWin->Create(m_hInstance, m_hClient, pTitle);
    }
    return (HWND)SendMessage(m_hClient, WM_MDIGETACTIVE, 0, 0);
}

BOOL RubyWin::IsOpened(
    const char *fullpath
    ) {
    LPOpenProc lp;
    lp.pname = fullpath;
    lp.IsOpened = FALSE;
    EnumChildWindows(m_hClient, &RubyWin::IsOpenProc, (LPARAM)(&lp));
    return lp.IsOpened;
}

BOOL RubyWin::IsOpenedMDIChild(
    const char *title
    ) {
    LPOpenProc lp;
    lp.pname = title;
    lp.IsOpened = FALSE;
    EnumChildWindows(m_hClient, &RubyWin::IsOpenMDIChiledProc, (LPARAM)(&lp));
    return lp.IsOpened;
}

BOOL CALLBACK RubyWin::CloseProc(
    HWND hWnd,
    LPARAM lParam
    ) {
    SendMessage(GetParent(hWnd), WM_MDIDESTROY, (WPARAM)hWnd, 0);
    return TRUE;
}

BOOL CALLBACK RubyWin::DocSavedProc(
    HWND hwnd,
    LPARAM lParam
    ) {
    BOOL *pIsAllSaved = reinterpret_cast<BOOL *>(lParam);
    if(SendMessage(hwnd, WM_COMMAND, CMD_UNSAVE, 0)) {
        *pIsAllSaved = FALSE;
        return FALSE;
    }
    return TRUE;
}

BOOL CALLBACK RubyWin::IsOpenProc(
    HWND hwnd,
    LPARAM lParam
    ) {
    LPOpenProc * plp = reinterpret_cast<LPOpenProc *>(lParam);
    DocWin * p = reinterpret_cast<DocWin *>(GetWindowLong(hwnd, 0));
    if (p != 0) {
        if (strcmp(p->FullPath(),plp->pname) == 0) {
            SendMessage(GetParent(hwnd), WM_MDIACTIVATE, (WPARAM)hwnd, 0);
            plp->IsOpened = TRUE;
            return FALSE;
        }
    }
    return TRUE;
}

BOOL CALLBACK RubyWin::IsOpenMDIChiledProc(
    HWND hwnd,
    LPARAM lParam
    ) {
    LPOpenProc * plp = reinterpret_cast<LPOpenProc *>(lParam);
    char szTitle[MAX_PATH];
    GetWindowText(hwnd, szTitle, MAX_PATH);
    if (strcmp(szTitle, plp->pname) == 0) {
        SendMessage(GetParent(hwnd), WM_MDIACTIVATE, (WPARAM)hwnd, 0);
        plp->IsOpened = TRUE;
        return FALSE;
    }
    return TRUE;
}

BOOL CALLBACK RubyWin::SetFontProc(
    HWND hwnd,
    LPARAM lParam
    ) {
    SendMessage(hwnd, WM_COMMAND, CMD_SETCHARFORMAT, lParam);
    return TRUE;
}

BOOL CALLBACK RubyWin::SetBackColorProc(
    HWND hwnd,
    LPARAM lParam
    ) {
    SendMessage(hwnd, WM_COMMAND, CMD_SETBACKCOLOR, lParam);
    return TRUE;
}

BOOL CALLBACK RubyWin::SetViewLineProc(
    HWND hwnd,
    LPARAM lParam
    ) {
    SendMessage(hwnd, WM_COMMAND, CMD_SETVIEWLINE, lParam);
    return TRUE;
}

void RubyWin::CharFormat2LogFont(
    CHARFORMAT *pfm,
    LOGFONT *plf,
    HWND hREdit
    ) {
    if (pfm->cbSize) {
        HDC hDC = GetDC(hREdit);
        plf->lfHeight = MulDiv(pfm->yHeight, GetDeviceCaps(hDC, LOGPIXELSY), -1440);
        ReleaseDC(hREdit, hDC);
        if (pfm->dwEffects & CFE_BOLD)
            plf->lfWeight = FW_BOLD;
        else
            plf->lfWeight = FW_NORMAL;
        if (pfm->dwEffects & CFE_ITALIC)
            plf->lfItalic = TRUE;
        if (pfm->dwEffects & CFE_UNDERLINE)
            plf->lfUnderline = TRUE;
        if (pfm->dwEffects & CFE_STRIKEOUT)
            plf->lfStrikeOut = TRUE;
        plf->lfCharSet = pfm->bCharSet;
        plf->lfQuality = DEFAULT_QUALITY;
        plf->lfPitchAndFamily = pfm->bPitchAndFamily;
        strcpy(plf->lfFaceName, pfm->szFaceName);
    }
    else {
        plf->lfWeight = FW_NORMAL;
        plf->lfQuality = DEFAULT_QUALITY;
    }
}

void RubyWin::LogFont2CharFormat(
    LOGFONT *plf
    ) {
    m_edprop.cfm.dwEffects = 0;
    if (plf->lfWeight >= FW_BOLD)
        m_edprop.cfm.dwEffects |= CFE_BOLD;
    if (plf->lfItalic)
        m_edprop.cfm.dwEffects |= CFE_ITALIC;
    if (plf->lfUnderline)
        m_edprop.cfm.dwEffects |= CFE_UNDERLINE;
    if (plf->lfStrikeOut)
        m_edprop.cfm.dwEffects |= CFE_STRIKEOUT;
    m_edprop.cfm.bPitchAndFamily = plf->lfPitchAndFamily;
    m_edprop.cfm.bCharSet = plf->lfCharSet;
    strcpy(m_edprop.cfm.szFaceName, plf->lfFaceName);
}

void RubyWin::LoadLib() {
    m_hSciLib = LoadLibrary("SciLexer.DLL");
}

void RubyWin::FreeLib() {
    FreeLibrary(m_hSciLib);
}

void RubyWin::LoadInitFile() {
    char path[MAX_PATH];
    GetModuleFileFolder(path);
    strcat(path, "\\rubywin.ini");
    PROPERTY prop;
    prop.load(path);
    m_edprop.load_property(prop);
    load_property(prop);
}

void RubyWin::load_property(
    PROPERTY & prop
    ) {
    string files;
    prop.get("RubyWin.recent_files", files);
#if 1
    istringstream istr(files);
    string file;
    while(getline(istr, file, '|')) {
        m_recent_files.push_back(file);
    }
#else
    string::size_type lpos = files.find_first_of('|');
    string::size_type fpos = 0;
    while (lpos != string::npos) {
        m_recent_files.push_back(files.substr(fpos, lpos-fpos));
        fpos = lpos + 1;
        lpos = files.find_first_of('|', fpos);
    }
#endif
    prop.get("RubyWin.max_recent_files", m_max_recent_files);
}

void RubyWin::StoreInitFile() {
    PROPERTY prop;
    m_edprop.store_property(prop);
    store_property(prop);
    char path[MAX_PATH];
    GetModuleFileFolder(path);
    strcat(path, "\\rubywin.ini");
    prop.store(path);
}

void RubyWin::store_property(
    PROPERTY & prop
    ) {
    string files = "";
    deque<string>::iterator i = m_recent_files.begin();
    for(; i != m_recent_files.end(); i++) {
        files += *i;
	files += '|';
    }
    prop.set("RubyWin.recent_files", files.c_str());
    prop.set("RubyWin.max_recent_files", m_max_recent_files);
}

void RubyWin::console_f_write(
    const char *p
    ) {
    HWND hwnd = NULL;
    LPARAM cmd_write = 0;
    switch(m_iobuf) {
    case IOBUF_CONSOLE:
        hwnd = OpenMDIChild(CONSOLE);
	cmd_write = CMD_CONSOLE_WRITE;
	break;
    case IOBUF_IRB:
    	hwnd = OpenMDIChild(IRB);
	cmd_write = CMD_CONSOLE_WRITE;
	break;
    case IOBUF_SPLIT_CONSOLE:
        hwnd = m_running_doc_hwnd;
	cmd_write = CMD_SPLIT_CONSOLE_WRITE;
	break;
    }
    SendMessage(hwnd, WM_COMMAND, cmd_write,
                reinterpret_cast<LPARAM>(p));
}

const char * RubyWin::console_f_gets() {
    HWND hwnd = NULL;
    LPARAM cmd_gets = 0;
    switch(m_iobuf) {
    case IOBUF_CONSOLE:
        hwnd = OpenMDIChild(CONSOLE);
        cmd_gets = CMD_CONSOLE_GETS;
        break;
    case IOBUF_IRB:
        hwnd = OpenMDIChild(IRB);
        cmd_gets = CMD_CONSOLE_GETS;
        break;
    case IOBUF_SPLIT_CONSOLE:
        hwnd = m_running_doc_hwnd;
	cmd_gets = CMD_SPLIT_CONSOLE_GETS;
	break;
    }
    return (const char *)SendMessage(hwnd, WM_COMMAND, cmd_gets, 0);
}

int RubyWin::run_file(
    const char *file,
    const char *fname,
    IOBUF iobuf,
    HWND running_doc_hwnd
    ) {
    m_iobuf = iobuf;
    m_running_doc_hwnd = running_doc_hwnd;
    m_status = RUN_RUBY;
    int state = m_Ruby.run_file(file, fname);
    m_status = RUN_NOTHING;
    return state;
}

int RubyWin::run_file_with_argv(
    const char *file,
    const char *fname,
    const char *argv,
    IOBUF iobuf,
    HWND running_doc_hwnd
    ) {
    m_iobuf = iobuf;
    m_running_doc_hwnd = running_doc_hwnd;
    m_status = RUN_RUBY;
    int state = m_Ruby.run_file_with_argv(file, fname, argv);
    m_status = RUN_NOTHING;
    return state;
}

int RubyWin::check_syntax(
    const char *file,
    const char *title,
    IOBUF iobuf,
    HWND running_doc_hwnd
    ) {
    m_status = RUN_RUBY;
    int state = m_Ruby.check_syntax(file, title);
    m_status = RUN_NOTHING;
    return state;
}

void RubyWin::set_def_fileio_code(
    const char * code
    ) {
    switch(code[0]) {
    case 'S':
    case 's':
        m_def_fileio_code = JP_SJIS;
        break;
    case 'J':
    case 'j':
        m_def_fileio_code = JP_JIS;
        break;
    case 'E':
    case 'e':
        m_def_fileio_code = JP_EUC;
        break;
    default:
    case 'N':
    case 'n':
    case 'A':
    case 'a':
    case 'U':
    case 'u':
        m_def_fileio_code = JP_UTF8;
        break;
    }
}
