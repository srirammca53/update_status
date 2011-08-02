class ContactsController < PostsController

  # If params[:letter] is specified, only returns users whose last names start with it
  def index
    @page_title = post_type.pluralize
    @post = model.new
    @posts = params[:letter] ? Contact.letter(params[:letter]) : Contact.find(:all)
  end

  private
    def model_name; 'Contact'; end

end
