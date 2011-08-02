require File.dirname(__FILE__) + '/../test_helper'
require 'sessions_controller'

# Re-raise errors caught by the controller.
class SessionsController; def rescue_action(e) raise e end; end

class SessionsControllerTest < Test::Unit::TestCase
  def setup
    @controller = SessionsController.new
    @request    = ActionController::TestRequest.new
    @response   = ActionController::TestResponse.new
  end
  
  fixtures :users
  assert_valid_markup :new

  def test_create
    post :create, 'session' => { 'email' => users(:alice).email, 'password' => users(:alice).password }
    assert_redirected_to :controller => 'messages', :action => 'home'
  end

  def test_delete
    delete :destroy, :id => '123'
    assert_redirected_to :controller => 'sessions', :action => 'new'
  end

end
