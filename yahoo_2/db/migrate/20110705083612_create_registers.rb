class CreateRegisters < ActiveRecord::Migration
  def self.up
    create_table :registers do |t|
      t.string :name
      t.string :gender
      t.date :birthday
      t.string :country
      t.string :email
      t.string :password
      t.string :security

      t.timestamps
    end
  end

  def self.down
    drop_table :registers
  end
end
