class CreateProfiles < ActiveRecord::Migration
  def self.up
    create_table :profiles do |t|
      t.string :name
      t.integer :age
      t.string :qualification
      t.text :address
      t.string :designation
      t.string :salary
      t.text :about_yourself

      t.timestamps
    end
  end

  def self.down
    drop_table :profiles
  end
end
