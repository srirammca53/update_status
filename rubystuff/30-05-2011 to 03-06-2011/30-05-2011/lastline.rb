last = File.open("para.txt") { |f| f.extend(Enumerable).inject { |_,ln| ln } 
}
puts last
