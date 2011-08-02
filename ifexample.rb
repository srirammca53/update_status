
puts " this is the if elase condition program"

puts "1,2,3,4,5,6,7,8,9,10 all these are optional choice you need to select on of these options"
choice = gets()
puts "you seleected "+choice

if (choice.to_i!=1 or choice.to_i!=2 or choice.to_i!=3 or choice.to_i!=4 or choice.to_i!=5 or choice.to_i!=6 or choice.to_i!=7 or choice.to_i!=8 or choice.to_i!=9 or choice.to_i!=10 ) 
puts "selected form the given options only you selected an invalid option"
end
