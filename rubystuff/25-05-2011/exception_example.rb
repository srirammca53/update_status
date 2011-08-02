# program to raise an exception
class Exception_Handling
	def raise_exception
	puts "before an exception raise"
	raise "An new Error Occured"
	puts "After an Exception raise"
	end


end

Exception_Handling.new.raise_exception
