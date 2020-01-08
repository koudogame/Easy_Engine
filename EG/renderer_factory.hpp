///
/// @file    renderer_factory.hpp
/// @author  板場
///
/// @brief   レンダラーのファクトリ
/// @details シングルトンクラスです。アクセスにはinstance関数を使用して下さい。<br>
///          新しいレンダラーの登録はADD_RENDERERマクロを使うと簡単に済みます。
///
#ifndef INCLUDED_EG_EG_RENDERER_FACTORY_HEADER_
#define INCLUDED_EG_EG_RENDERER_FACTORY_HEADER_
#include <unordered_map>
#include "renderer.hpp"

///
/// @def     ADD_RENDERER
/// @brief   レンダラーの登録処理
/// @details ヘッダーファイルで呼び出さないでください。
///
/// @param[in] ID : 登録するレンダラー識別ID
/// @param[in] pCreateFunction : 生成処理を実装した関数のアドレス
///
#define ADD_RENDERER( ID, pCreateFunction ) \
BEGIN_EG_EG \
namespace impl{} namespace { namespace impl { \
AddRenderer add_renderer( ID, pCreateFunction ); \
}} END_EG_EG

BEGIN_EG_EG
class RendererFactory
{
public :
    ///
    /// @brief  インスタンスを取得します。
    ///
    /// @return インスタンスのアドレス
    ///
    static RendererFactory* instance() { static RendererFactory i; return &i; }

    ///
    /// @brief  レンダラーの登録
    ///
    /// @param[in]  ID : レンダラー識別ID
    /// @param[in]  pCreateFunction : レンダラー生成関数へのポインタ
    ///
    void registerRenderer( RendererID ID, IRenderer*(*pCreateFunction)() )
    {
        functions_[ID] = pCreateFunction;
    }
    
    ///
    /// @brief  レンダラーの生成
    ///
    /// @param[in]  ID : 生成するレンダラーの識別ID
    /// @param[out] ppOutRenderer : 生成したレンダラーを受け取るインターフェイスのアドレス
    ///
    /// @return 生成に成功した場合[ true ] 失敗した場合[ false ]を返却します。
    ///
    bool create( RendererID ID, IRenderer** ppOutRenderer )
    {
        auto function = functions_.find(ID);
        if( function == functions_.end() ) return false;

        *ppOutRenderer = function->second();
        return true;
    }

private :
    RendererFactory() = default;
    std::unordered_map<RendererID, IRenderer*(*)()> functions_; /// レンダラー生成処理関数のアドレス群
};

class AddRenderer
{
public :
    AddRenderer( RendererID ID, IRenderer*(*pFunc)() )
    {
        RendererFactory::instance()->registerRenderer( ID, pFunc );
    }
};
END_EG_EG
#endif /// INCLUDED_EG_EG_RENDERER_FACTORY_HEADER_
/// EOF
