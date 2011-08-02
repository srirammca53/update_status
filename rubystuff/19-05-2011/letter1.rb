# program to generate a dynamic leave letter taking details from user


class Letter

def leave()

f = File.open("leaveletter.txt","a+")
arr = IO.readlines("leaveletter.txt")
arr_count = IO.readlines("leaveletter.txt").count

puts "enter your name"
name = gets.chop
for i in 1..arr_count.to_i
puts arr[i]
if (arr[i] == 'I,')

arr[i] = arr[i]<<(name)
puts arr[i]


puts f
end
end


f.close
end

end

c1 = Letter.new()
c1.leave()

