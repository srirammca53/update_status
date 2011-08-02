require File.dirname(__FILE__) + '/../test_helper'

class CommentTest < Test::Unit::TestCase
  fixtures :posts

  # Replace this with your real tests.
  def test_truth
    assert_kind_of Comment, posts(:comment)
  end
end
