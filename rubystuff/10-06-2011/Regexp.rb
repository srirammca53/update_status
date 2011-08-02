# program to RegExp

p "enter your website please"
web = gets.chop
p web

reg = %r{
	(?<protocol> www.){0}
          (?<name> /[a-z][0-9]/){0}
	(?<domain> /.com/){0}
	\g<protocol>\g<name>\g<domain>
        }

match1 =reg.match(web)

if match1==nil
p "invalid website address"
else 
p "valid website"
end
