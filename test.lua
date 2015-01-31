function display()
	print "It's alive! No compiles, thanks Lua."
	return "success"
end

function foo()
	print "Bar"
	return "success"
end

function bar()
	print "Foo"
	return "failure"
end

function foobar()
	print "foobar"
	return "running"
end
