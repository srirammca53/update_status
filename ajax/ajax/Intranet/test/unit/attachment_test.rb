require File.dirname(__FILE__) + '/../test_helper'

class AttachmentTest < Test::Unit::TestCase
  fixtures :attachments

  # Replace this with your real tests.
  def test_truth
    assert_kind_of Attachment, attachments(:first)
  end
end
