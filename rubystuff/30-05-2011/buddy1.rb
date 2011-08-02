
puts "enter your name"
$clt = gets.chop
puts "chat here"
	def chat 
	client = File.open("chat.txt","a+")
	today = Time.new
	@time = today.inspect
	client.seek(0,IO::SEEK_CUR)
	@chat = gets.chop
	last2 = File.open("chat.txt") { |f| f.extend(Enumerable).inject { |_,ln| ln } 
				}
	puts last2
	client.syswrite("#{@time}")
	client.syswrite("\n")
	client.syswrite( "#{$clt} :" )
	client.syswrite("#{@chat}")
	client.syswrite("\n")
	if @chat == "exit"
	close
	end
	chat
	end
chat
def close
puts "Thank you"
end


