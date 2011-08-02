require File.dirname(__FILE__) + '/../test_helper'
require 'comments_controller'

# Re-raise errors caught by the controller.
class CommentsController; def rescue_action(e) raise e end; end

class CommentsControllerTest < Test::Unit::TestCase
  def setup
    @controller = CommentsController.new
    @request    = ActionController::TestRequest.new
    @response   = ActionController::TestResponse.new
    signin
  end

  fixtures :users, :posts

  def test_index
    get :index, :post_id => posts(:message)
  end
  
  def test_create
    @request.env["HTTP_REFERER"] = '/'
    post :create, :post_id => posts(:message), :comment => posts(:comment).attributes
    assert_redirected_to :controller => 'messages', :action => 'home'
  end
  
  def test_show
    get :show, :post_id => posts(:comment).post_id, :id => posts(:comment).id
    assert_valid_markup
  end

end
