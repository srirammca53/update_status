class Comment < ActiveRecord::Base
# validates_as_choice :rating, 5
validates :commenter, :presence=>true
validates :rating, :presence=>true,:length=>{:maximum=>1}
validates :body, :presence => true
validates_acceptance_of :terms_of_service, :accept => 'yes'
 validates_format_of :rating, :with => /[0-5]/,
    :message => "Rating in between zero to five "
 #validates_length_of :commenter, :minimum => 6, :maximum => 12
  validates_length_of :body, :maximum => 500
#validates_numericality_of :rating, :only_integer => true, :less_than_or_equal_to => 5
validates_uniqueness_of :commenter, :case_sensitive => true, :on => :create
validates_confirmation_of :rating

validates_acceptance_of :terms_of_service, :accept => 'yes'
 validate :commenter_name,
    :rating_star
 
  def commenter_name
    errors.add(:commenter, "can't be blank") 
      if
      !commenter.blank? 
          end
  end
 
  def rating_star
    errors.add(:rating, "can't be greater than 5")
       if
       rating = 6 and rating > 6   
       end
      
  end
 

end
Comment.create(:commenter => "sriram").valid?
