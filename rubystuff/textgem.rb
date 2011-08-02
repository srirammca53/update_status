require "rubygems"
gem 'text-format', '~>1.0.0'

a1 = Text/Format
a1.Alpha.new(:postfix => ".")
puts a1[0]  # => "a."
puts a1[1]  # => "b.
puts a1[27] # => ""

a2 = Text::Format::Alpha.new(:prefix => "A.")
puts a2[0]  # => "A.a"
puts a2[1]  # => "A.b"
puts a2[27] # => ""

a3 = Text::Format::Alpha.new(:transform => :upcase)
puts a3[0]  # => "A"
puts a3[1]  # => "B"
puts a3[27] # => ""

a4 = Text::Format::Alpha.new(:wrap => true)
puts a4[0]  # => "a"
puts a4[27] # => "b"
