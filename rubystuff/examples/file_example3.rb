#program using files and arrays                     							


  
f = File.new("leaveletter.txt")   
f.seek(0,IO::SEEK_CUR)  
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

