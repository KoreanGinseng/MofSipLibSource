#pragma once
#include "Mof.h"

namespace sip
{
	struct HSV
	{
		union
		{
			MofS32 iv[3];
			struct 
			{
				MofS32 h;
				MofS32 s;
				MofS32 v;
			};
		};

		explicit HSV(MofS32 h, MofS32 s, MofS32 v);

		~HSV(void) = default;

		HSV& operator = (const Vector3Impl& v);

		HSV& operator = (const HSV& obj);

		HSV operator + (void) const;
		HSV operator - (void) const;

		HSV& operator += (const HSV& obj);
		HSV& operator -= (const HSV& obj);
		HSV& operator *= (const HSV& obj);
		HSV& operator /= (const HSV& obj);
		HSV operator + (const HSV& obj) const;
		HSV operator - (const HSV& obj) const;
		HSV operator * (const HSV& obj) const;
		HSV operator / (const HSV& obj) const;

		HSV& operator += (const Vector3Impl& v);
		HSV& operator -= (const Vector3Impl& v);
		HSV& operator *= (const Vector3Impl& v);
		HSV& operator /= (const Vector3Impl& v);
		HSV operator + (const Vector3Impl& v) const;
		HSV operator - (const Vector3Impl& v) const;
		HSV operator * (const Vector3Impl& v) const;
		HSV operator / (const Vector3Impl& v) const;

		HSV& operator += (MofS32 v);
		HSV& operator -= (MofS32 v);
		HSV& operator *= (MofS32 v);
		HSV& operator /= (MofS32 v);
		HSV operator + (MofS32 v) const;
		HSV operator - (MofS32 v) const;
		HSV operator * (MofS32 v) const;
		HSV operator / (MofS32 v) const;

		HSV& operator *= (float v);
		HSV& operator /= (float v);
		HSV operator * (float v) const;
		HSV operator / (float v) const;

		MofS32& operator[] (int i);
		const MofS32& operator[] (int i) const;

		bool operator == (const HSV& obj) const;
		bool operator != (const HSV& obj) const;

		bool operator == (const Vector3Impl& v) const;
		bool operator != (const Vector3Impl& v) const;
	};

	class CHSVUtilities
	{
	private:

		CHSVUtilities(void) = delete;
		~CHSVUtilities(void) = delete;

	public:

		static MofU32 ToRGB(const HSV& v);

		static MofU32 ToRGB(MofS32 h, MofS32 s, MofS32 v);

		static Vector4 ToVector4(const HSV& v);

		static Vector4 ToVector4(MofS32 h, MofS32 s, MofS32 v);
	};
}