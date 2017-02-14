#ifndef __VECTOR_H
#define __VECTOR_H

#include <cassert>
// This is based on Ogre3d's Vector,
// to test the ability of my binding approach.

class Vector
{
    public:
        float x, y, z;

        Vector( float nx, float ny, float nz ) : x(nx), y(ny), z(nz)
        {
        }

        Vector( float scalar ) : x(scalar), y(scalar), z(scalar)
        {
        }

        inline void swap( Vector& other )
        {
            std::swap( x, other.x );
            std::swap( y, other.y );
            std::swap( z, other.z );
        }

        inline float operator[] ( const size_t index ) const
        {
            assert( index < 3 );
            return *(&x+index);
        }

        inline float& operator[] ( const size_t index )
        {
            assert( index < 3 );
            return *(&x+index);
        }

        inline Vector& operator = ( const Vector& rkVector )
        {
            x = rkVector.x;
            y = rkVector.y;
            z = rkVector.z;
        }

        inline Vector& operator = ( const float fScaler )
        {
            x = fScaler;
            y = fScaler;
            z = fScaler;

            return *this;
        }

        inline bool operator == ( const Vector& rkVector ) const
        {
            return ( x == rkVector.x && y == rkVector.y && z == rkVector.z );
        }

        inline bool operator != ( const Vector& rkVector ) const
        {
            return ( x != rkVector.x || y != rkVector.y || z != rkVector.z );
        }

        inline Vector operator + ( const Vector& rkVector ) const
        {
            return Vector(
                x + rkVector.x,
                y + rkVector.y,
                z + rkVector.z);
        }

        inline Vector operator - ( const Vector& rkVector ) const
        {
            return Vector(
                x - rkVector.x,
                y - rkVector.y,
                z - rkVector.z);
        }

        inline Vector operator * ( const float fScalar ) const
        {
            return Vector(
                x * fScalar,
                y * fScalar,
                z * fScalar);
        }

        inline Vector operator * ( const Vector& rhs) const
        {
            return Vector(
                x * rhs.x,
                y * rhs.y,
                z * rhs.z);
        }

        inline Vector operator / ( const float fScalar ) const
        {
            assert( fScalar != 0.0 );

            float fInv = 1.0f / fScalar;

            return Vector(
                x * fInv,
                y * fInv,
                z * fInv);
        }

        inline Vector operator / ( const Vector& rhs) const
        {
            return Vector(
                x / rhs.x,
                y / rhs.y,
                z / rhs.z);
        }

        inline const Vector& operator + () const
        {
            return *this;
        }

        inline Vector operator - () const
        {
            return Vector(-x, -y, -z);
        }

};

#endif // __VECTOR_H
