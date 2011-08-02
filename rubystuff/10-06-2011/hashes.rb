# hashes are different while comparing to the ruby 1.8.7 in 1.9.1

# ruby 1.9.1 has many changes for Hash.

rank = {  cena: '2',randy: '1', micheals: '3'}
p rank.to_a
rank.each{|x| p x }
rank.each_pair{|x| p x }
puts rank.values 
puts rank.keys

puts rank.select{|x,y| x = :randy }

# to_s behaves differently while compare to ruby1.8.7

p rank.to_s

# to_a behave differently while compare to Ruby 1.8.7

p rank.to_a


