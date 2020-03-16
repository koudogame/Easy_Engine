///
/// @file   scene3d.hpp
/// @author ��
///
#ifndef INCLUDED_EGEG_SCENE3D_HEADER_
#define INCLUDED_EGEG_SCENE3D_HEADER_
#include <set>
#include "scene.hpp"
#include "actor3d.hpp"
BEGIN_EGEG
///
/// @class  Scene3D
/// @brief  3D�V�[��
///
class Scene3D :
    public Scene
{
public :
    template <class DCType>
    Scene3D( DCType&& ImmediateContext ) :
        Scene( std::forward<DCType>(ImmediateContext) )
    {
    }

    ///
    /// @brief  ���f���̃G���g���[
    ///
    /// @param[in] Actor : �`�悷��A�N�^�[
    ///
    void entry( const Actor3D* Actor ) { model_list_.emplace( Actor ); }
    ///
    /// @brief   ���f���̃G���g���[����
    /// @details entry()�֐��̌Ăяo������Arender()�֐��̌Ăяo���܂ł̊ԂɗL���ł��B
    ///
    /// @param[in] Actor : �G���g���[���������郂�f�������A�N�^�[
    ///
    void exit( const Actor3D* Actor ) { model_list_.erase( Actor ); }
    
    
/*-----------------------------------------------------------------*/
// Scene
    void render( 
        const std::vector<ID3D11RenderTargetView*>&,
        const std::vector<D3D11_VIEWPORT>&,
        const std::vector<D3D11_RECT>&,
        ID3D11DepthStencilView* = nullptr,
        ID3D11DepthStencilState* = nullptr,
        UINT = 0,
        ID3D11RasterizerState* = nullptr,
        ID3D11BlendState* = nullptr,
        float* = nullptr,
        UINT = 0xFFFFFFFF ) override;
/*-----------------------------------------------------------------*/


protected :
    std::set<const Actor3D*> model_list_;
};
END_EGEG
#endif /// !INCLUDED_EGEG_SCENE3D_HEADER_
/// EOF
