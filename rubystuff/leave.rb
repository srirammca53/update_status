f = File.open("sriram.txt" , "r+")
str = IO.readlines("sriram.txt")
puts "this is the file which you need"
  puts File.pipe?("sriram.txt")
f.seek(-50,IO::SEEK_END)  
puts "enter name"
name = gets.chop
a=f.getc
	while(a!=nil)
	a=f.getc
		if(a=="I,")
		puts name
		end
	
	end 

 f.close 
