class Nomethod

def add
puts "adding two number please enter two numbers one by one"
@num1 = gets.chop
@num2 = gets.chop
@num3 = @num1.to_i + @num2.to_i 
puts @num3
end
def method_missing(m, *args ,&block)
puts "No such method available here so please carry on"
end
end

c1 = Nomethod.new()
c1.add
c1.sub
class Nomethod
def sub
@num3 = @num1.to_i - @num2.to_i 
puts @num3
end
end
c1.sub
