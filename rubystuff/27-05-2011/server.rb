load "client.rb"
server = File.open("server.txt" , "r+")
client.syswrite(Io.readlines("server.txt"))
