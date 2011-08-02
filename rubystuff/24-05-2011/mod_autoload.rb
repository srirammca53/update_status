module F

def read()
	afile = File.new("textfile.txt" , "r")
		if(afile)
		content = afile.sysread(20)
		puts content
		else
		puts "unable to open"
		end
	end

end
F::read()

module B
puts "this is the module b"

end
B.autoload(:F, "textfile.txt")
B::F.doit 

