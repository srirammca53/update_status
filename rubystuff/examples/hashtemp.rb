class Hashtemp
def check()

h = { "a" => 100, "b" => 200 }
 h.each_value {|value| puts value }
puts h.empty?
end

end
c1 = Hashtemp.new()
c1.check()

