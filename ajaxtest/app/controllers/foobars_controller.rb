class FoobarsController < ApplicationController
  def index
      @foobars = Foobar.find(:all)
      
      respond_to do |format|
        format.html # index.html.erb
      end
    end
def set
    render :text  => params[:updatewith]
  end
end
