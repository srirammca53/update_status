  module Picky
	$ch = 9
     def Picky.extend_object(o)
       if Float === o
         puts "Can't add Picky to a String"
       else
         puts "Picky added to #{o.class}"
        end
     end
	puts $ch
	
   end
    self.freeze
	$ch =23
	puts $ch
   (s = Array.new).extend Picky  # Call Object.extend
   (s = 23.14).extend Picky
   (s = 123).extend Picky
