#pragma once
#include "Mof.h"
#include <unordered_map>

namespace sip
{
	// ********************************************************************************
	/// <summary>
	/// アセットのベースクラス
	/// </summary>
	// ********************************************************************************
	template <typename Key, typename T > class CAssetBase
	{
	private:

		void operator= (const CAssetBase<Key,T>&) = delete;

		std::unordered_map<Key, std::shared_ptr<T>> m_AssetMap;

		// ********************************************************************************
		/// <summary>
		/// コンストラクタ
		/// </summary>
		/// <created>いのうえ,2020/04/26</created>
		/// <changed>いのうえ,2020/04/26</changed>
		// ********************************************************************************
		CAssetBase(void) :
			m_AssetMap()
		{
		}

		// ********************************************************************************
		/// <summary>
		/// マップの取得
		/// </summary>
		/// <returns>マップ</returns>
		/// <created>いのうえ,2020/04/26</created>
		/// <changed>いのうえ,2020/04/26</changed>
		// ********************************************************************************
		static CAssetBase<Key,T>& GetAssetMap(void)
		{
			static CAssetBase<Key,T> assetMap;
			return assetMap;
		}

	public:

		// ********************************************************************************
		/// <summary>
		/// デストラクタ
		/// </summary>
		/// <created>いのうえ,2020/04/26</created>
		/// <changed>いのうえ,2020/04/26</changed>
		// ********************************************************************************
		~CAssetBase(void)
		{
			Release();
		}

		// ********************************************************************************
		/// <summary>
		/// アセットの登録。
		/// </summary>
		/// <param name="key">検索用キー</param>
		/// <param name="fileName">ファイル名</param>
		/// <returns>登録が成功すれば true それ以外 false</returns>
		/// <created>いのうえ,2020/04/26</created>
		/// <changed>いのうえ,2020/09/10</changed>
		// ********************************************************************************
		static bool Load(const Key& key, LPCMofChar fileName)
		{
			if (GetAssetMap().m_AssetMap.find(key) == GetAssetMap().m_AssetMap.end() ||
				GetAssetMap().m_AssetMap[key] == nullptr)
			{
				GetAssetMap().m_AssetMap[key] = std::make_shared<T>();
			}
			GetAssetMap().m_AssetMap[key]->Release();
			return GetAssetMap().m_AssetMap[key]->Load(fileName);
		}

		// ********************************************************************************
		/// <summary>
		/// 登録したキーからアセットの取得。
		/// </summary>
		/// <param name="key">キー</param>
		/// <returns>データを返す。データがない場合 empty を返す。</returns>
		/// <created>いのうえ,2020/04/26</created>
		/// <changed>いのうえ,2020/04/26</changed>
		// ********************************************************************************
		static std::shared_ptr<T> GetAsset(const Key& key)
		{
			return GetAssetMap().m_AssetMap[key];
		}

		// ********************************************************************************
		/// <summary>
		/// マップからキーのデータを削除する。
		/// </summary>
		/// <param name="key">検索用キー</param>
		/// <created>いのうえ,2020/09/10</created>
		/// <changed>いのうえ,2020/09/10</changed>
		// ********************************************************************************
		static void Erase(const Key& key)
		{
			if (GetAssetMap().m_AssetMap[key])
			{
				GetAssetMap().m_AssetMap[key]->Release();
			}
			GetAssetMap().m_AssetMap.erase(key);
		}

		// ********************************************************************************
		/// <summary>
		/// 全データの解放。
		/// </summary>
		/// <created>いのうえ,2020/04/26</created>
		/// <changed>いのうえ,2020/09/10</changed>
		// ********************************************************************************
		static void Release(void)
		{
			for (auto& itr : GetAssetMap().m_AssetMap)
			{
				if (itr.second)
				{
					itr.second->Release();
				}
			}
		}
	};

	// ********************************************************************************
	/// <summary>
	/// アセットクラスに対応させるためだけのフォントクラス
	/// </summary>
	// ********************************************************************************
	class CFontA : public CFont
	{
	public:
		bool Load(LPCMofChar pName)
		{
			return Create(24, pName);
		}
	};
}