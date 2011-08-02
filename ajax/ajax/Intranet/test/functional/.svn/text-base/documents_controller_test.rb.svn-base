require File.dirname(__FILE__) + '/../test_helper'
require 'documents_controller'

# Re-raise errors caught by the controller.
class DocumentsController; def rescue_action(e) raise e end; end

class DocumentsControllerTest < Test::Unit::TestCase

  include PostsTestHelpers

  def setup
    @controller = DocumentsController.new
    @post_type = :document
    setup2
  end

end
