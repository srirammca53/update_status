class SessionsController < ApplicationController

  before_filter :create_first_user, :only => :new
  skip_before_filter :require_login
  filter_parameter_logging :password

  def new
    redirect_to home_url if logged_in?
    @user = User.new
  end
  
  def create
    if user = User.authenticate(params[:session][:email], params[:session][:password])
      reset_session
      session[:user_id] = user.id
      redirect_back_or_default home_url
      flash[:notice] = "Signed in successfully"
    else
      flash[:warning] = "There was a problem signing you in. Please try again."
      @user = User.new
      render :action => 'new'
    end
  end

  def destroy
    reset_session
    flash[:notice] = "You have been signed out."
    redirect_to new_session_url
  end
  
  private
  
    # Before filter that automatically creates a recordand signs in for the first user of the system
    def create_first_user
      return true unless User.count == 0
      user = User.new :admin => 1
      user.save_with_validation false
      session[:user_id] = user.id
      redirect_to home_url
    end
  
end
