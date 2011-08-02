/*----------------------------------------
  resource.h
  $Date: 2001/08/14 13:19:57 $
  Copyright (C) 2000 - 2001 Masaki Suketa
------------------------------------------*/
#ifndef RESOURCE_H
#define RESOURCE_H

#define IDM_NEW			101
#define IDM_OPEN		102
#define IDM_CLOSE		103
#define IDM_SAVE        	104
#define IDM_SAVE_AS     	105
#define IDM_EXIT		106
#define IDM_OPEN_RECENT_FILE    107

#define IDM_UNDO		201
#define IDM_CUT			202
#define IDM_COPY		203
#define IDM_PASTE		204
#define IDM_DELETE		205
#define IDM_SELECT_ALL		206
#define IDM_REDO                207

#define IDM_FIND		301
#define IDM_FIND_NEXT		302
#define IDM_REPLACE		303
#define IDM_REPLACE_NEXT	304

#define IDM_EVAL_BUFFER		401
#define IDM_EVAL_WITH_ARGV	402
#define IDM_EVAL_SELECT		403
#define IDM_CHECK_SYNTAX	404
#define IDM_IRB			405
#define IDM_RUN_FILE		406
#define IDM_CONSOLE		407
#define IDM_SPLIT_CONSOLE       408

#define IDM_FONT		501
#define IDM_SET_TEXT_COLOR      502
#define IDM_SET_BACK_COLOR      503
#define IDM_VIEW_LINE           504

#define IDM_CASCADE		601
#define IDM_TILE_HORI		602
#define IDM_TILE_VERT		603
#define IDM_ARRANGE		604

#define IDM_VERSION		701

#define CMD_SAVED		801
#define CMD_UNSAVE		802
#define CMD_CONSOLE_GETS	803
#define CMD_SETCHARFORMAT       804
#define CMD_CONSOLE_WRITE       805
#define CMD_SETBACKCOLOR        806
#define CMD_SETVIEWLINE         807
#define CMD_SPLIT_CONSOLE_WRITE 808
#define CMD_SPLIT_CONSOLE_GETS  809

#define ID_TOOLBAR		900

#define IDM_FIRSTCHILD		32200

#define IDC_STATIC		1000
#define IDC_ST_RUBYWIN_VERSION	1001
#define IDC_ST_RUBY_VERSION	1002
#define IDC_ST_RUBY_COPYRIGHT	1003

#define IDC_CMB_ARGV		1004
#define IDC_CMB_FIND_STR	1005
#define IDC_CMB_REPL_STR	1006
#define IDC_CHK_MATCH_CASE	1007
#define IDC_CHK_WHOLE_WORD	1008

#define IDC_ST_SCILEXER_VERSION   1009
#define IDC_ST_SCILEXER_COPYRIGHT 1010

#define IDC_PB_TEXTCOLOR_DEFAULT     1031
#define IDC_PB_TEXTCOLOR_COMMENT     1032
#define IDC_PB_TEXTCOLOR_NUMBER      1033
#define IDC_PB_TEXTCOLOR_STRING      1034
#define IDC_PB_TEXTCOLOR_SSTRING     1035
#define IDC_PB_TEXTCOLOR_KEYWORD     1036
#define IDC_PB_TEXTCOLOR_CLASSNAME   1037
#define IDC_PB_TEXTCOLOR_METHOD      1038
#define IDC_PB_TEXTCOLOR_OPERATOR    1039

#endif
