class Account
	attr_accessor :balance
	private :balance
		def var()
		@var = "#{:balance}"
		great(other)
		end
	def great(other)
	return @var < other.balance
	end
end
class AccountC < Account
	def disp
		puts @var
	end
end
ob1=Account.new
ob2=Account.new
ob3=AccountC.new
ob1.balance=12
ob2.balance=39
ob3.balance=44
ob3.disp
puts ob1.great(ob2)
