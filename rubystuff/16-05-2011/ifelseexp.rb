
puts " this is the if elase condition program"

puts "1,2,3,4,5,6,7,8,9,10 all these are optional choice you need to select on of these options"
choice = gets.chop
puts "you seleected "
puts  (choice)

if (choice!=1 and choice.to_i!=2 and choice.to_i!=3 and choice.to_i!=4 and choice.to_i!=5 and choice.to_i!=6 and choice.to_i!=7 and choice.to_i!=8 and choice.to_i!=9 and choice.to_i!=10 ) 
puts "selected from the given options only you selected an invalid option"

else
puts "valid selection"
end
