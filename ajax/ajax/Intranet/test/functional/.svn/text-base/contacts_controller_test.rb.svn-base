require File.dirname(__FILE__) + '/../test_helper'
require 'contacts_controller'

# Re-raise errors caught by the controller.
class ContactsController; def rescue_action(e) raise e end; end

class ContactsControllerTest < Test::Unit::TestCase

  include PostsTestHelpers

  def setup
    @controller = ContactsController.new
    @post_type = :contact
    setup2
  end

end
