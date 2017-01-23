/* -------------------------------------------------------------------------------
 *
 * The original of this file has been previously released to the public domain by
 * Nigel Atkinson.
 *
 * See the wiki on www.ogre3d.org
 *
 * -------------------------------------------------------------------------------
 */

#pragma once

#include <string>
#include <vector>
#include "utf8.h"

class EditString
{
public:
    EditString(void) : mInsert(true), mPosition(mText.begin()), mCaret(0), mLocale_utf8( "C.UTF-8" )
    {}

    EditString( std::string newText )
    {
        setText( newText );
    }

    ~EditString(void)
    {}


protected:

    std::locale mLocale_utf8;

    // The text for editing
    // This is a vector of 32 bit code points.
    std::vector<long> mText;

    std::string utf8encoded;

    // Overwrite or insert
    bool mInsert;

    // Position for insert / overwrite
    std::vector<long>::iterator mPosition;

    // Caret Position - for positioning the cursor.
    int mCaret;

public:
    void setText( std::string& newText )
    {
        mText.clear();
        utf8::utf8to32( newText.begin(), newText.end(), std::back_inserter( mText ) );
        mPosition = mText.end();
        mCaret = (int)mText.size();
    }

    void clear()
    {
        mText.clear();
        mPosition = mText.end();
        mCaret = 0;
    }

    std::string & getText() {
        utf8encoded.clear();
        utf8::utf32to8( mText.begin(), mText.end(), std::back_inserter( utf8encoded ) );
        return utf8encoded;
    }

    bool inserting() { return mInsert; }

    // arg is a 32 bit codepoint.
    bool injectKeyPress( int ret, unsigned long arg );

    // gets the current position in the text for cursor placement
    int getPosition(void) { return mCaret; }
};

