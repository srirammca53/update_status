class CommentsController < ApplicationController
  def create
   
    @comment = Comment.r comment(params[:comment])
    respond_to do |format|
   format .html { redirect_to post_path(@comment.post_id) }
   format.js
    end
  end
def destroy
    @post = Post.find(params[:post_id])
    @comment = @post.comments.find(params[:id])
    @comment.destroy
    redirect_to post_path(@post)
  end
end
