class Swapwtv

def swap_it(a,b)
@d=a+b
@e=a-b
a=@d
b=@e
a=@e+b

puts "The variables After swapping:"
puts "The first variable after swapping :"+a
puts "The second variable after swapping :"+b
end

end
puts "enter two variables to swap"

puts "enter first varialble:"
v1=gets.chop
puts "enter second varialble:"
v2=gets.chop
puts "Variables before swapping:"
puts "variable 1:"+v1

puts "variable 2:"+v2

sw = Swapwtv.new()
sw.swap_it(v1,v2)

