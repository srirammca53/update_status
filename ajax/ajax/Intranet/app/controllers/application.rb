class ApplicationController < ActionController::Base

  include Authentication
  before_filter :require_login
  before_filter :set_system_announcement
  before_filter :check_for_valid_user
  
  private

    # Feel free to remove or change this announcement when customizing the application to your needs
    def set_system_announcement
      flash.now[:system_announcement] = "This is the <strong>Ajax on Rails Intranet</strong>, <br/>released as part of <a href=\"http://www.oreilly.com/catalog/9780596527440/\"><em>Ajax on Rails</em></a> from O&rsquo;Reilly Media."
    end

    # Helper method to determine whether the current user can modify +record+
    def can_edit? record
      return true if current_user.admin? # admins can edit anything
      case record.class.to_s
        when 'User'
          record.id == current_user.id # regular users can't edit other users
        when 'Message'
          record.created_by == current_user.id # messages can only be edited by their creators
        else true # everyone can edit anything else
      end
    end
    helper_method :can_edit?

    # Helper method to determine whether the current user is an administrator
    def admin?; current_user.admin?; end
    helper_method :admin?
    
    # Before filter to limit certain actions to administrators
    def require_admin
      unless admin?
        flash[:warning] = "Sorry, only administrators can do that."
        redirect_to messages_url
      end
    end

    # Before filter that insists the current user model is valid -- generally
    # just used when the first user is craeted.
    def check_for_valid_user
      if logged_in? and !current_user.valid?
        flash[:warning] = "Please create your administrator account"
        redirect_to edit_user_url(:id => current_user)
        return false
      end
    end

end
