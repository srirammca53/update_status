require File.dirname(__FILE__) + '/../test_helper'
require 'messages_controller'

# Re-raise errors caught by the controller.
class MessagesController; def rescue_action(e) raise e end; end

class MessagesControllerTest < Test::Unit::TestCase

  include PostsTestHelpers

  def setup
    @controller = MessagesController.new
    @post_type = :message
    setup2
  end

end
