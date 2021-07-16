#pragma once
#include "Mof.h"

namespace sip 
{
    /// <summary>
    /// 埋め込みリソースから読み込みするクラス
    /// </summary>
    template< class T >
    class CResourceAsset : public T
    {
    public:

        /// <summary>
        /// 埋め込みリソースから読み込み
        /// </summary>
        /// <param name="id">resource.hに定義されているID</param>
        /// <param name="lpName">ファイル名</param>
        /// <param name="type">ファイルの種類(例 : "PNG", "JPG", "WAVE", "MP3")</param>
        /// <returns>TRUE : 成功, FALSE : 失敗</returns>
        MofBool Load(DWORD id, LPCMofChar lpName, LPCMofChar type)
        {
            auto hRsrc = ::FindResource(NULL, MAKEINTRESOURCE(id), type);
            if (hRsrc == NULL)
            {
                MOF_PRINTLOG("%s の検索に失敗\n", lpName);
                return FALSE;
            }
            auto resource = ::LoadResource(NULL, hRsrc);
            if (resource == NULL)
            {
                MOF_PRINTLOG("%s の読み込みに失敗\n", lpName);
                return FALSE;
            }
            auto data = ::LockResource(resource);
            if (data == NULL)
            {
                MOF_PRINTLOG("%s のロックに失敗\n", lpName);
                return FALSE;
            }
            auto size = ::SizeofResource(NULL, hRsrc);
            return T::Load(lpName, data, size);
        }
    };

    using CResourceTexture     = CResourceAsset<CTexture>;
    using CResourceSoundBuffer = CResourceAsset<CSoundBuffer>;
}
