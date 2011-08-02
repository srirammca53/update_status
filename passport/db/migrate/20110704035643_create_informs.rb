class CreateInforms < ActiveRecord::Migration
  def self.up
    create_table :informs do |t|
      t.string :passport
      t.references :user

      t.timestamps
    end
  end

  def self.down
    drop_table :informs
  end
end
