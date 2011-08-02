 class Tabler
num=gets.chomp
till=gets.chomp
count=1
value=0
while count<till.to_i
	value= count*num.to_i
	puts value.to_s
	count+=1
end
end
