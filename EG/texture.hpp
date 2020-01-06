#ifndef INCLUDED_EG_EG_TEXTURE_HEADER_
#define INCLUDED_EG_EG_TEXTURE_HEADER_
// 作成者 : 板場
#include "easy_engine.hpp"
#include <memory>

BEGIN_EG_EG
//
// テクスチャリソースへのインターフェイス
// 
class ITexture
{
public :
    virtual ~ITexture() = default;

    // テクスチャリソースの解放処理
    virtual void release() = 0;
};
END_EG_EG
#endif // INCLUDED_EG_EG_TEXTURE_HEADER_
// EOF
