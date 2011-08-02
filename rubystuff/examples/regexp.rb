class Registration

def details()
str= "Registration Form"
puts str.center(40,'---')
puts "\n"
puts "Please enter your name"
@name = gets.chop
r1=/[a-z]{5,}/
match1 = @name.match r1
if(match1==nil)
puts "please enter name atleast 5 characters "
return false
end
puts "pleaase Enter your mobile number"
@mobile = gets.chop
r2 = /[0-9]{10}/
match2 = @mobile.match r2
if(match2==nil)
puts "Please enter a valid mobile number"
return false
end

puts "Please create a password to your account"
@pwd = gets.chop
if(@pwd==nil)
puts "Please enter the password field"
return false
end
puts "confirm your passwrod"
@cpwd = gets.chop
if(@cpwd!=@pwd)
puts "Password Not Matched "
puts "please enter again"
return false
end
puts "Please enter your website"
@web = gets.chop
r3=/[w]{3}[.][a-z]{5,}[.][com]/
match3 = @web.match r3
puts match3
if(match3==nil)
puts "please entera valid email id"
return false
end
puts "enter your age"
@age = gets.chop
r4 = /[0-9]{1,3}/
match4 = @age.match r4
if(match4==nil)
puts "Please enter age properly"
puts "Please try again"
return false
end
puts "your details are stored in to an array"
a = []
a<<@name
a<<@age
a<<@pwd
a<<@web
a<<@mobile
puts a
arr = [[1,2],[3,4],[a]]
puts arr.assoc("sriram")
puts arr
end




end


c1 = Registration.new()
c1.details()

