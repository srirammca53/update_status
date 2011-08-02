class First
def surprise
puts "surprise"
end
end
f = First.new
f.surprise
def f.another
puts "routine"
end
f.another
f.surprise
f.another
f2 = First.new
f2.surprise
f2.another
=begin
Singleton classes are nothing but virtual classes where we implement our own definition to an already exixting methods and they will work in that particular instance only. After that they will work with their real behaviour. 
=end


