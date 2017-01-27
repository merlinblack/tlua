#include <locale>
#include <sstream>
#include <lua.hpp>
#include <ncursesw/ncurses.h>
#include "Window.h"
#include "EditString.h"
#include "LuaInterpreter.h"
#include "utf8.h"

#include "../gitversioning.h"

#define TICKRATE 100

lua_State* init_lua();
bool init_ncurses();
void resize();
void processInput();
void processCommand( std::string& cmd );
void update();

bool fShouldStop;
Window output;
EditString commandline;
LuaInterpreter luaInterpreter;

int main( int argc, char* argv[] )
{
    setlocale(LC_ALL, ""); /* make sure UTF-8 */

    lua_State* L = init_lua();
    luaInterpreter.init( L );
    //luaL_dostring( L, "print=interpreterOutput" );
    luaL_dofile( L, "tlua.lua" );
    init_ncurses();
    printw( "Press ESC, or type 'quit' or 'exit' to exit..." );

    output.create( LINES-7, COLS-2, 5, 1 );
    output.scrollok();
    wbkgd( output.getwin(), COLOR_PAIR(1));
    output.print( "%s\n", GIT_REPO_REVISION );

    resize();

    while( ! fShouldStop ) {
        processInput();
        luaInterpreter.resume();
        update();
    }

    endwin();
    luaInterpreter.deinit();
    lua_close( L );
    return 0;
}

void processInput()
{
    wint_t key;
    int ret = get_wch( &key );
    unsigned long codepoint = (long)key;

    if( ret == ERR ) {
        return;
    }

    switch( key ) {
        case 27: // ESC or ALT
            ret = get_wch( &key );
            if( ret == ERR ) {   // ESC
                fShouldStop = true;
                break;
            } // else ALT something.
            break;
        case KEY_RESIZE:
            resize();
            break;
        case '\n':
            processCommand( commandline.getText() );
            output.refresh();
            commandline.clear();
            break;

        default:
            commandline.injectKeyPress( ret, codepoint  );
            break;
    }
}

void processCommand( std::string& cmd )
{
    if( cmd == "quit" || cmd == "exit" ) {
        fShouldStop = true;
        return;
    }
    luaInterpreter.insertLine( cmd, false );
    output.print( "\n%s\n", cmd.c_str() );
    output.refresh();
}

void update()
{
    std::string prompt = luaInterpreter.getPrompt();
    output.print( luaInterpreter.getOutput().c_str() );
    output.refresh();
    luaInterpreter.clearOutput();

    mvprintw( 0, COLS-15, "Coroutines: %3d", luaInterpreter.numCoroutines() );
    mvprintw( 1, 0, "%s%s", prompt.c_str(), commandline.getText().c_str() );
    clrtoeol();
    mvprintw( 1, COLS-15, "Mem used: %5d", lua_gc( luaInterpreter.getLuaInstance(), LUA_GCCOUNT, 0 ) );
    // Place cursor
    move( 1, utf8::distance( prompt.begin(), prompt.end() ) + commandline.getPosition());
}

void resize() {
    int lines = LINES;
    int cols = COLS;
    attron( COLOR_PAIR(1) );
    mvhline( 4, 1, ACS_HLINE, cols-2 );
    mvhline( lines-1, 1, ACS_HLINE, cols-2 );
    mvvline( 5, 0, ACS_VLINE, lines-6 );
    mvvline( 5, cols-1, ACS_VLINE, lines-6 );
    mvaddch( 4, 0, ACS_ULCORNER );
    mvaddch( 4, cols-1, ACS_URCORNER );
    mvaddch( lines-1, 0, ACS_LLCORNER );
    mvaddch( lines-1, cols-1, ACS_LRCORNER );
    attroff( COLOR_PAIR(1) );

    refresh();
    output.resize( lines-6, cols-2 );
    touchwin( output.getwin() );
    output.refresh();
}

lua_State* init_lua()
{
    lua_State* L = luaL_newstate();
    luaL_openlibs( L );

    return L;
}

bool init_ncurses()
{
    initscr();
    noecho();
    timeout(TICKRATE);
    cbreak();
    keypad(stdscr, TRUE);
    set_escdelay(25);
    start_color();

    init_pair( 1, COLOR_YELLOW+8, COLOR_BLUE );
}
