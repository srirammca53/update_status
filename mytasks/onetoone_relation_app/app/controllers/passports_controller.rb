class PassportsController < ApplicationController
 def create
    @detail = Detail.find(params[:detail_id])
    @detail = @detail.comments.create(params[:passport])
    redirect_to detail_path(@detail)
  end
end
