bin: $(PROGRAM) $(WPROGRAM)
lib: $(LIBRUBY)
dll: $(LIBRUBY_SO)

.SUFFIXES: .inc .h .c .y

RUBYLIB       = -
RUBYOPT       = -

SPEC_GIT_BASE = git://github.com/rubyspec
MSPEC_GIT_URL = $(SPEC_GIT_BASE)/mspec.git
RUBYSPEC_GIT_URL = $(SPEC_GIT_BASE)/rubyspec.git

STATIC_RUBY   = static-ruby

EXTCONF       = extconf.rb
RBCONFIG      = ./.rbconfig.time
LIBRUBY_EXTS  = ./.libruby-with-ext.time
RDOCOUT       = $(EXTOUT)/rdoc
ID_H_TARGET   = -id.h-

DMYEXT	      = dmyext.$(OBJEXT)
NORMALMAINOBJ = main.$(OBJEXT)
MAINOBJ       = $(NORMALMAINOBJ)
EXTOBJS	      = 
DLDOBJS	      = $(DMYEXT)
MINIOBJS      = $(ARCHMINIOBJS) dmyencoding.$(OBJEXT) miniprelude.$(OBJEXT)
ENC_MK        = enc.mk

COMMONOBJS    = array.$(OBJEXT) \
		bignum.$(OBJEXT) \
		class.$(OBJEXT) \
		compar.$(OBJEXT) \
		complex.$(OBJEXT) \
		dir.$(OBJEXT) \
		enum.$(OBJEXT) \
		enumerator.$(OBJEXT) \
		error.$(OBJEXT) \
		eval.$(OBJEXT) \
		load.$(OBJEXT) \
		proc.$(OBJEXT) \
		file.$(OBJEXT) \
		gc.$(OBJEXT) \
		hash.$(OBJEXT) \
		inits.$(OBJEXT) \
		io.$(OBJEXT) \
		marshal.$(OBJEXT) \
		math.$(OBJEXT) \
		numeric.$(OBJEXT) \
		object.$(OBJEXT) \
		pack.$(OBJEXT) \
		parse.$(OBJEXT) \
		process.$(OBJEXT) \
		random.$(OBJEXT) \
		range.$(OBJEXT) \
		rational.$(OBJEXT) \
		re.$(OBJEXT) \
		regcomp.$(OBJEXT) \
		regenc.$(OBJEXT) \
		regerror.$(OBJEXT) \
		regexec.$(OBJEXT) \
		regparse.$(OBJEXT) \
		regsyntax.$(OBJEXT) \
		ruby.$(OBJEXT) \
		safe.$(OBJEXT) \
		signal.$(OBJEXT) \
		sprintf.$(OBJEXT) \
		st.$(OBJEXT) \
		strftime.$(OBJEXT) \
		string.$(OBJEXT) \
		struct.$(OBJEXT) \
		time.$(OBJEXT) \
		transcode.$(OBJEXT) \
		util.$(OBJEXT) \
		variable.$(OBJEXT) \
		version.$(OBJEXT) \
		compile.$(OBJEXT) \
		debug.$(OBJEXT) \
		iseq.$(OBJEXT) \
		vm.$(OBJEXT) \
		vm_dump.$(OBJEXT) \
		thread.$(OBJEXT) \
		cont.$(OBJEXT) \
		$(BUILTIN_ENCOBJS) \
		$(BUILTIN_TRANSOBJS) \
		$(MISSING)

OBJS          = dln.$(OBJEXT) \
		encoding.$(OBJEXT) \
		prelude.$(OBJEXT) \
		$(COMMONOBJS)

GOLFOBJS      = goruby.$(OBJEXT) golf_prelude.$(OBJEXT)

PRELUDE_SCRIPTS = $(srcdir)/prelude.rb $(srcdir)/enc/prelude.rb $(srcdir)/gem_prelude.rb
PRELUDES      = prelude.c miniprelude.c
GOLFPRELUDES = golf_prelude.c

SCRIPT_ARGS   =	--dest-dir="$(DESTDIR)" \
		--extout="$(EXTOUT)" \
		--mflags="$(MFLAGS)" \
		--make-flags="$(MAKEFLAGS)"
EXTMK_ARGS    =	$(SCRIPT_ARGS) --extension $(EXTS) --extstatic $(EXTSTATIC) \
		--make-flags="MINIRUBY='$(MINIRUBY)'" --
INSTRUBY      =	$(MINIRUBY) $(srcdir)/instruby.rb
INSTRUBY_ARGS =	$(SCRIPT_ARGS) \
		--data-mode=$(INSTALL_DATA_MODE) \
		--prog-mode=$(INSTALL_PROG_MODE) \
		--installed-list $(INSTALLED_LIST)
INSTALL_PROG_MODE = 0755
INSTALL_DATA_MODE = 0644

PRE_LIBRUBY_UPDATE = $(MINIRUBY) -e 'ARGV[1] or File.unlink(ARGV[0]) rescue nil' -- \
			$(LIBRUBY_EXTS) $(LIBRUBY_SO_UPDATE)

TESTSDIR      = $(srcdir)/test
TESTWORKDIR   = testwork

