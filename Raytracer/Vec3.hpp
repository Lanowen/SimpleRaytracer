#pragma once 

#include <cassert>
#include <cmath>
#include <cfloat>
#include <sstream>

using namespace std;

class Vec3
{
public:
	/**
	\brief default constructor leaves data uninitialized.
	*/
	 inline Vec3() {}

	/**
	\brief Assigns scalar parameter to all elements.

	Useful to initialize to zero or one.

	\param[in] a Value to assign to elements.
	*/
	explicit  inline Vec3(double a): x(a), y(a), z(a) {}

	/**
	\brief Initializes from 3 scalar parameters.

	\param[in] nx Value to initialize X component.
	\param[in] ny Value to initialize Y component.
	\param[in] nz Value to initialize Z component.
	*/
	 inline Vec3(double nx, double ny, double nz): x(nx), y(ny), z(nz) {}

	/**
	\brief Copy ctor.
	*/
	 inline Vec3(const Vec3& v): x(v.x), y(v.y), z(v.z) {}

	//Operators

	/**
	\brief Assignment operator
	*/
	 inline	Vec3&	operator=(const Vec3& p)			{ x = p.x; y = p.y; z = p.z;	return *this;		}

	/**
	\brief element access
	*/
	 inline double& operator[](int index)					{ assert(index>=0 && index<=2); return (&x)[index]; }

	/**
	\brief element access
	*/
	 inline const double& operator[](int index) const		{ assert(index>=0 && index<=2); return (&x)[index]; }

	/**
	\brief returns true if the two vectors are exactly equal.
	*/
	 inline bool operator==(const Vec3&v) const	{ return x == v.x && y == v.y && z == v.z; }

	/**
	\brief returns true if the two vectors are not exactly equal.
	*/
	 inline bool operator!=(const Vec3&v) const	{ return x != v.x || y != v.y || z != v.z; }

	/**
	\brief tests for exact zero vector
	*/
	 inline bool isZero()	const					{ return x==0.0f && y==0.0f && z == 0.0f;			}

	/**
	\brief returns true if all 3 elems of the vector are finite (not NAN or INF, etc.)
	*/
	 inline bool isFinite() const
	{
		return _finite(x) && _finite(y) && _finite(z);
	}

	/**
	\brief is normalized - used by API parameter validation
	*/
	 inline bool isNormalized() const
	{
		const float unitTolerance = double(1e-4);
		return isFinite() && abs(magnitude()-1)<unitTolerance;
	}

	/**
	\brief returns the squared magnitude

	Avoids calling sqrt()!
	*/
	 inline double magnitudeSquared() const		{	return x * x + y * y + z * z;					}

	/**
	\brief returns the magnitude
	*/
	 inline double magnitude() const				{	return sqrt(magnitudeSquared());		}

	/**
	\brief negation
	*/
	 inline Vec3 operator -() const
	{
		return Vec3(-x, -y, -z);
	}

	/**
	\brief vector addition
	*/
	 inline Vec3 operator +(const Vec3& v) const		{	return Vec3(x + v.x, y + v.y, z + v.z);	}

	/**
	\brief vector difference
	*/
	 inline Vec3 operator -(const Vec3& v) const		{	return Vec3(x - v.x, y - v.y, z - v.z);	}

	/**
	\brief scalar post-multiplication
	*/
	 inline Vec3 operator *(double f) const				{	return Vec3(x * f, y * f, z * f);			}

	/**
	\brief scalar division
	*/
	 inline Vec3 operator /(double f) const
	{
		f = double(1) / f;	// PT: inconsistent notation with operator /=
		return Vec3(x * f, y * f, z * f);
	}

	/**
	\brief vector addition
	*/
	 inline Vec3& operator +=(const Vec3& v)
	{
		x += v.x;
		y += v.y;
		z += v.z;
		return *this;
	}
	
	/**
	\brief vector difference
	*/
	 inline Vec3& operator -=(const Vec3& v)
	{
		x -= v.x;
		y -= v.y;
		z -= v.z;
		return *this;
	}

	/**
	\brief scalar multiplication
	*/
	 inline Vec3& operator *=(double f)
	{
		x *= f;
		y *= f;
		z *= f;
		return *this;
	}
	/**
	\brief scalar division
	*/
	 inline Vec3& operator /=(double f)
	{
		f = 1.0f/f;	// PT: inconsistent notation with operator /
		x *= f;
		y *= f;
		z *= f;
		return *this;
	}

	/**
	\brief returns the scalar product of this and other.
	*/
	 inline double dot(const Vec3& v) const		
	{	
		return x * v.x + y * v.y + z * v.z;				
	}

	/**
	\brief cross product
	*/
	 inline Vec3 cross(const Vec3& v) const
	{
		return Vec3(y * v.z - z * v.y, 
					  z * v.x - x * v.z, 
					  x * v.y - y * v.x);
	}

	/** return a unit vector */

	 inline Vec3 getNormalized() const
	{
		const double m = magnitudeSquared();
		return m>0 ? *this * (1/sqrt(m)) : Vec3(0,0,0);
	}

	/**
	\brief normalizes the vector in place
	*/
	 inline double normalize()
	{
		const double m = magnitude();
		if (m>0) 
			*this /= m;
		return m;
	}

	/**
	\brief normalizes the vector in place. Does nothing if vector magnitude is under 1e-20f.
	Returns vector magnitude if >= 1e-20f and 0.0f otherwise.
	*/
	 inline double normalizeSafe()
	{
		const double mag = magnitude();
		if (mag < 1e-20f)
			return 0.0f;
		*this *= double(1) / mag;
		return mag;
	}

	/**
	\brief normalizes the vector in place. Asserts if vector magnitude is under 1e-20f.
	returns vector magnitude.
	*/
	 inline double normalizeFast()
	{
		const double mag = magnitude();
		assert(mag >= 1e-20f);
		*this *= double(1) / mag;
		return mag;
	}

	/**
	\brief a[i] * b[i], for all i.
	*/
	 inline Vec3 multiply(const Vec3& a) const
	{
		return Vec3(x*a.x, y*a.y, z*a.z);
	}

	/**
	\brief element-wise minimum
	*/
	 inline Vec3 minimum(const Vec3& v) const
	{ 
		
		return Vec3(min(x, v.x), min(y,v.y), min(z,v.z));	
	}

	/**
	\brief returns min(x, y, z);
	*/
	 inline float minElement()	const
	{
		return min(x, min(y, z));
	}
	
	/**
	\brief element-wise maximum
	*/
	 inline Vec3 maximum(const Vec3& v) const
	{ 
		return Vec3(max(x, v.x), max(y,v.y), max(z,v.z));	
	} 

	/**
	\brief returns max(x, y, z);
	*/
	 inline float maxElement()	const
	{
		return max(x, max(y, z));
	}

	string toString(){
		stringstream ss;
		ss << "(" << x << ", " << y << ", " << z << ")";
		return ss.str();
	}

	double x,y,z;
};

 static inline Vec3 operator *(double f, const Vec3& v)
{
	return Vec3(f * v.x, f * v.y, f * v.z);
}

