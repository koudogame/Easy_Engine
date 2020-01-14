///
/// @file    interface.hpp
/// @author  板場
///          
/// @brief   インターフェイス基底クラス
/// @details 外部からdeleteされないよう、デストラクタの呼び出しを制限しています。<br>
///          各派生クラスはデストラクタに終了処理を実装してください。
///
#ifndef INCLUDED_EGEG_INTERFACE_HEADER_
#define INCLUDED_EGEG_INTERFACE_HEADER_
#include "egeg_common.hpp"
BEGIN_EGEG
class Interface
{
public :
    void addRef() { ++ref_cnt_; }
    void release()
    {
        if( --ref_cnt_ <= 0 )
        {
            delete this;
        }
    }

    unsigned getRefCount() const { return ref_cnt_; }

protected :
    virtual ~Interface() = 0 {}
private :
    unsigned ref_cnt_ = 1U;
};
END_EGEG
#endif /// !INCLUDED_EGEG_INTERFACE_HEADER_
/// EOF
