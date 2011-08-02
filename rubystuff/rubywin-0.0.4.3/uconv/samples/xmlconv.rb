#! /usr/local/bin/ruby

## XML encoding converter
## 1998 by yoshidam
##
## XML ファイルのエンコーディングを EUC-JP に変換します。
## 変換できない文字は文字参照に置き換えます。

require 'kconv'
include Kconv
require 'uconv'
include Uconv

def Uconv.unknown_unicode_handler(u)
  return "&#x#{format('%04x', u)};"
end

## empty file
if ((xml = $<.gets).nil?); exit 1; end

$KCODE="NONE" 
## rewrite encoding in XML decl.
if xml =~ /^<\?xml\sversion=.+\sencoding=.EUC-JP./i
  $stderr.print "This file is already EUC-JP.\n"
  exit 1
elsif xml =~ /^<\?xml\sversion=.+\sencoding=.Shift_JIS./i
  xml.sub!(/Shift_JIS/i, "EUC-JP")
  encoding = "Shift_JIS"
elsif xml =~ /^<\?xml\sversion=.+\sencoding=.ISO-2022-JP./i
  xml.sub!(/ISO-2022-JP/i, "EUC-JP")
  encoding = "ISO-2022-JP"
elsif xml =~ /^<\?xml\sversion=.+\sencoding=.UTF-8./i
  xml.sub!(/UTF-8/i, "EUC-JP")
  encoding = "UTF-8"
elsif xml =~ /^<\?xml(\sversion=.+)?\s*\?>/i
  xml.sub!(/^<\?(.*)\?>/, "<?xml version='1.0' encoding='EUC-JP'?>")
  encoding = "UTF-8"
elsif xml =~ /^\377\376/
  encoding = "UTF-16-LE"
elsif xml !~ /^<\?xml/i
  xml.sub!(/^/, "<?xml version='1.0' encoding='EUC-JP'?>\n")
  encoding = "UTF-8"
else
  $stderr.print "Unknown encoding\n"
  exit 2
end
p encoding

## read body
xml += String($<.read)

## convert body encoding
if encoding == "Shift_JIS"
  xml = euctou8(kconv(xml, EUC, SJIS))
elsif encoding == "ISO-2022-JP"
  xml = euctou8(kconv(xml, EUC, JIS))
end
if encoding == "UTF-16-LE"
  print u2toeuc(xml)
else
  print u8toeuc(xml)
end
