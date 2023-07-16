#include <cmath>
#include <Windows.h>

#ifndef v2_HPP
#define v2_HPP

namespace v2
{
	struct Vector2
	{
		
		Vector2(float X, float Y);
		Vector2();
		void operator=(const Vector2& p1);
		bool operator==(const Vector2& p1);
		bool operator!=(const Vector2& p1);
		Vector2& operator+=(const Vector2& p1);
		Vector2 operator+(const Vector2& p1) const;
	
		Vector2& operator-=(const Vector2& p1);
		Vector2 operator-(const Vector2& p1) const;

		Vector2 operator*(float scale) const;
		Vector2& operator*=(float scale);


		Vector2 operator/(float scale) const;
		
		Vector2& operator/=(float scale);
	
		Vector2 operator*(Vector2& scale) const;
		Vector2& operator*=(Vector2& scale);

		Vector2 operator/(Vector2& scale) const;
		Vector2& operator/=(Vector2& scale);
	
		float x;
		float y;


		
	};

const  Vector2 zerov = Vector2(0, 0);

inline Vector2 Coordtovector(COORD pos) {


	return Vector2(pos.X,  -pos.Y);
}
inline Vector2::Vector2() {



	x = 0;
	y = 0;
}
	
	inline float distance(const Vector2& p,const Vector2& p1){

		return(sqrt((p.x - p1.x) * (p.x - p1.x) + (p.y - p1.y) * (p.y - p1.y)));
	}

	

	inline float magnitude(const Vector2& p) {

		return(sqrt(p.x*p.x + p.y*p.y));
	}

	inline Vector2 normal (const Vector2& p) {

		return(p/magnitude(p));
	}

	inline float dotproduct(const Vector2& p, const Vector2& p1) {

		return (p.x*p1.x+p.y+p1.y);
	}


	inline Vector2 lerp(const Vector2& p, const Vector2& p1,float t) {
		return p* (1-t) + p1 * t;


	}

	inline float slope(const Vector2& p, const Vector2& p1, float t) {
		return (p1.y-p.y)/(p1.x-p.x);


	}

	inline void Vector2::operator=(const Vector2& p1) {
	
		x = p1.x;
		y = p1.y;


	}




	inline Vector2 Vector2::operator+(const Vector2& p1) const {


		return Vector2(x + p1.x, y + p1.y);


	}
	inline Vector2& Vector2::operator+=(const Vector2& p1) {


		x += p1.x;
		y += p1.y;
		return *this;

	}
	
	


	
	inline Vector2 Vector2::operator-(const Vector2& p1) const {


		return Vector2(x - p1.x, y - p1.y);


	}
	inline Vector2& Vector2::operator-=(const Vector2& p1) {


		x -= p1.x;
		y -= p1.y;
		return *this;

	}
	
	inline Vector2 Vector2::operator*(float scale) const {

		return Vector2(x * scale, y * scale);



	}

	inline Vector2& Vector2::operator*=(float scale) {


		x *= scale;
		y *= scale;
		return *this;

	}

	inline Vector2 Vector2::operator/(float scale) const {

		return Vector2(x / scale, y / scale);
	}

	inline Vector2& Vector2::operator/=(float scale) {


		x /= scale;
		y /= scale;
		return *this;

	}


	inline Vector2 Vector2::operator*(Vector2 &scale) const {

		return Vector2(x * scale.x, y * scale.y);
	}


	inline Vector2& Vector2::operator*=(Vector2 &scale) {
		x *= scale.x;
		y *= scale.y;
		return *this;
	}

	inline Vector2 Vector2::operator/(Vector2 &scale) const {

		return Vector2(x / scale.x, y / scale.y);
	}


	inline Vector2& Vector2::operator/=(Vector2 &scale) {


		x /= scale.x;
		y /= scale.y;
		return *this;

	}


	inline Vector2::Vector2(float X, float Y) {

		x = X;
		y = Y;
	}
	inline bool Vector2::operator==(const Vector2& p1)
	{
		return (p1.x == x && p1.y == y);
		
	}
	inline bool Vector2::operator!=(const Vector2& p1)
	{
		return(p1.x != x || p1.y != y);
		
	}
}
#endif