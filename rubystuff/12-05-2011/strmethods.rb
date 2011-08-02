class Teststring

str = "this is the first string example "

puts str.capitalize #capitalize
puts str.capitalize! #capitalize!
puts str.casecmp("this Is The firSt string example ") #case comparision 	

str2 ="sree"
puts str2.center(52) #place the string at the position mentioned 
puts str2.center(52,'ram') # place the string at the postion in mbetween mentions characters
puts str.each_char{|c| print c,' '} # prints each char with specified seperator
puts str.chars # prints enumerator

str3 ="ram\n\t" 
puts str3.chomp # removes the special character from the string which is defined
str4 ="rama\n\t" 
puts str4.chomp!("\n")
puts str2.chop # returns a new string by removing last character 
puts str2
puts str2.chop! # returns the same string by removing a character with out creating new character
puts str2
str5 = "sreeram"
#puts str5.each_codepoints {|c| print c,' '} #not working 


#puts "sree"+str5.clear #not working
#puts  "abc".clear 


str6 = "there\nare\nsomany\nmethods:"
puts str6.each_line {|s| p s} # returns the given string by seperating with specified seperator 	
puts str6.each_line('n') {|s| p s}
puts str6.empty? # returns true or false whether the given string is empty or not

puts str6.end_with?(['s'])


str8 = "string"
str9 = "string"
puts str8.eql?(str9) # returns true or false of two strings

puts str.gsub(/[a,o]/, '*')   # replace the character with specified element
puts str8.hash # returns hash based on the element which we assigned

puts str.include?"is" # returns true or false that the given element is inculdn the string or not.
puts str.index('i')
end
