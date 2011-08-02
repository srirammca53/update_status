pdf.text "Profile ##{@profile.id}", :size => 30, :style => :bold

pdf.move_down(30)

items = @profile.map do |profile|
  [
    profile.name,
    profile.age
  ]
end

pdf.table profiles, :border_style => :grid,
  :row_colors => ["FFFFFF","DDDDDD"],
  :headers => ["Product", "Qty", "Unit Price", "Full Price"],
  :align => { 0 => :left, 1 => :right, 2 => :right, 3 => :right }

pdf.move_down(10)

pdf.text "Total Price: #{number_to_currency(@profile)}", :size => 16, :style => :bold
