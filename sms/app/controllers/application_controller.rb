class ApplicationController < ActionController::Base
  protect_from_forgery
include SMSFu
 has_sms_fu

end
