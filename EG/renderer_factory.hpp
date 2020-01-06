#ifndef INCLUDED_EG_EG_RENDERER_FACTORY_HEADER_
#define INCLUDED_EG_EG_RENDERER_FACTORY_HEADER_
// 作成者 : 板場
#include <unordered_map>
#include "renderer.hpp"

// プラットフォームの追加
#define ADD_RENDERER( ID, pCreateFunction ) \
BEGIN_EG_EG \
namespace impl{} namespace { namespace impl { \
AddRenderer add_renderer( ID, pCreateFunction ); \
}} END_EG_EG


BEGIN_EG_EG
//
// レンダラー用ファクトリ
// シングルトンクラスです。アクセスにはinstance関数を使用してください。
//
class RendererFactory
{
public :
    // インスタンスへのアクセス
    static RendererFactory* instance() { static RendererFactory i; return &i; }

    //
    // レンダラーの登録
    //
    // in ID : レンダラーID
    // in pCreateFunction : 生成処理を実装した関数へのポインタ
    //
    void registerRenderer( RendererID ID, IRenderer*(*pCreateFunction)() )
    {
        functions_[ID] = pCreateFunction;
    }
    
    //
    // レンダラーの生成
    //
    // in ID : 生成するレンダラーのID
    // in pOutPtr : 生成したオブジェクトへのポインタを格納する変数のアドレス
    //
    // out true  : 生成成功
    // out false : 生成失敗
    //
    bool create( RendererID ID, IRenderer** pOutPtr )
    {
        auto function = functions_.find(ID);
        if( function == functions_.end() ) return false;

        *pOutPtr = function->second();
        return true;
    }

private :
    RendererFactory() = default;
    std::unordered_map<RendererID, IRenderer*(*)()> functions_;
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
#endif // INCLUDED_EG_EG_RENDERER_FACTORY_HEADER_
// EOF
