#ifndef SUBWINDOW_H
#define SUBWINDOW_H                    
#include "Window.h"

class SubWindow : public Window
{
    protected:

    WINDOW* parent;

    public:

    bool create( Window &parentwindow, int starty, int startx, int endy, int endx )
    {
        parent = parentwindow.getwin();
        int width;
        int height;
        getmaxyx( parent, height, width );
        if( 0 > endy ) {
            height += endy;
            height--;
        } else {
            height = endy;
        }
        if( 0 > endx ) {
            width += endx;
            width--;
        } else {
            width = endx;
        }

        win = derwin( parent, height, width, starty, startx );

        if( win )
            return false;

        return true;
    }

    void refresh()
    {
        touchwin(parent);
        wrefresh(win);
    }
};

#endif // SUBWINDOW_H                    
