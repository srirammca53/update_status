class Register < ActiveRecord::Base

validates_presence_of :name
validates_presence_of :gender
validates_presence_of :country
validates_presence_of :email
validates_acceptance_of :accept
validates_presence_of :password
#validates_format_of :birthday, :with => /\d{2}\/\d{2}\/\d{4}/,
   # :message => " dd/mm/yyyy format"
validates_length_of :password,
    :minimum   => 6,
    :maximum   => 12
validates_uniqueness_of :email
 def password_strength
    errors.add(:password, "password is weak ") if
       password.length = 8 
    errors.add(:password, "password is strong") if
       password.length = 12 
  end

end
