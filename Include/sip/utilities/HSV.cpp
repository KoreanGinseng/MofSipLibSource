#include "HSV.h"

namespace sip
{
	HSV::HSV(MofS32 h, MofS32 s, MofS32 v)
		: h(h % 360)
		, s(s % 256)
		, v(v % 256)
	{
	}

	HSV & HSV::operator=(const Vector3Impl & v)
	{
		this->h = (MofS32)v.x;
		this->s = (MofS32)v.y;
		this->v = (MofS32)v.z;

		return *this;
	}
	
	HSV & HSV::operator=(const HSV & obj)
	{
		this->h = obj.h;
		this->s = obj.s;
		this->v = obj.v;

		return *this;
	}
	
	HSV HSV::operator+(void) const
	{
		return *this;
	}
	
	HSV HSV::operator-(void) const
	{
		return HSV(-h, -s, -v);
	}
	
	HSV & HSV::operator+=(const HSV & obj)
	{
		this->h += obj.h;
		this->s += obj.s;
		this->v += obj.v;

		return *this;
	}
	
	HSV & HSV::operator-=(const HSV & obj)
	{
		this->h -= obj.h;
		this->s -= obj.s;
		this->v -= obj.v;

		return *this;
	}
	
	HSV & HSV::operator*=(const HSV & obj)
	{
		this->h *= obj.h;
		this->s *= obj.s;
		this->v *= obj.v;

		return *this;
	}
	
	HSV & HSV::operator/=(const HSV & obj)
	{
		this->h /= obj.h;
		this->s /= obj.s;
		this->v /= obj.v;

		return *this;
	}

	HSV HSV::operator+(const HSV & obj) const
	{
		return HSV(this->h + obj.h, this->s + obj.s, this->v + obj.v);
	}

	HSV HSV::operator-(const HSV & obj) const
	{
		return HSV(this->h - obj.h, this->s - obj.s, this->v - obj.v);
	}

	HSV HSV::operator*(const HSV & obj) const
	{
		return HSV(this->h * obj.h, this->s * obj.s, this->v * obj.v);
	}

	HSV HSV::operator/(const HSV & obj) const
	{
		return HSV(this->h / obj.h, this->s / obj.s, this->v / obj.v);
	}
	
	HSV & HSV::operator+=(const Vector3Impl & v)
	{
		this->h += (MofS32)v.x;
		this->s += (MofS32)v.y;
		this->v += (MofS32)v.z;

		return *this;
	}
	
	HSV & HSV::operator-=(const Vector3Impl & v)
	{
		this->h -= (MofS32)v.x;
		this->s -= (MofS32)v.y;
		this->v -= (MofS32)v.z;

		return *this;
	}
	
	HSV & HSV::operator*=(const Vector3Impl & v)
	{
		this->h *= (MofS32)v.x;
		this->s *= (MofS32)v.y;
		this->v *= (MofS32)v.z;

		return *this;
	}
	
	HSV & HSV::operator/=(const Vector3Impl & v)
	{
		this->h /= (MofS32)v.x;
		this->s /= (MofS32)v.y;
		this->v /= (MofS32)v.z;

		return *this;
	}

	HSV HSV::operator+(const Vector3Impl & v) const
	{
		return HSV(this->h + (MofS32)v.x, this->s + (MofS32)v.y, this->v + (MofS32)v.z);
	}

	HSV HSV::operator-(const Vector3Impl & v) const
	{
		return HSV(this->h - (MofS32)v.x, this->s - (MofS32)v.y, this->v - (MofS32)v.z);
	}

	HSV HSV::operator*(const Vector3Impl & v) const
	{
		return HSV(this->h * (MofS32)v.x, this->s * (MofS32)v.y, this->v * (MofS32)v.z);
	}

	HSV HSV::operator/(const Vector3Impl & v) const
	{
		return HSV(this->h / (MofS32)v.x, this->s / (MofS32)v.y, this->v / (MofS32)v.z);
	}
	
	HSV & HSV::operator+=(MofS32 v)
	{
		this->h += v;
		this->s += v;
		this->v += v;

		return *this;
	}
	
	HSV & HSV::operator-=(MofS32 v)
	{
		this->h -= v;
		this->s -= v;
		this->v -= v;

		return *this;
	}
	
