=begin
program name: hashesmethods.rb
using hash methods
=end

class Methods_hash

def estimate()
puts "Resutarant section of food"
hash = Hash.new()
puts "enter how many types "
@types = gets.chop
puts "enter type of item"

@i=1
for @i in 1..@types.to_i
	@key = gets.chop
	puts "enter no of item belongs to this block"
	@item_nos =gets.chop
	
	for @i in 1..@item_nos.to_i
		@item["#@i"] =gets.chop
		@item["#@i"]+=","
		@no =@item["#@i"]
		@i+=1
	end	
	hash.store(@key,@no)
	
end


end
end
c1 = Methods_hash.new()
c1.estimate()

