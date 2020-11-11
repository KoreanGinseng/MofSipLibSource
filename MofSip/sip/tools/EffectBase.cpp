#include "EffectBase.h"

namespace sip
{
	// ********************************************************************************
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <created>いのうえ,2020/08/31</created>
	/// <changed>いのうえ,2020/08/31</changed>
	// ********************************************************************************
	CEffectBase::CEffectBase(void) :
		m_Emitter(),
		m_CreateInfo(),
		m_ParticleList()
	{
		//エミッターの動作パラメーター設定
		m_CreateInfo.UpdateBehavior.Color.SetDefaultParameter(Vector4(0, 0, 0, -1 / 60.0f));

		m_CreateInfo.ParameterBehavior.Existance.SetDefaultParameter(60);
		m_CreateInfo.ParameterBehavior.Blending = BLEND_ADD;
		m_CreateInfo.ParameterBehavior.Flag     = sip::CParticle::BillBoard;
		m_CreateInfo.ParameterBehavior.pTexture = nullptr;
		m_CreateInfo.ParameterBehavior.pMesh    = nullptr;

		m_CreateInfo.CreateBehavior.Position.Min.SetValue(-5, -5, -5);
		m_CreateInfo.CreateBehavior.Position.Max.SetValue(5, 5, 5);
		m_CreateInfo.CreateBehavior.Color.SetDefaultParameter(Vector4(1, 1, 1, 1));
		m_CreateInfo.CreateBehavior.Scale.SetDefaultParameter(Vector3(1, 1, 1));
		m_CreateInfo.CreateBehavior.Time  = 30;
		m_CreateInfo.CreateBehavior.Count = 10;
		m_Emitter.Initialize(m_CreateInfo);
	}

	// ********************************************************************************
	/// <summary>
	/// デストラクタ
	/// </summary>
	/// <created>いのうえ,2020/08/31</created>
	/// <changed>いのうえ,2020/08/31</changed>
	// ********************************************************************************
	CEffectBase::~CEffectBase(void)
	{
	}

	// ********************************************************************************
	/// <summary>
	/// 読み込み
	/// </summary>
	/// <param name="pFileName">ファイル名</param>
	/// <returns>成功したかどうか</returns>
	/// <created>いのうえ,2020/08/31</created>
	/// <changed>いのうえ,2020/08/31</changed>
	// ********************************************************************************
	bool CEffectBase::Load(LPCMofChar pFileName)
	{
		FILE* fp = fopen(pFileName, "rb");
		if (fp == NULL)
		{
			return false;
		}

		//解放処理
		MOF_SAFE_RELEASE(m_CreateInfo.ParameterBehavior.pTexture);
		MOF_SAFE_RELEASE(m_CreateInfo.ParameterBehavior.pMesh);

		//構造体読み込み
		fread(&m_CreateInfo, sizeof(m_CreateInfo), 1, fp);

		char pattern = 0;

		fread(&pattern, sizeof(char), 1, fp);

		char* str  = nullptr;
		int length = 0;
		switch (pattern)
		{
		case 0:
			break;
		case 1:
			//テクスチャ読み込み
			fread(&length, sizeof(int), 1, fp);
			str = new char[length + 1];
			fread(str, sizeof(char), length, fp);
			str[length] = '\0';
			m_CreateInfo.ParameterBehavior.pTexture = std::make_shared<CTexture>();
			if (!m_CreateInfo.ParameterBehavior.pTexture->Load(str))
			{
				MOF_SAFE_RELEASE(m_CreateInfo.ParameterBehavior.pTexture);
			}
			MOF_SAFE_DELETE_ARRAY(str);
			break;
		case 2:
			//メッシュ読み込み
			fread(&length, sizeof(int), 1, fp);
			str = new char[length + 1];
			fread(str, sizeof(char), length, fp);
			str[length] = '\0';
			m_CreateInfo.ParameterBehavior.pMesh = std::make_shared<CMeshContainer>();
			if (!m_CreateInfo.ParameterBehavior.pMesh->Load(str))
			{
				MOF_SAFE_RELEASE(m_CreateInfo.ParameterBehavior.pMesh);
			}
			MOF_SAFE_DELETE_ARRAY(str);
			break;
		}

		//ファイルを閉じる
		fclose(fp);

		RestartEmitter();
		return true;
	}

	// ********************************************************************************
	/// <summary>
	/// エミッターの再スタート
	/// </summary>
	/// <param name="pos">発生座標</param>
	/// <param name="t">寿命(単位は秒)</param>
	/// <returns>this</returns>
	/// <created>いのうえ,2020/08/07</created>
	/// <changed>いのうえ,2020/08/31</changed>
	// ********************************************************************************
	CEffectBase& CEffectBase::RestartEmitter(const Vector3 & pos, const float & t)
	{
		m_Emitter.Initialize(m_CreateInfo);
		SetPos(pos);
		SetLifeTime(t);
		m_ParticleList.clear();
		return *this;
	}