TESTRUN_SCRIPT = $(srcdir)/test.rb

BOOTSTRAPRUBY = $(BASERUBY)

COMPILE_PRELUDE = $(MINIRUBY) -I$(srcdir) -rrbconfig $(srcdir)/tool/compile_prelude.rb

all: encs exts
exts: $(MKFILES) incs $(PREP) $(RBCONFIG) $(LIBRUBY)
	@$(MINIRUBY) $(srcdir)/ext/extmk.rb --make="$(MAKE)" $(EXTMK_ARGS)
prog: $(PROGRAM) $(WPROGRAM)

loadpath: $(PREP)
	$(MINIRUBY) -e 'p $$:'

$(PREP): $(MKFILES)

miniruby$(EXEEXT): config.status $(NORMALMAINOBJ) $(MINIOBJS) $(COMMONOBJS) $(DMYEXT) $(ARCHFILE)

GORUBY = go$(RUBY_INSTALL_NAME)
golf: $(LIBRUBY) $(GOLFOBJS)
	$(MAKE) $(MFLAGS) MAINOBJ="$(GOLFOBJS)" PROGRAM=$(GORUBY)$(EXEEXT) program

program: $(PROGRAM)

$(PROGRAM): $(LIBRUBY) $(MAINOBJ) $(OBJS) $(EXTOBJS) $(SETUP) $(PREP)

$(LIBRUBY_A):	$(OBJS) $(DMYEXT) $(ARCHFILE)

$(LIBRUBY_SO):	$(OBJS) $(DLDOBJS) $(LIBRUBY_A) $(PREP) $(LIBRUBY_SO_UPDATE) $(BUILTIN_ENCOBJS)

$(LIBRUBY_EXTS):
	@exit > $@

$(STATIC_RUBY)$(EXEEXT): $(MAINOBJ) $(DLDOBJS) $(EXTOBJS) $(LIBRUBY_A)
	@$(RM) $@
	$(PURIFY) $(CC) $(MAINOBJ) $(DLDOBJS) $(EXTOBJS) $(LIBRUBY_A) $(MAINLIBS) $(EXTLIBS) $(LIBS) $(OUTFLAG)$@ $(LDFLAGS) $(XLDFLAGS)

ruby.imp: $(COMMONOBJS)
	@$(NM) -Pgp $(COMMONOBJS) | awk 'BEGIN{print "#!"}; $$2~/^[BD]$$/{print $$1}' | sort -u -o $@

install: install-nodoc $(RDOCTARGET)
install-all: install-nodoc install-doc

install-nodoc: pre-install-nodoc do-install-nodoc post-install-nodoc
pre-install-nodoc:: pre-install-local pre-install-ext
do-install-nodoc: $(PREP)
	$(INSTRUBY) --make="$(MAKE)" $(INSTRUBY_ARGS) --mantype="$(MANTYPE)"
post-install-nodoc:: post-install-local post-install-ext

install-local: pre-install-local do-install-local post-install-local
pre-install-local:: pre-install-bin pre-install-lib pre-install-man
do-install-local: $(PREP)
	$(INSTRUBY) --make="$(MAKE)" $(INSTRUBY_ARGS) --install=local --mantype="$(MANTYPE)"
post-install-local:: post-install-bin post-install-lib post-install-man

install-ext: pre-install-ext do-install-ext post-install-ext
pre-install-ext:: pre-install-ext-arch pre-install-ext-comm
do-install-ext: $(PREP)
	$(INSTRUBY) --make="$(MAKE)" $(INSTRUBY_ARGS) --install=ext
post-install-ext:: post-install-ext-arch post-install-ext-comm

install-arch: pre-install-arch do-install-arch post-install-arch
pre-install-arch:: pre-install-bin pre-install-ext-arch
do-install-arch: $(PREP)
	$(INSTRUBY) --make="$(MAKE)" $(INSTRUBY_ARGS) --install=bin --install=ext-arch
post-install-arch:: post-install-bin post-install-ext-arch

install-comm: pre-install-comm do-install-comm post-install-comm
pre-install-comm:: pre-install-lib pre-install-ext-comm pre-install-man
do-install-comm: $(PREP)
	$(INSTRUBY) --make="$(MAKE)" $(INSTRUBY_ARGS) --install=lib --install=ext-comm --install=man
post-install-comm:: post-install-lib post-install-ext-comm post-install-man

install-bin: pre-install-bin do-install-bin post-install-bin
pre-install-bin:: install-prereq
do-install-bin: $(PREP)
	$(INSTRUBY) --make="$(MAKE)" $(INSTRUBY_ARGS) --install=bin
post-install-bin::
	@$(NULLCMD)

install-lib: pre-install-lib do-install-lib post-install-lib
pre-install-lib:: install-prereq
do-install-lib: $(PREP)
	$(INSTRUBY) --make="$(MAKE)" $(INSTRUBY_ARGS) --install=lib
post-install-lib::
	@$(NULLCMD)

