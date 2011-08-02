puts "enum.all?"
%w{sreeram peter india cricket job}.all? {
|word| puts word.length}
puts "enum.any?"
 puts %w{ant bear cat}.any? {|word| word.length >= 4}   


 hash = Hash.new
  puts  %w(cat dog wombat).each_with_index 
puts hash
puts (1..7).entries
puts (1..34).find_index(23)
c = IO.constants
puts c.grep(/SEEK/)

 a = %w(cat sriam boss dog horse zzzzz elephant tttttttt)
  puts  a.min                                
  puts a.max {|a,b| a.length <=> b.length } 

