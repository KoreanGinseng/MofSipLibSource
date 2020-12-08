#pragma once
#include "EaseMotion.h"
#include "RoundRect.h"

namespace sip
{
	// ********************************************************************************
	/// <summary>
	/// 2D�p�J�����N���X
	/// </summary>
	// ********************************************************************************
	class CMyCamera2D
	{
	protected:

		Vector2              m_CenterPos;            //! ���S���W
		CEaseMotion<Vector2> m_MoveMotion;           //! �ړ��p���[�V����
		CRectangle           m_Limit{ NoneRect };    //! ���E�ړ��͈͋�`

	public:
		
		// ********************************************************************************
		/// <summary>
		/// �R���X�g���N�^
		/// </summary>
		/// <param name="center">���S���W</param>
		/// <created>���̂���,2020/11/23</created>
		/// <changed>���̂���,2020/11/23</changed>
		// ********************************************************************************
		explicit CMyCamera2D(const Vector2& center);
		
		// ********************************************************************************
		/// <summary>
		/// �f�X�g���N�^
		/// </summary>
		/// <created>���̂���,2020/11/23</created>
		/// <changed>���̂���,2020/11/23</changed>
		// ********************************************************************************
		virtual ~CMyCamera2D(void) = default;

		// ********************************************************************************
		/// <summary>
		/// �J�����̍X�V
		/// </summary>
		/// <created>���̂���,2020/11/23</created>
		/// <changed>���̂���,2020/11/23</changed>
		// ********************************************************************************
		virtual void Update(void);

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
		virtual void Move(const Vector2& endPos, const MofFloat sec = 1.0f, const Ease& ease = Ease::InOut, const EaseType& easeType = EaseType::Linear);

		// ********************************************************************************
		/// <summary>
		/// �J�����̒��S���W��ݒ肷��
		/// </summary>
		/// <param name="pos">�ݒ肷�钆�S���W</param>
		/// <created>���̂���,2020/11/23</created>
		/// <changed>���̂���,2020/11/23</changed>
		// ********************************************************************************
		inline virtual void SetCenterPos(const Vector2& center);

		// ********************************************************************************
		/// <summary>
		/// �J�����̌��E�ړ��͈͋�`�̐ݒ�
		/// </summary>
		/// <param name="rect">�ݒ肷��͈͋�`</param>
		/// <created>���̂���,2020/11/23</created>
		/// <changed>���̂���,2020/11/23</changed>
		// ********************************************************************************
		inline virtual void SetLimitRect(const CRectangle& rect);

		// ********************************************************************************
		/// <summary>
		/// �J�����̃��[���h���W�n�̋�`
		/// </summary>
		/// <returns></returns>
		/// <created>���̂���,2020/11/23</created>
		/// <changed>���̂���,2020/11/23</changed>
		// ********************************************************************************
		inline virtual CRectangle GetViewRect(void) const;

		// ********************************************************************************
		/// <summary>
		/// �J�����̈ړ��t���O�̎擾
		/// </summary>
		/// <returns>�ړ��t���O</returns>
		/// <created>���̂���,2020/11/23</created>
		/// <changed>���̂���,2020/11/23</changed>
		// ********************************************************************************
		inline virtual bool IsMoveMotion(void) const;

		// ********************************************************************************
		/// <summary>
		/// �J�����̕`��͈͋�`�Ɠ������Ă��邩
		/// </summary>
		/// <param name="rect">�����蔻�������`</param>
		/// <returns>true : �������Ă���, false : �������Ă��Ȃ�</returns>
		/// <created>���̂���,2020/11/23</created>
		/// <changed>���̂���,2020/11/23</changed>
		// ********************************************************************************
		inline virtual bool CollisionViewRect(const CRectangle& rect) const;

		// ********************************************************************************
		/// <summary>
		/// �J�����̃X�N���[����
		/// </summary>
		/// <returns>�X�N���[����</returns>
		/// <created>���̂���,2020/11/23</created>
		/// <changed>���̂���,2020/11/23</changed>
		// ********************************************************************************
		inline virtual Vector2 GetScroll(void) const;

		// ********************************************************************************
		/// <summary>
		/// ��ʒ������W�̎擾
		/// </summary>
		/// <returns>��ʒ������W</returns>
		/// <created>���̂���,2020/11/23</created>
		/// <changed>���̂���,2020/11/23</changed>
		// ********************************************************************************
		inline virtual Vector2 GetCenter(void) const;
	};
}

#include "MyCamera2D.inl"