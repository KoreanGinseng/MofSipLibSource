#pragma once
#include "Mof.h"
#include "MyTime.h"

namespace sip
{
	// ********************************************************************************
	/// <summary>
	/// ����I�Ȓl���擾����X�^�e�B�b�N�N���X
	/// </summary>
	// ********************************************************************************
	class CPeriodic
	{
	private:
		
		CPeriodic(void) = delete;
		~CPeriodic(void) = delete;

	public:
		// ********************************************************************************
		/// <summary>
		/// �T�C���g�̓���������
		/// </summary>
		/// <param name="periodSec">��������b</param>
		/// <param name="t">�o�ߎ���</param>
		/// <returns>�o�ߎ��Ԃł̗�</returns>
		/// <created>���̂���,2020/12/04</created>
		/// <changed>���̂���,2020/12/04</changed>
		// ********************************************************************************
		inline static float Sine0_1(const float& periodSec, const float& t = CMyTime::Time())
		{
			const float x = std::fmodf(t, periodSec) / (periodSec * (1 / MOF_MATH_2PI));

			return std::sinf(x) * 0.5f + 0.5f;
		}

		// ********************************************************************************
		/// <summary>
		/// 01���݂��
		/// </summary>
		/// <param name="periodSec">��������b</param>
		/// <param name="t">�o�ߎ���</param>
		/// <returns>�o�ߎ��Ԃł̗�</returns>
		/// <created>���̂���,2020/12/04</created>
		/// <changed>���̂���,2020/12/04</changed>
		// ********************************************************************************
		inline static float Square0_1(const float& periodSec, const float& t = CMyTime::Time())
		{
			return (std::fmodf(t, periodSec) < (periodSec * 0.5f)) ? 1.0f : 0.0f;
		}

		// ********************************************************************************
		/// <summary>
		/// �s���ċA���Ă�����
		/// </summary>
		/// <param name="periodSec">��������b</param>
		/// <param name="t">�o�ߎ���</param>
		/// <returns>�o�ߎ��Ԃł̗�</returns>
		/// <created>���̂���,2020/12/04</created>
		/// <changed>���̂���,2020/12/04</changed>
		// ********************************************************************************
		inline static float Triangle0_1(const float& periodSec, const float& t = CMyTime::Time())
		{
			const float x = std::fmodf(t, periodSec) / (periodSec * 0.5f);

			return x <= 1.0f ? x : 2.0f - x;
		}

		// ********************************************************************************
		/// <summary>
		/// ����ʍs���(�̂�����g)
		/// </summary>
		/// <param name="periodSec">��������b</param>
		/// <param name="t">�o�ߎ���</param>
		/// <returns>�o�ߎ��Ԃł̗�</returns>
		/// <created>���̂���,2020/12/04</created>
		/// <changed>���̂���,2020/12/04</changed>
		// ********************************************************************************
		inline static float Sawtooth0_1(const float& periodSec, const float& t = CMyTime::Time())
		{
			return std::fmodf(t, periodSec) / periodSec;
		}

		// ********************************************************************************
		/// <summary>
		/// �W�����v�I�Ȃ��
		/// </summary>
		/// <param name="periodSec">��������b</param>
		/// <param name="t">�o�ߎ���</param>
		/// <returns>�o�ߎ��Ԃł̗�</returns>
		/// <created>���̂���,2020/12/04</created>
		/// <changed>���̂���,2020/12/04</changed>
		// ********************************************************************************
		inline static float Jump0_1(const float& periodSec, const float& t = CMyTime::Time())
		{
			float x = std::fmodf(t, periodSec) / (periodSec * 0.5f);

			if (1.0f < x)
			{
				x = 2.0f - x;
			}

			return 2 * x - (x * x);
		}
	};
}