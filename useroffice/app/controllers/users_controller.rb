class UsersController < ApplicationController

  def index
    @users = User.all
      render :action => "index"
  end

  def show
    @user = User.find(params[:id])
    render :action => "show"
  end

  def new
    @user = User.new
     render :action => "new"
  end


  def edit
    @user = User.find(params[:id])
  end

  def create
    @user = User.new(params[:user])
   
      if @user.save
       redirect_to(@user, :notice => 'users was successfully created.')
      else
    render :action => "new"    
      end
    
  end


  def update
    @user = User.find(params[:id])
    
      if @user.update_attributes(params[:user])
        redirect_to(@user, :notice => 'users was successfully updated.')   
      else
        render :action => "edit" 
      
      
    end
  end

  def destroy
    @user = User.find(params[:id])
    @user.destroy

   
     redirect_to(users_url) 
 
    end
 
end

