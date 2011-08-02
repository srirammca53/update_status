class Arthematic

	def add()
	puts "enter any two numbers"
	@num1=gets()
	@num2=gets()
	@num3=@num1.to_i+@num2.to_i
	puts "the total addition by your numbers #@num3"
	end

	def sub()
	puts "enter any two numbers"
	@num1=gets()
	@num2=gets()
	@num3=@num1.to_i-@num2.to_i
	puts "the total substraction by your numbers #@num3"
	end

	def mul()
	puts "enter any two numbers"
	@num1=gets()
	@num2=gets()
	@num3=@num1.to_i*@num2.to_i
	puts "the total multiplication by your numbers #@num3"
	end

	def div()
	puts "enter any two numbers"
	@num1=gets()
	@num2=gets()
	@num3=@num1.to_i/@num2.to_i
	puts "the total addition by your numbers #@num3"
	end

end

obj1 = Arthematic.new()

obj1.add()
obj1.sub()
obj1.mul()
obj1.div()
