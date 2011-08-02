class Photo < ActiveRecord::Base
  belongs_to :album
  acts_as_list :scope => :album

  def file= file
    with_image file.read do |img|
      self.width  = img.columns
      self.height = img.rows
      write_attribute 'file', img.to_blob
    end
  end
  
  def full() file end

  def thumb
    with_image do |image|
      geometry_string = (1 > (height.to_f / width.to_f)) ? "x100" : "100"
  		image = image.change_geometry(geometry_string) do |cols, rows, img|
  		  img.resize!(cols, rows)
  		end
  		image = image.crop(Magick::CenterGravity, 100, 100)
  		image.profile!('*', nil)
  		return image.to_blob { self.format='JPG'; self.quality = 60 }
  	end
  end

  def medium
    with_image do |img|
      maxw, maxh = 640, 480
      newratio = maxw.to_f / maxh.to_f
      w, h = img.columns,  img.rows
      oldratio = w.to_f / h.to_f
      scaleratio = oldratio > newratio ? maxw.to_f / w : maxh.to_f / h
      return img.resize(scaleratio).to_blob { self.format='JPG'; self.quality = 60 }
    end
  end

  private

    def with_image file=nil
      data = Base64.b64encode(file || self.file)
      img = Magick::Image::read_inline(data).first
      yield img
      img = nil
      GC.start
    end

end
