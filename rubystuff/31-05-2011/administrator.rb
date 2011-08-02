class Administrator
puts "enter type of user 1.Administrator or 2.general user"
$ch = gets.chop
puts "enter name of the file to maintain your login details "
$file = gets.chop
f = File.open("#{$file}.txt" , "w+" )

	if $ch == 1
	admin
	end
	def admin	
	arr = f.readlines("#{$file}.txt")
		if arr == nil
		puts "enter username"
		@name = gets.chop
		puts "choose your password"
		@pwd = gets.chop
		f.syswrite(@name)
		f.syswrite("\n")
		f.syswrite(@pwd)
		login
		end
	login
	end

	def login
	puts "enter login details"
	puts "enter username"
	@name1 = gets.chop
	puts "enter password"
	@pwd1 = gets.chop
	afile = File.open("#{$name}.txt","r")
	arr = afile.readlines("#{$name}.txt" )
	puts arr[0]
	puts arr[1]
	end
end
c1 = Administrator.new
c1.login






