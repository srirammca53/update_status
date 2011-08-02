class MessagesController < PostsController
  
  # Default action for the app; might be changed to show a dashboard-like view
  def home
    flash.keep
    redirect_to messages_url
  end

  def index
    super
    @post_pages, @posts = paginate :messages, :order_by => 'created_at desc', :per_page => 30
  end

  private
    def model_name; 'Message'; end

end
