#include "RoundRect.h"

namespace sip
{
	RoundRect::RoundRect(void)
		: Rectangle()
		, r(0.0f)
	{
	}

	RoundRect::RoundRect(MofFloat left, MofFloat top, MofFloat right, MofFloat bottom, MofFloat r)
		: Rectangle(left, top, right, bottom)
		, r(r)
	{
	}

	RoundRect::RoundRect(const Vector2 & lt, const Vector2 & rb, MofFloat r)
		: Rectangle(lt, rb)
		, r(r)
	{
	}

	RoundRect::RoundRect(const Mof::Rectangle & rect, MofFloat r)
		: Rectangle(rect)
		, r(r)
	{
	}

	RoundRect::RoundRect(LPMofFloat pv)
		: Rectangle(pv)
		, r(pv[4])
	{
	}

	RoundRect::RoundRect(const sip::RoundRect & pObj)
		: Rectangle(pObj)
		, r(pObj.r)
	{
	}

	RoundRect::operator LPMofFloat(void)
	{
		return (LPMofFloat)&Left;
	}

	RoundRect::operator Mof::Rectangle(void)
	{
		return Rectangle(Left, Top, Right, Bottom);
	}

	bool RoundRect::operator==(const RoundRect & v) const
	{
		return Left == v.Left && Top == v.Top && Right == v.Right && Bottom == v.Bottom && r == v.r;
	}

	bool RoundRect::operator!=(const RoundRect & v) const
	{
		return Left != v.Left || Top != v.Top || Right != v.Right || Bottom != v.Bottom || r != v.r;
	}

	CRoundRect::CRoundRect(void)
		: RoundRect()
	{
		CalcRectCircle();
	}
	
	CRoundRect::CRoundRect(MofFloat left, MofFloat top, MofFloat right, MofFloat bottom, MofFloat r)
		: RoundRect(left, top, right, bottom, r)
	{
		CalcRectCircle();
	}
	
	CRoundRect::CRoundRect(const Vector2 & lt, const Vector2 & rb, MofFloat r)
		: RoundRect(lt, rb, r)
	{
		CalcRectCircle();
	}
	
	CRoundRect::CRoundRect(const Mof::Rectangle & rect, MofFloat r)
		: RoundRect(rect, r)
	{
		CalcRectCircle();
	}
	
	CRoundRect::CRoundRect(LPMofFloat pv)
		: RoundRect(pv)
	{
		CalcRectCircle();
	}
	
	CRoundRect::CRoundRect(const RoundRect & pObj)
		: RoundRect(pObj)
	{
		CalcRectCircle();
	}

	void CRoundRect::Expansion(const MofFloat & e, const MofFloat & r)
	{
		Left -= e;
		Top -= e;
		Right += e;
		Bottom += e;
		this->r += r;
		CalcRectCircle();
	}

	void CRoundRect::Expansion(const MofFloat & ex, const MofFloat & ey, const MofFloat & r)
	{
		Left -= ex;
		Top -= ey;
		Right += ex;
		Bottom += ey;
		this->r += r;
		CalcRectCircle();
	}

	void CRoundRect::Translation(const Vector2 & m)
	{
		MofFloat w = Right - Left;
		MofFloat h = Bottom - Top;
		Left += m.x;
		Top += m.y;
		Right = Left + w;
		Bottom = Top + h;
	}

	void CRoundRect::SetPosition(const Vector2 & pos)
	{
		MofFloat w = Right - Left;
		MofFloat h = Bottom - Top;
		Left = pos.x;
		Top = pos.y;
		Right = Left + w;
		Bottom = Top + h;
	}

	void CRoundRect::SetWidth(const MofFloat & w)
	{
		Right = Left + w;
		CalcRectCircle();
	}

	void CRoundRect::SetHeight(const MofFloat & h)
	{
		Bottom = Top + h;
		CalcRectCircle();
	}

	void CRoundRect::SetRadius(const MofFloat & r)
	{
		this->r = r;
		CalcRectCircle();
	}
	
	MofBool CRoundRect::CollisionPoint(const MofFloat & px, const MofFloat & py) const
	{
		for (int i = 0; i < 4; i++)
		{
			if (m_CircleArray[i] == NoneCircle)
			{
				break;
			}

			if (CCircleUtilities::CollisionPoint(m_CircleArray[i], px, py))
			{
				return TRUE;
			}
		}
		for (int i = 0; i < 2; i++)
		{
			if (m_RectArray[i] == NoneRect)
			{
				break;
			}

			if (CRectangleUtilities::CollisionPoint(m_RectArray[i], px, py))
			{
				return TRUE;
			}
		}
		return FALSE;
	}
	
	MofBool CRoundRect::CollisionPoint(const Vector2 & p) const
	{
		return CollisionPoint(p.x, p.y);
	}
	
