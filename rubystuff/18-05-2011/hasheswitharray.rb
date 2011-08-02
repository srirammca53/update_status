=begin
program with arrays using hash
=end

class Hash_Array


def functionality()
a=[]


puts "enter the size of array ad enter elements"
@size = gets.chop


	for @i in 1..@size.to_i
	    puts "element  " + @i.to_s + " ?" 
	    a.push gets
	end



end


def hash_Function()

hash = Hash.new()
puts "enter the size of hash"
@h_Size = gets.chop

for @j in 1..@h_Size.to_i
	puts "enter the key"
	key =gets.chop
	 functionality()
	puts a
	hash.store(key,a)
end
hash.each {|x,y| puts "#{x} => #{y}"}
end

end

c1=Hash_Array.new()
c1.hash_Function()