install-ext-comm: pre-install-ext-comm do-install-ext-comm post-install-ext-comm
pre-install-ext-comm:: install-prereq
do-install-ext-comm: $(PREP)
	$(INSTRUBY) --make="$(MAKE)" $(INSTRUBY_ARGS) --install=ext-comm
post-install-ext-comm::
	@$(NULLCMD)

install-ext-arch: pre-install-ext-arch do-install-ext-arch post-install-ext-arch
pre-install-ext-arch:: install-prereq
do-install-ext-arch: $(PREP)
	$(INSTRUBY) --make="$(MAKE)" $(INSTRUBY_ARGS) --install=ext-arch
post-install-ext-arch::
	@$(NULLCMD)

install-man: pre-install-man do-install-man post-install-man
pre-install-man:: install-prereq
do-install-man: $(PREP)
	$(INSTRUBY) --make="$(MAKE)" $(INSTRUBY_ARGS) --install=man --mantype="$(MANTYPE)"
post-install-man::
	@$(NULLCMD)

what-where: no-install
no-install: no-install-nodoc no-install-doc
what-where-all: no-install-all
no-install-all: no-install-nodoc

what-where-nodoc: no-install-nodoc
no-install-nodoc: pre-no-install-nodoc dont-install-nodoc post-no-install-nodoc
pre-no-install-nodoc:: pre-no-install-local pre-no-install-ext
dont-install-nodoc:  $(PREP)
	$(INSTRUBY) -n --make="$(MAKE)" $(INSTRUBY_ARGS) --mantype="$(MANTYPE)"
post-no-install-nodoc:: post-no-install-local post-no-install-ext

what-where-local: no-install-local
no-install-local: pre-no-install-local dont-install-local post-no-install-local
pre-no-install-local:: pre-no-install-bin pre-no-install-lib pre-no-install-man
dont-install-local: $(PREP)
	$(INSTRUBY) -n --make="$(MAKE)" $(INSTRUBY_ARGS) --install=local --mantype="$(MANTYPE)"
post-no-install-local:: post-no-install-bin post-no-install-lib post-no-install-man

what-where-ext: no-install-ext
no-install-ext: pre-no-install-ext dont-install-ext post-no-install-ext
pre-no-install-ext:: pre-no-install-ext-arch pre-no-install-ext-comm
dont-install-ext: $(PREP)
	$(INSTRUBY) -n --make="$(MAKE)" $(INSTRUBY_ARGS) --install=ext
post-no-install-ext:: post-no-install-ext-arch post-no-install-ext-comm

what-where-arch: no-install-arch
no-install-arch: pre-no-install-arch dont-install-arch post-no-install-arch
pre-no-install-arch:: pre-no-install-bin pre-no-install-ext-arch
dont-install-arch: $(PREP)
	$(INSTRUBY) -n --make="$(MAKE)" $(INSTRUBY_ARGS) --install=bin --install=ext-arch
post-no-install-arch:: post-no-install-lib post-no-install-man post-no-install-ext-arch

what-where-comm: no-install-comm
no-install-comm: pre-no-install-comm dont-install-comm post-no-install-comm
pre-no-install-comm:: pre-no-install-lib pre-no-install-ext-comm pre-no-install-man
dont-install-comm: $(PREP)
	$(INSTRUBY) -n --make="$(MAKE)" $(INSTRUBY_ARGS) --install=lib --install=ext-comm --install=man
post-no-install-comm:: post-no-install-lib post-no-install-ext-comm post-no-install-man

what-where-bin: no-install-bin
no-install-bin: pre-no-install-bin dont-install-bin post-no-install-bin
pre-no-install-bin:: install-prereq
dont-install-bin: $(PREP)
	$(INSTRUBY) -n --make="$(MAKE)" $(INSTRUBY_ARGS) --install=bin
post-no-install-bin::
	@$(NULLCMD)

what-where-lib: no-install-lib
no-install-lib: pre-no-install-lib dont-install-lib post-no-install-lib
pre-no-install-lib:: install-prereq
dont-install-lib: $(PREP)
	$(INSTRUBY) -n --make="$(MAKE)" $(INSTRUBY_ARGS) --install=lib
post-no-install-lib::
	@$(NULLCMD)

what-where-ext-comm: no-install-ext-comm
no-install-ext-comm: pre-no-install-ext-comm dont-install-ext-comm post-no-install-ext-comm
pre-no-install-ext-comm:: install-prereq
dont-install-ext-comm: $(PREP)
	$(INSTRUBY) -n --make="$(MAKE)" $(INSTRUBY_ARGS) --install=ext-comm
post-no-install-ext-comm::
	@$(NULLCMD)

what-where-ext-arch: no-install-ext-arch
no-install-ext-arch: pre-no-install-ext-arch dont-install-ext-arch post-no-install-ext-arch
pre-no-install-ext-arch:: install-prereq
dont-install-ext-arch: $(PREP)
	$(INSTRUBY) -n --make="$(MAKE)" $(INSTRUBY_ARGS) --install=ext-arch
post-no-install-ext-arch::
	@$(NULLCMD)

what-where-man: no-install-man
no-install-man: pre-no-install-man dont-install-man post-no-install-man
pre-no-install-man:: install-prereq
dont-install-man: $(PREP)
	$(INSTRUBY) -n --make="$(MAKE)" $(INSTRUBY_ARGS) --install=man --mantype="$(MANTYPE)"
