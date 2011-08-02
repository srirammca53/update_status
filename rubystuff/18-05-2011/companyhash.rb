
=begin
program using method
program name : Company 
methods: hashes
=end
class Company

  	def employees()
	puts "WEL COME TO ANIMATION WORLD "
	puts "---------------------------"
	puts "\n"
	puts "This company having 1.programmers , 2.Animaters , 3.Music directors , 4.producer"
	puts "Enter one of the group"
	ch = gets.chop
	pro = Hash.new{}
		if(ch.to_i == 1)
		puts "enter how many employees in programming gruop"
		s1 = gets.chop
		i = 1
		puts "enter name and age of an employee"
			for i in 1..s1.to_i
				p_Name = gets.chop
				p_Age = gets.chop
				pro.store(p_Name,p_Age.to_i)
				i+=1
			end
		puts "List of the programmers in the company"
		pro.each { |x,y| puts "Name :#{x} Age :#{y}" }
		puts "employees who are comes under 25"
	          pro.delete_if { |x,y| y > 25}
		pro.each { |x,y| puts "Name :#{x} Age :#{y}" }
			puts "if you want to continue to enter employees:y/n"
			ch =gets.chop
			if(ch=="y")
			employees()
			else
			puts"\n"
			end
		end
		
		# for animaters 
		ani = Hash.new{}
		if(ch.to_i == 2)
		puts "enter how many employees in  animation gruop"
		s2 = gets.chop
		i1 = 1
		puts "enter name and age of an employee"
			for i1 in 1..s2.to_i
				a_Name = gets.chop
				a_Age = gets.chop
				ani.store(a_Name,a_Age.to_i)
				i1+=1
			end
		puts "List of the Animators in the company"
		ani.each { |x,y| puts "Name :#{x} Age :#{y}" }
		puts "employees who are comes under 25"
	          ani.delete_if { |x,y| y > 25}
		ani.each { |x,y| puts "Name :#{x} Age :#{y}" }
			puts "if you want to continue to enter employees:y/n"
			ch =gets.chop
			if(ch=="y")
			employees()
			else
			puts"\n"
			end
		end
		#Music directors
		mus = Hash.new{}
		if(ch.to_i == 3)
		puts "enter how many employees in  Music Directors  gruop"
		s3 = gets.chop
		i2 = 1
		puts "enter name and age of an employee"
			for i2 in 1..s3.to_i
				m_Name = gets.chop
				m_Age = gets.chop
				mus.store(m_Name,m_Age.to_i)
				i2+=1
			end
		puts "List of the Music Directors in the company"
		mus.each { |x,y| puts "Name :#{x} Age :#{y}" }
		puts "employees who are comes under 25"
	          mus.delete_if { |x,y| y > 25}
		mus.each { |x,y| puts "Name :#{x} Age :#{y}" }
			puts "if you want to continue to enter employees:y/n"
			ch =gets.chop
			if(ch=="y")
			employees()
			else
			puts"\n"
			end
		end
		# producers
		prod = Hash.new{}
	
		if(ch.to_i == 4)
		puts "enter how many employees in  producers gruop"
		s4 = gets.chop
		i3 = 1
		puts "enter name and age of an employee"
			for i3 in 1..s4.to_i
				pro_Name = gets.chop
				pro_Age = gets.chop
				prod.store(pro_Name,pro_Age.to_i)
				i3+=1
			end
		puts "List of the Produceres in the company"
		prod.each { |x,y| puts "Name :#{x} Age :#{y}" }
		puts "employees who are comes under 25"
	          prod.delete_if { |x,y| y > 25}
		prod.each { |x,y| puts "Name :#{x} Age :#{y}" }
			puts "if you want to continue to enter employees:y/n"
			ch =gets.chop
			if(ch=="y")
			employees()
			else
			puts"\n"
			end
		end
		total = Hash.new()
		puts "total employees in the company comes under 25 "
		pro = pro.merge(ani)
		pro = pro.merge(mus)
		total = pro.merge(prod)
		total.each { |x,y| puts "Name :#{x} Age :#{y}" }
	end

	
		
end

c1 = Company.new()
c1.employees()
		
	 
