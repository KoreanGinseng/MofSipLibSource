#include "MyCamera2D.h"
namespace sip
{
	// ********************************************************************************
	/// <summary>
	/// カメラの中心座標を設定する
	/// </summary>
	/// <param name="pos">設定する中心座標</param>
	/// <created>いのうえ,2020/11/23</created>
	/// <changed>いのうえ,2020/11/23</changed>
	// ********************************************************************************
	inline void CMyCamera2D::SetCenterPos(const Vector2 & center)
	{
		m_CenterPos = center;
	}

	// ********************************************************************************
	/// <summary>
	/// カメラの限界移動範囲矩形の設定
	/// </summary>
	/// <param name="rect">設定する範囲矩形</param>
	/// <created>いのうえ,2020/11/23</created>
	/// <changed>いのうえ,2020/11/23</changed>
	// ********************************************************************************
	inline void CMyCamera2D::SetLimitRect(const CRectangle & rect)
	{
		m_Limit = rect;
	}

	// ********************************************************************************
	/// <summary>
	/// カメラのワールド座標系の矩形
	/// </summary>
	/// <returns></returns>
	/// <created>いのうえ,2020/11/23</created>
	/// <changed>いのうえ,2020/11/23</changed>
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
	/// カメラの移動フラグの取得
	/// </summary>
	/// <returns>移動フラグ</returns>
	/// <created>いのうえ,2020/11/23</created>
	/// <changed>いのうえ,2020/11/23</changed>
	// ********************************************************************************
	inline bool CMyCamera2D::IsMoveMotion(void) const
	{
		return m_MoveMotion.IsStart();
	}

	// ********************************************************************************
	/// <summary>
	/// カメラの描画範囲矩形と当たっているか
	/// </summary>
	/// <param name="rect">当たり判定を取る矩形</param>
	/// <returns>true : 当たっている, false : 当たっていない</returns>
	/// <created>いのうえ,2020/11/23</created>
	/// <changed>いのうえ,2020/11/23</changed>
	// ********************************************************************************
	inline bool CMyCamera2D::CollisionViewRect(const CRectangle & rect) const
	{
		return GetViewRect().CollisionRect(rect);
	}

	// ********************************************************************************
	/// <summary>
	/// カメラのスクロール量
	/// </summary>
	/// <returns>スクロール量</returns>
	/// <created>いのうえ,2020/11/23</created>
	/// <changed>いのうえ,2020/11/23</changed>
	// ********************************************************************************
	inline Vector2 CMyCamera2D::GetScroll(void) const
	{
		return -(GetViewRect().GetTopLeft());
	}

	// ********************************************************************************
	/// <summary>
	/// 画面中央座標の取得
	/// </summary>
	/// <returns>画面中央座標</returns>
	/// <created>いのうえ,2020/11/23</created>
	/// <changed>いのうえ,2020/11/23</changed>
	// ********************************************************************************
	inline Vector2 CMyCamera2D::GetCenter(void) const
	{
		return m_CenterPos;
	}
}