#! /usr/local/bin/ruby

require 'uconv'
include Uconv

## 補助漢字ハンドラ
def Uconv.unknown_euc_handler(e)
  ## 〓 (GETA MARK) に置換え
  return 0x3013
end

## バイトオーダーマーク
print "\xff\xfe"
while ($<.gets)
  print euctou2($_);
end
