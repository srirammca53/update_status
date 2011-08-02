class A  
  

               def four 
	     puts 'In Class A First method'  
	     end 
 
	     def third  
	     puts 'In Class A second method'  
	     end  
end  

class B < A 
@@m =10
     def third
     super
     puts 'In B class'  
     end  
end  

class C < B  
puts @@m
       def four 
       super
         
       puts 'In C class'  
       end  
end  
   son = C.new  
   son.four
   son.third
    
