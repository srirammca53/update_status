module ApplicationHelper

  def thumb_for photo
    url = thumb_photo_url(:album_id => photo.album_id, :id => photo)
    image = image_tag(url, :class => "thumb", :alt => "")
	  link_to_function image, nil, :class => "show" do |page|
	    page.photo.show medium_photo_url(:album_id => photo.album_id, :id => photo)
	  end
	end
	
	def toggle_edit_photo id
	  page.toggle "#{id}_name", "#{id}_edit", "#{id}_delete"
	end

end
