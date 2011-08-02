class Ducktp
	def add
	   @num1 = 12
	   @num2 = 24
	   @num2.to_i + @num1.to_i
	end
	def sub
	   @num1 = 12
	   @num2 = 24
	   @num2.to_i - @num1.to_i
	end
end
class Ducktq
	def add
	    run
	end
	def run
	@string ="sriram"
	@str = "mca"
	 @string + @str
	end
end
def run_it(ducktp)
   ducktp.add
end
puts run_it(Ducktp.new)
puts run_it(Ducktq.new)

		
