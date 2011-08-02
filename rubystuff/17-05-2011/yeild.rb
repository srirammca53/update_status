class Yeildexmp

def status()
puts " enter your name"
@name = gets.chop
puts "enter your age"
@age = gets.chop
@stat
	if(@age > 60)
	@stat = "retired"
	yeild(@status,@age,@name)
	else
	@status ="Working"
	yeild(@stat,@age,@name)
	end
puts"Want to try again :y/n"
@ch = gets.chop()
	if(@ch == 'y')
	status()
		if(@ch == 'n')
		puts "\n"
		else
		puts "you entered wrong key"
		end
	end
end

status {|x,y,z| puts z+"aged"+y+"present status is "+x }
end

c1 = Yeildexmp.new()
c1.status()
