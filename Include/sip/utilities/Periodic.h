#pragma once
#include "Mof.h"
#include "MyTime.h"

namespace sip
{
	// ********************************************************************************
	/// <summary>
	/// 定期的な値を取得するスタティッククラス
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
		/// サイン波の動きするやつ
		/// </summary>
		/// <param name="periodSec">周期する秒</param>
		/// <param name="t">経過時間</param>
		/// <returns>経過時間での量</returns>
		/// <created>いのうえ,2020/12/04</created>
		/// <changed>いのうえ,2020/12/04</changed>
		// ********************************************************************************
		inline static float Sine0_1(const float& periodSec, const float& t = CMyTime::Time())
		{
			const float x = std::fmodf(t, periodSec) / (periodSec * (1 / MOF_MATH_2PI));

			return std::sinf(x) * 0.5f + 0.5f;
		}

		// ********************************************************************************
		/// <summary>
		/// 01交互やつ
		/// </summary>
		/// <param name="periodSec">周期する秒</param>
		/// <param name="t">経過時間</param>
		/// <returns>経過時間での量</returns>
		/// <created>いのうえ,2020/12/04</created>
		/// <changed>いのうえ,2020/12/04</changed>
		// ********************************************************************************
		inline static float Square0_1(const float& periodSec, const float& t = CMyTime::Time())
		{
			return (std::fmodf(t, periodSec) < (periodSec * 0.5f)) ? 1.0f : 0.0f;
		}

		// ********************************************************************************
		/// <summary>
		/// 行って帰ってくるやつ
		/// </summary>
		/// <param name="periodSec">周期する秒</param>
		/// <param name="t">経過時間</param>
		/// <returns>経過時間での量</returns>
		/// <created>いのうえ,2020/12/04</created>
		/// <changed>いのうえ,2020/12/04</changed>
		// ********************************************************************************
		inline static float Triangle0_1(const float& periodSec, const float& t = CMyTime::Time())
		{
			const float x = std::fmodf(t, periodSec) / (periodSec * 0.5f);

			return x <= 1.0f ? x : 2.0f - x;
		}

		// ********************************************************************************
		/// <summary>
		/// 一方通行やつ(のこぎり波)
		/// </summary>
		/// <param name="periodSec">周期する秒</param>
		/// <param name="t">経過時間</param>
		/// <returns>経過時間での量</returns>
		/// <created>いのうえ,2020/12/04</created>
		/// <changed>いのうえ,2020/12/04</changed>
		// ********************************************************************************
		inline static float Sawtooth0_1(const float& periodSec, const float& t = CMyTime::Time())
		{
			return std::fmodf(t, periodSec) / periodSec;
		}

		// ********************************************************************************
		/// <summary>
		/// ジャンプ的なやつ
		/// </summary>
		/// <param name="periodSec">周期する秒</param>
		/// <param name="t">経過時間</param>
		/// <returns>経過時間での量</returns>
		/// <created>いのうえ,2020/12/04</created>
		/// <changed>いのうえ,2020/12/04</changed>
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