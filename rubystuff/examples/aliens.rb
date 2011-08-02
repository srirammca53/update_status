def aliens
if block_given?
  i = 1
  j = 2
  yield(i, j)
 else 
 puts "magic"
 end
end

aliens {
 |x, y|

 puts x * y 
}
aliens
