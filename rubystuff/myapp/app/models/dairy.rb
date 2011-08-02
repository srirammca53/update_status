class Dairy < ActiveRecord::Base
validates :name, :presence => true, :length => {:minimum => 2, :maximum => 12}
validates :relation, :presence => true, :confirmation => true
validates :mobile, :presence => true, :numericality => true
validates :location, :presence => true, :uniqueness => { :case_sensitive => false }
validate :address_part
def address_part
    errors.add(:address, "can't be blank") if
      address.blank? 
  end
end
