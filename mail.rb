 require 'mail'

 mail = Mail.new do
      from 'mikel@test.lindsaar.net'
        to 'you@test.lindsaar.net'
   subject 'This is a test email'
      body File.read('body.txt')
 end

 mail.to_s #=> "From: mikel@test.lindsaar.net\r\nTo: you@...

