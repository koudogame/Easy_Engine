///
/// @file   scene.hpp
/// @author 板場
///
#ifndef INCLUDED_EGEG_SCENE_HEADER_
#define INCLUDED_EGEG_SCENE_HEADER_
#include "egeg_utility.hpp"
#include "rendering_engine.hpp"
BEGIN_EGEG
///
/// @class   Scene
/// @brief   レンダリング単位
/// @details 派生クラスはシーンへのモデルの登録関数を各自定義して下さい。
///
class Scene :
    NonCopyable<Scene>
{
public :
    Scene( ID3D11DeviceContext* DeviceContext ) :
        device_context_( DeviceContext )
    {
        device_context_->AddRef();
    }
    virtual ~Scene() { device_context_->Release(); }

    virtual void render() = 0;

protected :
    ID3D11DeviceContext* device_context_;
};
END_EGEG
#endif /// !INCLUDED_EGEG_SCENE_HEADER_
/// EOF
