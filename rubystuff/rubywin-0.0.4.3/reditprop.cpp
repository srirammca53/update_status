/*----------------------------------------
  reditprop.cpp
  $Date: 2001/08/18 07:09:02 $
  $Revision: 1.8 $
  Copyright (C) 2000 - 2001 Masaki Suketa
------------------------------------------*/
#include <stdio.h>
#include "reditprop.h"
#include "rwcommon.h"
#include "dismscwarn.h"

static const int STYLE_COLOR_SIZE = 9;

static char STYLE_COLOR [9][100] = {
    "BUF.defaultColor",
    "BUF.commentColor",
    "BUF.numberColor",
    "BUF.stringColor",
    "BUF.singlequotedstrColor",
    "BUF.keywordColor",
    "BUF.classnameColor",
    "BUF.methodColor",
    "BUF.operatorColor"
};

static const TEXTCOLORID TCID[] = {
    TCID_DEFAULT,
    TCID_COMMENT,
    TCID_NUMBER,
    TCID_DQSTRING,
    TCID_SQSTRING,
    TCID_KEYWORD,
    TCID_CLASS,
    TCID_METHOD,
    TCID_OPERATOR
};

TEXTCOLOR::TEXTCOLOR():
    name(STYLE_COLOR[0]),
    id(TCID[0]),
    color(RGB(0,0,0)){
}
  
TEXTCOLOR::TEXTCOLOR(
    const char * col_name,
    const TEXTCOLORID col_id,
    COLORREF col_rgb
    ):
    name(col_name),
    id(col_id),
    color(col_rgb){
}

REDIT_PROPERTY::REDIT_PROPERTY() {
    memset(&cfm, 0, sizeof(CHARFORMAT));
    backColor = RGB(255, 255, 255);
    for(int i = 0; i < STYLE_COLOR_SIZE; i ++) {
        TEXTCOLOR t(STYLE_COLOR[i], TCID[i], RGB(0, 0, 0));
        textColor.push_back(t);
    }
    indent_size = DEFAULT_INDENT_SIZE;
    isDisplayLineNumber = false;
    is_clean_console = false;
    keywords = "__LINE__ __FILE__ BEGIN END alias and begin break "
               "case class def defined? do else elsif end ensure "
               "false for if in module next nil not or redo rescue "
               "retry return self super then true undef unless until "
               "when while yield";
}

void REDIT_PROPERTY::load_property(
    PROPERTY & prop
    ) {
    string s;
    long l;
    if(prop.get("BUF_CFM.dwEffects", l)) {
        cfm.dwEffects = l;
        cfm.cbSize = sizeof(CHARFORMAT);
        cfm.dwMask = CFM_BOLD | CFM_CHARSET | CFM_COLOR | CFM_FACE |
                       CFM_ITALIC | CFM_SIZE | CFM_STRIKEOUT | CFM_UNDERLINE;

    }
    if(prop.get("BUF_CFM.yHeight", l)) {
        cfm.yHeight = l;
    }
    if(prop.get("BUF_CFM.yOffset", l)) {
        cfm.yOffset = l;
    }
    if(prop.get("BUF_CFM.crTextColor", s)) {
        cfm.crTextColor = RGBStrtoColorREF(s);
    }
    if(prop.get("BUF_CFM.bCharSet", l)) {
        cfm.bCharSet = l;
    }
    if(prop.get("BUF_CFM.bPitchAndFamily", l)) {
        cfm.bPitchAndFamily = l;
    }
    if(prop.get("BUF_CFM.szFaceName", s)) {
        strcpy(cfm.szFaceName, s.c_str());
    }
    if(prop.get("BUF.backColor", s)) {
        backColor = RGBStrtoColorREF(s);
    }
    if(prop.get("BUF.keywords", s)) {
        keywords = s;
    }
    vector<TEXTCOLOR>::iterator i = textColor.begin();
    for (; i != textColor.end(); i++) {
        if(prop.get((*i).name, s)) {
            i->color = RGBStrtoColorREF(s);
        }
    }

    if(prop.get("BUF.isDisplayLineNumber", l)) {
        isDisplayLineNumber = l;
    }
    if(prop.get("BUF.indent_size", l)) {
        indent_size = l;
    }
    if(prop.get("CONSOLE.is_clean", l)) {
        is_clean_console = l;
    }
}

void REDIT_PROPERTY::store_property(
    PROPERTY & prop
    ) {
    char buf[12];
    if (cfm.cbSize > 0) {
        prop.set("BUF_CFM.dwEffects", cfm.dwEffects);
        prop.set("BUF_CFM.yHeight", cfm.yHeight);
        prop.set("BUF_CFM.yOffset", cfm.yOffset);
        ColorREFtoRGBStr(cfm.crTextColor, buf);
        prop.set("BUF_CFM.crTextColor", buf);
        prop.set("BUF_CFM.bCharSet", cfm.bCharSet);
        prop.set("BUF_CFM.bPitchAndFamily", cfm.bPitchAndFamily);
        prop.set("BUF_CFM.szFaceName", cfm.szFaceName);
    }
    ColorREFtoRGBStr(backColor, buf);
    prop.set("BUF.backColor", buf);

    vector<TEXTCOLOR>::iterator i = textColor.begin();
    for (; i != textColor.end(); i++) {
        ColorREFtoRGBStr(i->color, buf);
        prop.set(i->name, buf);
    }

    prop.set("BUF.keywords", keywords.c_str());
    prop.set("BUF.isDisplayLineNumber", isDisplayLineNumber);
    prop.set("BUF.indent_size", indent_size);
    prop.set("CONSOLE.is_clean", is_clean_console);
}

void REDIT_PROPERTY::ColorREFtoRGBStr(
    COLORREF cr,
    char *p
    ) {
    sprintf(p, "%d,%d,%d", GetRValue(cr), GetGValue(cr), GetBValue(cr));
}

COLORREF REDIT_PROPERTY::RGBStrtoColorREF(
    const string & s
    ) {
    string::size_type n1 = 0;
    string::size_type n2 = s.find(",");

    int r = atoi(s.substr(0,n2).c_str());
    n1 = n2+1;
    n2 = s.find(",", n1);
    int g = atoi(s.substr(n1,n2-n1).c_str());
    n1 = n2 + 1;
    n2 = s.find(",", n1);
    int b = atoi(s.substr(n1, n2-n1).c_str());
    return RGB(r, g, b);
}

