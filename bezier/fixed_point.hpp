#pragma once

template <typename T, unsigned FracBits>
struct Fixed {
    T v;

    static const unsigned factor = 1 << FracBits;

    Fixed() : v{0} {}
    Fixed(int val) : v{static_cast<T>(val)} {}
    Fixed(const Fixed& o) = default;
    Fixed(Fixed&& o) = default;
    Fixed(float val)  : v{static_cast<T>(val * factor)} {}
    Fixed(double val) : v{static_cast<T>(val * factor)} {}

    Fixed& operator =(const Fixed& rhs) = default;
    Fixed& operator =(Fixed&& rhs) = default;

    Fixed& operator =(float val) {
        v = static_cast<T>(val * factor);
        return *this;
    }
    Fixed& operator =(double val) {
        v = static_cast<T>(val * factor);
        return *this;
    }

    // Unary
    Fixed operator -() const {
        return Fixed(-v);
    }

    // prefix 
    Fixed& operator ++() {
        v += factor;
        return *this;
    }
    Fixed& operator --() {
        v -= factor;
        return *this;
    }
    // postfix
    Fixed operator ++(int) {
        Fixed tmp(v);
        v += factor;
        return tmp;
    }
    Fixed operator --(int) {
        Fixed tmp(v);
        v -= factor;
        return tmp;
    }

    // arithmetic
    Fixed& operator +=(const Fixed& rhs) {
        v += rhs.v;
        return *this;
    }

    Fixed& operator -=(const Fixed& rhs) {
        v -= rhs.v;
        return *this;
    }

    Fixed& operator *=(const Fixed& rhs) {
        v *= rhs.v;
        v >>= FracBits;
        return *this;
    }

    Fixed& operator /=(const Fixed& rhs) {
        v = (v << FracBits) / rhs.v;
        return *this;
    }

    friend Fixed operator +(Fixed lhs, const Fixed& rhs) {
        return lhs += rhs;
    }

    friend Fixed operator -(Fixed lhs, const Fixed& rhs) {
        return lhs -= rhs;
    }

    friend Fixed operator *(Fixed lhs, const Fixed& rhs) {
        return lhs *= rhs;
    }

    friend Fixed operator /(Fixed lhs, const Fixed& rhs) {
        return lhs /= rhs;
    }

    // Fixed T arithmetic
    // causes implicit conversion from int to float when adding int
    //Fixed& operator +=(float rhs) {
        //v += static_cast<T>(rhs * factor);
        //return *this;
    //}

    //Fixed& operator +=(T rhs) {
        //v += rhs;
        //return *this;
    //}

    //Fixed& operator -=(T rhs) {
        //v -= rhs;
        //return *this;
    //}

    //Fixed& operator *=(T rhs) {
        //v *= rhs;
        //v >>= FracBits;
        //return *this;
    //}

    //Fixed& operator /=(T rhs) {
        //v = (v << FracBits) / rhs;
        //return *this;
    //}

    //friend Fixed operator +(Fixed lhs, T rhs) {
        //return lhs += rhs;
    //}

    //friend Fixed operator -(Fixed lhs, T rhs) {
        //return lhs -= rhs;
    //}

    //friend Fixed operator *(Fixed lhs, T rhs) {
        //return lhs *= rhs;
    //}

    //friend Fixed operator /(Fixed lhs, T rhs) {
        //return lhs /= rhs;
    //}

    // Fixed Fixed comparison
    bool operator ==(const Fixed& rhs) const {
        return v == rhs.v;
    }

    bool operator !=(const Fixed& rhs) const {
        return v != rhs.v;
    }

    bool operator <(const Fixed& rhs) const {
        return v < rhs.v;
    }

    bool operator >(const Fixed& rhs) const {
        return v > rhs.v;
    }

    bool operator <=(const Fixed& rhs) const {
        return v <= rhs.v;
    }

    bool operator >=(const Fixed& rhs) const {
        return v >= rhs.v;
    }

    // Fixed T comparison
    //bool operator ==(T rhs) const {
        //return v == rhs;
    //}

    //bool operator !=(T rhs) const {
        //return v != rhs;
    //}

    //bool operator <(T rhs) const {
        //return v < rhs;
    //}

    //bool operator >(T rhs) const {
        //return v > rhs;
    //}

    //bool operator <=(T rhs) const {
        //return v <= rhs;
    //}

    //bool operator >=(T rhs) const {
        //return v >= rhs;
    //}

    // conversion
    operator int () const {
        return v >> FracBits;
    }
    //operator float () const {
        //return static_cast<float>(v) / FracBits;
    //}
};

typedef Fixed<int,8> f24_8;
typedef Fixed<short,8> f8_8;

//typedef int fixed;

//#define FIXED_BITS  8
//#define FIXED_ONE   (1<<FIXED_BITS)
//#define FIXED_HALF  ((1<<FIXED_BITS)>>1)

//#define f2i(A) ((A) >> FIXED_BITS)
//#define i2f(A) ((A) << FIXED_BITS)

//#define fixmul(A,B) f2i((A) * (B))
//#define fixdiv(A,B) i2f(A) / (B)

//#define fixceil(A) f2i((A) + (FIXED_ONE - 1))
//#define fixinv(A) fixdiv(FIXED_ONE,(A))

//#define imax(a, b) ((a) - (((a)-(b)) & ((a)-(b))>>31))
//#define imin(a, b) ((b) + (((a)-(b)) & ((a)-(b))>>31))

//#define max(x, y) ((x) > (y) ? (x) : (y))
//#define min(x, y) ((x) < (y) ? (x) : (y))
