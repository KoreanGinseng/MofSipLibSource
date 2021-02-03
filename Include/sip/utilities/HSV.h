#pragma once
#include "Mof.h"

namespace sip
{
	// ********************************************************************************
	/// <summary>
	/// HSV�\����
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
		/// �R���X�g���N�^
		/// </summary>
		/// <param name="h">�F��(0~359)</param>
		/// <param name="s">�ʓx(0~255)</param>
		/// <param name="v">���x(0~255)</param>
		/// <created>���̂���,2021/02/03</created>
		/// <changed>���̂���,2021/02/03</changed>
		// ********************************************************************************
		explicit HSV(MofS32 h, MofS32 s, MofS32 v);

		// ********************************************************************************
		/// <summary>
		/// �f�X�g���N�^
		/// </summary>
		/// <created>���̂���,2021/02/03</created>
		/// <changed>���̂���,2021/02/03</changed>
		// ********************************************************************************
		~HSV(void) = default;
        
        // ********************************************************************************
        /// <summary>
        /// �eoperator
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
	/// HSV�ėp�X�^�e�B�b�N�N���X
	/// </summary>
	// ********************************************************************************
	class CHSVUtilities
	{
	private:

        // �X�^�e�B�b�N�N���X�̏h��
		CHSVUtilities(void) = delete;
		~CHSVUtilities(void) = delete;

	public:

		// ********************************************************************************
		/// <summary>
		/// RGB�֕ϊ�
		/// </summary>
		/// <param name="v">HSV</param>
		/// <returns>RGB</returns>
		/// <created>���̂���,2021/02/03</created>
		/// <changed>���̂���,2021/02/03</changed>
		// ********************************************************************************
		static MofU32 ToRGB(const HSV& v);

		// ********************************************************************************
		/// <summary>
		/// RGB�֕ϊ�
		/// </summary>
		/// <param name="h">�F��(0~359)</param>
		/// <param name="s">�ʓx(0~255)</param>
		/// <param name="v">���x(0~255)</param>
		/// <returns>RGB</returns>
		/// <created>���̂���,2021/02/03</created>
		/// <changed>���̂���,2021/02/03</changed>
		// ********************************************************************************
		static MofU32 ToRGB(MofS32 h, MofS32 s, MofS32 v);

		// ********************************************************************************
		/// <summary>
		/// Vector4�֕ϊ�
		/// </summary>
		/// <param name="v">HSV</param>
		/// <returns>Vector4</returns>
		/// <created>���̂���,2021/02/03</created>
		/// <changed>���̂���,2021/02/03</changed>
		// ********************************************************************************
		static Vector4 ToVector4(const HSV& v);

		// ********************************************************************************
		/// <summary>
		/// Vector4�֕ϊ�
		/// </summary>
		/// <param name="h">�F��(0~359)</param>
		/// <param name="s">�ʓx(0~255)</param>
		/// <param name="v">���x(0~255)</param>
		/// <returns>Vector4</returns>
		/// <created>���̂���,2021/02/03</created>
		/// <changed>���̂���,2021/02/03</changed>
		// ********************************************************************************
		static Vector4 ToVector4(MofS32 h, MofS32 s, MofS32 v);
	};
}