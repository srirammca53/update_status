#!/usr/bin/ruby

class Hours

puts "hi this is my first Ruby program"
myname= gets()
puts "hi mr."+myname+" welcome"

puts "enter an year"
year = gets()
puts "you entered"+year.to_s+"year"
@hours=0
if year%4=="0"

puts "leap year"
@hours=366 * 24
puts " total hours:#@hours in "+year

else

puts "not a leap year"
@hours = 365 * 24
puts " total hours:#@hours in "+year
end
   
end


