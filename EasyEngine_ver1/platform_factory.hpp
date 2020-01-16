///
/// @file    platform_factory.hpp
/// @author  板場
///          
/// @brief   プラットフォームファクトリー
/// @details シングルトンクラスです。アクセスにはinstance関数を使用して下さい。<br>
///          新しいプラットフォームの登録はREGISTER_PLATFORMマクロを使用して下さい。<br>
///          登録する生成関数は、生成に失敗した場合必ずnullptrを返却するようにして下さい。
///
#ifndef INCLUDED_EGEG_PLATFORM_FACTORY_HEADER_
#define INCLUDED_EGEG_PLATFORM_FACTORY_HEADER_
#include <unordered_map>
#include "platform.hpp"
BEGIN_EGEG
class PlatformFactory
{
public :
    static PlatformFactory* instance() { static PlatformFactory i; return &i; }

    ///
    /// @brief  プラットフォームの生成
    ///
    /// @param[in] PlatformName : 生成するプラットフォームの名前
    /// @param[out] ppPlatform : 生成したプラットフォームを受け取るインターフェイス
    ///
    /// @return 生成に成功[ true ] 生成に失敗[ false ]
    ///
    bool create( const std::string& Platform, IPlatform** ppPlatform );

    ///
    /// @brief   プラットフォームの登録
    /// @details 実際は生成処理の登録です。
    ///
    /// @param[in] PlatformName : 関数が生成するプラットフォームの名前
    /// @param[in] pCreateFunction : プラットフォームを生成する関数のアドレス
    ///
    void registerPlatform( const std::string& PlatformName, IPlatform*(*pCreateFunction)() );

    PlatformFactory( const PlatformFactory& ) = delete;
    PlatformFactory& operator=( const PlatformFactory& ) = delete;
private :
    PlatformFactory() = default;
    std::unordered_map<std::string, IPlatform*(*)()> create_funcs_; /// 生成処理リスト
};


class REGISTER_PLATFORM
{
public :
    REGISTER_PLATFORM( const std::string& Name, IPlatform*(*pFunc)() )
    {
        PlatformFactory::instance()->registerPlatform( Name, pFunc );
    }
};
///
/// @def     REGISTER_PLATFORM
/// @brief   プラットフォームをファクトリに登録します。
/// @details ヘッダーファイルで呼び出さないでください。
///
/// @param[in] Name : 登録するプラットフォームの名前
/// @param[in] pCreateFunction : プラットフォームの生成を行う関数のアドレス
///
#define REGISTER_PLATFORM( Name, pCreateFunction ) \
BEGIN_EGEG \
namespace impl{} namespace { namespace impl { \
REGISTER_PLATFORM register_platform( Name, pCreateFunction ); \
}} END_EGEG

END_EGEG
#endif /// !INCLUDED_EGEG_PLATFORM_FACTORY_HEADER_
/// EOF
