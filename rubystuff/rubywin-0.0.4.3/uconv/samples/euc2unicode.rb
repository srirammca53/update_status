#! /usr/local/bin/ruby

require 'uconv'
include Uconv

## ��������ϥ�ɥ�
def Uconv.unknown_euc_handler(e)
  ## �� (GETA MARK) ���ִ���
  return 0x3013
end

## �Х��ȥ��������ޡ���
print "\xff\xfe"
while ($<.gets)
  print euctou2($_);
end
