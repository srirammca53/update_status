class AddLanguagesToUsers < ActiveRecord::Migration
  def self.up
    add_column :users, :languages, :string
  end

  def self.down
    remove_column :users, :languages
  end
end
