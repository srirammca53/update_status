=begin
program name: letter.rb
having letter formats in hash
user need to select one format and give details
=end


class Letter


	def format()
	#letter foramts with key 
	puts "\n"
	puts "\n"
	puts " In this company we have 4 types of letters please select one from following"
	hash = { "1" => "leave letter" , "2" => "transfer letter" , "3" => "resign letter" , "4" => "project request letter" }
	hash.each {|x,y| puts "#{x} => #{y} "}
	puts"\n"
	puts "please enter your option "
	@choice = gets.chop
	@a = 0
	@b = 0
	@c = 0
	@d = 0
		if(@choice.to_i == 1)
		leave()
		@a+=1
		else
		puts "\n"
		end

		if(@choice.to_i == 2)
		transfer()
		@b+=1
		else
		puts "\n"
		end
	 

		if(@choice.to_i == 3)
		resign()
		@c+=1
		else
		puts "\n"
		end
	 

		if(@choice.to_i == 4)
		project()
		@d+=1
		else
		puts "\n"
		end
	 puts "if any letter is selected more than  2 by users that letter will be disabled"
		if(@a == 2)
		hash.select {|x,y| x == "1" }
		end
		hash.each {|x,y| puts "#{x} => #{y} "}

	end

	def leave()
	puts "leave letter"
	puts "Please enter your name"
	@name = gets.chop
	puts "please enter how many days you need"
	@days = gets.chop
	puts "please enter name to whom you are requesting"
	@b_name = gets.chop
	
	puts "if you want to generate more letters:y/n"
	@ch=0
		if(@ch == "y")
		foramt()
		else
		puts "Thank you \n"
		end
	end

	def transfer()
	puts "Transfer letter"
	puts "if you want to generate more letters:y/n"
	@ch=0
		if(@ch == "y")
		foramt()
		else
		puts "Thank you \n"
		end
	end

	def resign()
	puts "Resign letter"
	puts "if you want to generate more letters:y/n"
	@ch=0
		if(@ch == "y")
		foramt()
		else
		puts "Thank you \n"
		end
	end

	def project()
	puts "Project letter"
	puts "if you want to generate more letters:y/n"
	@ch=0
		if(@ch == "y")
		foramt()
		else
		puts "Thank you \n"
		end
	end

end

c1 = Letter.new()
c1.format()

