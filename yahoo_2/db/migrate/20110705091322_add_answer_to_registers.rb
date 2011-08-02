class AddAnswerToRegisters < ActiveRecord::Migration
  def self.up
    add_column :registers, :answer, :string
  end

  def self.down
    remove_column :registers, :answer
  end
end
