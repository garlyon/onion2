#pragma once


namespace Math_NS
{
  template <typename T>
  struct Vector3
  {
    using Type = T;

    T x{}, y{}, z{};

    Vector3() = default;
    Vector3( T x, T y, T z ) : x( x ), y( y ), z( z ) {}

    Vector3& operator += ( const Vector3& v ) { x += v.x; y += v.y; z += v.z; return *this; }
    Vector3& operator -= ( const Vector3& v ) { x -= v.x; y -= v.y; z -= v.z; return *this; }
  };


  template <typename T> Vector3<T> operator + ( const Vector3<T>& a, const Vector3<T>& b ) { return Vector3<T>( a ) += b; }
  template <typename T> Vector3<T> operator - ( const Vector3<T>& a, const Vector3<T>& b ) { return Vector3<T>( a ) -= b; }

  template <typename T> T          operator * ( const Vector3<T>& a, const Vector3<T>& b ) { return a.x * b.x + a.y * b.y + a.z * b.z; }
  template <typename T> Vector3<T> operator ^ ( const Vector3<T>& a, const Vector3<T>& b ) { return Vector3<T>( a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x ); }

  template <typename T> bool operator == ( const Vector3<T>& a, const Vector3<T> &b ) { return a.x == b.x && a.y == b.y && a.z == b.z; }


  using Vector3D = Vector3<double>;
  using Vector3F = Vector3<float>;
  using Vector3I = Vector3<int>;
  using Vector3L = Vector3<long long int>;
}