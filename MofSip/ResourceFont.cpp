#include "ResourceFont.h"

namespace sip
{
	// ********************************************************************************
	/// <summary>
	/// 名前のラップ
	/// </summary>
	/// <param name="pName">フォント名</param>
	/// <returns>true : 成功, false : 失敗</returns>
	/// <created>いのうえ,2020/11/11</created>
	/// <changed>いのうえ,2020/11/11</changed>
	// ********************************************************************************
	bool CFontA::Load(LPCMofChar pName)
	{
		return Create(24, pName);
	}

	// ********************************************************************************
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <created>いのうえ,2020/11/11</created>
	/// <changed>いのうえ,2020/11/11</changed>
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
	/// デストラクタ
	/// </summary>
	/// <created>いのうえ,2020/11/11</created>
	/// <changed>いのうえ,2020/11/11</changed>
	// ********************************************************************************
	CResourceFont::~CResourceFont(void)
	{
		Release();
	}

	// ********************************************************************************
	/// <summary>
	/// フォントハンドルの生成
	/// </summary>
	/// <param name="logFont">フォント生成情報</param>
	/// <returns>true : 成功, false : 失敗</returns>
	/// <created>いのうえ,2020/11/11</created>
	/// <changed>いのうえ,2020/11/11</changed>
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
	/// ファイルの読み込み
	/// </summary>
	/// <param name="pFile">読み込むファイル名\0フォント名\0\0</param>
	/// <returns>true : 成功, false : 失敗</returns>
	/// <created>いのうえ,2020/11/11</created>
	/// <changed>いのうえ,2020/11/11</changed>
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
	/// サイズの設定
	/// </summary>
	/// <param name="s">フォントサイズ</param>
	/// <returns>true : 成功, それ以外 : 失敗</returns>
	/// <created>いのうえ,2020/11/11</created>
	/// <changed>いのうえ,2020/11/11</changed>
	// ********************************************************************************
	MofBool CResourceFont::SetSize(MofS32 s)
	{
		m_FontInfo.lfHeight = m_FontInfo.lfWidth = s;
		return Create(m_FontInfo);
	}

	// ********************************************************************************
	/// <summary>
	/// 解放
	/// </summary>
	/// <param name="pData">解放追加データ</param>
	/// <returns>true : 成功, それ以外 : 失敗</returns>
	/// <created>いのうえ,2020/11/11</created>
	/// <changed>いのうえ,2020/11/11</changed>
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
