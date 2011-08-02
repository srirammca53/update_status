class Contact < Post

  validates_format_of :name, :with => /^.+ .+$/, :message => "must include full name"
  validates_format_of :email, :with => /^(([^@\s]+)@((?:[-a-z0-9]+\.)+[a-z]{2,}))?$/

  # Find by first letter of last name
  def self.letter letter
    Contact.find :all, :conditions => [ "name like ?", '% '+letter+'%' ]
  end
  
  # Turns "Scott Douglas Raymond" into "Raymond, Scott Douglas"
  def reversed_name
    names = name.split
    "#{names.pop}, #{names.join ' '}"
  end

end