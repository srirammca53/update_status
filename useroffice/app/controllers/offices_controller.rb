class OfficesController < ApplicationController

  def index
    @offices = Office.all
         render :action => "index"     
end


  def show
    @office = Office.find(params[:id])
        render :action => "show"
     end

  def new
    @office = Office.new
    render :action =>  "new" 
  
  end


  def edit
    @office = Office.find(params[:id])
   
  end

 
  def create
    @office = Office.new(params[:office])
      if @office.save
         redirect_to(@office, :notice => 'office was successfully created.') 
      else
         render :action => "new" 
    end
  end

 
  def update
    @office = Office.find(params[:id])

    
      if @office.update_attributes(params[:office])
         redirect_to(@office, :notice => 'users was successfully updated.') 
      else
        render :action => "edit" 
    end
  end


  def destroy
    @office = Office.find(params[:id])
    @office.destroy
           redirect_to(offices_url)
         end

end
