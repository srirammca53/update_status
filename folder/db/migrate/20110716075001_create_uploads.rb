class CreateUploads < ActiveRecord::Migration
  def self.up
    create_table :uploads do |t|
      t.string :folder_password
      t.integer :folder_days
      t.string :folder_file_name
      t.string :folder_content_type
      t.string :folder_file_size
      t.datetime :folder_updated_at
      t.timestamps
    end
  end

  def self.down
    drop_table :uploads
  end
end
