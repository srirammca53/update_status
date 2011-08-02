module CommentsHelper
ActiveRecord::Base.class_eval do
		  def self.validates_as_choice(attr_name, n, options={})
		    validates_inclusion_of attr_name, {:in => 1..n}.merge(options)
		  end
	end
end
