data,change=Array.new,Array.new
count=-1
File.open("data.txt","r") {|myfile| myfile.each_line {|line| data=line.split(" ")}}
data.collect {|item| change[count+=1]=item if item.match(/^#/)}
data.collect {|item| change[count+=1]=item if !item.match(/^#/)}
change.collect {|item| item.gsub!("#","")}
File.open("data.txt","a+") {|myfile| change.collect {|item| myfile.write(item+"\n")}}

