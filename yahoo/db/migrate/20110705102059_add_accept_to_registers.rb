class AddAcceptToRegisters < ActiveRecord::Migration
  def self.up
    add_column :registers, :accept, :string
  end

  def self.down
    remove_column :registers, :accept
  end
end
