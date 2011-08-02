require File.dirname(__FILE__) + '/../test_helper'
require 'projects_controller'

# Re-raise errors caught by the controller.
class ProjectsController; def rescue_action(e) raise e end; end

class ProjectsControllerTest < Test::Unit::TestCase

  include PostsTestHelpers

  def setup
    @controller = ProjectsController.new
    @post_type = :project
    setup2
  end

end
