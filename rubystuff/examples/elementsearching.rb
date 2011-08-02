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
while @@i<num do
@@i+=1
numer = "#{elements.at(@@i)}"
if (numer==search)

puts numer
end

end

end
