
class Overflow
	def check
	puts "enter the number below 100"
	@num = gets.chop
	@reg =  /[\d]{1,}/
	@match1 = @num.match @reg
	if @match1 == nil
	begin
	raise ArgumentError.new("not a number")
	rescue Exception => e
	puts e.message
	end
	end
		if @num.to_i > 100
			begin
			raise StandardError.new("out of range")
			rescue Exception => e
			puts e.message
			end
		end
	end
end
c1 = Overflow.new()
c1.check
	
