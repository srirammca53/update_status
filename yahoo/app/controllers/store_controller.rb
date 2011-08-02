class StoreController < ApplicationController
private
def find_cart
session[:cart] || = Cart.new
end 
end
