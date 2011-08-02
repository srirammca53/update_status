class User < ActiveRecord::Base
def initialize(session)
    @session = session
    @session[:user_ids] ||= []
  end
  
  def add_user(user)
    @session[:user_ids] << user.id
  end
  
  def can_edit_user?(user)
    @session[:user_ids].include?(user.id) && user.created_at > 15.minutes.ago
  end

end
