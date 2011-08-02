class Rangeexmp

 puts "Cricket game "
	def play()
	team_selection()
	toss()
	end

	def team_selection()
	puts "You need two teams to play cricket game"
	puts "---------------------------------------"
	puts "\n"
	puts "Enter 2 teams one by one "
	@team1 = gets.chop
	@team2 = gets.chop
	puts "\n"
	puts "#@team1  VS   #@team2 "
	puts "select your team from these two"
	@my_Team = gets.chop
		case  
			when @my_Team == @team1 
			puts "Your team is #@team1"
			when @my_Team == @team2 
			puts "Your team is #@team2"
			else 
			puts "please make your selection valid"
			return false
		end
 	end

	def toss()
	puts "The toss is based on the number you entered if even number u won the toss else u lost the toss"
	puts "enter the number"
	@toss = gets.chop
	
			if(@toss.to_i%2 == 0)
			@total = 0
			@total_runsgiven = 0
			puts "You won the toss"
			puts "Batting(1) / Bowling(2)"
			@innings = gets.chop
			
				if(@innings.to_i == 1)
				puts "#@my_Team selected batting"
				batting()
				puts "#@my_Team scored #@total"
				end
				if(@innings.to_i == 2)
				puts "#@my_Team selected bowling"
				bowling()
				puts "total runs given to oppenent team:#@total_runsgiven"
				end
			end
		
			if(@toss.to_i%2 == 1)
			puts "you lost the toss"
			puts "The oppent chooses bowling"
			bowling()
			end
			
	
	end


	def batting()
	@total =0
	@i=1
		puts "Enter individual scores of each player"
		puts "enter 0-100 only"
		for @i in 1..10
		@score = gets.chop
		puts "Player#@i :#@score"
		@total = @total.to_i + @score.to_i
		@i+=1
		end
	end

	def bowling()
	puts "total five bolwers"
	puts "Enter how many runs he given to oppent team"
	@j = 1
	@total_runsgiven = 0
		for @j in 1..5
		@runs = gets.chop
		puts "bolwer #@j: #@runs"
		@total_runsgiven =@total_runsgiven.to_i + @runs.to_i
		@j+=1
		end
	puts "total runs given to oppenent team:#@total_runsgiven"
	
	end
	

	

end
c1 = Rangeexmp.new()
c1.play()
 
