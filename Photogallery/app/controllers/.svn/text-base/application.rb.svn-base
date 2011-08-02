class ApplicationController < ActionController::Base
  
  private
  
    # Before filter to protect administrator actions
    def require_login
      unless logged_in?
        redirect_to home_url
        return false
      end
    end

    # Login information is set in environment.rb
    def logged_in?
      session[:username] == USERNAME and
      session[:password] == PASSWORD
    end
    helper_method :logged_in?
    
end