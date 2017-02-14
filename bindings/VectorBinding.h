#ifndef __VECTORBINDING_H
#define __VECTORBINDING_H
#include <sstream>
#include "Binding.h"
#include "Vector.h"

typedef std::shared_ptr<Vector> VectorPtr;

struct VectorBinding: public Binding<VectorBinding, Vector> {

    static constexpr const char* class_name = "Vector";

    static luaL_Reg* members()
    {
        static luaL_Reg members[] = {
            { "swap", swap },
            { "__arrayindex", arrayindex },
            { "__arraynewindex", arraynewindex },
            { "__eq", is_equal },
            { "__tostring", tostring },
            { NULL, NULL }
        };
        return members;
    }

    static bind_properties* properties() {
        static bind_properties properties[] = {
            { "x", get, set },
            { "y", get, set },
            { "z", get, set },
            { NULL, NULL, NULL }
        };
        return properties;
    }

    // Lua constructor
    static int create( lua_State *L )
    {
        checkArgCount( L, 3 );

        float x = luaL_checknumber( L, 1 );
        float y = luaL_checknumber( L, 2 );
        float z = luaL_checknumber( L, 3 );

        VectorPtr sp = std::make_shared<Vector>( x, y, z );

        push( L, sp );

        return 1;
    }

    // Method glue functions
    //

    static int swap( lua_State* L )
    {
        checkArgCount( L, 2 );

        VectorPtr self  = fromStack( L, 1 );
        VectorPtr other = fromStack( L, 1 );

        self->swap( *other );

        return 0;
    }

    static int arrayindex( lua_State* L )
    {
        checkArgCount( L, 2 );

        VectorPtr self = fromStack( L, 1 );
        int index = lua_tointeger( L, 2 );

        // Adjust to 0 based index.
        index--;

        if( index > 2 ) {
            luaL_error( L, "Index out of bounds for Vector" );
        }

        lua_pushnumber( L, (*self)[index] );

        return 1;
    }

    static int arraynewindex( lua_State* L )
    {
        checkArgCount( L, 3 );

        VectorPtr self = fromStack( L, 1 );
        int index = lua_tointeger( L, 2 );
        float value = lua_tonumber( L, 3 );

        // Adjust to 0 based index.
        index--;

        if( index > 2 ) {
            luaL_error( L, "Index out of bounds for Vector" );
        }

        (*self)[index] = value;

        return 0;
    }

    static int is_equal( lua_State* L )
    {
        checkArgCount( L, 2 );

        VectorPtr self = fromStack( L, 1 );
        VectorPtr other = fromStack( L, 2 );

        lua_pushboolean( L, (*self) == (*other) );

        return 1;
    }

    static int tostring( lua_State* L )
    {
        checkArgCount( L, 1 );

        VectorPtr self = fromStack( L, 1 );

        std::stringstream ss;

        ss << "Vector( " 
           << self->x << ", "
           << self->y << ", "
           << self->z << " )";

        lua_pushstring( L, ss.str().c_str() );

        return 1;
    }


    // Property getters and setters
    static const char *prop_keys[];

    // 1 - class metatable
    // 2 - key
    static int get( lua_State *L )
    {
        checkArgCount( L, 2 );

        VectorPtr v = fromStack( L, 1 );

        int which = luaL_checkoption( L, 2, NULL, VectorBinding::prop_keys );

        switch( which )
        {
            case 0:
                lua_pushnumber( L, v->x );
                break;
            case 1:
                lua_pushnumber( L, v->y );
                break;
            case 2:
                lua_pushnumber( L, v->z );
                break;
            default:
                luaL_argerror( L, 2, "What?" );
                break;
        }

        return 1;
    }

    // 1 - class metatable
    // 2 - key
    // 3 - value
    static int set( lua_State *L )
    {
        checkArgCount( L, 3 );

        VectorPtr v = fromStack( L, 1 );

        int which = luaL_checkoption( L, 2, NULL, VectorBinding::prop_keys );

        float value = lua_tonumber( L, 3 );

        switch( which )
        {
            case 0:
                v->x = value;
                break;
            case 1:
                v->y = value;
                break;
            case 2:
                v->z = value;
                break;
            default:
                luaL_argerror( L, 2, "What?" );
                break;
        }
        return 0;
    }

};

const char *VectorBinding::prop_keys[] = { "x", "y", "z", NULL };

#endif // __VECTORBINDING_H
