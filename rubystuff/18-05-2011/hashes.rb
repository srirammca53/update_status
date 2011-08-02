=begin
program : print the student number whose id'd not match with roll number" 
program name:hashes.rb
=end
class Hashes 

	def check()
	
	@i=0
		for @i in 1..100
		puts "#@i,"
		end
	puts " These are the roll numbers belongs to the students of this class "
	puts "\n"
	
	puts "how many students id's you need to enter"
	@students = gets.chop
	student_id = []
	puts "enter student id's you need to check for suspension"
	for @i in 1..@students.to_i
	 @stu_id = gets.chop
	@i+=1
	student_id<<"#@stu_id"
	end
	student_id.each {|x| puts "#{x}" }
	
	puts "enter the range from ehich roll number that you want to check"
	@from = gets.chop
	puts "enter the range to which roll number that you want to check"
	@to = gets.chop
	puts "rollno's with in the given range "
	roll_no = [] 
	#roll_no = (@from.to_i..@to.to_i).to_a
	 	for @j in @from.to_i..@to.to_i
		roll_no<<"#@j"
		end
	roll_no.each {|x| puts "#{x}" }

	 results = Hash[*roll_no.collect {
			|v| [v, student_id.include?(v)]
				   }.flatten]
	 results.each_pair {|k,v| puts "Key: #{k} is true!" if v == true}
		results.each {|x,y| puts "#{x} => #{y}" }
	puts " the students who are suspended " 
	puts results.delete_if {|k,v| v == false}

	end
end

c1 = Hashes.new()
c1.check()

