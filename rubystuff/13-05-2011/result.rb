class Result

$total
	def details()
			
	puts "enter name of the student Name"
	@name = gets()
	marks = []
	puts "enter how many subjects you have"
	@i=gets()
	puts "you have total:#@i subjects"
	puts "enter your subject marks one by one"
	@total=0
		for @t in 1..@i.to_i
		marks[@t]=gets.chop
		puts "subject#@t :"+marks[@t]
		@total=@total + marks[@t].to_i
		end
	puts "total marks of the subjects #@name scored is   :#@total"
	@avg = @total.to_i/@i.to_i
	puts "Percentage of marks :#@avg "
		@flag = 0
		for @t in 1..@i.to_i
			if(marks[@t].to_i<35)
			@flag = @flag.to_i + 1
			break
			else
			@flag = 0
			end
			
		end
			if(@flag.to_i==0)
			puts "The final result is pass"
			end
			if(@flag.to_i >=1)
			puts "The final result is fail"
			end
	 end
	
	


end

c1 = Result.new()
puts "Total number of students in the class"
nos = gets.chop
j=1
for j in 1..nos.to_i
c1.details()
end



