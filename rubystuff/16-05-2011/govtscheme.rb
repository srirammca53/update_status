class Schemes

	

def eligible()
time = Time.new
puts "present year :"+time.year.to_s
puts "Government  new Educational scheme for poor students please enter the details of"+time.year.to_s
puts " \n"
puts "enter your age to know which scheme you are eligble "
@age = gets.chop
@scholarship = 2000
@benifits =0
	case @age.to_i
		when 5..12
		puts " you are elgible for convent scheme"
		@benifits = @scholarship.to_i * 7
		puts "The govt provides the total money #@benifits "
		
		
		when 13..17
		puts " you are elgible for High school scheme"
		@benifits = (@scholarship.to_i * 4) + 3000
		puts "The govt provides the total money #@benifits "
		
		when 18..21
		puts " you are elgible for college scheme"
		@benifits = (@scholarship.to_i * 3) + 5000
		puts "The govt provides the total money #@benifits "
	
		when 22..25
		puts " you are elgible for university scheme"
		@benifits = (@scholarship.to_i * 3) + 10000
		puts "The govt provides the total money #@benifits "
	
		else
		puts "you are not elgilbe to this scheme on the base of age factor"
		
	end
end






end

c1 = Schemes.new()
c1.eligible()
