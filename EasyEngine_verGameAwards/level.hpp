///
/// @file   level.hpp
/// @author 板場
///
#ifndef INCLUDED_EGEG_LEVEL_HEADER_
#define INCLUDED_EGEG_LEVEL_HEADER_

#include "level_manager.hpp"

BEGIN_EGEG

///
/// @file   Level
/// @brief  レベル基底
///
class Level
{
public :
    ///
    /// @breif  コンストラクタ
    ///
    /// @param[in] Manager : レベルマネージャー
    ///
    Level( LevelManager* Manager ) :
        manager_( Manager )
    {}
    ///< 仮想デストラクタ
    virtual ~Level() = default;

    ///
    /// @brief  初期化処理
    ///
    /// @return 初期化成功[ true ]　初期化失敗[ false ]
    ///
    virtual bool initialize() = 0;
    ///
    /// @breif  終了処理
    ///
    virtual void finalize() = 0;

    ///< レベルマネージャーの取得
    LevelManager* getManager() const noexcept { return manager_; }

private :
    LevelManager* manager_;
};

template class Factory<Level, class LevelManager*>;           ///< レベル用ファクトリクラスの明示的インスタンス化
using LevelFactory = Factory<Level, class LevelManager*>;     ///< レベル用ファクトリクラス型

END_EGEG
#endif /// !INCLUDED_EGEG_LEVEL_HEADER_
/// EOF
