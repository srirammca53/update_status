class Example
@@name = "sriram"
def display
 @@name
end
self.class_variable_set(:@@name , "sreeram")
end
c1 = Example.new()
puts Example.class_variable_defined?(:@@name)


Example.new.display
