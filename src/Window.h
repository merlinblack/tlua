#ifndef WINDOW_H
#define WINDOW_H
#include <ncurses.h>

class Window
{
    protected:

    WINDOW *win;

    public:

    WINDOW* getwin() { return win; }

    Window() : win(NULL)
    {}
    ~Window() 
    {
        if( win )
            destroy();
    }

    void destroy() 
    {
        delwin( win );
        win = NULL;
    }

    bool create( int height, int width, int y, int x )
    {
        if( win )
            destroy();

        win = newwin( height, width, y, x );

        if( win )
            return false;
        else
            return true;
    }

    bool move( int y, int x )
    {
        return mvwin( win, y, x ) == ERR;
    }

    void box()
    {
        ::box( win, 0, 0 );
    }

    void refresh()
    {
        wrefresh(win);
    }

    bool resize( int height, int width )
    {
        return wresize( win, height, width ) == ERR;
    }

    bool clear()
    {
        return wclear(win) == ERR;
    }

    bool mvcur( int y, int x )
    {
        return wmove( win, y, x ) == ERR;
    }
    
    int print( const char* fmt, ... )
    {
        va_list args;
        va_start( args, fmt );
        int ret = vwprintw( win, fmt, args );
        va_end( args );
    }

    void scrollok()
    {
        ::scrollok(win,true);
    }

};

#endif // WINDOW_H
