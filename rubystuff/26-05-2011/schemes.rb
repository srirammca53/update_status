# 
class File1
	def create
	puts "The Govt schemes"
	puts "please select a name for your file "
	@file_name = gets.chop
	afile = File.new("#{@file_name}.txt" , "w+")
	afile.close
	end

	def scheme
	create
	puts "enter your name"
	@name = gets.chop
	@reg1 = /\w{6,9}/
	match1 = @name.match @reg1
	if match1 == nil
	puts "please enter your name with min 6 characters and max 9 characters"
	scheme
	end
	puts "enter your age"
	@age = gets.chop
	@reg2 = /\d{2}/
	match2 = @age.match @reg2
	if match2 == nil
	puts "please enter your age"
	return false
	end
	puts "enter your Qualification"
	@qual = gets.chop
	@q = @qual.split("")[0]
	if @q =="m" or @q == "M" 
	puts "you are a Master Degree Holder"
	@elg1 = "you are a Master Degree Holder"
	end
	if @q =="b" or @q == "B"
	puts "You are Bachelor Degree Holder"
	@elg1 = "You are Bachelor Degree Holder"
	end
	if @q != "m" and @q != "M" and @q !="b" and @q != "B"
	puts "You have a minimum Qualification"
	@elg1 = "You have a minimum Qualification"
	end
	puts "enter your income"
	@inc = gets.chop
	@tax = (@inc.to_i * 12) * 12 / 100
	if @tax.to_i > 25000
	puts "You have to pay #{@tax} every year and more than 25,000 of tax are not eligible 			for the Government Schemes"
	@elg2 = "You have to pay #{@tax} every year and more than 25,000 of tax are not eligible for the Government Schemes"
	puts "Thank you"
	end
	if @tax.to_i < 25000
	puts "You have no tax to pay so you are elgible for Goverment schemes"
	@elg2 = "You have no tax to pay so you are elgible for Goverment schemes"
	form
	end
	
	afile = File.open("#{@file_name}.txt" , "r+")
	afile.syswrite("Name:#{@name}")
	afile.syswrite("\n")
	afile.syswrite("Age:#{@age}")
	afile.syswrite("\n")
	afile.syswrite("Qualification:#{@qual}")
	afile.syswrite("\n")
	afile.syswrite("Income:#{@inc}")
	afile.syswrite("\n")
	afile.syswrite("Your result is")
	afile.syswrite("\n")
	afile.syswrite("#{@elg1}")
	afile.syswrite("\n")
	afile.syswrite("#{@elg2}")
	afile.syswrite("\n")
	
	
	
	
end
	def form
	 puts "The Government schemes are 1.Health 2.Homeplan 3.Traveldiscount"
	case 
		when '1'
		then
		puts "please enter number of members in your family"
		@tot = gets.chop
		puts "Total #{@tot} members of your family having 75% discount in govt hospitals	"
		when '2'
		then
		puts "please enter your town"
		@town = gets.chop
		puts "You are elgible to have a own house in your #{@town}"
		when '3'
		then
		puts "please enter your state"
		@state = gets.chop
		puts "your family having 75% discount when travelling in #{@state} only"		
		else
		puts "no such schemes"
		end		

	end

end

c1 = File1.new
c1.scheme()
