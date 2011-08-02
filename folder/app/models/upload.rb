class Upload < ActiveRecord::Base
 
attr_accessible :folder, :folder_password , :folder_days

has_attached_file :folder

end
