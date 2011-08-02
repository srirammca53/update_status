

def status()
puts " enter your name"
$name = gets.chop
puts "enter your age"
$age = gets.chop
$status = 0
	if($age.to_i > 60)
	$status = "retired"
	yield($status,$age,$name)
	else
	$status ="Working"
	 yield($status,$age,$name)
	end

end

status {|x,y,z| puts z+", aged "+y+"and his/her present status is "+x }




