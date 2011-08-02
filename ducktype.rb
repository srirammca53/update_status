class Ducktp
	def add
	   @num1 = 12
	   @num2 = 24
	   puts "#{@num2.to_i} + #{@num2.to_i}"
	end
	def sub
	   @num1 = 12
	   @num2 = 24
	   puts "#{@num2.to_i} - #{@num2.to_i}"
	end
end
class Ducktq
	def add
	    run
	end
	def run
	@string ="sriram"
	@str = "mca"
	puts @string + @str
	end
end
def run_it(ducktp)
   ducktp.add
end
puts run_it(Ducktp.new)
puts run_it(Ducktq.new)

		
