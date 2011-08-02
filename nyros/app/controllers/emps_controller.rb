class EmpsController < ApplicationController
 def index
    @emps = Emp.all
      render :action => "index"
  end

  def show
    @emp = Emp.find(params[:id])
    render :action => "show"
  end

  def new
    @emp = Emp.new
     render :action => "new"
  end


  def edit
    @emp = Emp.find(params[:id])
  end

  def create
    @emp = Emp.new(params[:emp])
   
      if @emp.save
       redirect_to(@emp, :notice => 'emp was successfully created.')
      else
    render :action => "new"    
      end
    
  end


  def update
    @emp = Emp.find(params[:id])
    
      if @emp.update_attributes(params[:emp])
        redirect_to(@emp, :notice => 'emp was successfully updated.')   
      else
        render :action => "edit" 
      
      
    end
  end

  def destroy
    @emp = Emp.find(params[:id])
    @emp.destroy

   
     redirect_to(emps_url) 
 
    end
 
end
