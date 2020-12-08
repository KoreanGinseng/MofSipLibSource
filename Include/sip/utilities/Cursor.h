#pragma once
#include <wuapi.h>
#include <vector>

namespace sip
{
	// ********************************************************************************
	/// <summary>
	/// カーソルの種類
	/// </summary>
	// ********************************************************************************
	enum CursorType
	{
		ARROW,            //! 矢印
		IBEAM,            //! 文字入力のアレ
		WAIT,             //! いつもグルグルしてるやつ
		CROSS,            //! 十字
		UPARROW,          //! アゲアゲ
		SIZENWSE,         //! 右上左下
		SIZENESW,         //! 左上右下
		SIZEWE,           //! 左右
		SIZENS,           //! 上下
		SIZEALL,          //! 上下左右
		NO,               //! 禁止マーク
		HAND,             //! 指差しやつ
		APPSTARTING,      //! 矢印＋ぐるぐる
		HELP,             //! 矢印＋？
		PIN,              //! 矢印＋マップ座標に刺さるアレ
		PERSON,           //! 矢印＋人

		DEFAULT = ARROW,  //! デフォルト(矢印)
	};

	// ********************************************************************************
	/// <summary>
	/// カーソル変更用スタティッククラス
	/// </summary>
	// ********************************************************************************
	class CCursor
	{
	private:
		//スタティッククラスなので消されているね。
		CCursor(void) = delete;
		~CCursor(void) = delete;

	protected:
		// ********************************************************************************
		/// <summary>
		/// カーソルハンドルたちの取得。
		/// </summary>
		/// <returns>カーソルハンドル配列</returns>
		/// <created>いのうえ,2020/11/23</created>
		/// <changed>いのうえ,2020/11/23</changed>
		// ********************************************************************************
		static const std::vector<HCURSOR>& GetHandleArray(void)
		{
			static const std::vector<HCURSOR> map =
			{
				LoadCursor(NULL, IDC_ARROW),
				LoadCursor(NULL, IDC_IBEAM),
				LoadCursor(NULL, IDC_WAIT),
				LoadCursor(NULL, IDC_CROSS),
				LoadCursor(NULL, IDC_UPARROW),
				LoadCursor(NULL, IDC_SIZENWSE),
				LoadCursor(NULL, IDC_SIZENESW),
				LoadCursor(NULL, IDC_SIZEWE),
				LoadCursor(NULL, IDC_SIZENS),
				LoadCursor(NULL, IDC_SIZEALL),
				LoadCursor(NULL, IDC_NO),
				LoadCursor(NULL, IDC_HAND),
				LoadCursor(NULL, IDC_APPSTARTING),
				LoadCursor(NULL, IDC_HELP),
				LoadCursor(NULL, IDC_PIN),
				LoadCursor(NULL, IDC_PERSON),
			};

			return map;
		}

	public:
		// ********************************************************************************
		/// <summary>
		/// カーソルの変更
		/// </summary>
		/// <param name="type">変更するタイプ</param>
		/// <created>いのうえ,2020/11/23</created>
		/// <changed>いのうえ,2020/11/23</changed>
		// ********************************************************************************
		static void ChangeCursor(const CursorType& type)
		{
			SetCursor(GetHandleArray()[type]);
		}
	};
}