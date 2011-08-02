# program to read content from exixting file and count the no of words

puts "enter a file name:"
fname = gets.chop
afile = File.open("#{fname}.txt","r")
yes = File.exists?("#{fname}.txt")

if yes.to_s == "true"
counts = afile.readlines("#{fname}.txt")
word = (counts.to_s).split(" ")
a = word
puts a.size
puts a
puts "No Of words in the file #{word.length}"
else
puts " File not found"
end
