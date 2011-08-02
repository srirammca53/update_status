class Power

	def result(n)

	@n = n
	@res = @n.to_i
	puts @n
	puts "enter a power number to get the value "
	@power = gets.chop
	@i = 1
		while (@i < @power.to_i)
		@res*=@res
		@i+=1
		end
	puts @res
	end

end

c1 = Power.new()
puts "please enter a number "
num = gets.chop

c1.result(num)
