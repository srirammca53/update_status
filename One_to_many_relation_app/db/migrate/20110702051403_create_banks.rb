class CreateBanks < ActiveRecord::Migration
  def self.up
    create_table :banks do |t|
      t.string :name
      t.string :account_number
      t.string :account_type
      t.text :address

      t.timestamps
    end
  end

  def self.down
    drop_table :banks
  end
end
