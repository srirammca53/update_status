/*----------------------------------------
  rubywin.h
  $Date: 2001/08/18 07:09:24 $
  $Revision: 1.7 $
  Copyright (C) 2000 - 2001 Masaki Suketa
------------------------------------------*/
#ifndef RUBYWIN_H
#define RUBYWIN_H

#include <windows.h>
#include <richedit.h>
#include <deque>
#include "rwwinbase.h"
#include "rubyitpr.h"
#include "docwin.h"
#include "findinfo.h"
#include "cmbinfo.h"
#include "reditprop.h"
using namespace std;

enum STATUS {
    RUN_NOTHING = 0,
    RUN_RUBY
};

enum RUN_TYPE {
    RUN_TYPE_IRB = 0,
    RUN_TYPE_CONSOLE,
    RUN_TYPE_BUFFER
};

enum IOBUF {
    IOBUF_CONSOLE = 0,
    IOBUF_SPLIT_CONSOLE,
    IOBUF_IRB
};

const char * const CONSOLE = "Console";
const char * const IRB = "IRB";

const int INDEX_IDM_WINDOW = 5;
const int POS_SEP_RWMENU_EXIT = 3;
const int POS_SEP_DOCMENU_EXIT = 6;
const int MAX_RECENT_FILES = 10;

class RubyWin :public RWWinbase {
public:
    RubyWin();
    virtual ~RubyWin(){}
    BOOL InitInstance(HINSTANCE hInstance);
    int Run(const char *szCmdLine, int nCmdShow);
    void DrawMenu(BOOL isActivate);
    void TagJump(const char * fname, int line);
    void OpenDropFiles(HDROP hDrop);
    LRESULT CALLBACK WndProc(UINT msg, WPARAM wParam, LPARAM lParam);
    HINSTANCE hInstance() {return m_hInstance;}
    CHARFORMAT & CharFormat() {return m_edprop.cfm;}
    REDIT_PROPERTY & ReditProperty() {return m_edprop;}
    void UpdateRecentFiles(const char *file);

    int indent_size() {return m_edprop.indent_size;}
    bool is_clean_console() {return m_edprop.is_clean_console;}
    void console_f_write(const char* p);
    const char * console_f_gets();
    int run_file(const char* fname, const char *title, 
                 IOBUF iobuf, HWND hwnd = NULL);
    int run_file_with_argv(const char* fname, const char *title,
                           const char *argv, IOBUF iobuf, HWND hwnd = NULL);
    int check_syntax(const char *fname, const char *title,
                     IOBUF iobuf, HWND hwnd = NULL);
    FindInfo & GetFindInfo(){return m_findinfo;}
    CMBINFO & GetArgvInfo() {return m_argvinfo;}
    BOOL get_auto_judge_jcode() {return m_auto_judge_jcode;}
    void set_auto_judge_jcode(BOOL flg) {m_auto_judge_jcode = flg;}
    unsigned char get_def_fileio_code() {return m_def_fileio_code;}
    void set_def_fileio_code(const char *code);
private:
    int MessageLoop();
    void CreateWnd();
    void LoadMenus();

    LRESULT CALLBACK WmCreate(WPARAM wParam, LPARAM lParam);
    LRESULT CALLBACK WmClose(WPARAM wParam, LPARAM lParam);
    LRESULT CALLBACK WmDestroy(WPARAM wParam, LPARAM lParam);
    LRESULT CALLBACK WmInitMenuPopup(WPARAM wParam, LPARAM lParam);
    LRESULT CALLBACK WmDropFiles(WPARAM wParam, LPARAM lParam);
    LRESULT CALLBACK WmSize(WPARAM wParam, LPARAM lParam);
    LRESULT CALLBACK WmActivate(WPARAM wParam, LPARAM lParam);
    LRESULT CALLBACK WmCommand(WPARAM wParam, LPARAM lParam);

