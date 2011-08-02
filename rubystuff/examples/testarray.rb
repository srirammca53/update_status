class Testarray

my_string = <<MY_STRING
This is a simple string that is
pre-formatted, which means that the
way it is formatted here including
tabs and newlines will be duplicated
when I print it out.
MY_STRING

args = [ "-m", "-q", "filename" ]
   puts args.shift
end
