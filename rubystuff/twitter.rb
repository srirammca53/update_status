require 'rubygems'
require 'twitter'

puts Twitter::Client.new.user("srirammca").name
puts twitter = Twitter::Base.new( 'srirammca', 'nagamca' )

puts Twitter.user("srirammca").location
#puts Twitter.friends("srirammca")
#Twitter::user.Authenticated?("srirammca")
search = Twitter::Search.new
search.containing("Hi").to("orton").result_type("recent").per_page(3).each do |r|
  puts "#{r.from_user}: #{r.text}"
end
#puts Twitter.follower_ids("srirammca")
#puts Twitter.status(27558893223).text
c = Twitter::Client.new;
puts c.respond_to?('status')