post-no-install-man::
	@$(NULLCMD)

install-doc: rdoc pre-install-doc do-install-doc post-install-doc
pre-install-doc:: install-prereq
do-install-doc: $(PROGRAM)
	$(INSTRUBY) --make="$(MAKE)" $(INSTRUBY_ARGS) --install=rdoc --rdoc-output="$(RDOCOUT)"
post-install-doc::
	@$(NULLCMD)

rdoc: $(PROGRAM) PHONY
	@echo Generating RDoc documentation
	$(RUNRUBY) "$(srcdir)/bin/rdoc" --all --ri --op "$(RDOCOUT)" "$(srcdir)"

what-where-doc: no-install-doc
no-install-doc: pre-no-install-doc dont-install-doc post-no-install-doc
pre-no-install-doc:: install-prereq
dont-install-doc:: $(PREP)
	$(INSTRUBY) -n --make="$(MAKE)" $(INSTRUBY_ARGS) --install=rdoc --rdoc-output="$(RDOCOUT)"
post-no-install-doc::
	@$(NULLCMD)

CLEAR_INSTALLED_LIST = clear-installed-list

install-prereq: $(CLEAR_INSTALLED_LIST)

clear-installed-list:
	@exit > $(INSTALLED_LIST)

clean: clean-ext clean-local clean-enc clean-golf clean-rdoc clean-extout
clean-local::
	@$(RM) $(OBJS) $(MINIOBJS) $(MAINOBJ) $(LIBRUBY_A) $(LIBRUBY_SO) $(LIBRUBY) $(LIBRUBY_ALIASES)
	@$(RM) $(PROGRAM) $(WPROGRAM) miniruby$(EXEEXT) dmyext.$(OBJEXT) $(ARCHFILE) .*.time
	@$(RM) *.inc y.tab.c y.output encdb.h transdb.h
clean-ext::
clean-enc:
	@-$(MAKE) -f $(ENC_MK) $(MFLAGS) clean
clean-golf:
	@$(RM) $(GORUBY)$(EXEEXT) $(GOLFOBJS)
clean-rdoc:
clean-extout:
	@-$(RMDIRS) $(EXTOUT)/$(arch)

distclean: distclean-ext distclean-local distclean-enc distclean-golf distclean-extout
distclean-local:: clean-local
	@$(RM) $(MKFILES) rbconfig.rb yasmdata.rb encdb.h
	@$(RM) config.cache config.log config.status config.status.lineno $(PRELUDES)
	@$(RM) *~ *.bak *.stackdump core *.core gmon.out $(PREP)
distclean-ext::
distclean-enc: clean-enc
	@-$(MAKE) -f $(ENC_MK) $(MFLAGS) distclean
distclean-golf: clean-golf
	@$(RM) $(GOLFPRELUDES)
distclean-rdoc:
distclean-extout: clean-extout
	@-$(RMDIRS) $(EXTOUT)

realclean:: realclean-ext realclean-local realclean-enc realclean-golf realclean-extout
realclean-local:: distclean-local
	@$(RM) parse.c parse.h lex.c newline.c revision.h
realclean-ext::
realclean-enc:: distclean-enc
realclean-golf: distclean-golf
realclean-extout: distclean-extout

check: test test-all

btest: miniruby$(EXEEXT) PHONY
	$(BOOTSTRAPRUBY) "$(srcdir)/bootstraptest/runner.rb" --ruby="$(MINIRUBY)" $(OPTS)

btest-ruby: miniruby$(EXEEXT) $(RBCONFIG) $(PROGRAM) PHONY
	@$(RUNRUBY) "$(srcdir)/bootstraptest/runner.rb" --ruby="$(PROGRAM) -I$(srcdir)/lib" -q $(OPTS)

test-sample: miniruby$(EXEEXT) $(RBCONFIG) $(PROGRAM) PHONY
	@$(RUNRUBY) $(srcdir)/rubytest.rb

test-knownbug: miniruby$(EXEEXT) $(PROGRAM) $(RBCONFIG) PHONY
	$(MINIRUBY) "$(srcdir)/bootstraptest/runner.rb" --ruby="$(PROGRAM)" $(OPTS) $(srcdir)/KNOWNBUGS.rb

test: test-sample btest-ruby test-knownbug

test-all:
	$(RUNRUBY) "$(srcdir)/test/runner.rb" $(TESTS)

extconf: $(PREP)
	$(MAKEDIRS) "$(EXTCONFDIR)"
	$(RUNRUBY) -C "$(EXTCONFDIR)" $(EXTCONF) $(EXTCONFARGS)

$(RBCONFIG): $(srcdir)/mkconfig.rb config.status $(PREP)
	@$(MINIRUBY) $(srcdir)/mkconfig.rb -timestamp=$@ \
		-install_name=$(RUBY_INSTALL_NAME) \
		-so_name=$(RUBY_SO_NAME) rbconfig.rb

