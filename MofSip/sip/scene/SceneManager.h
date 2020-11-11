#pragma once
#include "Mof.h"
#include <unordered_map>
#include "StopWatch.h"

// �Q�l SceneManager.hpp in Siv3D

namespace sip
{
	template <class State, class Data> class CSceneManager;

	struct EmptyData {};

	// �V�[���E�C���^�[�t�F�[�X
	template<class State, class Data>
	class IScene
	{
	public:

		struct InitData
		{
			State                       state;

			std::shared_ptr<Data>       pData;

			CSceneManager<State, Data>* pManager;

			InitData(void) = default;

			InitData(const State& s, std::shared_ptr<Data>& d, CSceneManager<State, Data>* m) :
				state(s),
				pData(d),
				pManager(m) {}
		};

	private:

		State                           m_State;

		std::shared_ptr<Data>           m_pData;

		CSceneManager<State, Data>*     m_pManager;

	public:

		explicit IScene(const InitData& init) :
			m_State(init.state),
			m_pData(init.pData),
			m_pManager(init.pManager) {}

		virtual ~IScene(void) = default;

		// �t�F�[�h�C�����̍X�V
		virtual void UpdateFadeIn(float) {}

		// �ʏ펞�̍X�V
		virtual void Update(void) {}

		// �t�F�[�h�A�E�g���̍X�V
		virtual void UpdateFadeOut(float) {}

		// �ʏ펞�̕`��
		virtual void Render(void) {}

		// �t�F�[�h�C�����̕`��
		virtual void RenderFadeIn(float t) 
		{
			Render();

			MofU32 color     = m_pManager->GetFadeColor();

			MofU8  alpha     = (1.0f - t) * 255;

			MofU32 fadeColor = MOF_ARGB(alpha, MOF_GetRed(color), MOF_GetGreen(color), MOF_GetBlue(color));

			CGraphicsUtilities::RenderFillRect(
				0, 0,
				g_pGraphics->GetTargetWidth(), g_pGraphics->GetTargetHeight(),
				fadeColor
			);
		}

		// �t�F�[�h�A�E�g���̕`��
		virtual void RenderFadeOut(float t)
		{
			Render();

			MofU32 color     = m_pManager->GetFadeColor();

			MofU8  alpha     = t * 255;

			MofU32 fadeColor = MOF_ARGB(alpha, MOF_GetRed(color), MOF_GetGreen(color), MOF_GetBlue(color));

			CGraphicsUtilities::RenderFillRect(
				0, 0,
				g_pGraphics->GetTargetWidth(), g_pGraphics->GetTargetHeight(),
				fadeColor
			);
		}

	protected:

		const State& GetState(void) const
		{
			return m_State;
		}

		// ���L�f�[�^�ւ̎Q�Ƃ��擾����B
		Data& GetData(void) const
		{
			return *m_pData;
		}

		// ********************************************************************************
		/// <summary>
		/// �V�[���̕ύX��ʒm����B
		/// </summary>
		/// <param name="state">���̃V�[���̃L�[</param>
		/// <param name="transitionTime">�t�F�[�h�C���E�A�E�g�̎���(�P��:�b)</param>
		/// <param name="crossFade">�N���X�t�F�[�h��L���ɂ��邩</param>
		/// <returns>�V�[���̕ύX���\�Ńt�F�[�h�C���E�A�E�g���J�n�����ꍇ true, ����ȊO false</returns>
		/// <created>���̂���,2020/05/22</created>
		/// <changed>���̂���,2020/05/22</changed>
		// ********************************************************************************
		bool ChangeScene(const State& state, const float& transitionTime = 1.0f, bool crossFade = false)
		{
			return m_pManager->ChangeScene(state, transitionTime, crossFade);
		}

		// �G���[�̔�����ʒm����B
		// ���̊֐����ĂԂƁA�ȍ~�� CSceneManager::Update() / CSceneManager::Render() �� false ��Ԃ��B
		void NotifyError(void)
		{
			return m_pManager->NotifyError();
		}
	};

