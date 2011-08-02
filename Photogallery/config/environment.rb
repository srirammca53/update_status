RAILS_GEM_VERSION = '1.1.5'

require File.join(File.dirname(__FILE__), 'boot')

Rails::Initializer.run do |config|
end

require 'rmagick'
require 'base64'

Mime::Type.register 'image/jpeg', :jpg
USERNAME, PASSWORD = "admin", "admin"
SITE_TITLE = "Gallery"
