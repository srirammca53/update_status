#Index operator for string now returns string instead of ASCII value.
puts "ruby on rails"[6]

#? works differently while compare to ruby1.8.7 returns character instead of ascii value
puts ?a


a=[1,34,3.5,"sree","naga"]
puts a.to_s # array.to_s 

#lambda in ruby 1.9.1
l= ->(x,y){x*y}
puts l.call(10,5);

# hashs in ruby 1.9.1 is different while comparing to 1.8.7 the hash declaration is

h = {:first => "ram",:second => "sree",:third => "nyros"}
puts h

# we can also declare hash as follows in ruby 1.9.1
h1 = {first: "ram", second: "sree", third: "nyros"}
puts h1

h2 = {1 => "sree", 2 => "ram"}
puts h2

# for loop
for i in 1..12
puts "s"
end
p i

#each 
(1..12).each{|j|}
# p j     --> raises  undefined local variable or method `j'

puts (1..53).cover?(37)

a="string clear"
# string.clear will raise undefined method in ruby 1.8.7 

puts a.clear

#dot syntax changes

string = "this is the string for dot syntax change"
test = string
.split(" ")
.to_a

puts test[2]

puts test

#string index operator
puts string[3]

str = "this is string"

#lambda
multiply_2 = ->(x){x*2}
p multiply_2.call(4)


#parser changes

games = %w(cricket basketball shuttle)
puts games
[*games, 'wwe']
puts games






