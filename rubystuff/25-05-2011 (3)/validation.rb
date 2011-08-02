# program on Validation example in exception handling


class Validation

	def details
	puts "enter the details"
	puts "enter your name" 
	@name =gets.chop
		if @name == nil or @name.size == 0
		raise ArgumentError.new("the name should not be empty")
		end
	puts "enter your age"
	@age = gets.chop
		if @age == nil or @age.size == 0
		raise ArgumentError.new("the age should not be empty")
		end
	end
	def average(num1,num2)
	@num1 = num1.to_i
	@num2 = num2.to_i
		@avg = (@num1 * 100) / @num2
		puts @avg
		if @num2 == nil or @num2 == 0
			begin
				raise "zero division erroer in calculating average"
				rescue 
				puts "standard error"
				ensure
				puts @avg				
			end
	        end
	puts @avg
		
	end
	

end
Validation.new.details
Validation.new.display
puts "enter your marks and total marks"
marks = gets.chop
total = gets.chop
Validation.new.average(marks,total)
