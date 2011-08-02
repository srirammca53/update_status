class HomeController < ApplicationController
  def index
  end
  def user_details
   session[:register] = params[:username]
   session[:register] = params[:password]
   redirect_to users_path
 end
end
