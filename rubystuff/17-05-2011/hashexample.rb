class Hashexample

def check()
puts "Enter each hash values"
puts "enter expenditure for loan"
@value1 = gets.chop
puts "enter expenditure for tax"
@value2 = gets.chop
puts "enter expenditure for rent"
@value3 = gets.chop
puts "enter expenditure for fuel"
@value4 = gets.chop
puts "enter expenditure for bills"
@value5 = gets.chop
h = {"loan" => @value1,"tax" => @value2,"rent" => @value3,"fuel" => @value4,"bills" => @value5}
puts "Is the hash is empty:#{h.empty?}"
h.each {|num,value| puts "#{num} : #{value}" }
h1=[]
puts "enter the size of hash"
 @size = gets.chop
puts "enter  the key and values "
@i = 1
 for @i in 1..@size.to_i
puts "enter key #@i" 
@key = gets.chop
puts "enter value" 
 @val= gets.chop
h1["#@key"] = "#@val"
end
h1.each {|n,val| puts "#{n} : #{val}" }
end
 

def test()



end


end

c1 = Hashexample.new()
c1.check()
c1.test()
