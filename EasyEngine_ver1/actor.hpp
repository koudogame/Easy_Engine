///
/// @file   actor.hpp
/// @author 板場
///
#ifndef INCLUDED_EGEG_ACTOR_HEADER_
#define INCLUDED_EGEG_ACTOR_HEADER_
#include <cstdint>
#include <unordered_map>
#include "egeg_common.hpp"
BEGIN_EGEG
class Component;
///
/// @class  Actor
///
/// @brief  アクター基底クラス
class Actor
{
public :
    virtual ~Actor() = default;

    ///
    /// @brief  初期化処理
    ///
    /// @return 初期化成功[ true ]　初期化失敗[ false ]
    ///
    virtual bool initialize() = 0;
    ///
    /// @brief  終了処理
    ///
    virtual void finalize() = 0;

    ///
    /// @brief  更新処理
    ///
    /// @param[in] DeltaTimeMS : 前回呼び出し時からの時間の差(: ミリ秒)
    ///
    virtual void update( uint64_t DeltaTimeMS ) = 0;

    ///
    /// @brief  アクター識別IDセット
    ///
    void setID( uint32_t ID ) { id_ = ID; }
    ///
    /// @brief  アクター識別ID取得
    ///
    /// @return ID
    ///
    uint32_t getID() const { return id_; }

    ///
    /// @brief  コンポーネントの追加
    ///
    /// @param[in] ComponentID : 追加するコンポーネントの識別ID
    ///
    /// @return 追加したコンポーネントのアドレス
    ///
    Component* addComponent( uint32_t ComponentID );
    ///
    /// @brief  コンポーネントの削除
    ///
    /// @param[in] ComponentID : 削除するコンポーネントの識別ID
    ///
    void removeComponent( uint32_t ComponentID );
    ///
    /// @brief   コンポーネントの取得
    /// @details IDに対応したコンポーネントを保持していない場合は、nullptrを返却します。
    ///
    /// @param[in] ComponentID : 取得するコンポーネントの識別ID
    ///
    /// @return IDに対応したコンポーネント
    ///
    Component* getComponent( uint32_t ComponentID );

private :
    uint32_t id_ = 0U;                                      /// アクター識別ID
    std::unordered_map<uint32_t, Component*> components_;   /// コンポーネント群
};
END_EGEG
#endif /// !INCLUDED_EGEG_ACTOR_HEADER_
/// EOF
