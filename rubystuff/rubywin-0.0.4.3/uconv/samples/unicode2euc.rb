#! /usr/local/bin/ruby

require 'uconv'
include Uconv

## 無変換文字ハンドラ
def Uconv.unknown_unicode_handler(u)
  ## 〓 (GETA MARK) に置換え
  return '〓'
end

line = $<.read
if line =~ /^\xff\xfe/
  print u2toeuc(line)
elsif (line =~ /^\xfe\xff/)
  print u2toeuc(u2swap(line))
else
  print u8toeuc(line)
end
