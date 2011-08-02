# program on method overriding

class Methodoverride
	def method()
	@a = 3
	@b = 4
	puts "adding two number:#{@a + @b }"
	end
end
class B < Methodoverride

	def method()	
	super()	
	@a1 =12
	@b1 =23
	puts "addition od 2 numbers :#{@a * @b * @a1.to_i * @b1.to_i }"
	end
end
c1 = Methodoverride.new()
c1.method()
b=B.new()
b.method()

