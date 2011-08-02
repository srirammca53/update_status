class Findarray
	def find(n)
	@range=n.to_i
	puts "The number which are divisable by 5 and 7 from 1 to #@range"

	puts "select method  iterate until the end of  list is reached and returns all if the block returned true" 
	puts (1..@range).select {|i| i%5 == 0 and i%7 == 0}
	puts "Detect also one method which detects the element up to condition becomes true at first time and stops"
	puts (1..@range).detect {|i| i%5 == 0 and i%7 == 0}
	end
end
puts " enter the range to find the numbers divisable by 5 and 7"
r=gets()
puts " you entered :"+r
c1 = Findarray.new()
c1.find(r)

