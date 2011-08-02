class Login < ActiveRecord::Base
 attr_accessible :email, :password
  has_secure_password
  validates_presence_of :password, :on => :create

end
