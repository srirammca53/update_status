class WebController < ApplicationController

def details 
@name ="myname"
@age = "24"
@qualification = "MCA"
render :layout => "display"

end
