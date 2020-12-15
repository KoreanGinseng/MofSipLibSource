#include "SipFramework.h"
#include "../utilities/MyTime.h"

namespace sip
{
	CSipFrameworkThread::CSipFrameworkThread(void)
		: CThread()
	{
		CThread::Start("SipFrameworkThread");
	}

	CSipFrameworkThread::~CSipFrameworkThread(void)
	{
		this->EndThread();
	}

	void CSipFrameworkThread::Run(void)
	{
		m_bEnd = false;
		CMyTime::InitTime();

		while (!m_bEnd)
		{
		}
	}

	void CSipFrameworkThread::EndThread(void)
	{
		m_bEnd = true;
		CThread::Join(250);
		CThread::Release();
	}
}