encs: enc trans
encs enc trans: $(ENC_MK) $(LIBRUBY) $(PREP)
	$(MAKE) -f $(ENC_MK) RUBY="$(MINIRUBY)" MINIRUBY="$(MINIRUBY)" $(MFLAGS) $@

enc: encdb.h
trans: transdb.h

$(ENC_MK): $(srcdir)/enc/make_encmake.rb $(srcdir)/enc/Makefile.in $(srcdir)/enc/depend \
	$(srcdir)/lib/mkmf.rb $(RBCONFIG)
	$(MINIRUBY) $(srcdir)/enc/make_encmake.rb --builtin-encs="$(BUILTIN_ENCOBJS)" --builtin-transes="$(BUILTIN_TRANSOBJS)" $@ $(ENCS)

.PRECIOUS: $(MKFILES)

.PHONY: test install install-nodoc install-doc dist

PHONY:

parse.c: parse.y $(srcdir)/tool/ytab.sed
parse.h parse.h: parse.c

.y.c:
	$(YACC) -d $(YFLAGS) -o y.tab.c $(<:\\=/)
	sed -f $(srcdir)/tool/ytab.sed -e "/^#/s!y\.tab\.c!$@!" y.tab.c > $@.new
	@$(MV) $@.new $@
	sed -e "/^#line.*y\.tab\.h/d;/^#line.*parse\.y/d" y.tab.h > $(@:.c=.h).new
	@$(IFCHANGE) $(@:.c=.h) $(@:.c=.h).new
	@$(RM) y.tab.c y.tab.h

acosh.$(OBJEXT): acosh.c
alloca.$(OBJEXT): alloca.c config.h
crypt.$(OBJEXT): crypt.c
dup2.$(OBJEXT): dup2.c
erf.$(OBJEXT): erf.c
finite.$(OBJEXT): finite.c
flock.$(OBJEXT): flock.c
memcmp.$(OBJEXT): memcmp.c
memmove.$(OBJEXT): memmove.c
mkdir.$(OBJEXT): mkdir.c
strchr.$(OBJEXT): strchr.c
strdup.$(OBJEXT): strdup.c
strerror.$(OBJEXT): strerror.c
strstr.$(OBJEXT): strstr.c
strtod.$(OBJEXT): strtod.c
strtol.$(OBJEXT): strtol.c
nt.$(OBJEXT): nt.c
os2.$(OBJEXT): os2.c
dl_os2.$(OBJEXT): dl_os2.c
ia64.$(OBJEXT): ia64.s
	$(CC) $(CFLAGS) -c $<

# when I use -I., there is confliction at "OpenFile" 
# so, set . into environment varible "include"
win32.$(OBJEXT): win32.c $(RUBY_H_INCLUDES)

###

RUBY_H_INCLUDES    = ruby.h config.h defines.h \
		     intern.h missing.h st.h
ENCODING_H_INCLUDES= encoding.h oniguruma.h
ID_H_INCLUDES      = id.h
VM_CORE_H_INCLUDES = vm_core.h vm_opts.h \
	             thread_$(THREAD_MODEL).h \
		     node.h $(ID_H_INCLUDES)

array.$(OBJEXT): array.c $(RUBY_H_INCLUDES) util.h
bignum.$(OBJEXT): bignum.c $(RUBY_H_INCLUDES)
class.$(OBJEXT): class.c $(RUBY_H_INCLUDES) node.h
compar.$(OBJEXT): compar.c $(RUBY_H_INCLUDES)
complex.$(OBJEXT): complex.c $(RUBY_H_INCLUDES)
dir.$(OBJEXT): dir.c $(RUBY_H_INCLUDES) util.h \
  $(ENCODING_H_INCLUDES)
dln.$(OBJEXT): dln.c dln.h $(RUBY_H_INCLUDES)
dmydln.$(OBJEXT): dmydln.c dln.$(OBJEXT)
dmyext.$(OBJEXT): dmyext.c
dmyencoding.$(OBJEXT): dmyencoding.c $(RUBY_H_INCLUDES) \
  regenc.h util.h $(ENCODING_H_INCLUDES) \
  encoding.c
encoding.$(OBJEXT): encoding.c $(RUBY_H_INCLUDES) \
  $(ENCODING_H_INCLUDES) regenc.h util.h
enum.$(OBJEXT): enum.c $(RUBY_H_INCLUDES) node.h \
  util.h
enumerator.$(OBJEXT): enumerator.c $(RUBY_H_INCLUDES)
error.$(OBJEXT): error.c known_errors.inc $(RUBY_H_INCLUDES) \
  $(VM_CORE_H_INCLUDES) debug.h
eval.$(OBJEXT): eval.c eval_intern.h \
  $(RUBY_H_INCLUDES) $(VM_CORE_H_INCLUDES) eval_error.c \
  eval_jump.c debug.h \
  iseq.h
load.$(OBJEXT): load.c eval_intern.h \
  util.h $(RUBY_H_INCLUDES) $(VM_CORE_H_INCLUDES) \
  dln.h debug.h
file.$(OBJEXT): file.c $(RUBY_H_INCLUDES) io.h \
  $(ENCODING_H_INCLUDES) util.h dln.h
