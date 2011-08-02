class New
	def print(name)
	@name = name
	puts "enter your age  "
	puts "#{@name} is #{@age = gets.chop} "
	end
end
New.class_exec{ def details() puts "these are legal details of the user" end }
New.class_exec{ def operate(num1,num2) @num1,@num2 = num1,num2 
			puts "#{@num1.to_i + @num2.to_i}" 
					 end }
New.new.details()
New.new.print("sriram")
New.new.operate(23,32)


