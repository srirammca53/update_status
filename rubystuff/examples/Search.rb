class Search
	elements = Array['23','43','45','56','67','78','89','90']
	puts "#{elements}"
	puts "#{elements.join(',')}"
	num = elements.length
	puts num
    @@i=0
	puts "#@@i"
	puts "enter your number to search"
	search = gets()
    if @@i<num 
	@@i+=1

          if (elements.at(@@i)==search)
	puts numer
         end

    end

end
