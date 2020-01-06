#ifndef INCLUDED_EG_EG_INTERFACE_HEADER_
#define INCLUDED_EG_EG_INTERFACE_HEADER_
// 作成者 : 板場
#include "easy_engine.hpp"

BEGIN_EG_EG
//
// インターフェイス用基底クラス
//
class Interface
{
public :
    // 参照数カウントアップ
    virtual void addRef() = 0;
    // 解放　参照数が0になったら自身のメモリ領域を解放すること
    virtual void release() = 0;

protected :
    virtual ~Interface() = default;
};
END_EG_EG
#endif // INCLUDED_EG_EG_INTERFACE_HEADER_
// EOF
