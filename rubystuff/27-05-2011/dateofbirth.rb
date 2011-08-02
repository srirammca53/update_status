# program about Date and Time

class  D_O_Dob

	def find
	puts "enter your date of birth in the format of dd\mm\yyyy"
	@dob = gets.chop
	@reg1 = /[0-9]{2}\\[0-9]{2}\\[0-9]{4}/
	@match = @dob.match @reg1
		if @match == nil
		puts "Enter in mentioned format"
		find
		end
		if @match != nil
		puts @dob
		end
	@new =  @dob.split("")[6] + @dob.split("")[7] + @dob.split("")[8] + @dob.split("")[9]
	puts @new
	@days1 = @dob.split("")[0] + @dob.split("")[1]
	puts @days1
	@days2 = @dob.split("")[3] + @dob.split("")[4]
	puts @days2
	end
end

c1 = D_O_Dob.new()
c1.find