	// �V�[���Ǘ�
	// State : �V�[������ʂ���L�[�̌^
	// Data  : �V�[���Ԃŋ��L����f�[�^�̌^
	template<class State, class Data = EmptyData>
	class CSceneManager
	{
	private:

		using Scene_t = std::shared_ptr<IScene<State, Data>>;

		using FactoryFunction_t = std::function<Scene_t()>;

		std::unordered_map<State, FactoryFunction_t> m_Factories;

		std::shared_ptr<Data>                        m_pData;

		Scene_t                                      m_pCurrent;

		Scene_t                                      m_pNext;

		State                                        m_CurrentState;

		State                                        m_NextState;
		
		std::shared_ptr<State>                       m_pFirst;

		enum class TransitionState
		{
			None,

			FadeIn,

			Active,

			FadeOut,

			FadeInOut,

		} m_TransitionState = TransitionState::None;

		CStopWatch                                   m_StopWatch;

		float                                        m_TransitionTime = 1.0f;

		MofU32                                       m_FadeColor = MOF_COLOR_BLACK;

		bool                                         m_bCrossFade = false;

		bool                                         m_bError = false;

		bool UpdateSingle(void)
		{
			m_StopWatch.Update();

			float elapsed = m_StopWatch.GetTime();

			if (m_TransitionState == TransitionState::FadeOut && elapsed >= m_TransitionTime)
			{
				m_pCurrent = nullptr;

				m_pCurrent = m_Factories[m_NextState]();

				if (IsError())
				{
					return false;
				}

				m_CurrentState = m_NextState;

				m_TransitionState = TransitionState::FadeIn;

				m_StopWatch.Reset();

				elapsed = 0.0f;
			}

			if (m_TransitionState == TransitionState::FadeIn && elapsed >= m_TransitionTime)
			{
				m_StopWatch.Reset();

				m_TransitionState = TransitionState::Active;
			}

			switch (m_TransitionState)
			{
			case TransitionState::FadeIn:
				assert(m_TransitionTime);
				m_pCurrent->UpdateFadeIn(elapsed / m_TransitionTime);
				return !IsError();
			case TransitionState::Active:
				m_pCurrent->Update();
				return !IsError();
			case TransitionState::FadeOut:
				assert(m_TransitionTime);
				m_pCurrent->UpdateFadeOut(elapsed / m_TransitionTime);
				return !IsError();
			default:
				return false;
			}
		}

		bool UpdateCross(void)
		{
			m_StopWatch.Update();

			const float elapsed = m_StopWatch.GetTime();

			if (m_TransitionState == TransitionState::FadeInOut)
			{
				if (elapsed >= m_TransitionTime)
				{
					m_pCurrent = m_pNext;

					m_pNext = nullptr;

					m_StopWatch.Reset();

					m_TransitionState = TransitionState::Active;
				}
			}

			if (m_TransitionState == TransitionState::Active)
			{
				m_pCurrent->Update();

				return !IsError();
			}
			else
			{
				assert(m_TransitionTime);

				const float t = elapsed / m_TransitionTime;

				m_pCurrent->UpdateFadeOut(t);

				if (IsError())
				{
					return false;
				}

				m_pNext->UpdateFadeIn(t);

				return !IsError();
			}
		}

		bool IsError(void) const noexcept
		{
			return m_bError;
		}

	public:

		// �V�[���̃C���^�[�t�F�[�X
		using CScene = IScene<State, Data>;

		// �V�[���Ǘ��̏�����������B
		CSceneManager(void) :
			m_pData(std::make_shared<Data>()) {}

		// �V�[���Ǘ��̏�����������B
		CSceneManager(const std::shared_ptr<Data>& data) :
			m_pData(data) {}

		// �V�[����ǉ�����B
		template<class CScene>
		CSceneManager& Add(const State& state)
		{
			typename CScene::InitData initData(state, m_pData, this);

			FactoryFunction_t factory = [=] {
				return std::make_shared<CScene>(initData);
			};

			auto it = m_Factories.find(state);

			if (it != m_Factories.end())
			{
				m_Factories[state] = factory;
			}
			else
			{
				m_Factories.emplace(state, factory);

				if (!m_pFirst)
				{
					m_pFirst = std::make_shared<State>();
					*(m_pFirst.get()) = state;
				}
			}

			return *this;
		}

