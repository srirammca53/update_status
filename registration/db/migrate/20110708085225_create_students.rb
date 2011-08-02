class CreateStudents < ActiveRecord::Migration
  def self.up
    create_table :students do |t|
      t.string :email
      t.string :password

      t.timestamps
    end
  end

  def self.down
    drop_table :students
  end
end
