class CreateDairies < ActiveRecord::Migration
  def self.up
    create_table :dairies do |t|
      t.string :name
      t.string :mobile
      t.text :address
      t.string :relation
      t.date :dob
      t.string :location

      t.timestamps
    end
  end

  def self.down
    drop_table :dairies
  end
end
