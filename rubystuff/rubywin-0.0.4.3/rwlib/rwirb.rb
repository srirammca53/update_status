## -- rwirb.rb for irb-0.6X and irb-0.7X
begin
  require "irb"
  require "irb/version"
rescue LoadError
  require "irb/main"
end

puts IRB.version

module IRB
  class RUBYWINInputMethod < StdioInputMethod
    def gets 
      print @prompt
      str = RW_IO_EMULATE.gets
      if /^exit/ =~ str
        exit
      end
      @line[@line_no += 1] = str
    end
  end

  def IRB.start_on_rubywin
    IRB.initialize(nil)

    im = RUBYWINInputMethod.new

    if (@RELEASE_VERSION.scan(/[0-9]+/) <=> ["0", "7"]) >= 0
      irb = Irb.new(nil, im)
    else
      bind = workspace_binding
      main = eval("self", bind)
      irb = Irb.new(main, bind, im)
    end
    @CONF[:IRB_RC].call(irb.context) if @CONF[:IRB_RC]
    @CONF[:MAIN_CONTEXT] = irb.context

    trap("SIGINT") do
      irb.signal_handle
    end

    catch(:IRB_EXIT) do
      irb.eval_input
    end
    print "\n"
  end
end
 
IRB.start_on_rubywin

