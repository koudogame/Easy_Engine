///
/// @file   mini_scene_reverse.hpp
/// @author î¬èÍ
///
#ifndef INCLUDED_EGEG_MINI_SCENE_REVERSE_HEADER_
#define INCLUDED_EGEG_MINI_SCENE_REVERSE_HEADER_

#include <wrl.h>
#include <d3d11.h>
#include "level_scene.hpp"
#include "task.hpp"

BEGIN_EGEG

class MiniSceneReverse :
    public LevelScene
{
public :
// override
    bool initialize( std::istream& ) override;
    void finalize() override;
    void entry( RenderComponent* ) override {};
    void exit( RenderComponent* ) override {};
    void setCamera( LevelCamera* ) override {};
    void addLight( LevelLight* ) override {};
    void render( uint64_t ) override;

private :
    Task task_;

    Microsoft::WRL::ComPtr<ID3D11Texture2D> render_texture_;
    Microsoft::WRL::ComPtr<ID3D11RenderTargetView> render_target_;
    Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> shader_resource_;

    Microsoft::WRL::ComPtr<ID3D11DepthStencilView> depth_stencil_;
};

END_EGEG
#endif /// !INCLUDED_EGEG_MINI_SCENE_REVERSE_HEADER_
/// EOF
