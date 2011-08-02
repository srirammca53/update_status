class Maths

def add(a,b)
a1=a
b1=b
c=a1 + b1
puts "if addition"+c.to_i
end

def sub(a,b)
a1=a
b1=b
c=a1 - b1
puts "if substraction "+c.to_i
end

def mul(a,b)
a1=a
b1=b
c=a1 * b1
puts "if multiplication "+c.to_i
end
end

Maths() m1=new Maths()
puts "enter any 2 numbers"
i= gets()

j= gets()
puts i+"\n"+j

m1.add(i.to_i,j.to_i)
m1.sub(i.to_i,j.to_i)
m1.mul(i.to_i,j.to_i)

