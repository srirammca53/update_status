require File.dirname(__FILE__) + '/../test_helper'

class StatusesTest < ActionController::IntegrationTest
  fixtures :users
  
  def test_active_change
    alice = new_session :alice
    bob = new_session :bob
    alice.sees_inactive :bob
    bob.checks_statuses
    alice.sees_active :bob
  end
  
  def test_status_change
    #
  end
  
  private
  
    module TestExtensions

      def signs_in person=:alice
        get new_session_url
        assert_response :success
        assert_template 'sessions/new'
        post sessions_url, :session => { :email => users(person).email, :password => users(person).password }
        assert_response :redirect
        follow_redirect!
      end

      def goes_home
        get home_url
        follow_redirect!
        assert_response :success
        assert_template 'messages/index'
      end
      
      def checks_statuses
        get statuses_users_url
      end
      
      def sees_inactive person
        checks_statuses
        assert_tag :tag => "li", :attributes => { :class => "inactive" }, :child => Regexp.new(users(person).short_name)
      end

      def sees_active person
        checks_statuses
        assert_tag :tag => "li", :child => Regexp.new(users(person).short_name)
        assert_no_tag :tag => "li", :attributes => { :class => "inactive" }, :child => Regexp.new(users(person).short_name)
      end
      
      def looks_at_message message
        get message_url(:id => messages(message))
        assert_response :success
        assert_template "messages/show"
      end
      
      def adds_comment post, body
        post cart_items_url, :id => downloads(product).id
        assert_response :success
      end
      
    end
    
    def new_session person=nil
      open_session do |sess|
        sess.extend TestExtensions
        sess.signs_in(person) unless person.nil?
        yield sess if block_given?
      end
    end
  
end