gc.$(OBJEXT): gc.c $(RUBY_H_INCLUDES) re.h \
  regex.h $(ENCODING_H_INCLUDES) $(VM_CORE_H_INCLUDES) \
  gc.h io.h eval_intern.h util.h \
  debug.h
hash.$(OBJEXT): hash.c $(RUBY_H_INCLUDES) util.h
inits.$(OBJEXT): inits.c $(RUBY_H_INCLUDES)
io.$(OBJEXT): io.c $(RUBY_H_INCLUDES) io.h \
  util.h $(ENCODING_H_INCLUDES)
main.$(OBJEXT): main.c $(RUBY_H_INCLUDES) debug.h \
  node.h
marshal.$(OBJEXT): marshal.c $(RUBY_H_INCLUDES) io.h \
  $(ENCODING_H_INCLUDES) util.h
math.$(OBJEXT): math.c $(RUBY_H_INCLUDES)
numeric.$(OBJEXT): numeric.c $(RUBY_H_INCLUDES) \
  $(ENCODING_H_INCLUDES)
object.$(OBJEXT): object.c $(RUBY_H_INCLUDES) util.h
pack.$(OBJEXT): pack.c $(RUBY_H_INCLUDES)
parse.$(OBJEXT): parse.c $(RUBY_H_INCLUDES) \
  node.h $(ENCODING_H_INCLUDES) $(ID_H_INCLUDES) \
  regenc.h regex.h util.h lex.c \
  defs/keywords id.c
proc.$(OBJEXT): proc.c eval_intern.h \
  $(RUBY_H_INCLUDES) gc.h $(VM_CORE_H_INCLUDES) \
  debug.h
process.$(OBJEXT): process.c $(RUBY_H_INCLUDES) \
  util.h io.h $(ENCODING_H_INCLUDES) dln.h \
  $(VM_CORE_H_INCLUDES) debug.h
random.$(OBJEXT): random.c $(RUBY_H_INCLUDES)
range.$(OBJEXT): range.c $(RUBY_H_INCLUDES) \
  $(ENCODING_H_INCLUDES)
rational.$(OBJEXT): rational.c $(RUBY_H_INCLUDES)
re.$(OBJEXT): re.c $(RUBY_H_INCLUDES) re.h \
  regex.h $(ENCODING_H_INCLUDES) util.h \
  regint.h regenc.h
regcomp.$(OBJEXT): regcomp.c regparse.h \
  regint.h regenc.h oniguruma.h \
  $(RUBY_H_INCLUDES)
regenc.$(OBJEXT): regenc.c regint.h \
  regenc.h oniguruma.h $(RUBY_H_INCLUDES)
regerror.$(OBJEXT): regerror.c regint.h \
  regenc.h oniguruma.h $(RUBY_H_INCLUDES)
regexec.$(OBJEXT): regexec.c regint.h \
  regenc.h oniguruma.h $(RUBY_H_INCLUDES)
regparse.$(OBJEXT): regparse.c regparse.h \
  regint.h regenc.h oniguruma.h \
  $(RUBY_H_INCLUDES)
regsyntax.$(OBJEXT): regsyntax.c regint.h \
  regenc.h oniguruma.h $(RUBY_H_INCLUDES)
ruby.$(OBJEXT): ruby.c $(RUBY_H_INCLUDES) util.h \
  $(ENCODING_H_INCLUDES) eval_intern.h $(VM_CORE_H_INCLUDES) \
  dln.h debug.h
safe.$(OBJEXT): safe.c $(RUBY_H_INCLUDES) \
  $(VM_CORE_H_INCLUDES) debug.h
signal.$(OBJEXT): signal.c $(RUBY_H_INCLUDES) \
  $(VM_CORE_H_INCLUDES) debug.h
sprintf.$(OBJEXT): sprintf.c $(RUBY_H_INCLUDES) re.h \
  regex.h vsnprintf.c $(ENCODING_H_INCLUDES)
st.$(OBJEXT): st.c config.h defines.h \
  st.h ruby.h missing.h intern.h
strftime.$(OBJEXT): strftime.c ruby.h \
  config.h defines.h missing.h \
  intern.h st.h
string.$(OBJEXT): string.c $(RUBY_H_INCLUDES) re.h \
  regex.h $(ENCODING_H_INCLUDES)
struct.$(OBJEXT): struct.c $(RUBY_H_INCLUDES)
thread.$(OBJEXT): thread.c eval_intern.h \
  $(RUBY_H_INCLUDES) gc.h $(VM_CORE_H_INCLUDES) \
  debug.h thread_$(THREAD_MODEL).c
transcode.$(OBJEXT): transcode.c $(RUBY_H_INCLUDES) \
  $(ENCODING_H_INCLUDES) transcode_data.h
cont.$(OBJEXT): cont.c $(RUBY_H_INCLUDES) \
  $(VM_CORE_H_INCLUDES) gc.h eval_intern.h \
  debug.h
time.$(OBJEXT): time.c $(RUBY_H_INCLUDES) \
  $(ENCODING_H_INCLUDES)
