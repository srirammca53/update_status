# program about Date and Time

Class D_O_Dob

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
	puts @dob.split("")[7..10]
	end
end

c1 = D_O_Dob.new()
c1.find
