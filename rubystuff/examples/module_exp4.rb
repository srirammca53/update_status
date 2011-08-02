Class Abc
end
a = {
 def  hello() 
 "hello" 
end 
}
Abc.module_eval(a)
puts Abc.new.hello()
Abc.module_eval("sriram" , "hello" , "1")

