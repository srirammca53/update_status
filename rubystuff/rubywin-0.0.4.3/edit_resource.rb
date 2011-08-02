require 'ftools'
require 'mkmf'
def get_rubywin_version(version_file)
  v = "0.0.0.0"
  File.foreach(version_file) do |line|
    if /RUBYWIN_VERSION\s+\"(.*)\"/ =~ line
      v = $1
    end
  end
  v
end

version_file = ARGV.shift
resource_file = ARGV.shift
$ver_str1 = get_rubywin_version(version_file)
$ver_str2 = $ver_str1.gsub(/\./, ',')

def edit_resource(l)
  if /FILEVERSION/ =~ l
    l.sub(/\d,\d,\d,\d/, $ver_str2)
  elsif /PRODUCTVERSION/ =~ l
    l.sub(/\d,\d,\d,\d/, $ver_str2)
  elsif /FileVersion/ =~ l
    l.sub(/\d\.\d\.\d\.\d/, $ver_str1)
  elsif /ProductVersion/ =~ l
    l.sub(/\d\.\d\.\d\.\d/, $ver_str1)
  elsif /Copyright.*Masaki Suketa/ =~ l
    l.sub(/1999-\d{4}/, "1999-#{Time.now.year}")
  else
    l
  end
end

File.copy resource_file, resource_file+".org"
ofs = open(resource_file, "w")
File.foreach(resource_file + ".org") do |l|
  ofs.print edit_resource(l)
end 

