#include "ResourceFont.h"
#include "../tools/FileDialog.h"

namespace sip
{
	// ********************************************************************************
	/// <summary>
	/// ���O�̃��b�v
	/// </summary>
	/// <param name="pName">�t�H���g��</param>
	/// <returns>true : ����, false : ���s</returns>
	/// <created>���̂���,2020/11/11</created>
	/// <changed>���̂���,2020/11/11</changed>
	// ********************************************************************************
	bool CFontA::Load(LPCMofChar pName)
	{
		return Create(24, pName);
	}

	// ********************************************************************************
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <created>���̂���,2020/11/11</created>
	/// <changed>���̂���,2020/11/11</changed>
	// ********************************************************************************
	CResourceFont::CResourceFont(void)
		: CFont()
		, m_hResourceFontHandle(NULL)
	{
		m_FontInfo.lfHeight         = 24;
		m_FontInfo.lfWidth          = 24;
		m_FontInfo.lfEscapement     = 0;
		m_FontInfo.lfOrientation    = 0;
		m_FontInfo.lfWeight         = FW_REGULAR;
		m_FontInfo.lfItalic         = FALSE;
		m_FontInfo.lfUnderline      = FALSE;
		m_FontInfo.lfStrikeOut      = FALSE;
		m_FontInfo.lfCharSet        = DEFAULT_CHARSET;
		m_FontInfo.lfOutPrecision   = OUT_DEFAULT_PRECIS;
		m_FontInfo.lfClipPrecision  = CLIP_DEFAULT_PRECIS;
		m_FontInfo.lfQuality        = PROOF_QUALITY;
		m_FontInfo.lfPitchAndFamily = DEFAULT_PITCH;
	}

	// ********************************************************************************
	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	/// <created>���̂���,2020/11/11</created>
	/// <changed>���̂���,2020/11/11</changed>
	// ********************************************************************************
	CResourceFont::~CResourceFont(void)
	{
		DeleteHandle();
	}

	// ********************************************************************************
	/// <summary>
	/// �t�@�C���̓ǂݍ���
	/// </summary>
	/// <param name="pFile">�ǂݍ��ރt�@�C����\0�t�H���g��\0\0</param>
	/// <returns>true : ����, false : ���s</returns>
	/// <created>���̂���,2020/11/11</created>
	/// <changed>���̂���,2020/11/11</changed>
	// ********************************************************************************
	bool CResourceFont::Load(LPCMofChar pFileName)
	{
		// �t�@�C�����̃R�s�[
		std::vector<std::string> v;
		CFileDialog::SeparatePath(pFileName, v, &m_FileName);
		
		// �t�H���g�t�@�C�����g����悤�ɒǉ�����B
		AddFontResourceEx(TEXT(m_FileName.c_str()), FR_PRIVATE, NULL);
		
		// �t�H���g���𐶐����ɓo�^�B
		strcpy(m_FontInfo.lfFaceName, TEXT(v[0].c_str()));
		
		// �t�H���g�̐���
		if (m_hResourceFontHandle != NULL)
		{
			DeleteObject(m_hResourceFontHandle);
		}
		m_hResourceFontHandle = CreateFontIndirect(&m_FontInfo);
		return CFont::Create((MofFont)m_hResourceFontHandle);
	}

	// ********************************************************************************
	/// <summary>
	/// �T�C�Y�̐ݒ�
	/// </summary>
	/// <param name="s">�t�H���g�T�C�Y</param>
	/// <returns>true : ����, ����ȊO : ���s</returns>
	/// <created>���̂���,2020/11/11</created>
	/// <changed>���̂���,2020/11/11</changed>
	// ********************************************************************************
	MofBool CResourceFont::SetSize(MofS32 s)
	{
		m_FontInfo.lfHeight = m_FontInfo.lfWidth = s;
		// �t�H���g�̐���
		if (m_hResourceFontHandle != NULL)
		{
			DeleteObject(m_hResourceFontHandle);
		}
		m_hResourceFontHandle = CreateFontIndirect(&m_FontInfo);
		return CFont::Create((MofFont)m_hResourceFontHandle);
	}

	// ********************************************************************************
	/// <summary>
	/// �t�H���g�n���h���̌�n��
	/// </summary>
	/// <returns>true : ����, ����ȊO : ���s</returns>
	/// <created>���̂���,2020/11/11</created>
	/// <changed>���̂���,2020/11/11</changed>
	// ********************************************************************************
	MofBool CResourceFont::DeleteHandle(void)
	{
		if (m_hResourceFontHandle != NULL)
		{
			DeleteObject(m_hResourceFontHandle);
		}
		RemoveFontResourceEx(TEXT(m_FileName.c_str()), FR_PRIVATE, NULL);
		return TRUE;
	}
}
