class Admin
def user
puts "please enter your file name "
@fname = gets.chop
puts "enter your username"
@uname = gets.chop
puts "enter password"
@pwd = gets.chop
f = File.open("#{@fname}.txt","r+")
arr = f.readlines("#{@fname}.txt")
puts arr[0]
puts @uname
if arr[0] != "#{@uname}"
puts "invalid username"
end
if arr[1] != @pwd
puts "invalid password"
end

end
end
puts "admin : enter type of user 1.Administrator or 2.general user"
ch = gets.chop
admin = Admin.new
def admin.adminuser
puts "enter your username"
@user = gets.chop
puts "enter password"
@pwd = gets.chop
puts "welcome #{@user}"
puts "user details modification? :y/n"
@ch1 = gets.chop
	if @ch1 == "y"
	puts Dir["*.txt"]
	puts "please enter user file name only to modify"
	@file = gets.chop
	f2 = File.open("#{@file}.txt","w+")
	puts "modify the username"
	@mname = gets.chop
	puts "modify the password"
	@mpwd = gets.chop
	f2.syswrite(@mname)
	f2.syswrite("\n")
	f2.syswrite(@mpwd)
	puts f2.readlines("#{@file}.txt")
	end
end
	if ch == "1"
	
	admin.adminuser
	end 
	if ch == "2"
	admin.user
	end
puts "user : enter type of user 1.Administrator or 2.general user"
ch1 = gets.chop
if ch1 == "1"
user = Admin.new
user.adminuser
end
if ch == "2"
user = Admin.new
user.user
end


