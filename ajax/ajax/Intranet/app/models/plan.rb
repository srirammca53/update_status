class Plan < Post
  
  def self.this_week
    Plan.find :all, :conditions => "start_date >= now() and start_date < '#{Date.today + 7}'", :order => "start_date asc"
  end
  
  def self.next_three_weeks
    Plan.find :all, :conditions => "start_date >= '#{Date.today + 7}' and start_date < '#{Date.today + 28}'", :order => "start_date asc"
  end
  
  def self.beyond
    Plan.find :all, :conditions => "start_date >= '#{Date.today + 28}'", :order => "start_date asc"
  end

end