util.$(OBJEXT): util.c $(RUBY_H_INCLUDES) util.h
variable.$(OBJEXT): variable.c $(RUBY_H_INCLUDES) \
  node.h util.h
version.$(OBJEXT): version.c $(RUBY_H_INCLUDES) \
  version.h $(srcdir)/revision.h

compile.$(OBJEXT): compile.c iseq.h \
  $(RUBY_H_INCLUDES) $(VM_CORE_H_INCLUDES) insns.inc \
  insns_info.inc optinsn.inc debug.h
iseq.$(OBJEXT): iseq.c gc.h iseq.h \
  $(RUBY_H_INCLUDES) $(VM_CORE_H_INCLUDES) insns.inc \
  insns_info.inc node_name.inc debug.h
vm.$(OBJEXT): vm.c gc.h iseq.h \
  eval_intern.h $(RUBY_H_INCLUDES) $(ENCODING_H_INCLUDES) \
  $(VM_CORE_H_INCLUDES) vm_method.c vm_eval.c \
  vm_insnhelper.c vm_insnhelper.h vm_exec.c \
  vm_exec.h insns.def vmtc.inc \
  vm.inc insns.inc debug.h
vm_dump.$(OBJEXT): vm_dump.c $(RUBY_H_INCLUDES) \
  $(VM_CORE_H_INCLUDES) debug.h
debug.$(OBJEXT): debug.c $(RUBY_H_INCLUDES) \
  $(ENCODING_H_INCLUDES) $(VM_CORE_H_INCLUDES) eval_intern.h \
  util.h debug.h
id.$(OBJEXT): id.c $(RUBY_H_INCLUDES) $(ID_H_INCLUDES)
miniprelude.$(OBJEXT): miniprelude.c $(RUBY_H_INCLUDES) \
  $(VM_CORE_H_INCLUDES) debug.h
prelude.$(OBJEXT): prelude.c $(RUBY_H_INCLUDES) \
  $(VM_CORE_H_INCLUDES) debug.h
golf_prelude.$(OBJEXT): golf_prelude.c $(RUBY_H_INCLUDES) \
  $(VM_CORE_H_INCLUDES) debug.h
goruby.$(OBJEXT): goruby.c main.c $(RUBY_H_INCLUDES) \
  debug.h node.h

ascii.$(OBJEXT): ascii.c regenc.h config.h \
  defines.h oniguruma.h
us_ascii.$(OBJEXT): us_ascii.c regenc.h \
  config.h defines.h oniguruma.h
unicode.$(OBJEXT): unicode.c regint.h \
  config.h defines.h regenc.h \
  oniguruma.h st.h ruby.h \
  missing.h intern.h
utf_8.$(OBJEXT): utf_8.c regenc.h config.h \
  defines.h oniguruma.h

newline.c: $(srcdir)/enc/trans/newline.trans $(srcdir)/tool/transcode-tblgen.rb
newline.$(OBJEXT): newline.c defines.h \
  intern.h missing.h st.h \
  transcode_data.h ruby.h config.h

INSNS2VMOPT = --srcdir="$(srcdir)"

$(INSNS): $(srcdir)/insns.def vm_opts.h $(srcdir)/defs/opt_operand.def $(srcdir)/defs/opt_insn_unif.def

minsns.inc: $(srcdir)/template/minsns.inc.tmpl

opt_sc.inc: $(srcdir)/template/opt_sc.inc.tmpl

optinsn.inc: $(srcdir)/template/optinsn.inc.tmpl

optunifs.inc: $(srcdir)/template/optunifs.inc.tmpl

insns.inc: $(srcdir)/template/insns.inc.tmpl

insns_info.inc: $(srcdir)/template/insns_info.inc.tmpl

vmtc.inc: $(srcdir)/template/vmtc.inc.tmpl

vm.inc: $(srcdir)/template/vm.inc.tmpl

srcs: parse.c lex.c newline.c $(srcdir)/ext/ripper/ripper.c srcs-enc

srcs-enc: $(ENC_MK)
	$(MAKE) -f $(ENC_MK) RUBY="$(MINIRUBY)" MINIRUBY="$(MINIRUBY)" $(MFLAGS) srcs

incs: $(INSNS) node_name.inc encdb.h transdb.h known_errors.inc $(srcdir)/revision.h

insns: $(INSNS)

node_name.inc: node.h

encdb.h: $(PREP) $(srcdir)/tool/generic_erb.rb $(srcdir)/template/encdb.h.tmpl
	$(MINIRUBY) $(srcdir)/tool/generic_erb.rb -c -o $@ $(srcdir)/template/encdb.h.tmpl $(srcdir)/enc enc

transdb.h: $(PREP) srcs-enc $(srcdir)/tool/generic_erb.rb $(srcdir)/template/transdb.h.tmpl
	$(MINIRUBY) $(srcdir)/tool/generic_erb.rb -c -o $@ $(srcdir)/template/transdb.h.tmpl $(srcdir)/enc/trans enc/trans

# id.h: parse.h $(srcdir)/tool/generic_erb.rb $(srcdir)/template/id.h.tmpl
# 	$(BASERUBY) $(srcdir)/tool/generic_erb.rb --if-change --output=$@ \
# 		$(srcdir)/template/id.h.tmpl --vpath=$(VPATH) parse.h

