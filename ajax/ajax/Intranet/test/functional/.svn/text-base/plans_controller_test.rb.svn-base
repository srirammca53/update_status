require File.dirname(__FILE__) + '/../test_helper'
require 'plans_controller'

# Re-raise errors caught by the controller.
class PlansController; def rescue_action(e) raise e end; end

class PlansControllerTest < Test::Unit::TestCase

  include PostsTestHelpers

  def setup
    @controller = PlansController.new
    @post_type = :plan
    setup2
  end

end
