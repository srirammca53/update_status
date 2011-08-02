class Application
	def register
	 puts "Welcome to the registration"
	 puts "enter user name is atleast 8 characters"
	 @name = gets.chop
	 @reg = /\w{8,}/
	 @match = @name.match @reg
	 raise "Username must be 8 character only" if @match == nil
	 rescue Exception => e
	 puts e.message
	 register
	 else
	 puts "select password "
	 @pwd = gets.chop
	 afile = File.new("login.txt" , "r+")
	 if afile
	  afile.syswrite(@name)
	  afile.syswrite("\n")
	  afile.syswrite(@pwd)
	 end
	 afile.close
	 
	end

	def login
	register
	puts "Login"
	today = Time.new
	@time = today.inspect
	  afile = File.open("login.txt" , "a+")
	  afile.syswrite("\n")
	  afile.syswrite(@time)
	  afile.close
	puts "enter your username"
	@user = gets.chop
	puts "enter your password"
	@cpwd = gets.chop
	afile = File.open("login.txt" , "r+")
	arr = IO.readlines("login.txt")
	puts arr[0]
	puts @user
	@match1 = arr[0].match @user
	if @match1 == nil
	puts "Incorrect username " 
	end	
	@match2 = arr[1].match @cpwd
	if @match2 == nil
	puts "Incorrect password" 
	end
	if @match1 != nil and @match2 != nil
	puts "login successfully"
	puts "present time : #{today.inspect}"
	puts "your last login is on #{arr[2]}"
	end
	puts "\n"
	end
end

Application.new.login

