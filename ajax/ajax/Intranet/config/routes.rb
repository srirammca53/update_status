ActionController::Routing::Routes.draw do |map|

  # A resource for each post type
  map.resources :messages, :plans, :documents, :projects, :contacts, :member => { :download => :get }

  # A comments resource under every post type; e.g., /messages/comments and /documents/comments
  map.resources :comments, :path_prefix => "/:post_type/:post_id"

  # User and session resources
  map.resources :sessions
  map.resources :users, :collection => { :statuses => :get }, :member => { :status => :any }

  # Home and default routes
  map.home '', :controller => 'messages', :action => 'home'
  map.connect ':controller/:action/:id'

end
