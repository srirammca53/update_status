require File.dirname(__FILE__) + '/../test_helper'
require 'users_controller'

# Re-raise errors caught by the controller.
class UsersController; def rescue_action(e) raise e end; end

class UsersControllerTest < Test::Unit::TestCase
  def setup
    @controller = UsersController.new
    @request    = ActionController::TestRequest.new
    @response   = ActionController::TestResponse.new
    signin
  end

  fixtures :users
  assert_valid_markup :index, :new

  def test_create
    post :create, 'user' => { 'email' => 'new@example.com', 'name' => 'New Smith', 'password' => 'secret' }
    assert_redirected_to :action => 'show'
  end
  
  def test_show
    get :show, :id => '1'
    assert_valid_markup
    # also test picture
  end
  
  def test_edit
    get :edit, :id => '1'
    assert_valid_markup
  end
  
  def test_update
    post :update, 'id' => 1, 'user' => { 'email' => 'updated@example.com', 'name' => 'Bob Smith' }
    assert_redirected_to :action => 'show', :id => '1'
  end
  
  def test_delete
    delete :destroy, :id => 1
    assert_redirected_to :action => 'index'
  end
  
end
