require File.dirname(__FILE__) + '/../test_helper'
require 'quizzes_controller'

# Re-raise errors caught by the controller.
class QuizzesController; def rescue_action(e) raise e end; end

class QuizzesControllerTest < Test::Unit::TestCase
  def setup
    @controller = QuizzesController.new
    @request    = ActionController::TestRequest.new
    @response   = ActionController::TestResponse.new
  end

  # Replace this with your real tests.
  def test_truth
    assert true
  end
end
