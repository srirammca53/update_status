require 'runit/testcase'
require 'runit/cui/testrunner'

class UconvTest < RUNIT::TestCase
  REPLACEMENT_CHAR_U32 = "\xfd\xff\x00\x00"
  REPLACEMENT_CHAR_U16 = "\xfd\xff"
  REPLACEMENT_CHAR_U8 = "\xef\xbf\xbd"


  require 'uconv'

  def to_hex(str)
    ret = ""
    str.each_byte do |c|
      ret << format("%02X", c)
    end
    ret
  end

  def setup
    Uconv::replace_invalid = Uconv::REPLACEMENT_CHAR
  end

  def test_00
    Uconv::shortest = true
    assert_equal(Uconv.u8tou16("\xc0\x80"), REPLACEMENT_CHAR_U16)
    assert_equal(Uconv.u8tou16("\xc1\x80"), REPLACEMENT_CHAR_U16)
    assert_equal(Uconv.u8tou16("\xc2\x80"), "\x80\x00")
  end

  def test_01
    Uconv::shortest = true
    assert_equal(Uconv.u8tou16("\xe0\x80\x80"), REPLACEMENT_CHAR_U16)
    assert_equal(Uconv.u8tou16("\xe0\x9f\x80"), REPLACEMENT_CHAR_U16)
    assert_equal(Uconv.u8tou16("\xe0\xa0\x80"), "\x00\x08")
    assert_equal(Uconv.u8tou16("\xe1\x80\x80"), "\x00\x10")
  end

  def test_02
    Uconv::shortest = true
    assert_equal(Uconv.u8tou16("\xf0\x8f\x80\x80"), REPLACEMENT_CHAR_U16)
    assert_equal(Uconv.u8tou16("\xf0\x90\x80\x80"), "\x00\xd8\x00\xdc")
    assert_equal(Uconv.u8tou16("\xf1\x80\x80\x80"), "\xc0\xd8\x00\xdc")
    assert_equal(Uconv.u8tou16("\xf4\x8f\xbf\xbf"), "\xff\xdb\xff\xdf")
    assert_equal(Uconv.u8tou16("\xf4\x90\x80\x80"), REPLACEMENT_CHAR_U16)
  end


  def test_10
    Uconv::shortest = true
    assert_equal(Uconv.u8tou4("\xc0\x80"), REPLACEMENT_CHAR_U32)
    assert_equal(Uconv.u8tou4("\xc1\x80"), REPLACEMENT_CHAR_U32)
    assert_equal(Uconv.u8tou4("\xc2\x80"), "\x80\x00\x00\x00")
  end

  def test_11
    Uconv::shortest = true
    assert_equal(Uconv.u8tou4("\xe0\x80\x80"), REPLACEMENT_CHAR_U32)
    assert_equal(Uconv.u8tou4("\xe0\x9f\x80"), REPLACEMENT_CHAR_U32)
    assert_equal(Uconv.u8tou4("\xe0\xa0\x80"), "\x00\x08\x00\x00")
    assert_equal(Uconv.u8tou4("\xe1\x80\x80"), "\x00\x10\x00\x00")
  end

  def test_12
    Uconv::shortest = true
    assert_equal(Uconv.u8tou4("\xf0\x8f\x80\x80"), REPLACEMENT_CHAR_U32)
    assert_equal(Uconv.u8tou4("\xf0\x90\x80\x80"), "\x00\x00\x01\x00")
    assert_equal(Uconv.u8tou4("\xf1\x80\x80\x80"), "\x00\x00\x04\x00")
    assert_equal(Uconv.u8tou4("\xf4\x8f\xbf\xbf"), "\xff\xff\x10\x00")
  end

  def test_13
    Uconv::shortest = true
    assert_equal(Uconv.u8tou4("\xf8\x87\x80\x80\x80"), REPLACEMENT_CHAR_U32)
    assert_equal(Uconv.u8tou4("\xf8\x88\x80\x80\x80"), "\x00\x00\x20\x00")
    assert_equal(Uconv.u8tou4("\xf9\x80\x80\x80\x80"), "\x00\x00\x00\x01")
  end

  def test_14
    Uconv::shortest = true
    assert_equal(Uconv.u8tou4("\xfc\x83\x80\x80\x80\x80"), REPLACEMENT_CHAR_U32)
    assert_equal(Uconv.u8tou4("\xfc\x84\x80\x80\x80\x80"), "\x00\x00\x00\x04")
    assert_equal(Uconv.u8tou4("\xfd\x80\x80\x80\x80\x80"), "\x00\x00\x00\x40")
    assert_equal(Uconv.u8tou4("\xfd\xbf\xbf\xbf\xbf\xbf"), "\xff\xff\xff\x7f")
    assert_equal(Uconv.u8tou4("\xfe\x80\x80\x80\x80\x80\x80"),
                 REPLACEMENT_CHAR_U32 * 7)
  end



  def test_20
    Uconv::shortest = false
    assert_equal(Uconv.u8tou16("\xc0\x80"), "\x00\x00")
    assert_equal(Uconv.u8tou16("\xc1\x80"), "\x40\x00")
    assert_equal(Uconv.u8tou16("\xc2\x80"), "\x80\x00")
  end

  def test_21
    Uconv::shortest = false
    assert_equal(Uconv.u8tou16("\xe0\x80\x80"), "\x00\x00")
    assert_equal(Uconv.u8tou16("\xe0\x9f\x80"), "\xc0\x07")
    assert_equal(Uconv.u8tou16("\xe0\xa0\x80"), "\x00\x08")
    assert_equal(Uconv.u8tou16("\xe1\x80\x80"), "\x00\x10")
  end

  def test_22
    Uconv::shortest = false
    assert_equal(Uconv.u8tou16("\xf0\x8f\x80\x80"), "\x00\xf0")
    assert_equal(Uconv.u8tou16("\xf0\x90\x80\x80"), "\x00\xd8\x00\xdc")
    assert_equal(Uconv.u8tou16("\xf1\x80\x80\x80"), "\xc0\xd8\x00\xdc")
    assert_equal(Uconv.u8tou16("\xf4\x8f\xbf\xbf"), "\xff\xdb\xff\xdf")
    assert_equal(Uconv.u8tou16("\xf4\x90\x80\x80"), REPLACEMENT_CHAR_U16)
  end


  def test_30
    Uconv::shortest = false
    assert_equal(Uconv.u8tou4("\xc0\x80"), "\x00\x00\x00\x00")
    assert_equal(Uconv.u8tou4("\xc1\x80"), "\x40\x00\x00\x00")
    assert_equal(Uconv.u8tou4("\xc2\x80"), "\x80\x00\x00\x00")
  end

  def test_31
    Uconv::shortest = false
    assert_equal(Uconv.u8tou4("\xe0\x80\x80"), "\x00\x00\x00\x00")
    assert_equal(Uconv.u8tou4("\xe0\x9f\x80"), "\xc0\x07\x00\x00")
    assert_equal(Uconv.u8tou4("\xe0\xa0\x80"), "\x00\x08\x00\x00")
    assert_equal(Uconv.u8tou4("\xe1\x80\x80"), "\x00\x10\x00\x00")
  end

  def test_32
    Uconv::shortest = false
    assert_equal(Uconv.u8tou4("\xf0\x8f\x80\x80"), "\x00\xf0\x00\x00")
    assert_equal(Uconv.u8tou4("\xf0\x90\x80\x80"), "\x00\x00\x01\x00")
    assert_equal(Uconv.u8tou4("\xf1\x80\x80\x80"), "\x00\x00\x04\x00")
    assert_equal(Uconv.u8tou4("\xf4\x8f\xbf\xbf"), "\xff\xff\x10\x00")
  end

  def test_33
    Uconv::shortest = false
    assert_equal(Uconv.u8tou4("\xf8\x87\x80\x80\x80"), "\x00\x00\x1c\x00")
    assert_equal(Uconv.u8tou4("\xf8\x88\x80\x80\x80"), "\x00\x00\x20\x00")
    assert_equal(Uconv.u8tou4("\xf9\x80\x80\x80\x80"), "\x00\x00\x00\x01")
  end

  def test_34
    Uconv::shortest = false
    assert_equal(Uconv.u8tou4("\xfc\x83\x80\x80\x80\x80"), "\x00\x00\x00\x03")
    assert_equal(Uconv.u8tou4("\xfc\x84\x80\x80\x80\x80"), "\x00\x00\x00\x04")
    assert_equal(Uconv.u8tou4("\xfd\x80\x80\x80\x80\x80"), "\x00\x00\x00\x40")
    assert_equal(Uconv.u8tou4("\xfd\xbf\xbf\xbf\xbf\xbf"), "\xff\xff\xff\x7f")
    assert_equal(Uconv.u8tou4("\xfe\x80\x80\x80\x80\x80\x80"),
                 REPLACEMENT_CHAR_U32 * 7)
  end

  def test_40
    Uconv::shortest = false
    assert_equal(Uconv.u16tou8("\x00\xd8"), REPLACEMENT_CHAR_U8)
    assert_equal(Uconv.u16tou8("\x00\xdc"), REPLACEMENT_CHAR_U8)
    assert_equal(Uconv.u16tou8("\x00\xd8\x20\x00"),
                 REPLACEMENT_CHAR_U8 + "\x20")
    assert_equal(Uconv.u16tou8("\x00\xdc\x20\x00"),
                 REPLACEMENT_CHAR_U8 + "\x20")
  end

  def test_41
    Uconv::shortest = false
    assert_equal(Uconv.u4tou8("\x00\xd8\x00\x00"), REPLACEMENT_CHAR_U8)
    assert_equal(Uconv.u4tou8("\x00\xdc\x00\x00"), REPLACEMENT_CHAR_U8)
    assert_equal(Uconv.u4tou8("\x00\xd8\x00\x00\x20\x00\x00\x00"),
                 REPLACEMENT_CHAR_U8 + "\x20")
    assert_equal(Uconv.u4tou8("\x00\xdc\x00\x00\x20\x00\x00\x00"),
                 REPLACEMENT_CHAR_U8 + "\x20")
  end

  def test_42
    Uconv::shortest = false
    assert_equal(Uconv.u4tou16("\x00\xd8\x00\x00"), REPLACEMENT_CHAR_U16)
    assert_equal(Uconv.u4tou16("\x00\xdc\x00\x00"), REPLACEMENT_CHAR_U16)
    assert_equal(Uconv.u4tou16("\x00\xd8\x00\x00\x20\x00\x00\x00"),
                 REPLACEMENT_CHAR_U16 + "\x20\x00")
    assert_equal(Uconv.u4tou16("\x00\xdc\x00\x00\x20\x00\x00\x00"),
                 REPLACEMENT_CHAR_U16 + "\x20\x00")
    assert_equal(Uconv.u4tou16("\xff\xff\x10\x00"),
                 "\xff\xdb\xff\xdf")
    assert_equal(Uconv.u4tou16("\x00\x00\x11\x00"),
                 REPLACEMENT_CHAR_U16)
  end

  def test_43
    Uconv::shortest = false
    assert_equal(Uconv.u16tou4("\x00\xd8"), REPLACEMENT_CHAR_U32)
    assert_equal(Uconv.u16tou4("\x00\xdc"), REPLACEMENT_CHAR_U32)
    assert_equal(Uconv.u16tou4("\x00\xd8\x20\x00"),
                 REPLACEMENT_CHAR_U32 + "\x20\x00\x00\x00")
    assert_equal(Uconv.u16tou4("\x00\xdc\x20\x00"),
                 REPLACEMENT_CHAR_U32 + "\x20\x00\x00\x00")
  end

end

RUNIT::CUI::TestRunner.run(UconvTest.suite)
