# program on redefining methods
class Redefining
def parent
	def method(a,b)
	puts "you entered two numbers "
	@a,@b = a,b
	puts @a.to_i + @b.to_i
	end
	puts "enter two numbers"
	@@a,@@b = gets.chop,gets.chop 
	method(@@a,@@b)
	puts "after method is redefined"
	def method(a,b)
	puts "you entered two numbers "
	@a,@b  = a, b
	puts @a.to_i * @b.to_i
	end
	puts "enter two numbers"
	@@a1,@@b1 = gets.chop,gets.chop
	method(@@a1,@@b1)
end
end
c1 = Redefining.new()
#it call parent containing 2 method one is defined and another one is redefined so calls one after another
c1.parent
#while we call direct method we are able to call only redefined method .
c1.method(3,2)

