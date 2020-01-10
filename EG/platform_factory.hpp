///
/// @file    platform_factory.hpp
/// @author  板場
///          
/// @brief   プラットフォームファクトリ
/// @details シングルトンクラスです。アクセスにはinstance関数を使用してください。<br>
///          新しいプラットフォームの登録はREGISTER_PLATFORMマクロを使用してください。
///
#ifndef INCLUDED_EG_EG_PLATFORM_FACTORY_HEADER_
#define INCLUDED_EG_EG_PLATFORM_FACTORY_HEADER_
#include <unordered_map>
#include "platform.hpp"
BEGIN_EG_EG
class PlatformFactory
{
public :
    ///
    /// @brief  インスタンスを取得します。
    ///
    /// @return インスタンスのアドレス
    ///
    static PlatformFactory* instance() { static PlatformFactory i; return &i; }

    ///
    /// @brief  プラットフォームの登録
    ///
    /// @param[in] ID : プラットフォーム識別ID
    /// @param[in] pCreateFunction : プラットフォーム生成関数へのポインタ
    ///
    void registerPlatform( PlatformID ID, IPlatform*(*pCreateFunction)() )
    {
        functions_[ID] = pCreateFunction;
    }

    ///
    /// @brief  プラットフォームの生成
    ///
    /// @param[in] ID : 生成するプラットフォームの識別ID
    /// @param[out] ppOutPlatform : 生成したプラットフォームを受け取るインターフェイスのアドレス
    ///
    /// @return 生成に成功した場合[ true ] 失敗した場合[ false ]を返却します。
    ///
    bool create( PlatformID ID, IPlatform** pOutPtr )
    {
        auto function = functions_.find(ID);
        if( function == functions_.end() ) return false;

        *pOutPtr = function->second();
        if( *pOutPtr == nullptr ) return false;

        return true;
    }

private :
    PlatformFactory() = default;
    std::unordered_map<PlatformID, IPlatform*(*)()> functions_; /// プラットフォーム生成処理関数のアドレス群
};


class REGISTER_PLATFORM
{
public :
    REGISTER_PLATFORM( PlatformID ID, IPlatform*(*pFunc)() )
    {
        PlatformFactory::instance()->registerPlatform(ID, pFunc);
    }
};
///
/// @def     REGISTER_PLATFORM
/// @brief   プラットフォームをファクトリに登録します。
/// @details ヘッダーファイルで呼び出さないでください。
///
/// @param[in] ID : 登録するプラットフォームの識別ID
/// @param[in] pCreateFunction : 生成処理を実装した関数のアドレス
///
#define REGISTER_PLATFORM( ID, pCreateFunction ) \
BEGIN_EG_EG \
namespace register_platform{} namespace { namespace register_platform { \
REGISTER_PLATFORM register_the_platform( ID, pCreateFunction ); \
}} END_EG_EG

END_EG_EG
#endif /// !INCLUDED_EG_EG_PLATFORM_FACTORY_HEADER_
/// EOF
