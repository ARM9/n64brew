#pragma once

template<class T, unsigned N>
struct Matrix {
    T v[N];
};

template<class T>
struct Vec2 {
    T x, y;

    Vec2() : x(0), y(0) {}
    Vec2(T _x, T _y) : x(_x), y(_y) {}
    Vec2(const Vec2& o) = default;
    Vec2(Vec2&& o) = default;

    Vec2& operator =(const Vec2& rhs) = default;
    Vec2& operator =(Vec2&& rhs) = default;

    Vec2& set(T _x, T _y) {
        x = _x;
        y = _y;
        return *this;
    }

    // Unary
    Vec2 operator -() const {
        return Vec2(-x, -y);
    }

    // Vector scalar
    Vec2& operator +=(T rhs) {
        x += rhs;
        y += rhs;
        return *this;
    }

    Vec2& operator -=(T rhs) {
        x -= rhs;
        y -= rhs;
        return *this;
    }

    friend Vec2 operator +(Vec2 lhs, T rhs) {
        return lhs += rhs;
    }
    friend Vec2 operator -(Vec2 lhs, T rhs) {
        return lhs -= rhs;
    }

    Vec2& operator *=(T rhs) {
        x *= rhs;
        y *= rhs;
        return *this;
    }

    Vec2& operator /=(T rhs) {
        x /= rhs;
        y /= rhs;
        return *this;
    }

    friend Vec2 operator *(Vec2 lhs, T rhs) {
        return lhs *= rhs;
    }

    friend Vec2 operator *(T lhs, Vec2 rhs) {
        return rhs *= lhs;
    }

    friend Vec2 operator /(Vec2 lhs, T rhs) {
        return lhs /= rhs;
    }

    friend Vec2 operator /(T lhs, Vec2 rhs) {
        return Vec2(lhs / rhs.x, lhs / rhs.y);
    }


    // Vector vector
    Vec2& operator +=(const Vec2& rhs) {
        x += rhs.x;
        y += rhs.y;
        return *this;
    }

    Vec2& operator -=(const Vec2& rhs) {
        x -= rhs.x;
        y -= rhs.y;
        return *this;
    }

    friend Vec2 operator +(Vec2 lhs, const Vec2& rhs) {
        return lhs += rhs;
    }

    friend Vec2 operator -(Vec2 lhs, const Vec2& rhs) {
        return lhs -= rhs;
    }

    static T dot(const Vec2& lhs, const Vec2& rhs) {
        return lhs.x * rhs.x + lhs.y * rhs.y;
    }

    T dot(const Vec2& rhs) const {
        return x * rhs.x + y * rhs.y;
    }

    static T cross(const Vec2& lhs, const Vec2& rhs) {
        return lhs.x * rhs.y - lhs.y * rhs.x;
    }

    T cross(const Vec2& rhs) const {
        return x * rhs.y - y * rhs.x;
    }

    // Vector Vector comparison
    bool operator ==(const Vec2& rhs) const {
        return x == rhs.x && y == rhs.y;
    }

    bool operator !=(const Vec2& rhs) const {
        return !(this == rhs);
    }

    bool operator <(const Vec2& rhs) const {
        return x < rhs.x && y < rhs.y;
    }

    bool operator >(const Vec2& rhs) const {
        return x > rhs.x && y > rhs.y;
    }

    bool operator <=(const Vec2& rhs) const {
        return !(this > rhs);
    }

    bool operator >=(const Vec2& rhs) const {
        return !(this < rhs);
    }
};

template <class T>
struct Vec3 {
    T x, y, z;

    Vec3() : x(0), y(0), z(0) {}
    Vec3(T _x, T _y, T _z) : x(_x), y(_y), z(_z) {}
    Vec3(const Vec3& o) = default;
    Vec3(Vec3&& o) = default;

    Vec3& operator =(const Vec3& rhs) = default;
    Vec3& operator =(Vec3&& rhs) = default;

    Vec3& set(T _x, T _y, T _z) {
        x = _x;
        y = _y;
        z = _z;
        return *this;
    }

    // Unary
    Vec3 operator -() const {
        return Vec3(-x, -y, -z);
    }

    // Vector scalar
    Vec3& operator +=(T rhs) {
        x += rhs;
        y += rhs;
        z += rhs;
        return *this;
    }

    Vec3& operator -=(T rhs) {
        x -= rhs;
        y -= rhs;
        z -= rhs;
        return *this;
    }

    friend Vec3 operator +(Vec3 lhs, T rhs) {
        return lhs += rhs;
    }

    friend Vec3 operator -(Vec3 lhs, T rhs) {
        return lhs -= rhs;
    }

    Vec3& operator *=(T rhs) {
        x *= rhs;
        y *= rhs;
        z *= rhs;
        return *this;
    }

    Vec3& operator /=(T rhs) {
        x /= rhs;
        y /= rhs;
        z /= rhs;
        return *this;
    }

    friend Vec3 operator *(Vec3 lhs, T rhs) {
        return lhs *= rhs;
    }

    friend Vec3 operator *(T lhs, Vec3 rhs) {
        return rhs *= lhs;
    }

    friend Vec3 operator /(Vec3 lhs, T rhs) {
        return lhs /= rhs;
    }

    friend Vec3 operator /(T lhs, Vec3 rhs) {
        return Vec3(lhs / rhs.x, lhs / rhs.y, lhs / rhs.z);
    }

    // Vector vector
    Vec3& operator +=(const Vec3& rhs) {
        x += rhs.x;
        y += rhs.y;
        z += rhs.z;
        return *this;
    }

    Vec3& operator -=(const Vec3& rhs) {
        x -= rhs.x;
        y -= rhs.y;
        z -= rhs.z;
        return *this;
    }

    friend Vec3 operator +(Vec3 lhs, const Vec3& rhs) {
        return lhs += rhs;
    }

    friend Vec3 operator -(Vec3 lhs, const Vec3& rhs) {
        return lhs -= rhs;
    }

    static T dot(const Vec3& lhs, const Vec3& rhs) {
        return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z;
    }

    T dot(const Vec3& rhs) const {
        return x * rhs.x + y * rhs.y + z * rhs.z;
    }

    static Vec3& cross(const Vec3& a, const Vec3& b) {
        Vec3 t = (a.y * b.z - a.z * b.y
                 ,a.z * b.x - a.x * b.z
                 ,a.x * b.y - a.y * b.x);
        return t;
    }

    Vec3& cross(const Vec3& rhs) {
        return Vec3::cross(this, rhs);
    }

    // Vector Vector comparison
    bool operator ==(const Vec3& rhs) const {
        return x == rhs.x && y == rhs.y && z == rhs.z;
    }

    bool operator !=(const Vec3& rhs) const {
        return !(this == rhs);
    }

    bool operator <(const Vec3& rhs) const {
        return x < rhs.x && y < rhs.y && z < rhs.z;
    }

    bool operator >(const Vec3& rhs) const {
        return x > rhs.x && y > rhs.y && z > rhs.z;
    }

    bool operator <=(const Vec3& rhs) const {
        return !(this > rhs);
    }

    bool operator >=(const Vec3& rhs) const {
        return !(this < rhs);
    }
};

