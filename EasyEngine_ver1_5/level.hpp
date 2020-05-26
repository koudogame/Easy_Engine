///
/// @file   level.hpp
/// @author 板場
///
#ifndef INCLUDED_EGEG_LEVEL_HEADER_
#define INCLUDED_EGEG_LEVEL_HEADER_

#include <wrl.h>
#include <d3d11.h>
#include "non_copyable.hpp"
#include "level_manager.hpp"
#include "factory.hpp"
#include "name.hpp"
#include "scene.hpp"
#include "actor.hpp"


BEGIN_EGEG

///
/// @def     REGISTER_LEVEL
/// @brief   レベルをファクトリに登録
///
/// @param[in] LevelType : 登録するレベル型
/// @param[in] LevelName : レベルの名前( .lvlファイルで使用します。)
///
/// @details level.hppの86行目に、Levelの登録を行っています。参考にして下さい。
///
#define REGISTER_LEVEL( LevelType, LevelName ) \
static constexpr const char LevelType ## Name[] = #LevelName; \
REGISTER_WITH_FACTORY( LevelFactory, LevelType, Name<LevelType ## Name> )


///
/// @class Level
/// @brief レベル
///
class Level :
    NonCopyable<Level>
{
public :
    virtual ~Level() = default;
    ///
    /// @brief 初期化
    ///
    /// @param[in] LevelDataStream
    ///
    /// @return true:成功　false:失敗
    ///
    virtual bool initialize( std::istream& LevelDataStream );

    ///
    /// @brief 終了
    ///
    virtual void finalize();

    ///
    /// @brief シーン描画
    ///
    void render( uint64_t );

    ///
    /// @brief シーンの取得
    ///
    /// @return 描画対象のシーン
    ///
    Scene* getScene() noexcept{ return &scene_; }

protected :
    bool initScene();
    bool loadActor( std::istream& );

    Microsoft::WRL::ComPtr<IDXGISwapChain> swap_chain_;
    Task task_;
    Scene scene_;
    std::vector<std::unique_ptr<Actor>> actors_;
};


///< レベルファクトリの宣言
template class Factory<std::string, Level>;
using LevelFactory = Factory<std::string, Level>;


///< レベルの登録
REGISTER_LEVEL( Level, Default );

END_EGEG
#endif /// !INCLUDED_EGEG_LEVEL_HEADER_
/// EOF
