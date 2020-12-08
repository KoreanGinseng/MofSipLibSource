#pragma once
#include "sip/scene/SceneManager.h"
#include "sip/tools/AnimationData.h"
#include "sip/tools/EffectBase.h"
#include "sip/tools/FileDialog.h"
#include "sip/utilities/AssetBase.h"
#include "sip/utilities/EaseMotionController.h"
#include "sip/utilities/ResourceFont.h"
#include "sip/utilities/RoundRect.h"
#include "sip/utilities/FreeCamera.h"
#include "sip/utilities/MyCamera2D.h"
#include "sip/utilities/Cursor.h"
#include "sip/utilities/Periodic.h"
#include "sip/utilities/FlagBase.h"
#include "sip/shader/ToonShader.h"

namespace sip
{
	using Flags8  = CFlagBase<MofU8 >;
	using Flags16 = CFlagBase<MofU16>;
	using Flags32 = CFlagBase<MofU32>;
	using Flags64 = CFlagBase<MofU64>;
}

using namespace sip;