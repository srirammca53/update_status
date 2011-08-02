 h={}
begin
	puts "Enter a number"
	num=gets.chomp.to_i
	factors=Proc.new do|num|
		factors_arra=""
		1.upto(num-1) do |factor|
			factors_arra=factors_arra+" "+factor.to_s if(num%factor==0)		
		end	
		factors_arra
	end
	h[num]=factors.call(num)	
	puts "You wish to continue (y/n)"
	continue=gets.chomp
end while(continue=='y')
arra=h.to_a
arra.collect {|va| puts va}
