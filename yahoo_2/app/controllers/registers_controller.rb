class RegistersController < ApplicationController
 before_filter :authenticate, :except => [:index, :show, :create]
  def index
    @registers = Register.all
      render :action => "index"
  end

  def show
    @register = Register.find(params[:id])
    render :action => "show"
  end

  def new
    @register = Register.new
     render :action => "new"
  end


  def edit
    @register = Register.find(params[:id])
  end

  def create
    @register = Register.new(params[:register])
   
      if @register.save
       redirect_to(@register, :notice => 'register was successfully created.')
      else
    render :action => "new"    
      end
    
  end


  def update
    @register = Register.find(params[:id])
    
      if @register.update_attributes(params[:register])
        redirect_to(@register, :notice => 'register was successfully updated.')   
      else
        render :action => "edit" 
      
      
    end
  end

  def destroy
    @register = Register.find(params[:id])
    @register.destroy

   
     redirect_to(registers_url) 
 
    end
 
end
