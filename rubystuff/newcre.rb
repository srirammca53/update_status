file = File.open("sriram.txt" , "r+")
puts file
size =  IO.readlines("sriram.txt").size
ar = IO.readlines("sriram.txt")
for i in 0..size.to_i
firstline =  ar[i].split(" ")
lsize = firstline.size
for j in 0..lsize.to_i
if firstline[j] == "rr"
puts "enter a number"
@num = gets.chop
firstline[j] = "#{@num}"
end
end
end
puts file
