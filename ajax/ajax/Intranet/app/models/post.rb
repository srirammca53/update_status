class Post < ActiveRecord::Base
  
  has_many   :comments,  :order => 'id', :dependent => :destroy
  belongs_to :creator, :class_name => 'User', :foreign_key => "created_by"
  belongs_to :attachment, :dependent => :destroy

  validates_presence_of :name

  # Creates an attachment from a file upload
  def file=(file)
    unless file.size == 0
      attachment=Attachment.new :content => file.read
      attachment.save
      write_attribute('attachment_id', attachment.id)
      write_attribute('attachment_filename', file.original_filename)
      write_attribute('attachment_content_type', file.content_type)
      write_attribute('attachment_size', file.size)
    end
  end
  
end