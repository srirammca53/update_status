require 'logger' 
class Logging

$ENTRY = Logger.new('log_entry.log' , 'monthly')
 	def wonders_7
	puts "enter 7 wonders names"
	arr = []
	
		for i in 1..10
		@wonder = gets.chop
		$ENTRY.debug("arr index out of bound")
				if(i > 7)
				begin
				arr.push(@wonder)
				rescue Exception => e
				$ENTRY.error "error array index out of bound: #{e}"
				end
			end
		end
	puts arr
	end

end

c1 = Logging.new
c1.wonders_7
