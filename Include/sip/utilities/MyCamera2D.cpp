#include "MyCamera2D.h"

namespace sip
{
	// ********************************************************************************
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="center">中心座標</param>
	/// <created>いのうえ,2020/11/23</created>
	/// <changed>いのうえ,2020/11/23</changed>
	// ********************************************************************************
	CMyCamera2D::CMyCamera2D(const Vector2 & center)
	{
		m_CenterPos = center;
		m_MoveMotion.SetBeginEnd(m_CenterPos, m_CenterPos);
	}

	// ********************************************************************************
	/// <summary>
	/// カメラの更新
	/// </summary>
	/// <created>いのうえ,2020/11/23</created>
	/// <changed>いのうえ,2020/11/23</changed>
	// ********************************************************************************
	void CMyCamera2D::Update(void)
	{
		m_MoveMotion.Update();
		m_CenterPos = m_MoveMotion.GetValue();

		if (m_MoveMotion.IsEnd())
		{
			m_MoveMotion.Reset();
			m_MoveMotion.Stop();
		}

		if (m_Limit == NoneRect)
		{
			return;
		}

		CRectangle rect = GetViewRect();
		std::function<void(MofFloat, MofFloat, int)> OverControll = 
			[this](MofFloat over, MofFloat limit, int x)
		{
			if (over < limit)
			{
				((x) ? m_CenterPos.x : m_CenterPos.y) -= (over - limit);
			}
		};

		OverControll(rect.Left  , m_Limit.Left  , 1);
		OverControll(rect.Right , m_Limit.Right , 1);
		OverControll(rect.Top   , m_Limit.Top   , 0);
		OverControll(rect.Bottom, m_Limit.Bottom, 0);
	}

	// ********************************************************************************
	/// <summary>
	/// 指定した時間でカメラの移動
	/// </summary>
	/// <param name="endPos">移動最終地点</param>
	/// <param name="sec">移動にかける秒数</param>
	/// <param name="ease">イーズの種類</param>
	/// <param name="easeType">イーズ計算の種類</param>
	/// <created>いのうえ,2020/11/23</created>
	/// <changed>いのうえ,2020/11/23</changed>
	// ********************************************************************************
	void CMyCamera2D::Move(const Vector2 & endPos, const MofFloat sec, const Ease & ease, const EaseType & easeType)
	{
		if (IsMoveMotion())
		{
			return;
		}
		m_MoveMotion.SetBeginEnd(m_CenterPos, endPos);
		m_MoveMotion.SetEase(ease, easeType);
		m_MoveMotion.SetMotionTime(sec);
		m_MoveMotion.Start();
	}
}
