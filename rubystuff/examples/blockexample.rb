
def profit()


@share = 4
puts "enter your share details when at 09:50 a.m "

@amount = gets.chop
puts "\n"
puts "today share increase up to 4 % "
yeild(@share,@amount)
puts 
end
profit  {|x,y| puts y *x/100 + y}

