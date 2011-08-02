class Numberprint



def add(a,b,c)
      @n1=a
      @n2=b
      @n3=c
      @n4=@n1.to_i+@n2.to_i+@n3.to_i
   end
   def display()
      puts "first number#@n1"
      puts "second number #@n2"
      puts "Third number #@n3"
      puts "the total addition:#@n4"
    end
end


add1=Numberprint.new()
add2=Numberprint.new()


add1.add("2","3","4")
add2.add("21","22","23")

add1.display()
add2.display()



