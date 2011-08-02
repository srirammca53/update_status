ActionController::Routing::Routes.draw do |map|

  map.resources :quizzes,
    :member => { :create_q  => :post,
                 :destroy_q => :post,
                 :reorder   => :post,
                 :answer    => :post,
                 :reset     => :post }

  map.home '', :controller => 'quizzes'
  map.connect ':controller/:action/:id'

end
