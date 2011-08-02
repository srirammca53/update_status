puts "enter your name"
$server = gets.chop
puts "chat here"
def chat
server = File.open("chat.txt","a+")
arr = server.readlines("chat.txt")
server.seek(0,IO::SEEK_CUR)
@chat = gets.chop
puts arr
server.syswrite("\n")
server.syswrite( "#{$server} :" )
server.syswrite("#{@chat}")
server.syswrite("\n")
	if @chat == "exit"
	close
	end
	chat
end

chat
def close
puts "Thank you"
end



