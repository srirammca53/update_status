class Reservation

def booking()
puts "*************please ebter the details of the following querires************"
puts "------------------------------------------------------------------------------"
puts "\n"
puts "Enter your name"
@name = gets.chop
puts "Enter your age"
@age = gets.chop
puts "\n"
	 @age.to_i > 60? @quota = "senior citizen": @quota =  "general quota"
	
 	
puts "Enter the source station"
@source = gets.chop
puts "trains to following states only"
puts "Hyderabad,chennai,Banglore,Mumbai"
puts "\n"
puts "Enter your destination"
@station = gets.chop
puts case

	 
	when @station.match(/Hyderabad/) then
	      
	 " #@name Journey from #@source to #@station  is charged Rs 800 "
	when @station.match(/Chennai/) then
	     
	 " #@name Journey from #@source to #@station charged  Rs 1200 "
	when @station.match(/Banglore/) then
	      
	 " #@name Journey from #@source to #@station charged   Rs 1500"
	when @station.match(/Mumbai/) then
	      
	 " #@name Journey from #@source to #@station charged   Rs 1800 "
	else
	 "No train to your station at present"
	end

puts "\n"
puts "------------------thank you ----------------------"

puts "**************************************************"
end
end

c1 = Reservation.new()
c1.booking()

	




