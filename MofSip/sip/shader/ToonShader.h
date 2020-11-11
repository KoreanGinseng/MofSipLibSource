#pragma once

//INCLUDE
#include "Mof.h"
#include <Graphics/ShaderEffect_ToonShader.h>
#include <Graphics/ShaderEffect_ToonEdge.h>
#include <Graphics/ShaderEffect_EdgeBaseOutput.h>

namespace sip
{
	// ********************************************************************************
	/// <summary>
	/// MOF�����ō쐬���ꂽToonShader�𗘗p����N���X
	/// </summary>
	// ********************************************************************************
	class CToonShader
	{
	private:

		CShaderEffect_ToonShader     m_ToonShader;            //! �g�D�[���}�b�v�V�F�[�_�[
		CShaderEffect_ToonEdge       m_ToonEdge;              //! �G�b�W�`��V�F�[�_�[
		CShaderEffect_EdgeBaseOutput m_EdgeBase;              //! �G�b�W�����V�F�[�_�[

		CTexture                     m_RenderTex;             //! �`��Ώۃe�N�X�`��
		CTexture                     m_ToonTex;               //! �G�b�W�`��e�N�X�`��
		CTexture                     m_ToonMapTex;            //! �g�D�[���}�b�v�p�e�N�X�`��

		LPRenderTarget               m_pOriginalRenderTarget; //! �f�t�H���g�̕`��^�[�Q�b�g
		LPDepthTarget                m_pOriginalDepthTarget;  //! �f�t�H���g�̐[�x�^�[�Q�b�g

	public:

		// ********************************************************************************
		/// <summary>
		/// �R���X�g���N�^
		/// </summary>
		/// <created>���̂���,2020/11/06</created>
		/// <changed>���̂���,2020/11/06</changed>
		// ********************************************************************************
		explicit CToonShader(void);

		// ********************************************************************************
		/// <summary>
		/// �f�X�g���N�^
		/// </summary>
		/// <created>���̂���,2020/11/06</created>
		/// <changed>���̂���,2020/11/06</changed>
		// ********************************************************************************
		~CToonShader(void);

		// ********************************************************************************
		/// <summary>
		/// �V�F�[�_�[�̍쐬
		/// </summary>
		/// <returns>TRUE�F�����AFALSE�F���s</returns>
		/// <created>���̂���,2020/11/06</created>
		/// <changed>���̂���,2020/11/06</changed>
		// ********************************************************************************
		bool Create(void);

		// ********************************************************************************
		/// <summary>
		/// �K������g�D�[���}�b�v�摜�̓ǂݍ���
		/// </summary>
		/// <param name="pFileName">�t�@�C����</param>
		/// <returns>TRUE�F�����AFALSE�F���s</returns>
		/// <created>���̂���,2020/11/06</created>
		/// <changed>���̂���,2020/11/06</changed>
		// ********************************************************************************
		bool LoadToonMap(LPCMofChar pFileName);
		
		// ********************************************************************************
		/// <summary>
		/// ���
		/// </summary>
		/// <created>���̂���,2020/11/06</created>
		/// <changed>���̂���,2020/11/06</changed>
		// ********************************************************************************
		void Release(void);

		// ********************************************************************************
		/// <summary>
		/// �g�D�[�������_�����O�̊J�n
		/// </summary>
		/// <created>���̂���,2020/11/06</created>
		/// <changed>���̂���,2020/11/06</changed>
		// ********************************************************************************
		void Begin(void);

		// ********************************************************************************
		/// <summary>
		/// �g�D�[�������_�����O�̏I��
		/// </summary>
		/// <created>���̂���,2020/11/06</created>
		/// <changed>���̂���,2020/11/06</changed>
		// ********************************************************************************
		void End(void);
	};
}

