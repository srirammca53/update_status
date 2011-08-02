require File.dirname(__FILE__) + '/../test_helper'

class DocumentTest < Test::Unit::TestCase
  fixtures :posts

  # Replace this with your real tests.
  def test_truth
    assert_kind_of Document, posts(:document)
  end
end
