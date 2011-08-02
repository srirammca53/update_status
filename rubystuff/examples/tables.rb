class Table

number = []
   a=0
   a = gets.chop
   len = a.to_i
    puts "\n"
	 i=0
	puts "First table: "
	for i in i..len
	number[i] = gets.chop
            
	  for j in 1..12
	   print number[i]
	   print "*"
	   print j
	   print "="
	   print ((number[i]).to_i)*j
	   puts "\n"

	  end
	  puts "Next table: "
  	end
	puts "\n"
	range = number.length
	puts range
	
	
end


