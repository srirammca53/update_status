# program on Rescue and raise 

class Rescue_test
	def rescue_raise
	begin
	puts "before error"
	raise " an error occured"
	puts "after an exception"
	rescue Exception => e
	puts e.message
	puts e.backtrace.inspect
	puts "iam rescued"
	end
	
	puts " iam after the block"
end
end
Rescue_test.new.rescue_raise

