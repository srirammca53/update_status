class Reg

  re = /\(\d{3}\) \d{3}-\d{4}/ 
 puts "(123) 456-7890".match re # returns nil if no match found else return the data itself

puts "this is my first program on RegExp" =~/pro/ # this will return the position where the defined pattern is available in the string  else return nil

re = /\[viz]\[0-9]{5}/
rno1 = "viz12345"
rno2 = "viz12o35"
match1 = rno1.match re
match2 = rno2.match re

puts match1
puts match2


puts "no white space before the string".match /(\w*)/


end

