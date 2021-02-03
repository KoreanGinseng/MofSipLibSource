#include "SipFramework.h"
#include "../utilities/MyTime.h"

namespace sip
{
    // ********************************************************************************
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    /// <created>���̂���,2021/02/03</created>
    /// <changed>���̂���,2021/02/03</changed>
    // ********************************************************************************
	CSipFrameworkThread::CSipFrameworkThread(void)
		: CThread()
	{
		CThread::Start("SipFrameworkThread");
	}

    // ********************************************************************************
    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    /// <created>���̂���,2021/02/03</created>
    /// <changed>���̂���,2021/02/03</changed>
    // ********************************************************************************
	CSipFrameworkThread::~CSipFrameworkThread(void)
	{
		this->EndThread();
	}

    // ********************************************************************************
    /// <summary>
    /// �X���b�h�̎��s�֐�
    /// </summary>
    /// <created>���̂���,2021/02/03</created>
    /// <changed>���̂���,2021/02/03</changed>
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
    /// �X���b�h�I������
    /// </summary>
    /// <created>���̂���,2021/02/03</created>
    /// <changed>���̂���,2021/02/03</changed>
    // ********************************************************************************
	void CSipFrameworkThread::EndThread(void)
	{
		m_bEnd = true;
		CThread::Join(250);
		CThread::Release();
	}
}