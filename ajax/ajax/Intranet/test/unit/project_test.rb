require File.dirname(__FILE__) + '/../test_helper'

class ProjectTest < Test::Unit::TestCase
  fixtures :posts

  # Replace this with your real tests.
  def test_truth
    assert_kind_of Project, posts(:project)
  end
end
