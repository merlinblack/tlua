/* -------------------------------------------------------------------------------
 *
 * The original of this file has been previously released to the public domain by
 * Nigel Atkinson.
 *
 * See the wiki on www.ogre3d.org
 *
 * -------------------------------------------------------------------------------
 */


#include "EditString.h"
#include <locale>
#include <ncursesw/ncurses.h>

// Process a key press.  Return true if it was used.

bool EditString::injectKeyPress( int ret, unsigned long arg )
{
    bool keyUsed = true;

    if( ret == KEY_CODE_YES ) {

        switch( arg )
        {
            case KEY_BACKSPACE:
                if( mPosition != mText.begin() )
                {
                    mPosition = mText.erase( --mPosition );
                    --mCaret;
                }
                break;

            case KEY_IC:
                mInsert = ! mInsert;
                break;

            case KEY_HOME:
                mPosition = mText.begin();
                mCaret = 0;
                break;

            case KEY_END:
                mPosition = mText.end();
                mCaret = (int)mText.size();
                break;

            case KEY_LEFT:
                if( mPosition != mText.begin() )
                {
                    mPosition--;
                    mCaret--;
                }
                break;

            case KEY_RIGHT:
                if( mPosition != mText.end() )
                {
                    mPosition++;
                    mCaret++;
                }
                break;

            case KEY_DC:
                if( mPosition != mText.end() )
                    mPosition = mText.erase( mPosition );
                break;

            default:
                keyUsed = false;
                break;
        }
    }
    else
    {
        if( isgraph( (wchar_t)arg, mLocale_utf8 ) || isspace( (wchar_t)arg ) )
        {
            if( mInsert || mPosition == mText.end() )
            {
                mPosition = mText.insert( mPosition, arg );
            }
            else
            {
                *mPosition = arg;
            }
            mPosition++;
            mCaret++;
        }
        else 
        {
            keyUsed = false;
        }
    }

    return keyUsed;
}

