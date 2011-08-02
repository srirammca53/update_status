class CreatePainters < ActiveRecord::Migration
  def self.up
    create_table :painters do |t|
      t.string :name
      t.integer :age
      t.integer :paint_cost
      t.integer :points

      t.timestamps
    end
  end

  def self.down
    drop_table :painters
  end
end
