require 'logger' 
class Logging

$ENTRY = Logger.new('log_entry2.log' , 'monthly')
 	def wonders_7	
	puts "enter age"
	@age = gets.chop
	$ENTRY.debug("age error")
	if @age == nil or @age == 0
	begin
	
	rescue Exception => e
	puts e.message
	end
	end
	
	end
	$ENTRY.info "YOu need to be hurry"
	$ENTRY.warn "THISS ERROR MAY CORRUPT YOUR FILES "
	$ENTRY.fatal "this is fatal"
end 

c1 = Logging.new
c1.wonders_7
