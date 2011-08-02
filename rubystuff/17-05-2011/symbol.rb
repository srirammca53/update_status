
	
class Symbolexmp

	def check()
	puts "enter the name"
	@str = gets.chop
	puts @str.to_sym
		if (@str == @str.to_sym)
		puts "equal"
		else
		puts "not equal"
		end
	puts "The object id of the given string #{@str.object_id} "
	puts "The object id of the symbol belongs to the string #{(@str.to_sym).object_id}"
	@symbol = @str.to_sym
		if (@symbol == @str)
		puts "the string and the symbol are equal at values"
			elsif(@symbol.object_id == @str.object_id)
			puts "the string and the symbol are equal at Object id"
			else
			puts "not equal"
			
		end
	

	end


end

c1 = Symbolexmp.new()
c1.check()

