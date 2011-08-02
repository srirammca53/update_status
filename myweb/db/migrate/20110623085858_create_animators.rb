class CreateAnimators < ActiveRecord::Migration
  def self.up
    create_table :animators do |t|
      t.string :Animator_name
      t.integer :Animator_age
      t.interger :Animator_salary

      t.timestamps
    end
  end

  def self.down
    drop_table :animators
  end
end
