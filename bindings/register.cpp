#include <iostream>
#include <lua.hpp>
#include "MyActor.h"
#include "MyActorBinding.h"
#include "MyVector3d.h"
#include "MyVector3dBinding.h"

int registerBindings( lua_State* L )
{
    MyActorBinding::register_class( L );
    MyVector3dBinding::register_class( L );
    return 0;
}
