/*----------------------------------------
  reditprop.h
  $Date: 2001/08/14 13:19:31 $
  $Revision: 1.7 $
  Copyright (C) 2000 - 2001 Masaki Suketa
------------------------------------------*/
#ifndef REDITPROP_H
#define REDITPROP_H

#include <windows.h>
#include <richedit.h>
#include <string>
#include <vector>
#include <Scintilla.h>
#include "property.h"
using namespace std;

enum TEXTCOLORID {
    TCID_DEFAULT = 0,
    TCID_COMMENT,
    TCID_NUMBER,
    TCID_DQSTRING,
    TCID_SQSTRING,
    TCID_KEYWORD,
    TCID_CLASS = 8,
    TCID_METHOD,
    TCID_OPERATOR
};

const int DEFAULT_INDENT_SIZE = 2;

struct TEXTCOLOR {
    string name;
    TEXTCOLORID id;
    COLORREF color;
    TEXTCOLOR(const char * col_name,
              const TEXTCOLORID col_id,
              COLORREF col_rgb
              );
    TEXTCOLOR();
#if defined(_MSC_VER) && (_MSC_VER == 1100)
    friend bool operator<(const TEXTCOLOR& tc1, 
                          const TEXTCOLOR& tc2) {
                    return tc1.id < tc2.id;
    }
    friend bool operator==(const TEXTCOLOR& tc1, 
                           const TEXTCOLOR& tc2) {
                    return tc1.id == tc2.id;
    }
#endif
};


struct REDIT_PROPERTY {
    string keywords;
    CHARFORMAT cfm;
    COLORREF   backColor;
    vector<TEXTCOLOR> textColor;
    int indent_size;
    bool isDisplayLineNumber;
    bool is_clean_console;    
    REDIT_PROPERTY();
    void load_property(PROPERTY & prop);
    void store_property(PROPERTY & prop);
    void ColorREFtoRGBStr(COLORREF cr, char *p);
    COLORREF RGBStrtoColorREF(const string & s);
};

#endif
