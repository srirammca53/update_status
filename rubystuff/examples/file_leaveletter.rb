







	afile = File.new("leaveletter.txt" , "r")
		if(afile)
		content = afile.sysread(1000)
		puts content
		else
		puts "unable to open"
		end
	
		
       	

	
	
	
		
		arr = IO.readlines("leaveletter.txt")
		i=1
		for i in 1..24
		puts arr[i]
			
		end


		afile = File.open("leaveletter.txt", "a+")
		afile.each { |line|
  		if line.match(/for/)
		puts "enter how many days leave u applied and reason"
		@reason = gets.chop
    		afile.syswrite("#{@reason}")
  		end
		}
	

		afile = File.open("leaveletter.txt", "a+")
		afile.each { |line|
	  		if line.match(/your obidiently/)
			puts "enter your name"
			@final= gets.chop
	    		afile.puts("#{@final}")
	  		end
				}


		


