#include "MyCamera2D.h"

namespace sip
{
	// ********************************************************************************
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="center">���S���W</param>
	/// <created>���̂���,2020/11/23</created>
	/// <changed>���̂���,2020/11/23</changed>
	// ********************************************************************************
	CMyCamera2D::CMyCamera2D(const Vector2 & center)
	{
		m_CenterPos = center;
		m_MoveMotion.SetBeginEnd(m_CenterPos, m_CenterPos);
	}

	// ********************************************************************************
	/// <summary>
	/// �J�����̍X�V
	/// </summary>
	/// <created>���̂���,2020/11/23</created>
	/// <changed>���̂���,2020/11/23</changed>
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
	/// �w�肵�����ԂŃJ�����̈ړ�
	/// </summary>
	/// <param name="endPos">�ړ��ŏI�n�_</param>
	/// <param name="sec">�ړ��ɂ�����b��</param>
	/// <param name="ease">�C�[�Y�̎��</param>
	/// <param name="easeType">�C�[�Y�v�Z�̎��</param>
	/// <created>���̂���,2020/11/23</created>
	/// <changed>���̂���,2020/11/23</changed>
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
