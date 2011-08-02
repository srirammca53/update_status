class Event

def check()
	puts "Enter the score details of each participant "
	arr1 = []
	puts "No of stages cleared by participant 1"
	@s = gets()
	
	puts "enter name"
	@name1 = gets()
	arr1.push(@name1)
	puts "please enter the scores of participant1"
		for @i in 1..@s.to_i
		@val = gets()
		arr1<<@val
		end
	puts "The score details"
	puts arr1

	arr2 = []
	puts "No of stages cleared by participant 2"
	@s1 = gets()
	
	puts "enter name"
	@name2 = gets()
	arr2.push(@name2)
	puts "please enter the scores of participant2"	
		for @i1 in 1..@s1.to_i
		@val1 = gets()
		arr2<<@val1
		end
	puts "The score details"
	puts arr2

	arr3 = []
	puts "No of stages cleared by participant 3"
	@s2 = gets()
	
	puts "enter name"
	@name3 = gets()
	arr3.push(@name3)
	puts "please enter the scores of participant 3"
		for @i2 in 1..@s2.to_i
		@val2 = gets()
		arr3<<@val2
		end
	puts "The score details"
	puts arr3

	arr4 = []
	puts "No of stages cleared by participant 4"
	@s3 = gets()
	puts "enter name"
	@name4 = gets()
	arr4.push(@name4)
	puts "please enter the scores of participant 4"
		for @i3 in 1..@s3.to_i
		@val3 = gets()
		arr4<<@val3
		end
	puts "The score details"
	puts arr4
arr5 = []
if(@s.to_i > 2)
puts "#@name1 is qualified for semis round"
arr5.push(arr1)
else
puts  "#@name1 is terminated"
end

if(@s1.to_i > 2)
puts "#@name2 is  qualified for semis round"
arr5.push(arr2)
else
puts  "#@name2 is terminated"
end

if(@s2.to_i > 2)
puts "#@name3 is qualified for semis round"
arr5.push(arr3)
else
puts  "#@name3 is terminated"
end

if(@s3.to_i > 2)
puts "#@name4 is qualified for semis round"
arr5.push(arr4)
else
puts  "#@name4 is terminated"
end
 
puts "the total participants to semis and there scores"
puts arr5



end




end

c1 = Flat.new()
c1.check()

