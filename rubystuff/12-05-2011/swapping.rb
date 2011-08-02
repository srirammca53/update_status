class Swapping

def swap_it(a,b)
@temp=a
a=b
b=@temp

puts "The variables After swapping:"
puts "The first variable after swapping :"+a
puts "The second variable after swapping :"+b

end

end
puts "enter two variables to swap"

puts "enter first varialble:"
v1=gets()
puts "enter second varialble:"
v2=gets()
puts "Variables before swapping:"
puts "variable 1:"+v1

puts "variable 2:"+v2

sw = Swapping.new()
sw.swap_it(v1,v2)

