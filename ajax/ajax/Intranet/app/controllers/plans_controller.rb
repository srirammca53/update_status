class PlansController < PostsController
    
  def index
    super
    @page_title = "Upcoming Event Plans"
    @this_week = Plan.this_week
    @next_three_weeks = Plan.next_three_weeks
    @beyond = Plan.beyond
  end

  private
    def model_name; 'Plan'; end
    def post_type; 'Event Plan'; end

end
