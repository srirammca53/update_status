

# program to copy the content of one file to other file at a particular line

afile1 = File.open("text1.txt","a+")
afile2 = File.open("text2.txt","a+")
puts "this is the content of first file"
puts"\n"
puts afile1.readlines
puts "\n"
puts "this is the content of second file"
puts "\n"
@content = afile2.readlines
puts @content
puts "now you need to append the file2 in file1"


    	
		afile1.syswrite(@content)
  		
		
afile1.close
afile2.close

