require 'mkmf'

$CFLAGS="-DUSE_EUC -DUSE_SJIS"
##$CFLAGS="-DUSE_SJIS -DUSE_WIN32API"
create_makefile("uconv")
