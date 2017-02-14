#include <iostream>
#include <lua.hpp>
#include "MyActor.h"
#include "MyActorBinding.h"
#include "Vector.h"
#include "VectorBinding.h"

int registerBindings( lua_State* L )
{
    MyActorBinding  ::register_class( L );
    VectorBinding   ::register_class( L );
    return 0;
}
