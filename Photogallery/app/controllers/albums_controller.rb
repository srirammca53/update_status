class AlbumsController < ApplicationController
  
  before_filter :require_login, :only => [ :create, :update, :destroy ]
  before_filter :find_album, :only => [ :show, :update, :destroy ]

  def index
    @albums = Album.find :all
  end
  
  def create
    @album = Album.create params[:album]
    redirect_to album_url(:id => @album)
  end
  
  def show
  end
  
  def update
    @album.update_attributes params[:album]
    render :text => @album.name
  end
  
  def destroy
    @album.destroy
    redirect_to albums_url
  end
  
  private
  
    def find_album() @album = Album.find params[:id] end

end
