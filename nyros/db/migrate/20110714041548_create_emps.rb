class CreateEmps < ActiveRecord::Migration
  def self.up
    create_table :emps do |t|
      t.string :empname
      t.string :empdepartment
      t.date :date
      t.string :present
      t.string :late
      t.string :absent

      t.timestamps
    end
  end

  def self.down
    drop_table :emps
  end
end
