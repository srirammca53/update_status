require 'mkmf'

srcdir = File.dirname($0)

$OBJS = []
for f in Dir["#{srcdir}/*.{#{SRC_EXT.join(%q{,})}}"].sort
  f = File.basename(f)
  f.sub!(/(#{SRC_EXT.join(%q{|})})$/, $OBJEXT)
  $OBJS.push f
end
$TARGET = 'rubywin'
$STACK = "0x2000000"

case PLATFORM
when /mswin/
  $RUBY_INSTALL_NAME = "$(exec_prefix:/=\\)\\bin\\#{CONFIG['RUBY_INSTALL_NAME']}"
  $EXEC_CC = '$(CC) $(CFLAGS) -c $<'
  $EXEC_CC_FOR_VERSIONDLG = '$(CC) $(CFLAGS) -c $(srcdir)/$*.cpp'
  $CC = CONFIG['CC']
  $CFLAGS = CONFIG['CFLAGS'] + ' -I$(srcdir) -I$(srcdir)/scintilla/include -I$(srcdir)/uconv -GX -GR-'
  $RESEXT = '.res'
  $LIBS = "shell32.lib kernel32.lib gdi32.lib user32.lib winmm.lib comdlg32.lib version.lib comctl32.lib imm32.lib ole32.lib uuid.lib -link /LIBPATH:$(topdir) /STACK:#{$STACK}"
  $SETLIB = "set LIB=#{CONFIG['libdir']};$(LIB)\n\t"
  $OBJRULE = <<STR
.cpp.obj:
	$(CC) $(CFLAGS) -c $<
{$(srcdir)}.cpp{}.obj:
	$(CC) $(CFLAGS) -c $<
.c.obj:
	$(CC) $(CFLAGS) -c $<
{$(srcdir)}.c{}.obj:
	$(CC) $(CFLAGS) -c $<
STR

  $OBJRULE2 = $OBJS.collect{|obj|
     src = obj
     SRC_EXT.each{ |ext|
       temp = obj.sub($OBJEXT, ext)
       temp = File.join(srcdir, temp) if /nmake/i =~ $make
       if FileTest.exist?( temp )      
         src  = temp
       end
    }
    "#{obj}:#{src}"
  }.join("\n")
  $SUFFIX = ""

  $RESCC = <<STR
resource.res: $(srcdir)/resource.rc $(srcdir)/resource.h
	rc.exe /fo resource.res $(srcdir)/resource.rc
STR

when /mingw/, /cygwin/
  $RUBY_INSTALL_NAME = "$(exec_prefix)/bin/#{CONFIG['RUBY_INSTALL_NAME']}"
  $EXEC_CC = '$(CC) $(CXXFLAGS) -c $< -o $@'
  $EXEC_CC_FOR_VERSIONDLG = $EXEC_CC
  $CC = CONFIG['CC']
  $CFLAGS += ' -I$(srcdir) -I$(srcdir)/scintilla/include -I$(srcdir)/uconv -Wall -fno-exceptions -fno-rtti'
  $RESEXT = '.o'
  $LDFLAGS =  " -L" + CONFIG["libdir"] + " -mwindows -e _mainCRTStartup --stack,#{$STACK}"
  $LIBS = '-lkernel32 -lgdi32 -luser32 -lwinmm -lcomdlg32 -lcomctl32 -limm32 -lole32 -luuid -lversion -lstdc++'
  $SETLIB = ''
  $OBJRULE = <<STR
.cpp.o:
	$(CC) $(CXXFLAGS) -c $< -o $@
.c.o:
	$(CC) $(CXXFLAGS) -c $< -o $@
STR
  $OBJRULE2 = ""
  $SUFFIX = '.SUFFIXES: .cpp'

  $RESCC = <<STR
resource.o: $(srcdir)/resource.rc $(srcdir)/resource.h
	#{CONFIG['WINDRES']} --include-dir $(srcdir) --define USE_WINDRES $(srcdir)/resource.rc resource.o
STR

end

$OBJS = $OBJS.join(" ")
$OBJS += " resource#{$RESEXT}"

drive = File::PATH_SEPARATOR == ';' ? /\A\w:/ : /\A/
ofs = open("Makefile", "w")
ofs.print <<EOF
srcdir = #{srcdir || $srcdir}
VPATH = $(srcdir)
topdir = #{$topdir}
hdrdir = #{$hdrdir}
arch = #{CONFIG["arch"]}
ruby_version = #{Config::CONFIG["ruby_version"]}
#{
if destdir = CONFIG["prefix"].scan(drive)[0] and !destdir.empty?
  "\nDESTDIR = " + destdir
else
  ""
end
}
prefix = $(DESTDIR)#{CONFIG["prefix"].sub(drive, '')}
exec_prefix = #{CONFIG["exec_prefix"].sub(drive, '')}
libdir = #{$libdir.sub(drive, '')}
rubylibdir = #{$rubylibdir.sub(drive, '')}
archdir = #{$archdir.sub(drive, '')}
sitedir = #{$sitedir.sub(drive, '')}
sitelibdir = #{$sitelibdir.sub(drive, '')}
sitearchdir = #{$sitearchdir.sub(drive, '')}

#{$SUFFIX}
CC = #{$CC}
TARGET = #{$TARGET}#{CONFIG["EXEEXT"]}

LIBS =
CFLAGS = #{CONFIG["CCDLFLAGS"]} -I$(hdrdir) #{$CFLAGS} -I#{CONFIG["includedir"]}
CPPFLAGS = #{$CPPFLAGS}
CXXFLAGS = $(CFLAGS)

LIBRUBY = #{CONFIG['LIBRUBY']}
LIBRUBY_A = #{CONFIG['LIBRUBY_A']}
LIBRUBYARG_SHARED = #$LIBRUBYARG_SHARED
LIBRUBYARG_STATIC = #$LIBRUBYARG_STATIC

LDFLAGS = #$LDFLAGS
DLDFLAGS = #$LDFLAGS #{CONFIG['DLDFLAGS']} #$DLDFLAGS

RUBY_INSTALL_NAME = #{CONFIG["RUBY_INSTALL_NAME"]}
RUBY_SO_NAME = #{CONFIG["RUBY_SO_NAME"]}

#{$OBJRULE}

OBJS = #{$OBJS}
LIBS = #{CONFIG["LIBRUBYARG"]} #{$LIBS}

$(TARGET): $(OBJS)
	#{$SETLIB}$(CC) $(LDFLAGS) -o $(TARGET) $(OBJS) $(LIBS)

versiondlg.#{$OBJEXT}: $(srcdir)/versiondlg.cpp $(srcdir)/versiondlg.h $(srcdir)/version.h
	#{$EXEC_CC_FOR_VERSIONDLG}

#{$OBJRULE2}
#{$RESCC}

$(srcdir)/resource.rc: $(srcdir)/version.h
	#{$RUBY_INSTALL_NAME} $(RUBYOPT1) $(srcdir)/edit_resource.rb $(srcdir)/version.h $(srcdir)/resource.rc

install: $(TARGET)
	#{$RUBY_INSTALL_NAME} $(RUBYOPT1) $(srcdir)/install.rb $(RUBYOPT2)
EOF

ofs.close
puts "Makefile created"
