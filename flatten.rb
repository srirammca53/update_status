class Flat
def check()
arr1 = []
puts "Enter size of an array"
@t = gets()
for @i in 1..@t.to_i
@ele = gets()
arr1<<@ele
end
puts arr1
end
c1 = Flat.new()
c1.check()