    LRESULT CALLBACK IdmNew(WPARAM wParam, LPARAM lParam);
    LRESULT CALLBACK IdmOpen(WPARAM wParam, LPARAM lParam);
    LRESULT CALLBACK IdmClose(WPARAM wParam, LPARAM lParam);
    LRESULT CALLBACK IdmExit(WPARAM wParam, LPARAM lParam);
    LRESULT CALLBACK IdmRunFile(WPARAM wParam, LPARAM lParam);
    LRESULT CALLBACK IdmConsole(WPARAM wParam, LPARAM lParam);
    LRESULT CALLBACK IdmIRB(WPARAM wParam, LPARAM lParam);
    LRESULT CALLBACK IdmFont(WPARAM wParam, LPARAM lParam);
    LRESULT CALLBACK IdmSetTextColor(WPARAM wParam, LPARAM lParam);
    LRESULT CALLBACK IdmSetBackColor(WPARAM wParam, LPARAM lParam);
    LRESULT CALLBACK IdmViewLine(WPARAM wParam, LPARAM lParam);
    LRESULT CALLBACK IdmTileVert(WPARAM wParam, LPARAM lParam);
    LRESULT CALLBACK IdmTileHori(WPARAM wParam, LPARAM lParam);
    LRESULT CALLBACK IdmCascade(WPARAM wParam, LPARAM lParam);
    LRESULT CALLBACK IdmArrange(WPARAM wParam, LPARAM lParam);
    LRESULT CALLBACK IdmVersion(WPARAM wParam, LPARAM lParam);

    LRESULT CALLBACK IdmOpenRecentFile(WPARAM wParam, LPARAM lParam);

    LRESULT CALLBACK DefaultCommand(WPARAM wParam, LPARAM lParam);

    DocWin *CreateDocWin();
    void CreateToolbar();
    HWND Open(const char *file);
    void OpenFileSpecifiedByCmdLine();
    HWND OpenMDIChild(const char *title);

    void DeleteMenuRecentFiles();
    void InsertMenuRecentFiles();

    BOOL IsOpened(const char* p);
    BOOL IsOpenedMDIChild(const char *title);
    static BOOL CALLBACK CloseProc(HWND hwnd, LPARAM lp);
    static BOOL CALLBACK DocSavedProc(HWND hwnd, LPARAM lParam);
    static BOOL CALLBACK IsOpenProc(HWND hwnd, LPARAM lParam);
    static BOOL CALLBACK IsOpenMDIChiledProc(HWND hwnd, LPARAM lParam);
    static BOOL CALLBACK SetFontProc(HWND hwnd, LPARAM lParam);
    static BOOL CALLBACK SetBackColorProc(HWND hwnd, LPARAM lParam);
    static BOOL CALLBACK SetViewLineProc(HWND hwnd, LPARAM lParam);
    void LoadLib();
    void FreeLib();

    void LoadInitFile();
    void load_property(PROPERTY & prop);
    void StoreInitFile();
    void store_property(PROPERTY & prop);

    void CharFormat2LogFont(CHARFORMAT *pfm, LOGFONT *plf, HWND hREdit);
    void LogFont2CharFormat(LOGFONT *plf);

    HWND m_hClient;
    HWND m_hToolbar;
    HMENU m_hMenuDoc;
    HMENU m_hMenuWnd;
    HMENU m_hMenuDocWnd;
    RubyITPR m_Ruby;
    HINSTANCE m_hInstance;
    HINSTANCE m_hSciLib;
    HACCEL m_hAccel;
    CHARFORMAT m_cfm;
    REDIT_PROPERTY m_edprop;

    long m_doc_id;
    STATUS m_status;
    IOBUF m_iobuf;
    HWND m_running_doc_hwnd;

    FindInfo m_findinfo;
    CMBINFO  m_argvinfo;

    const char * m_pcmdline;

    BOOL m_auto_judge_jcode;
    unsigned char m_def_fileio_code;

    deque<string> m_recent_files;
    deque<string>::size_type  m_max_recent_files;
};

struct LPOpenProc {
    const char* pname;
    BOOL IsOpened;
};

#endif
