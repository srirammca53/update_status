class Temp
num = Array [10,25,34,95,76,54,59,37,71,64]
puts num
key = gets()
puts key
i=0
while i<num.length
if num[i]==key
puts "Value found."
i+=1
end
if i==num.length
puts "Value not found."
end
end
