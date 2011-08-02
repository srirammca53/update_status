class Company
 	def groups(ch)
	@ror=0
	@java=0
	@net=0
	@php=0
	puts "please enter your details"
	puts "enter your name:"
	name = gets()
	puts "enter your group:"
	group = gets()
	puts "enter your emp no:"
	id = gets()
	puts "enter your age:"
	age = gets()
		if(ch==ruby)
		@ror+=1
		puts "total memebers in group :#@ror"
		end
		if(ch==java)
		@java+=1
		puts "total memebers in group :#@java"
		end
		if(ch==net)
		@net+=1
		puts "total memebers in group :#@net"
		end
		if(ch==php)
		@php+=1
		puts "total memebers in group :#@php"
		end
	end
	def display()
	puts "Mr."+name+"your details"
	puts "Name      :"+name
	puts "Group     :"+group
	puts "Emp no      :"id
	puts "Age   :"+age
	end
end
puts "please enter your group"
a = gets()

c1=Company.new()
c1.groups(a)
c1.display()

