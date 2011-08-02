class Switchcase



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

puts "1.add,2.sub,3.mul,4.div"

puts "enter your choice"
ch=gets()

case(ch.to_i)
when (1)
obj1.add()
when (2)
obj1.sub()
when (3)
obj1.mul()
when (4)
obj1.div()
else
puts "wrong choice"
end
