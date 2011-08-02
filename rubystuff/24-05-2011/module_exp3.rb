class Ab

attr_accessor(:one, :two)
:one
puts :one
attr_reader(:one, :two)
attr_writer(:one, :two)

end

puts Ab.instance_methods.sort
 c1 = Ab.new()
c1.one=23