	HSV & HSV::operator*=(MofS32 v)
	{
		this->h *= v;
		this->s *= v;
		this->v *= v;

		return *this;
	}
	
	HSV & HSV::operator/=(MofS32 v)
	{
		this->h /= v;
		this->s /= v;
		this->v /= v;

		return *this;
	}

	HSV HSV::operator+(MofS32 v) const
	{
		return HSV(this->h + v, this->s + v, this->v + v);
	}

	HSV HSV::operator-(MofS32 v) const
	{
		return HSV(this->h - v, this->s - v, this->v - v);
	}

	HSV HSV::operator*(MofS32 v) const
	{
		return HSV(this->h * v, this->s * v, this->v * v);
	}

	HSV HSV::operator/(MofS32 v) const
	{
		return HSV(this->h / v, this->s / v, this->v / v);
	}

	HSV & HSV::operator*=(float v)
	{
		this->h *= v;
		this->s *= v;
		this->v *= v;

		return *this;
	}

	HSV & HSV::operator/=(float v)
	{
		// TODO: return ステートメントをここに挿入します
	}

	HSV HSV::operator*(float v) const
	{
		return HSV();
	}

	HSV HSV::operator/(float v) const
	{
		return HSV();
	}
	
	MofS32 & HSV::operator[](int i)
	{
		return iv[i];
	}
	
	const MofS32 & HSV::operator[](int i) const
	{
		return iv[i];
	}
	
	bool HSV::operator==(const HSV & obj) const
	{
		return (this->h == obj.h && this->s == obj.s && this->v == obj.v);
	}
	
	bool HSV::operator!=(const HSV & obj) const
	{
		return (this->h != obj.h || this->s != obj.s || this->v != obj.v);
	}
	
	bool HSV::operator==(const Vector3Impl & v) const
	{
		return (this->h == (MofS32)v.x && this->s == (MofS32)v.y && this->v == (MofS32)v.z);
	}
	
	bool HSV::operator!=(const Vector3Impl & v) const
	{
		return (this->h != (MofS32)v.x || this->s != (MofS32)v.y || this->v != (MofS32)v.z);
	}
	
	MofU32 CHSVUtilities::ToRGB(const HSV & v)
	{
		if (v.s == 0)
		{
			return MOF_XRGB(v.v, v.v, v.v);
		}

		float tmpMax = v.v;
		float tmpMin = tmpMax - (((float)v.s / 255.0f) * tmpMax);

		int h = v.h / 60;

		int r, g, b;

		switch (h)
		{
		case 0:
			r = tmpMax;
			g = ((float)v.h / 60.0f) * (tmpMax - tmpMin) + tmpMin;
			b = tmpMin;
			break;
		case 1:
			r = ((float)(120 - v.h) / 60.0f) * (tmpMax - tmpMin) + tmpMin;
			g = tmpMax;
			b = tmpMin;
			break;
		case 2:
			r = tmpMin;
			g = tmpMax;
			b = ((float)(v.h - 120) / 60.0f) * (tmpMax - tmpMin) + tmpMin;
			break;
		case 3:
			r = tmpMin;
			g = ((float)(240 - v.h) / 60.0f) * (tmpMax - tmpMin) + tmpMin;
			b = tmpMax;
			break;
		case 4:
			r = ((float)(v.h - 240) / 60.0f) * (tmpMax - tmpMin) + tmpMin;
			g = tmpMin;
			b = tmpMax;
			break;
		case 5:
			r = tmpMax;
			g = tmpMin;
			b = ((float)(360 - v.h) / 60.0f) * (tmpMax - tmpMin) + tmpMin;
			break;
		case 6:
			r = tmpMax;
			g = tmpMin;
			b = tmpMin;
		default:
			break;
		}

		return MOF_XRGB(r, g, b);
	}

	MofU32 CHSVUtilities::ToRGB(MofS32 h, MofS32 s, MofS32 v)
	{
		return ToRGB(HSV(h, s, v));
	}

	Vector4 CHSVUtilities::ToVector4(const HSV & v)
	{
		Vector4 color;
		CVector4Utilities::SetU32Color(ToRGB(v), color);
		return color;
	}

	Vector4 CHSVUtilities::ToVector4(MofS32 h, MofS32 s, MofS32 v)
	{
		Vector4 color;
		CVector4Utilities::SetU32Color(ToRGB(HSV(h, s, v)), color);
		return color;
	}
}