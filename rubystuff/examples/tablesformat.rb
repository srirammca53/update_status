class PrintTable
puts "enter how many rows you need ?"
puts "\n"
rows= gets.chop
puts "you need "+rows+"rows"
puts "\n"
puts "enter how many cols you need ?"
puts "\n"
rows= gets.chop
puts "you need "+cols+"cols"
     i=1
      for i in i..rows.to_i
          for j in j..cols.to_i
	    r="-----"
  	    c="|"
	    puts r
	    puts c
         end
      end
end

