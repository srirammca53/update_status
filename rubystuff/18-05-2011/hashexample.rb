

	
	puts "please enter the size of hash "
	size = gets.chop
	puts "enter the values of key and values"
	hash=Hash.new{}
	i=1
	key = 0
	value = 0
		for i in 1..size.to_i
		key = gets.chop
		value = gets.chop
		hash.store(key,value)
		i+=1
		end
	 hash.each {|x,y| puts "#{x} is #{y}" }
	#puts hash.invert
	hash1 = Hash.new()
	hash1 = {  "sriram","Sachin"}
	hash2 = {  "sourav", "sreesanth"}
	hash1[0] = "dravid"
	h = { hash1 => "rank1" , hash2 =>"rank2" }
	hash1.rehash


