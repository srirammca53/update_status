class CommentsController < ApplicationController

  before_filter :find_post

  def index
  end

  # Handles both Ajax and regular form submissions
  def create
    @comment = Comment.new params[:comment]
    @comment.post_id = @post.id
    @comment.name = "Re: #{@post.name}"
    @comment.creator = current_user
    @comment.save
    respond_to do |format|
      format.html {
        flash[:notice] = "Comment saved."
        redirect_to :back
      }
      format.js {
        render :update do |page|
          page[:comments].reload
        end
      }
    end
  end
  
  def show
    @comment = @post.comments.find params[:id]
  end
  
  private
  
    def find_post
      @post = Post.find params[:post_id]
    end
  
end