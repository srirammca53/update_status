#
# rwinit.rb
# 
# This file is autoloaded by RubyWin to initialize RubyWin Environment

require 'mkmf'

bindir = CONFIG["bindir"]
Config::expand(bindir)
if File.exist?("#{bindir}/rwlib/irb/input-method.rb")
  $LOAD_PATH.unshift("#{bindir}/rwlib")
elsif File.exist?("#{Dir.pwd}/rwlib/irb/input-method.rb")
  $LOAD_PATH.unshift("#{Dir.pwd}/rwlib")
end

# Ruby supports "SJIS", "EUC", "UTF-8" for Japanese User. 
# But RubyWin supports only "UTF-8" for Japanese User.
# If You don't use Japanese-Kanji, set $KCODE = "N"
$KCODE = "UTF8"

#------------------------------------------------
# for Japanese-Kanji(SJIS)
# REMARK!!! THESE FUNCTIONS ARE ALPHA VERSION!!!
#
# Japanese-Kanji Auto Judgement
# If RubyWin.auto_judge_jcode is true, then
# RubyWin judges SJIS code of file automatically.
#
RubyWin.auto_judge_jcode = true;
#
# Setting Default File IO Code
# If RubyWin::Buffer.default_fileio_code is "SJIS"
# then RubyWin saves file using SJIS code.
#
RubyWin::Buffer.default_fileio_code = "SJIS"
#
# -------------------------------------------------

# for emulation STDOUT, STDERR
class RW_CONSOLE
  public :print
  public :printf
  public :puts
end

module RUBYWIN
  LOAD_TIME = {}
  alias org_require require
  def full_path_of_library(feature)
    $LOAD_PATH.each do |dir|
      if File.exist?(dir + "/" + feature)
        return dir + "/" + feature
      end
    end
    nil
  end

  def loaded?(feature)
    $".collect{|f|
      f.sub(/\.[^\.]+$/, "")
    }.include?(feature)
  end
    
  def re_require(feature)
    $".delete_if{|f| f == feature + ".rb"}
    org_require feature
  end

  def new_require(feature)
    ret = false
    path = full_path_of_library(feature + ".rb")
    if !path
      ret = org_require(feature)
    else
      if loaded?(feature)
        if File.mtime(path) > LOAD_TIME[path]
          LOAD_TIME[path] = File.mtime(path)
          ret = re_require(feature)
        else
          LOAD_TIME[path] = File.mtime(path)
          ret = org_require(feature)
        end
      else
        LOAD_TIME[path] = File.mtime(path)
        ret = org_require(feature)
      end
    end
    ret
  end
  module_function :new_require, :full_path_of_library
  module_function :loaded?, :re_require
end

# if you want overload original `require' method,
# then set USING_RUBYWIN_REQUIRE true (AT YOUR OWN RISK!!!)
USING_RUBYWIN_REQUIRE = false
if USING_RUBYWIN_REQUIRE  
  def new_require(feature)
    RUBYWIN::new_require(feature)
  end
  alias org_require require
  alias require new_require
end

