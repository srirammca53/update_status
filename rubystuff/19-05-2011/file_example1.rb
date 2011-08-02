
class File_Operations

	def read()
	afile = File.new("textfile.txt" , "r")
		if(afile)
		content = afile.sysread(20)
		puts content
		else
		puts "unable to open"
		end
	end

	def write()
	afile = open('textfile.txt', 'r+')
		if(afile)
		afile.syswrite("sriram")
		puts afile
		else
		puts "unable to write"
		end
		
	end
	
	def append()
	afile = open('textfile.txt','a+')
		if(afile)
		puts "enter the content that you need to append"
		@content = gets.chop	
		@content
		afile.syswrite("#{@content.upcase} \n")
		puts "\n"
		puts afile
		else
		puts "unable to append"
		end
		puts afile
	end
                                                                                                    		
end

c1 = File_Operations.new()
c1.read()
c1.write()
c1.append()
