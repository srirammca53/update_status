class A
  def hi
    puts "Hi from #{self.class}"
  end
def bye
    puts "Bye from #{self.class}"
  end
def achoo
    puts "Achoo from #{self.class}"
  end
end

class B
	def initialize
    		@b = A.new
	end
	A.instance_methods.each do |name|  
		define_method (name) do
			@b.send(name)
		end
	end
end
A.new.hi
B.new.hi
B.new.bye
B.new.achoo
