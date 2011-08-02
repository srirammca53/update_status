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
	@year =  @dob.split("")[6] + @dob.split("")[7] + @dob.split("")[8] + @dob.split("")[9]
	@day = @dob.split("")[0] + @dob.split("")[1]
	if @day.to_i < 1  or @day.to_i > 31
	raise StandardError.new("Day is not in the valid range")
			begin 
			rescue Exception => e
			puts e.message
			end
		end
	@month = @dob.split("")[3] + @dob.split("")[4]
		if @month.to_i < 1 or @month.to_i > 12
		raise StandardError.new("Month is not in the valid range")
			begin 
			rescue Exception => e
			puts e.message
			end
		end
		if @month.to_i == 01 and @month.to_i == 03 and @month.to_i == 05 and @month.to_i == 07 and @month.to_s == '08' and @month.to_i == 10 and @month.to_i == 12
	           raise StandardError.new("day is not in valid range") if @day.to_i < 1 or @day.to_i > 31
			begin
			rescue Exception => e
			puts e.message
			end
		end
		if @month == 04 and @month == 06 and @month.to_s == '09' and @month == 11 
	           raise StandardError.new("day is not in valid range") if @day.to_i < 1 or @day.to_i > 30
			begin
			rescue Exception => e
			puts e.message
			end
		end
		if @month == 02
		puts "true"
			if (@year.to_i)%4 == 0
			puts "true"
				raise StandardError.new("day is not in valid range") if @day.to_i < 1 or @day.to_i > 29
				begin
				rescue Exception => e
				puts e.message
				end
			end	
			if (@year.to_i)%4 != 0
				raise StandardError.new("day is not in valid range") if @day.to_i < 1 or @day.to_i > 28
				begin
				rescue Exception => e
				puts e.message
				end
			end	
		end
	Time.now
	t = Time.local(@year,@month,@day)
	 @lday = (t.to_s).split("")[0] + (t.to_s).split("")[1] + (t.to_s).split("")[2]
	 if @lday = "wed" 
	  puts "the day is #{@lday}nesday"
	 end
	if @lday == "thu" 
	  puts "the day is #{@lday}rsday"
	 end
	if @lday == "mon" 
	  puts "the day is #{@lday}day"
	 end
	if @lday == "tue" 
	  puts "the day is #{@lday}sday"
	 end
	if @lday == "fri" 
	  puts "the day is #{@lday}day"
	 end
	if @lday == "sat" 
	  puts "the day is #{@lday}urday"
	 end
	if @lday == "sun" 
	  puts "the day is #{@lday}day"
	 end
	
	 
	end
end
c1 = D_O_Dob.new()
c1.find
