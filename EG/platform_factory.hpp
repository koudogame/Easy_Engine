#ifndef INCLUDED_EG_EG_PLATFORM_FACTORY_HEADER_
#define INCLUDED_EG_EG_PLATFORM_FACTORY_HEADER_
// 作成者 : 板場
#include <unordered_map>
#include "platform.hpp"

#define ADD_PLATFORM( ID, pCreateFunction ) \
BEGIN_EG_EG \
namespace impl{} namespace { namespace impl { \
AddPlatform add_platform( ID, pCreateFunction ); \
}} END_EG_EG


BEGIN_EG_EG
enum PlatformID
{
    kWindows,
    kNintendoSwitch,
};
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
    // プラットフォームの追加
    //
    // in ID : プラットフォームID
    // in pCreateFunction : 生成処理を実装した関数へのポインタ
    //
    void registerCreateFunction( PlatformID ID, IPlatform*(*pCreateFunction)() )
    {
        functions_[ID] = pCreateFunction;
    }

    //
    // プラットフォームの生成
    //
    IPlatform* create( PlatformID ID )
    {
        auto function = functions_.find(ID);
        return function->second();
    }

private :
    std::unordered_map<PlatformID, IPlatform*(*)()> functions_;
};

class AddPlatform
{
public :
    AddPlatform( PlatformID ID, IPlatform*(*pFunc)() )
    {
        PlatformFactory::instance()->registerCreateFunction(ID, pFunc);
    }
};
END_EG_EG
#endif // INCLUDED_EG_EG_PLATFORM_FACTORY_HEADER_
// EOF
