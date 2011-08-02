class A
  def main
    method1
  end
 
  private
  def method1
    puts "hello from #{A}"
  end
end
 
class B < A
  def main
    method1
  end
end
 # private methods can call from only class which they belongs so call it through the class
A.new.main
B.new.main