		// �ŏ��̃V�[��������������B
		bool Initialize(const State& state)
		{
			if (m_pCurrent)
			{
				return false;
			}

			auto it = m_Factories.find(state);

			if (it == m_Factories.end())
			{
				return false;
			}

			m_CurrentState = state;

			m_pCurrent = it->second();

			if (IsError())
			{
				return false;
			}

			m_TransitionState = TransitionState::FadeIn;

			m_StopWatch.Start();

			return true;
		}

		// �V�[�����X�V����B
		bool UpdateScene(void)
		{
			if (IsError())
			{
				return false;
			}

			if (!m_pCurrent)
			{
				if (!m_pFirst)
				{
					return true;
				}
				else if (!Initialize(*m_pFirst.get()))
				{
					return false;
				}
			}

			if (m_bCrossFade)
			{
				return UpdateCross();
			}
			else
			{
				return UpdateSingle();
			}
		}

		// �V�[����`�悷��B
		void RenderScene(void)
		{
			if (!m_pCurrent)
			{
				return;
			}

			if (m_TransitionState == TransitionState::Active || !m_TransitionTime)
			{
				m_pCurrent->Render();
			}

			const float elapsed = m_StopWatch.GetTime();

			if (m_TransitionState == TransitionState::FadeIn)
			{
				m_pCurrent->RenderFadeIn(elapsed / m_TransitionTime);
			}
			else if (m_TransitionState == TransitionState::FadeOut)
			{
				m_pCurrent->RenderFadeOut(elapsed / m_TransitionTime);
			}
			else if (m_TransitionState == TransitionState::FadeInOut)
			{
				m_pCurrent->RenderFadeOut(elapsed / m_TransitionTime);

				if (m_pNext)
				{
					m_pNext->RenderFadeIn(elapsed / m_TransitionTime);
				}
			}
		}

		// �V�[���̍X�V���s���B
		bool Update(void)
		{
			if (!UpdateScene())
			{
				return false;
			}

			return true;
		}

		// �V�[���̕`����s���B
		bool Render(void)
		{
			if (IsError())
			{
				return false;
			}

			RenderScene();

			return true;
		}

		// ���L�f�[�^���擾����B
		std::shared_ptr<Data> GetData(void)
		{
			return m_pData;
		}

		// ���L�f�[�^���擾����B
		const std::shared_ptr<const Data> GetData(void) const
		{
			return m_Data;
		}

		// �V�[����ύX����B
		bool ChangeScene(const State& state, float transitionTime, bool crossFade)
		{
			if (state == m_CurrentState)
			{
				crossFade = false;
			}

			if (m_Factories.find(state) == m_Factories.end())
			{
				return false;
			}

			m_NextState = state;

			m_bCrossFade = crossFade;

			if (crossFade)
			{
				m_TransitionTime = transitionTime;

				m_TransitionState = TransitionState::FadeInOut;

				m_pNext = m_Factories[m_NextState]();

				if (IsError())
				{
					return false;
				}

				m_CurrentState = m_NextState;

				m_StopWatch.Start();
			}
			else
			{
				m_TransitionTime = transitionTime * 0.5f;

				m_TransitionState = TransitionState::FadeOut;

				m_StopWatch.Start();
			}

			return true;
		}

		// �t�F�[�h�C���E�A�E�g�̃f�t�H���g�̐F��ݒ肷��B
		CSceneManager& SetFadeColor(const MofU32& color)
		{
			m_FadeColor = color;
			return *this;
		}

		// �t�F�[�h�C���E�A�E�g�̃f�t�H���g�F���擾����B
		const MofU32& GetFadeColor(void) const
		{
			return m_FadeColor;
		}

		// �G���[�̔�����ʒm����B
		void NotifyError(void)
		{
			m_bError = true;
		}
	};
}

