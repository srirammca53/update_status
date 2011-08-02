module Mod
	include Math
	include Comparable
     alias_method :orig_exit, :exit
     def orig_exit(code=0)
	 puts "#{code}"
      puts "Exiting with code #{code}"
      
	puts "orginal code is :"
	puts "orig_exit(#{code})"
	
     end
   end
   include Mod
	puts Mod.ancestors
   orig_exit(99)
   exit(200)

