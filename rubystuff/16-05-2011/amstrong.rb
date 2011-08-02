class Amstrong

	def result()
	puts "please enter a number  to check it whether it is amstrong or not"
	@str = gets.chop
	puts @str
	@s = @str.length
	@n = @str.to_i
	puts @s
	@i=0
	@total = 0
	@pro = 0
	while ( @i < @s)
	@reminder = @str.to_i % 10
	
	@pro += (@reminder * @reminder *@reminder)
	@str = @str.to_i / 10
	@i+=1
	end
	puts @pro
	if( @pro == @n )
	puts "its amstrong number"
	else
	puts "not an amstrong number"
	end
	

	end
end

c1 = Amstrong.new()
c1.result()
