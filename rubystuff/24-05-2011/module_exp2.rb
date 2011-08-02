module M
     def self.included(klass)
       puts "Included in #{klass}"
     end
   end

module A
     include M  # -> Included in A
	append_features(M)
   end

module B
     append_features(M)  # Nothing
   end

puts M
puts A
puts B
