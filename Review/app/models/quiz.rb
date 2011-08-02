class Quiz < ActiveRecord::Base

  # Methods added to the association proxy, e.g quiz.questions.unmissed
  module AssociationExtension

    def unmissed(right_keys = nil)
      cond = "id not in (#{right_keys})" unless right_keys.blank?
      find :all, :conditions => (cond || nil), :limit => 5
    end

  end

  has_many :questions, 
    :order     => 'position', 
    :dependent => :destroy, 
    :extend    => AssociationExtension

  # Finds the last 20 quizzes created
  def self.recent
    find :all, :limit => 20, :order => "created_at desc"
  end

end
