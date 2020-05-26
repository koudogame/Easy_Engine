///
/// @file   rendering_manager_child.hpp
/// @author 板場
/// 
#ifndef INCLUDED_EGEG_RENDERING_MANAGER_CHILD_HEADER_
#define INCLUDED_EGEG_RENDERING_MANAGER_CHILD_HEADER_

#include "egeg_def.hpp"

BEGIN_EGEG

class RenderingManager; ///< RenderingManager前方宣言( 循環参照回避 )

///
/// @class RenderingManagerChild
/// @brief レンダリングマネージャ―により生成されるオブジェクト
///
class RenderingManagerChild
{
public :
    virtual ~RenderingManagerChild() = default;

    ///
    /// @brief マネージャーの取得
    ///
    /// @return レンダリングマネージャー
    ///
    RenderingManager* getManager() const noexcept { return manager_; }


    ///
    /// @brief マネージャーのセット
    ///
    /// @param[in] Manager : レンダリングマネージャ―
    ///
    void setManager( RenderingManager& Manager ) noexcept { manager_ = &Manager; }

private :
    RenderingManager* manager_{ nullptr };
};

END_EGEG
#endif /// !INCLUDED_EGEG_RENDERING_MANAGER_CHILD_HEADER_
/// EOF
