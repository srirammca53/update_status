class Comment < Post

  belongs_to :post

  validates_presence_of :body
  
end