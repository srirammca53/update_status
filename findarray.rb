class Findarray

def find(n)
@range=n
puts "The number which are divisable by 5 and 7 from 1 to :#@range"
(1..@range).detect {|i| i%5 == 0 and i%7 == 0}
print i
end
end

puts " enter the range to find the numbers divisable by 5 and 7"
r=gets.chop
puts " you entered :"+r.to_i

c1 = Findarray.new()
c1.find(r)