known_errors.inc: $(srcdir)/template/known_errors.inc.tmpl $(srcdir)/defs/known_errors.def

miniprelude.c: $(srcdir)/tool/compile_prelude.rb $(srcdir)/prelude.rb

prelude.c: $(srcdir)/tool/compile_prelude.rb $(RBCONFIG) $(PRELUDE_SCRIPTS) $(PREP)
	$(COMPILE_PRELUDE) $(PRELUDE_SCRIPTS) $@

golf_prelude.c: $(srcdir)/tool/compile_prelude.rb $(RBCONFIG) $(srcdir)/prelude.rb $(srcdir)/golf_prelude.rb $(PREP)
	$(COMPILE_PRELUDE) $(srcdir)/golf_prelude.rb $@

prereq: incs srcs preludes

preludes: miniprelude.c
preludes: golf_prelude.c

$(srcdir)/revision.h: $(srcdir)/version.h $(srcdir)/ChangeLog $(srcdir)/tool/file2lastrev.rb $(REVISION_FORCE)
	@-$(BASERUBY) $(srcdir)/tool/file2lastrev.rb --revision.h "$(@D)" > "$@.tmp"
	@$(IFCHANGE) "$@" "$@.tmp"

$(srcdir)/ext/ripper/ripper.c:
	cd $(srcdir)/ext/ripper && exec $(MAKE) -f depend $(MFLAGS) top_srcdir=../.. srcdir=.

##

run: miniruby$(EXEEXT) PHONY
	$(MINIRUBY) $(TESTRUN_SCRIPT) $(RUNOPT)

runruby: $(PROGRAM) PHONY
	$(RUNRUBY) $(TESTRUN_SCRIPT)

parse: miniruby$(EXEEXT) PHONY
	$(MINIRUBY) $(srcdir)/tool/parse.rb $(TESTRUN_SCRIPT)

COMPARE_RUBY = $(BASERUBY)
ITEM = 
OPTS = 

benchmark: $(PROGRAM) PHONY
	$(BASERUBY) $(srcdir)/benchmark/driver.rb -v \
	            --executables="$(COMPARE_RUBY); $(RUNRUBY)" \
	            --pattern='bm_' --directory=$(srcdir)/benchmark $(OPTS)

benchmark-each: $(PROGRAM) PHONY
	$(BASERUBY) $(srcdir)/benchmark/driver.rb -v \
	            --executables="$(COMPARE_RUBY); $(RUNRUBY)" \
	            --pattern=$(ITEM) --directory=$(srcdir)/benchmark $(OPTS)

tbench: $(PROGRAM) PHONY
	$(BASERUBY) $(srcdir)/benchmark/driver.rb -v \
	            --executables="$(COMPARE_RUBY); $(RUNRUBY)" \
	            --pattern='bmx_' --directory=$(srcdir)/benchmark $(OPTS)

run.gdb:
	echo b ruby_debug_breakpoint           > run.gdb
	echo '# handle SIGINT nostop'         >> run.gdb
	echo '# handle SIGPIPE nostop'        >> run.gdb
	echo '# b rb_longjmp'                 >> run.gdb
	echo source $(srcdir)/breakpoints.gdb >> run.gdb
	echo source $(srcdir)/.gdbinit        >> run.gdb
	echo run                              >> run.gdb

gdb: miniruby$(EXEEXT) run.gdb PHONY
	gdb -x run.gdb --quiet --args $(MINIRUBY) $(TESTRUN_SCRIPT)

gdb-ruby: $(PROGRAM) run.gdb PHONY
	gdb -x run.gdb --quiet --args $(PROGRAM) $(TESTRUN_SCRIPT)

dist:
	$(BASERUBY) $(srcdir)/tool/make-snapshot tmp $(RELNAME)

up::
	-@$(MAKE) $(MFLAGS) REVISION_FORCE=PHONY "$(srcdir)/revision.h"

help: PHONY
	@echo "                Makefile of Ruby"
	@echo ""
	@echo "targets:"
	@echo "  all (default):   builds ruby"
	@echo "  miniruby:        builds only miniruby"
	@echo "  run:             runs test.rb by miniruby"
	@echo "  runruby:         runs test.rb by ruby you just built"
	@echo "  gdb:             runs test.rb by miniruby under gdb"
	@echo "  gdb-ruby:        runs test.rb by ruby under gdb"
	@echo "  all:             compile ruby and extensions"
	@echo "  check:           equals make test test-all"
	@echo "  test:            ruby core tests"
	@echo "  test-all:        all ruby tests"
	@echo "  test-rubyspec    run RubySpec test suite"
	@echo "  update-rubyspec  update local copy of RubySpec"
	@echo "  install:         install all ruby distributions"
	@echo "  install-nodoc:   install without rdoc"
	@echo "  clean:           clean built objects"
	@echo "  golf:            for golfers"
	@echo
	@echo "see DeveloperHowto for more detail: "
	@echo "  http://redmine.ruby-lang.org/wiki/ruby/DeveloperHowto"
