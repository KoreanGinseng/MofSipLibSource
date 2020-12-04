#include "MyCamera2D.h"
namespace sip
{
	// ********************************************************************************
	/// <summary>
	/// �J�����̒��S���W��ݒ肷��
	/// </summary>
	/// <param name="pos">�ݒ肷�钆�S���W</param>
	/// <created>���̂���,2020/11/23</created>
	/// <changed>���̂���,2020/11/23</changed>
	// ********************************************************************************
	inline void CMyCamera2D::SetCenterPos(const Vector2 & center)
	{
		m_CenterPos = center;
	}

	// ********************************************************************************
	/// <summary>
	/// �J�����̌��E�ړ��͈͋�`�̐ݒ�
	/// </summary>
	/// <param name="rect">�ݒ肷��͈͋�`</param>
	/// <created>���̂���,2020/11/23</created>
	/// <changed>���̂���,2020/11/23</changed>
	// ********************************************************************************
	inline void CMyCamera2D::SetLimitRect(const CRectangle & rect)
	{
		m_Limit = rect;
	}

	// ********************************************************************************
	/// <summary>
	/// �J�����̃��[���h���W�n�̋�`
	/// </summary>
	/// <returns></returns>
	/// <created>���̂���,2020/11/23</created>
	/// <changed>���̂���,2020/11/23</changed>
	// ********************************************************************************
	inline CRectangle CMyCamera2D::GetViewRect(void) const
	{
		Vector2 size{ 
			(MofFloat)g_pGraphics->GetTargetWidth(),
			(MofFloat)g_pGraphics->GetTargetHeight()
		};
		CRectangle rect{ Vector2(), size };
		rect.Translation(m_CenterPos - (size * 0.5f));
		return rect;
	}

	// ********************************************************************************
	/// <summary>
	/// �J�����̈ړ��t���O�̎擾
	/// </summary>
	/// <returns>�ړ��t���O</returns>
	/// <created>���̂���,2020/11/23</created>
	/// <changed>���̂���,2020/11/23</changed>
	// ********************************************************************************
	inline bool CMyCamera2D::IsMoveMotion(void) const
	{
		return m_MoveMotion.IsStart();
	}

	// ********************************************************************************
	/// <summary>
	/// �J�����̕`��͈͋�`�Ɠ������Ă��邩
	/// </summary>
	/// <param name="rect">�����蔻�������`</param>
	/// <returns>true : �������Ă���, false : �������Ă��Ȃ�</returns>
	/// <created>���̂���,2020/11/23</created>
	/// <changed>���̂���,2020/11/23</changed>
	// ********************************************************************************
	inline bool CMyCamera2D::CollisionViewRect(const CRectangle & rect) const
	{
		return GetViewRect().CollisionRect(rect);
	}

	// ********************************************************************************
	/// <summary>
	/// �J�����̃X�N���[����
	/// </summary>
	/// <returns>�X�N���[����</returns>
	/// <created>���̂���,2020/11/23</created>
	/// <changed>���̂���,2020/11/23</changed>
	// ********************************************************************************
	inline Vector2 CMyCamera2D::GetScroll(void) const
	{
		return -(GetViewRect().GetTopLeft());
	}

	// ********************************************************************************
	/// <summary>
	/// ��ʒ������W�̎擾
	/// </summary>
	/// <returns>��ʒ������W</returns>
	/// <created>���̂���,2020/11/23</created>
	/// <changed>���̂���,2020/11/23</changed>
	// ********************************************************************************
	inline Vector2 CMyCamera2D::GetCenter(void) const
	{
		return m_CenterPos;
	}
}