#include "SipFramework.h"
#include "../utilities/MyTime.h"

namespace sip
{
    // ********************************************************************************
    /// <summary>
    /// コンストラクタ
    /// </summary>
    /// <created>いのうえ,2021/02/03</created>
    /// <changed>いのうえ,2021/02/03</changed>
    // ********************************************************************************
	CSipFrameworkThread::CSipFrameworkThread(void)
		: CThread()
	{
		CThread::Start("SipFrameworkThread");
	}

    // ********************************************************************************
    /// <summary>
    /// デストラクタ
    /// </summary>
    /// <created>いのうえ,2021/02/03</created>
    /// <changed>いのうえ,2021/02/03</changed>
    // ********************************************************************************
	CSipFrameworkThread::~CSipFrameworkThread(void)
	{
		this->EndThread();
	}

    // ********************************************************************************
    /// <summary>
    /// スレッドの実行関数
    /// </summary>
    /// <created>いのうえ,2021/02/03</created>
    /// <changed>いのうえ,2021/02/03</changed>
    // ********************************************************************************
	void CSipFrameworkThread::Run(void)
	{
		m_bEnd = false;
		CMyTime::InitTime();
        MOF_PRINTLOG("START SIP THREAD \n");

		while (!m_bEnd)
		{
		}

        MOF_PRINTLOG("END SIP THREAD \n");
	}

    // ********************************************************************************
    /// <summary>
    /// スレッド終了処理
    /// </summary>
    /// <created>いのうえ,2021/02/03</created>
    /// <changed>いのうえ,2021/02/03</changed>
    // ********************************************************************************
	void CSipFrameworkThread::EndThread(void)
	{
		m_bEnd = true;
		CThread::Join(250);
		CThread::Release();
	}
}