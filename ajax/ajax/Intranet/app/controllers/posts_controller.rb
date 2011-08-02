class PostsController < ApplicationController
  
  before_filter :find_post, :only => [ :show, :download, :edit, :update, :destroy ]
  before_filter :check_permissions, :only => [ :update, :destroy ]
  
  def index
    @page_title = post_type.pluralize
    @post = model.new
    @posts = model.find :all
  end
  
  def new
    @page_title = "New #{post_type}"
    @edit_on = true
    @post = model.new
  end

  def create
    @post = model.new params[:post]
    @post.creator = current_user
    @post.updated_by = @post.created_by
    if @post.save 
      flash[:notice] = 'Post successfully created.'
      redirect_to :action => 'index'
    else
      @page_title = "New #{post_type}"
      @edit_on = true
      render :action => 'new'
    end
  end

  def show
  end

  def download
    filename = @post.attachment_filename.split(/\\/).last
    send_data @post.attachment.content, :filename => filename, :type => @post.attachment_content_type, :disposition => 'attachment'
  end
  
  def edit
    @edit_on = true
    render :action => 'show'
  end
  
  def update
    if @post.update_attributes params[:post].merge(:updated_by => current_user)
      flash[:notice] = 'Your changes were saved.'
      redirect_to :action => 'show'
    else
      @edit_on = true
      render :action => 'show'
    end
  end

  def destroy
    @post.destroy
    flash[:notice] = "The post was deleted."
    redirect_to :action => 'index'
  end
  
  private
  
    # The name of the model associated with the controller. Expected to be overridden.
    def model_name; 'Post'; end

    # The 'human name' of the model, if different from the actual model name.
    def post_type; model_name; end
    helper_method :post_type

    # The model class associated with the controller.
    def model; eval model_name; end
  
    def find_post
      @post = model.find params[:id]
    end
    
    # Before filter to bail unless the user has permission to edit the post.
    def check_permissions
      unless can_edit? @post
        flash[:warning] = "You can't edit that post."
        redirect_to :action => 'show'
        return false
      end
    end
  
end
