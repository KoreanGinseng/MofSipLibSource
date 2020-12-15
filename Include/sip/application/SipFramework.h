#pragma once
#include "Mof.h"

namespace sip
{
	class CSipFrameworkThread : public CThread
	{
	private:

		bool m_bEnd{ false };

	public:
		
		CSipFrameworkThread(void);
		
		virtual ~CSipFrameworkThread(void);

		virtual void Run(void) override;

		void EndThread(void);
	};

	using LPSipFrameworkThread = CSipFrameworkThread*;
}