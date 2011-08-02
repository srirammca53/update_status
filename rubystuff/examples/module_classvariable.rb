
class A
  ACONST = "aconst"

  def self.const_missing(constant)
    puts "A MISSING"
    constant == :AMISS ? "amiss" : super
  end  
end

class B < A
  BCONST = "bconst"
  
  def self.const_missing(constant)
    puts "B MISSING"
    constant == :BMISS ? "bmiss" : super
  end
end

class C
end

A::FOO
A::ACONST
A::AMISS
A::BCONST
A::BMISS

B::FOO
B::ACONST
B::AMISS
B::BCONST
B::BMISS

C::FOO

