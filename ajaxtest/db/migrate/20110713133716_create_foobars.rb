class CreateFoobars < ActiveRecord::Migration
  def self.up
    create_table :foobars do |t|
      t.string :foo
      t.string :bar

      t.timestamps
    end
  end

  def self.down
    drop_table :foobars
  end
end
