class Dog
def talk

@sum =duck.23 + duck.34
puts @sum
end
end
class Duck
def talk
puts "Quack"
end
end
[Dog.new, Duck.new].each { |a| a.talk }
