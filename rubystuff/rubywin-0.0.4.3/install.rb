require 'mkmf'
require 'ftools'
require 'find'

bindir = CONFIG["bindir"]
Config::expand(bindir)
srcdir = File.dirname($0)

for dll in Dir["#{srcdir}/*.dll"]
  File.install dll, bindir, 0755, true
end

for exe in Dir['*.exe']
  File.install exe, bindir, 0755, true
end

File.makedirs "#{bindir}/rwlib/irb"
for rb in Dir["#{srcdir}/rwlib/*.rb"]
  File.install rb, "#{bindir}/rwlib", 0644, true
end

for rb in Dir["#{srcdir}/rwlib/irb/*.rb"]
  File.install rb, "#{bindir}/rwlib/irb", 0644, true
end
