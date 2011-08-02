=begin
Name of the program: citizenhash.rb
methods : hashes
=end



class Citizen

	def details()
		puts "-------------Citizen details--------------"	
		puts "             ---------------               "
		puts "\n"
		puts "enter your name"
		@name = gets.chop
		puts "enter your age "
		@age = gets.chop
		@v_points = 0
		@p_points = 0
		@d_points = 0
		if(@age.to_i > 18 )
		puts "enter your votercard number"
		@voter_id = gets.chop
			if(@voter_id = "" or @voter_id = nil)
			@v_Points = 10
			else
			@v_Points = 0
			end
		puts "enter your Pan card number"
		@pan_id = gets.chop
			if(@pan_id = "" or @pan_id = nil)
			@p_Points = 10
			else
			@p_Points = 0
			end
		puts "enter your Driving license  number"
		@drive_id = gets.chop
			if(@drive_id = "" or @drive_id = nil)
			@d_Points = 10
			else
			@d_Points = 0
			end
		@cards = (@v_Points.to_i + @p_Points.to_i + @d_Points.to_i)
		else
		@v_points = 6
		@p_points = 6
		@d_points = 6
		end
		puts "Enter your designation "
		@desig = gets.chop
		@traffic = 0
		@duty = 0
		@social = 0
		
		puts "\n"
		puts "please answer the few questions by y/n"
		puts "\n"
		puts "Question 1 : You follow traffic rules at any time ?"
		@ch = gets.chop
			if(@ch == y )
			@traffic = 20
			else
			@traffic = 0
			end
		puts "question 2 :	You are regular to your duty ?"
		@ch1 = gets.chop
			if(@ch1 == y )
			@duty = 20
			else
			@duty = 0
			end
		puts "question 3 : You are interested in social service ?"
		@ch2 = gets.chop
			if(@ch2 == y )
			@social = 20
			else
			@social = 0
			end
		@r_social = (@traffic.to_i + @duty + @social)
		@total = @r_social + @cards
		puts "the total responsibility :#@total "

	end

end
