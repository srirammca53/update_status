# Base class - Person
# subclasses - Teacher, Staff and Delegate

class Person
def initialize(cost,name = "unknown")
@name = name
@cost = cost
end
def aussie
print "Wotcha, #{@name}\n"
end
def getcost
return @cost
end
def getname
return @name
end
end
class Delegate < Person
end
class Staff < Person
def initialize(name = "open")
super(0.00,name)
end
end
class Teacher < Person
def aussie
print "G'Day, #{@name}\n"
end
end

ingroup = [ Delegate.new(70.50,"Ann"),
Delegate.new(70.50,"Bill"),
Teacher.new(0.00,"Reginald"),
Delegate.new(0.00,"Chloe"),
Teacher.new(0.00,"Graham"),
Delegate.new(35.25),
Staff.new("Leah"),
Staff.new("Lisa"),
Staff.new,
Delegate.new(35.25,"David")]

totcost = 0.0
ingroup.each do |psn|
psn.aussie
totcost += psn.getcost
end
print "Total cost is #{totcost}\n"



