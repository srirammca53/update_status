afile = File.new("plaiin.txt" , "w+")
afile.syswrite("this is the plain text a part from prince of persia")
puts afile
afile.close
afile = File.open("plaiin.txt","r+")
arr1 = []


arr1 =  %w{ "#{IO.readlines("plaiin.txt")}" }
puts arr1

