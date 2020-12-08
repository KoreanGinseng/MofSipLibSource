#pragma once
#include "EaseMotion.h"
#include "RoundRect.h"

namespace sip
{
	// ********************************************************************************
	/// <summary>
	/// 2D用カメラクラス
	/// </summary>
	// ********************************************************************************
	class CMyCamera2D
	{
	protected:

		Vector2              m_CenterPos;            //! 中心座標
		CEaseMotion<Vector2> m_MoveMotion;           //! 移動用モーション
		CRectangle           m_Limit{ NoneRect };    //! 限界移動範囲矩形

	public:
		
		// ********************************************************************************
		/// <summary>
		/// コンストラクタ
		/// </summary>
		/// <param name="center">中心座標</param>
		/// <created>いのうえ,2020/11/23</created>
		/// <changed>いのうえ,2020/11/23</changed>
		// ********************************************************************************
		explicit CMyCamera2D(const Vector2& center);
		
		// ********************************************************************************
		/// <summary>
		/// デストラクタ
		/// </summary>
		/// <created>いのうえ,2020/11/23</created>
		/// <changed>いのうえ,2020/11/23</changed>
		// ********************************************************************************
		virtual ~CMyCamera2D(void) = default;

		// ********************************************************************************
		/// <summary>
		/// カメラの更新
		/// </summary>
		/// <created>いのうえ,2020/11/23</created>
		/// <changed>いのうえ,2020/11/23</changed>
		// ********************************************************************************
		virtual void Update(void);

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
		virtual void Move(const Vector2& endPos, const MofFloat sec = 1.0f, const Ease& ease = Ease::InOut, const EaseType& easeType = EaseType::Linear);

		// ********************************************************************************
		/// <summary>
		/// カメラの中心座標を設定する
		/// </summary>
		/// <param name="pos">設定する中心座標</param>
		/// <created>いのうえ,2020/11/23</created>
		/// <changed>いのうえ,2020/11/23</changed>
		// ********************************************************************************
		inline virtual void SetCenterPos(const Vector2& center);

		// ********************************************************************************
		/// <summary>
		/// カメラの限界移動範囲矩形の設定
		/// </summary>
		/// <param name="rect">設定する範囲矩形</param>
		/// <created>いのうえ,2020/11/23</created>
		/// <changed>いのうえ,2020/11/23</changed>
		// ********************************************************************************
		inline virtual void SetLimitRect(const CRectangle& rect);

		// ********************************************************************************
		/// <summary>
		/// カメラのワールド座標系の矩形
		/// </summary>
		/// <returns></returns>
		/// <created>いのうえ,2020/11/23</created>
		/// <changed>いのうえ,2020/11/23</changed>
		// ********************************************************************************
		inline virtual CRectangle GetViewRect(void) const;

		// ********************************************************************************
		/// <summary>
		/// カメラの移動フラグの取得
		/// </summary>
		/// <returns>移動フラグ</returns>
		/// <created>いのうえ,2020/11/23</created>
		/// <changed>いのうえ,2020/11/23</changed>
		// ********************************************************************************
		inline virtual bool IsMoveMotion(void) const;

		// ********************************************************************************
		/// <summary>
		/// カメラの描画範囲矩形と当たっているか
		/// </summary>
		/// <param name="rect">当たり判定を取る矩形</param>
		/// <returns>true : 当たっている, false : 当たっていない</returns>
		/// <created>いのうえ,2020/11/23</created>
		/// <changed>いのうえ,2020/11/23</changed>
		// ********************************************************************************
		inline virtual bool CollisionViewRect(const CRectangle& rect) const;

		// ********************************************************************************
		/// <summary>
		/// カメラのスクロール量
		/// </summary>
		/// <returns>スクロール量</returns>
		/// <created>いのうえ,2020/11/23</created>
		/// <changed>いのうえ,2020/11/23</changed>
		// ********************************************************************************
		inline virtual Vector2 GetScroll(void) const;

		// ********************************************************************************
		/// <summary>
		/// 画面中央座標の取得
		/// </summary>
		/// <returns>画面中央座標</returns>
		/// <created>いのうえ,2020/11/23</created>
		/// <changed>いのうえ,2020/11/23</changed>
		// ********************************************************************************
		inline virtual Vector2 GetCenter(void) const;
	};
}

#include "MyCamera2D.inl"