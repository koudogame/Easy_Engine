#ifndef INCLUDED_EG_EG_PLATFORM_FACTORY_HEADER_
#define INCLUDED_EG_EG_PLATFORM_FACTORY_HEADER_
// 作成者 : 板場
#include <unordered_map>
#include "platform.hpp"

// プラットフォームの追加
#define ADD_PLATFORM( ID, pCreateFunction ) \
BEGIN_EG_EG \
namespace impl{} namespace { namespace impl { \
AddPlatform add_platform( ID, pCreateFunction ); \
}} END_EG_EG


BEGIN_EG_EG
//
// プラットフォーム用ファクトリ
// シングルトンクラスです。アクセスには instance関数を使用して下さい。
//
class PlatformFactory
{
public :
    // インスタンスへのアクセス
    static PlatformFactory* instance() { static PlatformFactory i; return &i; }

    //
    // プラットフォームの登録
    //
    // in ID : プラットフォームID
    // in pCreateFunction : 生成処理を実装した関数へのポインタ
    //
    void registerPlatform( PlatformID ID, IPlatform*(*pCreateFunction)() )
    {
        functions_[ID] = pCreateFunction;
    }

    //
    // プラットフォームの生成
    // 
    // in ID : 生成するプラットフォームのID
    // in pOutPtr : 生成したオブジェクトへのポインタを格納する変数のアドレス
    //
    // out true  : 生成成功
    // out false : 生成失敗
    //
    bool create( PlatformID ID, IPlatform** pOutPtr )
    {
        auto function = functions_.find(ID);
        if( function == functions_.end() ) return false;

        *pOutPtr = function->second();
        return true;
    }

private :
    PlatformFactory() = default;
    std::unordered_map<PlatformID, IPlatform*(*)()> functions_;
};

class AddPlatform
{
public :
    AddPlatform( PlatformID ID, IPlatform*(*pFunc)() )
    {
        PlatformFactory::instance()->registerPlatform(ID, pFunc);
    }
};
END_EG_EG
#endif // INCLUDED_EG_EG_PLATFORM_FACTORY_HEADER_
// EOF
