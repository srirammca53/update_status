class HomeController < ApplicationController
  def index
@name = "sriram"
@qualification = "MCA"
@station = "kakinada"
#render :action => "index"
#render_to_string "this is the string"
render :partial => 'home'
#@i=0
#render :file => '/app/views/home/home.rhtml', :layout =>true
#render :text => "Let's use a layout", :layout => true and return if @i.nil?
#render :nothing, :status => 403 
#render :action => "index.rhtml", 

         # :content_type => "home.html"
#render :inline => "<%= 'hello , ' * 3 + 'again' %>"
#render :inline => "<%= 'hello ' + name %>", 
                   # :locals => { :name => "david" }
#render :nothing
#render_to_string(:partial => 'Temporary', :layout => false, 
                 #:locals => {:my_object => "temp"})

#@left_sidebar = render_to_string(:template => 'home/index.rhtml', :layout => false)
#render_to_string :index

	
	


  end

end
