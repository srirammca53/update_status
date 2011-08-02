







f=File.new("leaveletter.txt","r+")
puts "enter your name"
name = gets.chop
puts "enter fullname"
fname = gets.chop

f.seek(0,IO::SEEK_CUR)
a=f.getc
while (a!=nil)	
	if(a.chr=="@")
		
		a.chr.replace(name)
		f.print
	end
	if(a.chr=="-")
		
		f.print(fname)
	end
	a=f.getc
end
f.close

















