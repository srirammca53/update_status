class Tables

   number = []
   a=0
   a = gets.chomp
   puts a.to_i
   len = a.to_i
	i = 0
     	for i in 0..len
   	  number[i] = gets.chomp
      	end
          puts "enter a number to find "
	find = gets()
	if number[i] == find
	puts "yes"
	else
	puts "no"
	end
end
