class SessionsController < ApplicationController

  def create
    session[:username], session[:password] = params[:username], params[:password]
    flash[:notice] = "Couldn't authenticate you." unless logged_in?
    redirect_to :back
  end

  def destroy
    reset_session
    redirect_to :back
  end

end
