yield = coroutine.yield

function print( ... )
    local printResult = '';

    for i,v in ipairs( {...} ) do
        printResult = printResult .. tostring( v ) .. "\t"
    end
    printResult = "\n" .. printResult
    interpreterOutput( printResult )
end

function test()
    while( not stop ) do
        yield()
    end
    print( '\nCoroutine Çıkış\n' )
end

function delay( seconds, func )
    if type(func) ~= 'function' then
        error( 'Second parameter must be a function.' )
        return;
    end

    local start = os.time();

    while( os.difftime( os.time(), start ) < seconds ) do
        yield();
    end

    return func() -- tail call.
end

print( '\ntlua.lua loaded\n' )
