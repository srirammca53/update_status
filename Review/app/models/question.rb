class Question < ActiveRecord::Base
  belongs_to   :quiz
  acts_as_list :scope => :quiz
  
  # Returns the next question in the quiz after
  # this one, excluding those keys passed in +right_keys+
  def next right_keys
    quiz.questions.find :first,
      :conditions => "position > #{position}" +
        (right_keys.blank? ? "" : " and id not in (#{right_keys})")
  end
end