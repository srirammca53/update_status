ActionController::Routing::Routes.draw do |map|

  %w(full thumb medium).each do |size|
    map.named_route "#{size}_photo", "albums/:album_id/photos/:id.#{size}.jpg", :controller => 'photos', :action => size
  end

  map.resources :sessions
  map.resources :albums do |album|
    album.resources :photos
  end

  map.home '', :controller => 'albums'
  map.connect ':controller/:action/:id'

end
