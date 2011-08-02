class Salary
puts "\n"
puts "\n"
	def calculate()


	puts "--------New Salaries after the sanction of increment and bonus -------"
	puts "\n"

	puts "This Company have Groups A, B, C & D  enter your Group"
	@group = gets.chop
	@group.downcase
 
		 case

		 when @group.match(/A/) then
			groupA()
		 when @group.match(/B/) then
			groupB()
		 when @group.match(/C/) then
			groupC()
		 when @group.match(/D/) then
			groupD()
		 else 
		 puts "No such group in this oraganisation"
		end
	end

	def groupA()
	puts "Please enter your Basic pay"
	@basic = gets.chop
	puts "Enter your age "
	@age = gets.chop
		if(@age.to_i > 50)
		@salary = @basic.to_i + 5000
		puts "Your Present salary is: #@salary"
		else
		@salary = @basic.to_i + 3000
		puts "Your Present salary is: #@salary"
		end
	puts "please enter how many months of increment"
 	@months = gets.chop
		if(@months.to_i<12)
		@increment = @months.to_i * 350
		elsif (@month.to_i < 20)
		@increment = @months.to_i * 500
		else
		@increment = @months.to_i * 600
		end
	
	puts @increment.to_i
	puts "your increment amount is #@increment "
	@totalsalary = @salary.to_i + @increment.to_i
	puts "Your Present salary is: #@totalsalary"
	end

	def groupB()
	puts "Please enter your Basic pay"
	@basic = gets.chop
	puts "Enter your age "
	@age = gets.chop
		if(@age.to_i > 50)
		@salary = @basic.to_i + 3000
		puts "Your Present salary is: #@salary"
		else
		@salary = @basic.to_i + 1500
		puts "Your Present salary is: #@salary"
		end
	puts "please enter how many months of increment"
 	@months = gets.chop
	@j=0
	@increment1 = 0
		if(@months.to_i<12)
		@increment = @months.to_i * 250
		elsif (@month.to_i < 20)
		@increment = @months.to_i * 400
		else
		@increment = @months.to_i * 500
		end
	puts "your increment amount is #@increment1 "
	@totalsalary = @salary.to_i + @increment1.to_i
	puts "Your Present salary is: #@totalsalary"
	end

	def groupC()
	puts "Please enter your Basic pay"
	@basic = gets.chop
	puts "Enter your age "
	@age = gets.chop
		if(@age.to_i > 50) 
		@salary = @basic.to_i + 2500
		puts "Your Present salary is: #@salary"
		else
		@salary = @basic.to_i + 1200
		puts "Your Present salary is: #@salary"
		end
	puts "please enter how many months of increment"
 	@months = gets.chop
	@k=0
	@increment2 = 0
		if(@months.to_i<12)
		@increment = @months.to_i * 150
		elsif (@month.to_i < 20)
		@increment = @months.to_i * 250
		else
		@increment = @months.to_i * 400
		end
	puts "your increment amount is #@increment2 "
	@totalsalary = @salary.to_i + @increment2.to_i
	puts "Your Present salary is: #@totalsalary"
	end

	def groupD()
	puts "Please enter your Basic pay"
	@basic = gets.chop
	puts "Enter your age "
	@age = gets.chop
		if(@age.to_i > 50)
		@salary = @basic.to_i + 2000
		puts "Your Present salary is: #@salary"
		else
		@salary = @basic.to_i + 1000
		puts "Your Present salary is: #@salary"
		end
	puts "please enter how many months of increment"
 	@months = gets.chop
	@p=0
	@increment3 = 0
		if(@months.to_i<12)
		@increment = @months.to_i * 120
		elsif (@month.to_i < 20)
		@increment = @months.to_i * 150
		else
		@increment = @months.to_i * 200
		end
	puts "your increment amount is #@increment3 "
	@totalsalary = @salary.to_i + @increment3.to_i
	puts "Your Present salary is: #@totalsalary"
	end
end

c1 = Salary.new()
c1.calculate()