	void CRoundRect::SetValue(MofFloat left, MofFloat top, MofFloat right, MofFloat bottom, MofFloat r)
	{
		Left = left;
		Top = top;
		Right = right;
		Bottom = bottom;
		this->r = r;
		CalcRectCircle();
	}

	void CRoundRect::Render(const MofU32 & color)
	{
		// 円の描画
		for (int i = 0; i < 4; i++)
		{
			if (m_CircleArray[i] == NoneCircle)
			{
				break;
			}
			CGraphicsUtilities::RenderFillCircle(m_CircleArray[i], color);
		}
		// 矩形の描画
		for (int i = 0; i < 2; i++)
		{
			if (m_RectArray[i] == NoneRect)
			{
				break;
			}
			CGraphicsUtilities::RenderFillRect(m_RectArray[i], color);
		}
	}
	
	MofFloat CRoundRect::GetWidth(void) const
	{
		return Right - Left;
	}
	
	MofFloat CRoundRect::GetHeight(void) const
	{
		return Bottom - Top;
	}
	
	MofFloat CRoundRect::GetRadius(void) const
	{
		return r;
	}
	
	Vector2 CRoundRect::GetCenter(void) const
	{
		return Vector2((Left + Right) * 0.5f, (Top + Bottom) * 0.5f);
	}
	
	CRoundRect::operator sip::RoundRect(void)
	{
		return sip::RoundRect(Left, Top, Right, Bottom, r);
	}

	void CRoundRect::CalcRectCircle(void)
	{
		// 配列の初期化
		for (int i = 0; i < 4; i++)
		{
			m_CircleArray[i] = NoneCircle;
			if (i >= 2) continue;
			m_RectArray[i] = NoneRect;
		}

		// 高さと半径のチェック
		bool bLessW = (GetWidth() <= r * 2);
		// 横幅と半径のチェック
		bool bLessH = (GetHeight() <= r * 2);

		// 半径の制御
		r = MOF_CLIPING(r, 0, MOF_MIN(GetHeight(), GetWidth()) * 0.5f);

		// 高さ、幅の両方を半径が超えている場合、円のみ。
		if (bLessW && bLessH)
		{
			m_CircleArray[0] = Mof::Circle(GetCenter(), r);
		}
		// どちらか片方超えている場合、使用する配列を減らす。
		else if (bLessW || bLessH)
		{
			if (bLessW)
			{
				m_RectArray[0] = Mof::Rectangle(Left, Top + r, Right, Bottom - r);
			}
			else
			{
				m_RectArray[0] = Mof::Rectangle(Left + r, Top, Right - r, Bottom);
			}
			m_CircleArray[0] = Mof::Circle(Left  + r, Top    + r, r);
			m_CircleArray[1] = Mof::Circle(Right - r, Bottom - r, r);
		}
		else
		{
			m_RectArray[0] = Mof::Rectangle(Left, Top + r, Right, Bottom - r);
			m_RectArray[1] = Mof::Rectangle(Left + r, Top, Right - r, Bottom);

			m_CircleArray[0] = Mof::Circle(Left  + r, Top    + r, r);
			m_CircleArray[1] = Mof::Circle(Right - r, Top    + r, r);
			m_CircleArray[2] = Mof::Circle(Left  + r, Bottom - r, r);
			m_CircleArray[3] = Mof::Circle(Right - r, Bottom - r, r);
		}
	}

	MofBool CRoundRectUtilities::CollisionPoint(const sip::RoundRect & rrect, const MofFloat & px, const MofFloat & py)
	{
		const CRoundRect r(rrect);
		return r.CollisionPoint(px, py);
	}

	MofBool CRoundRectUtilities::CollisionPoint(const sip::RoundRect & rrect, const Vector2 & p)
	{
		return CollisionPoint(rrect, p.x, p.y);
	}

	void CRoundRectUtilities::Render(const sip::RoundRect & rrect, const MofU32 & color)
	{
		CRoundRect r(rrect);
		r.Render(color);
	}

	void CRoundRectUtilities::Render(const sip::RoundRect & rrect, const LPTexture & pTexture, const MofU32 & color)
	{
		CRoundRect r(rrect);
		g_pGraphics->SetStencilEnable(TRUE);
		g_pGraphics->SetStencilValue(1);
		g_pGraphics->SetStencilControl(COMPARISON_ALWAYS, STENCIL_REPLACE, STENCIL_REPLACE, STENCIL_REPLACE);
		r.Render(MOF_ARGB(0, 0, 0, 0));
		g_pGraphics->SetStencilControl(COMPARISON_EQUAL, STENCIL_KEEP, STENCIL_KEEP, STENCIL_KEEP);
		pTexture->Render(rrect, color);
		g_pGraphics->SetStencilEnable(FALSE);
	}
}
