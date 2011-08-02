class RegistersController < ApplicationController

  def index
    @registers = Register.all    
  end

  def show
    @register = Register.find(params[:id])
  end

  def new
    @register = Register.new 
  end

  def edit
    @register = Register.find(params[:id])
  end

  def create
    @register = Register.new (params[:register])
     pic = params[:register][:picture]
 if @register.picture = pic.original_filename
  FileUtils.copy(pic.path, "#{Rails.root}/public/myfiles/#{pic.original_filename}")
 
      if @register.save
       redirect_to(@register, :notice => 'register was successfully created.')
      else
    render :action => "new"    
      end
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
