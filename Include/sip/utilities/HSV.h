#pragma once
#include "Mof.h"

namespace sip
{
	// ********************************************************************************
	/// <summary>
	/// HSV構造体
	/// </summary>
	// ********************************************************************************
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

		// ********************************************************************************
		/// <summary>
		/// コンストラクタ
		/// </summary>
		/// <param name="h">色相(0~359)</param>
		/// <param name="s">彩度(0~255)</param>
		/// <param name="v">明度(0~255)</param>
		/// <created>いのうえ,2021/02/03</created>
		/// <changed>いのうえ,2021/02/03</changed>
		// ********************************************************************************
		explicit HSV(MofS32 h, MofS32 s, MofS32 v);

		// ********************************************************************************
		/// <summary>
		/// デストラクタ
		/// </summary>
		/// <created>いのうえ,2021/02/03</created>
		/// <changed>いのうえ,2021/02/03</changed>
		// ********************************************************************************
		~HSV(void) = default;
        
        // ********************************************************************************
        /// <summary>
        /// 各operator
        /// </summary>
        // ********************************************************************************
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

	// ********************************************************************************
	/// <summary>
	/// HSV汎用スタティッククラス
	/// </summary>
	// ********************************************************************************
	class CHSVUtilities
	{
	private:

        // スタティッククラスの宿命
		CHSVUtilities(void) = delete;
		~CHSVUtilities(void) = delete;

	public:

		// ********************************************************************************
		/// <summary>
		/// RGBへ変換
		/// </summary>
		/// <param name="v">HSV</param>
		/// <returns>RGB</returns>
		/// <created>いのうえ,2021/02/03</created>
		/// <changed>いのうえ,2021/02/03</changed>
		// ********************************************************************************
		static MofU32 ToRGB(const HSV& v);

		// ********************************************************************************
		/// <summary>
		/// RGBへ変換
		/// </summary>
		/// <param name="h">色相(0~359)</param>
		/// <param name="s">彩度(0~255)</param>
		/// <param name="v">明度(0~255)</param>
		/// <returns>RGB</returns>
		/// <created>いのうえ,2021/02/03</created>
		/// <changed>いのうえ,2021/02/03</changed>
		// ********************************************************************************
		static MofU32 ToRGB(MofS32 h, MofS32 s, MofS32 v);

		// ********************************************************************************
		/// <summary>
		/// Vector4へ変換
		/// </summary>
		/// <param name="v">HSV</param>
		/// <returns>Vector4</returns>
		/// <created>いのうえ,2021/02/03</created>
		/// <changed>いのうえ,2021/02/03</changed>
		// ********************************************************************************
		static Vector4 ToVector4(const HSV& v);

		// ********************************************************************************
		/// <summary>
		/// Vector4へ変換
		/// </summary>
		/// <param name="h">色相(0~359)</param>
		/// <param name="s">彩度(0~255)</param>
		/// <param name="v">明度(0~255)</param>
		/// <returns>Vector4</returns>
		/// <created>いのうえ,2021/02/03</created>
		/// <changed>いのうえ,2021/02/03</changed>
		// ********************************************************************************
		static Vector4 ToVector4(MofS32 h, MofS32 s, MofS32 v);
	};
}