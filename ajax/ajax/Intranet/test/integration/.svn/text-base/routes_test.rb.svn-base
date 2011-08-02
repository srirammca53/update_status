require "#{File.dirname(__FILE__)}/../test_helper"

class RoutesTest < ActionController::IntegrationTest
  
  def setup
    get "/" # needed to create a controller context
  end

  def test_recognize
    assert_routing "/messages/1", :controller => 'messages', :action => 'show', :id => "1"
  end

  def test_generate
    assert_equal "http://www.example.com/messages", messages_url
  end
  
end
