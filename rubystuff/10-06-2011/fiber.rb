# fiber is lighter than thread and a bit like a method.but instead of being run in its entirety #when called, a Fiber will run until it yields a value. At this point, it will save its internal #state and suspend itself and control will return to the caller. 

 def read(file)
   Fiber.new do
     f = File.open( file, 'r' )
     puts f.sysread(4)
     until f.eof
       Fiber.yield( f.read.split(/ /) )
     end
   end
 end
 
 fib = read('ruby1.9.1.txt')
 
 while true do
   puts fib.resume 
#Fibers are like little sub-programs that can be run, paused and resumed at
# any time.They provide a thread-like interface for very little RAM.
 end
 


