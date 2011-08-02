# program using method overridding


class Overridding

	def intialize(name)
	@gamename = name
	puts @gamename
	puts "enter the country name "
	@coutry = gets.chop
	puts @country
	puts  "enter the captian name "
	@captain = gets.chop
	puts @captain
	puts "Our #{@country} #{@gamename} team captain is #{@captain}"  
	end
end

class B < Overridding

	def intialize(name)
	@student = name
	puts @student
	puts "enter the country name "
	@class = gets.chop
	puts @class
	puts "enter the captian name"
	@school = gets.chop
	puts @school
	puts "Our #{@student} from  #{@student} team captain of  #{@school}"
	end 
end

c1 = Overridding.new()
b = B.new()
b.intialize("cricket")
c1.intialize("cricket")

