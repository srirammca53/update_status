
puts "enter your name"
$clt = gets.chop
puts "chat here"
	def chat 
	client = File.open("chat.txt","a+")
	arr = client.readlines("chat.txt")
	client.seek(0,IO::SEEK_CUR)
	@chat = gets.chop
	puts arr
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



