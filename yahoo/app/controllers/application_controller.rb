class ApplicationController < ActionController::Base
  protect_from_forgery
session :session_key => '_depot_session_id' 
	def find_cart
	unless session[:cart]
	session[:cart] = Cart.new 
	end
session[:cart] 
end 
end

