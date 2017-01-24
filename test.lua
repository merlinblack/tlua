yield = coroutine.yield

function test()
    while( not stop ) do
        yield()
    end
    print( '\nCoroutine Çıkış\n' )
end

print( '\ntest.lua loaded\n' )
