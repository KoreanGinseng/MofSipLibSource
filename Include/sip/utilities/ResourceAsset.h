#pragma once
#include "Mof.h"

namespace sip 
{
    /// <summary>
    /// ���ߍ��݃��\�[�X����ǂݍ��݂���N���X
    /// </summary>
    template< class T >
    class CResourceAsset : public T
    {
    public:

        /// <summary>
        /// ���ߍ��݃��\�[�X����ǂݍ���
        /// </summary>
        /// <param name="id">resource.h�ɒ�`����Ă���ID</param>
        /// <param name="lpName">�t�@�C����</param>
        /// <param name="type">�t�@�C���̎��(�� : "PNG", "JPG", "WAVE", "MP3")</param>
        /// <returns>TRUE : ����, FALSE : ���s</returns>
        MofBool Load(DWORD id, LPCMofChar lpName, LPCMofChar type)
        {
            auto hRsrc = ::FindResource(NULL, MAKEINTRESOURCE(id), type);
            if (hRsrc == NULL)
            {
                MOF_PRINTLOG("%s �̌����Ɏ��s\n", lpName);
                return FALSE;
            }
            auto resource = ::LoadResource(NULL, hRsrc);
            if (resource == NULL)
            {
                MOF_PRINTLOG("%s �̓ǂݍ��݂Ɏ��s\n", lpName);
                return FALSE;
            }
            auto data = ::LockResource(resource);
            if (data == NULL)
            {
                MOF_PRINTLOG("%s �̃��b�N�Ɏ��s\n", lpName);
                return FALSE;
            }
            auto size = ::SizeofResource(NULL, hRsrc);
            return T::Load(lpName, data, size);
        }
    };

    using CResourceTexture     = CResourceAsset<CTexture>;
    using CResourceSoundBuffer = CResourceAsset<CSoundBuffer>;
}