	// ********************************************************************************
	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="pos">発生座標</param>
	/// <param name="t">寿命(単位は秒)</param>
	/// <returns>this</returns>
	/// <created>いのうえ,2020/08/31</created>
	/// <changed>いのうえ,2020/08/31</changed>
	// ********************************************************************************
	CEffectBase & CEffectBase::Initialize(const Vector3 & pos, const float & t)
	{
		RestartEmitter(pos, t);
		return *this;
	}

	// ********************************************************************************
	/// <summary>
	/// 更新
	/// </summary>
	/// <created>いのうえ,2020/08/31</created>
	/// <changed>いのうえ,2020/08/31</changed>
	// ********************************************************************************
	void CEffectBase::Update(void)
	{
		// 寿命の減少 寿命をマイナス指定している場合は通らない。
		if (0 < m_LifeTime)
		{
			m_LifeTime -= CUtilities::GetFrameSecond();
			
			if (m_LifeTime < 0)
			{
				m_LifeTime = 0;
			}
		}

		m_Emitter.Update(&m_ParticleList);

		// イテレート中に要素削除をするような場合には、
		// 範囲for文は使用できない
		for (auto it = m_ParticleList.begin(); it != m_ParticleList.end();)
		{
			(*it)->Update();
			// 条件一致した要素を削除する
			if ((*it)->IsEnd())
			{
				// 削除された要素の次を指すイテレータが返される。
				*it = nullptr;
				it  = m_ParticleList.erase(it);
			}
			// 要素削除をしない場合に、イテレータを進める
			else 
			{
				++it;
			}
		}

		// ソートの実行
		for (const auto& it : m_ParticleList)
		{
			it->UpdateViewPosition();
		}
		m_ParticleList.sort(CParticle::ViewComp);
	}

	// ********************************************************************************
	/// <summary>
	/// 描画
	/// </summary>
	/// <created>いのうえ,2020/08/31</created>
	/// <changed>いのうえ,2020/08/31</changed>
	// ********************************************************************************
	void CEffectBase::Render(void) const
	{
		// 生存終了しているなら描画しない
		if (m_LifeTime == 0)
		{
			return;
		}

		// パーティクルの描画
		for (const auto& it : m_ParticleList)
		{
			it->Render();
		}
		g_pGraphics->SetBlending(BLEND_NORMAL);
	}

	// ********************************************************************************
	/// <summary>
	/// 解放
	/// </summary>
	/// <created>いのうえ,2020/08/31</created>
	/// <changed>いのうえ,2020/08/31</changed>
	// ********************************************************************************
	void CEffectBase::Release(void)
	{
		MOF_SAFE_RELEASE(m_CreateInfo.ParameterBehavior.pMesh);
		MOF_SAFE_RELEASE(m_CreateInfo.ParameterBehavior.pTexture);
	}

	// ********************************************************************************
	/// <summary>
	/// 座標の設定
	/// </summary>
	/// <param name="pos">発生座標</param>
	/// <returns>this</returns>
	/// <created>いのうえ,2020/08/31</created>
	/// <changed>いのうえ,2020/08/31</changed>
	// ********************************************************************************
	CEffectBase & CEffectBase::SetPos(const Vector3 & pos)
	{
		m_Emitter.SetPosition(pos);
		return *this;
	}

	// ********************************************************************************
	/// <summary>
	/// 寿命の設定
	/// </summary>
	/// <param name="t">寿命(単位は秒)</param>
	/// <returns>this</returns>
	/// <created>いのうえ,2020/08/31</created>
	/// <changed>いのうえ,2020/08/31</changed>
	// ********************************************************************************
	CEffectBase & CEffectBase::SetLifeTime(const float & t)
	{
		m_LifeTime = t;
		return *this;
	}

	// ********************************************************************************
	/// <summary>
	/// 寿命の取得
	/// </summary>
	/// <returns>寿命(単位は秒)</returns>
	/// <created>いのうえ,2020/08/31</created>
	/// <changed>いのうえ,2020/08/31</changed>
	// ********************************************************************************
	float CEffectBase::GetLifeTime(void) const
	{
		return m_LifeTime;
	}

	// ********************************************************************************
	/// <summary>
	/// テクスチャの取得
	/// </summary>
	/// <returns>テクスチャのポインタ</returns>
	/// <created>いのうえ,2020/08/31</created>
	/// <changed>いのうえ,2020/08/31</changed>
	// ********************************************************************************
	std::shared_ptr<CTexture> CEffectBase::GetTexture(void)
	{
		return m_CreateInfo.ParameterBehavior.pTexture;
	}

	// ********************************************************************************
	/// <summary>
	/// メッシュの取得
	/// </summary>
	/// <returns>メッシュのポインタ</returns>
	/// <created>いのうえ,2020/08/31</created>
	/// <changed>いのうえ,2020/08/31</changed>
	// ********************************************************************************
	std::shared_ptr<CMeshContainer> CEffectBase::GetMesh(void)
	{
		return m_CreateInfo.ParameterBehavior.pMesh;
	}
}