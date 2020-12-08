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
	/// MOF内部で作成されたToonShaderを利用するクラス
	/// </summary>
	// ********************************************************************************
	class CToonShader
	{
	private:

		CShaderEffect_ToonShader     m_ToonShader;            //! トゥーンマップシェーダー
		CShaderEffect_ToonEdge       m_ToonEdge;              //! エッジ描画シェーダー
		CShaderEffect_EdgeBaseOutput m_EdgeBase;              //! エッジ準備シェーダー

		CTexture                     m_RenderTex;             //! 描画対象テクスチャ
		CTexture                     m_ToonTex;               //! エッジ描画テクスチャ
		CTexture                     m_ToonMapTex;            //! トゥーンマップ用テクスチャ

		LPRenderTarget               m_pOriginalRenderTarget; //! デフォルトの描画ターゲット
		LPDepthTarget                m_pOriginalDepthTarget;  //! デフォルトの深度ターゲット

	public:

		// ********************************************************************************
		/// <summary>
		/// コンストラクタ
		/// </summary>
		/// <created>いのうえ,2020/11/06</created>
		/// <changed>いのうえ,2020/11/06</changed>
		// ********************************************************************************
		explicit CToonShader(void);

		// ********************************************************************************
		/// <summary>
		/// デストラクタ
		/// </summary>
		/// <created>いのうえ,2020/11/06</created>
		/// <changed>いのうえ,2020/11/06</changed>
		// ********************************************************************************
		~CToonShader(void);

		// ********************************************************************************
		/// <summary>
		/// シェーダーの作成
		/// </summary>
		/// <returns>TRUE：成功、FALSE：失敗</returns>
		/// <created>いのうえ,2020/11/06</created>
		/// <changed>いのうえ,2020/11/06</changed>
		// ********************************************************************************
		bool Create(void);

		// ********************************************************************************
		/// <summary>
		/// 適応するトゥーンマップ画像の読み込み
		/// </summary>
		/// <param name="pFileName">ファイル名</param>
		/// <returns>TRUE：成功、FALSE：失敗</returns>
		/// <created>いのうえ,2020/11/06</created>
		/// <changed>いのうえ,2020/11/06</changed>
		// ********************************************************************************
		bool LoadToonMap(LPCMofChar pFileName);
		
		// ********************************************************************************
		/// <summary>
		/// 解放
		/// </summary>
		/// <created>いのうえ,2020/11/06</created>
		/// <changed>いのうえ,2020/11/06</changed>
		// ********************************************************************************
		void Release(void);

		// ********************************************************************************
		/// <summary>
		/// トゥーンレンダリングの開始
		/// </summary>
		/// <created>いのうえ,2020/11/06</created>
		/// <changed>いのうえ,2020/11/06</changed>
		// ********************************************************************************
		void Begin(void);

		// ********************************************************************************
		/// <summary>
		/// トゥーンレンダリングの終了
		/// </summary>
		/// <created>いのうえ,2020/11/06</created>
		/// <changed>いのうえ,2020/11/06</changed>
		// ********************************************************************************
		void End(void);
	};
}

