class CommentsController < ApplicationController
def create
    @google = Google.find(params[:google_id])
    @comment = @google.comments.create(params[:comment])
    redirect_to google_path(@google)
  end
  def destroy
    @google = Google.find(params[:google_id])
    @comment = @google.comments.find(params[:id])
    @comment.destroy
    redirect_to google_path(@google)
  end
end
