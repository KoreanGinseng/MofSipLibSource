#include "ResourceFont.h"

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
		m_FontInfo.lfCharSet        = ANSI_CHARSET;
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
		Release();
	}

	// ********************************************************************************
	/// <summary>
	/// �t�H���g�n���h���̐���
	/// </summary>
	/// <param name="logFont">�t�H���g�������</param>
	/// <returns>true : ����, false : ���s</returns>
	/// <created>���̂���,2020/11/11</created>
	/// <changed>���̂���,2020/11/11</changed>
	// ********************************************************************************
	bool CResourceFont::Create(const LOGFONT & logFont)
	{
		if (m_hResourceFontHandle != NULL)
		{
			DeleteObject(m_hResourceFontHandle);
		}
		m_hResourceFontHandle = CreateFontIndirect(&m_FontInfo);
		return CFont::Create(m_hResourceFontHandle);
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
		m_FileName = pFileName;
		std::string fontName{ pFileName[strlen(pFileName) + 1] };
		AddFontResourceEx(TEXT(m_FileName.c_str()), FR_PRIVATE, NULL);
		strcpy(m_FontInfo.lfFaceName, TEXT(fontName.c_str()));
		return Create(m_FontInfo);
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
		return Create(m_FontInfo);
	}

	// ********************************************************************************
	/// <summary>
	/// ���
	/// </summary>
	/// <param name="pData">����ǉ��f�[�^</param>
	/// <returns>true : ����, ����ȊO : ���s</returns>
	/// <created>���̂���,2020/11/11</created>
	/// <changed>���̂���,2020/11/11</changed>
	// ********************************************************************************
	MofBool CResourceFont::Release(LPMofVoid pData)
	{
		if (m_hResourceFontHandle != NULL)
		{
			DeleteObject(m_hResourceFontHandle);
		}
		RemoveFontResourceEx(TEXT(m_FileName.c_str()), FR_PRIVATE, NULL);
		return CFont::Release(pData);
	}
}
