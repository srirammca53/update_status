class Album < ActiveRecord::Base
  has_many :photos, :order => "position", :dependent => :destroy
end
