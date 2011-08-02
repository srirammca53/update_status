class PhotosController < ApplicationController
  
  before_filter :require_login, :only => [ :create, :update, :destroy ]
  before_filter :find_album
  before_filter :find_photo, :only => [ :update, :destroy ]
  
  def index
    render :partial => "index"
  end

  # Renders HTML containing a JavaScript callback to finish the upload
  def create
    @photo = @album.photos.create params[:photo]
    render :layout => false
  end
  
  %w(full thumb medium).each do |size|
    class_eval <<-END
      def #{size}
        find_photo
        send_data @photo.#{size}, :filename => "\#{@photo.id}.#{size}.jpg", :type => 'image/jpeg', :disposition => 'inline'
      end
      caches_page :#{size}
    END
  end
  
  def update
    @photo.update_attributes :name => params[:name]
    render :update do |page|
      page["#{@photo.id}_name"].replace_html @photo.name
    end
  end

  def destroy
    @photo.destroy
    render :update do |page|
      page[:photos].update render(:partial => "index")
    end
  end
  
  private
  
    def find_album() @album = Album.find params[:album_id] end
    def find_photo() @photo = @album.photos.find params[:id] end

end
