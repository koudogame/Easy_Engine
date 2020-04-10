///
/// @file   rendering2d.hpp
/// @author ��
///
#ifndef INCLUDED_EGEG_RENDERING2D_COMPONENT_HEADER_
#define INCLUDED_EGEG_RENDERING2D_COMPONENT_HEADER_

#include <wrl.h>
#include <d3d11.h>
#include "component2d.hpp"
#include "vertex_shader.hpp"
#include "geometry_shader.hpp"
#include "pixel_shader.hpp"

BEGIN_EGEG
namespace component
{

///
/// @class  Rendering2D
/// @brief  �`��R���|�[�l���g
///
class Rendering2D :
    public Component2D
{
public :
    static constexpr TypeID<Rendering2D> getID() noexcept { return TypeID<Rendering2D>(); }

    Rendering2D( Actor2D* Owner ) :
        Component2D( Owner )
    {}
    
    ///
    /// @brief  �e�N�X�`���̃Z�b�g
    ///
    /// @param[in] ShaderResourceView : �e�N�X�`���ւ̃r���[
    ///
    template <class ViewPtr>
    void setTexture( ViewPtr&& ShaderResourceView ) noexcept
    {
        texture_ = std::forward<ViewPtr>( ShaderResourceView );
    }
    ///
    /// @brief  �e�N�X�`���̎擾
    ///
    /// @return �e�N�X�`���ւ̃r���[
    ///
    Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> getTexture() const noexcept 
    {
        return texture_; 
    }

    ///
    /// @brief  �؂���͈͂̃Z�b�g
    /// @brief  �����{ x: 0, y: 0 } �Ƃ��A�s�N�Z���P�ʂŎw�肵�ĉ������B
    ///
    /// @param[in] Range : �؂���͈�
    ///
    void setTrimmingRange( const D3D11_RECT& Range ) noexcept
    {
        trimming_range_ = Range;
    }
    ///
    /// @brief  �؂���͈͂̎擾
    ///
    /// @return �؂���͈�
    ///
    const D3D11_RECT& getTrimmingRange() const noexcept
    {
        return trimming_range_;
    }

    ///
    /// @brief  ���_�V�F�[�_�\�̃Z�b�g
    ///
    /// @param[in] Shader : �Z�b�g����V�F�[�_�[
    ///
    void setVertexShader( VertexShader* Shader ) noexcept { vertex_shader_ = Shader; }
    ///
    /// @brief  ���_�V�F�[�_�\�̎擾
    ///
    /// @return ���_�V�F�[�_�\
    ///
    VertexShader* getVertexShader() const noexcept { return vertex_shader_; }

    ///
    /// @brief  �W�I���g���V�F�[�_�[�̃Z�b�g
    ///
    /// @param[in] Shader : �Z�b�g����V�F�[�_�[
    ///
    void setGeometryShader( GeometryShader* Shader ) noexcept { geometry_shader_ = Shader; }
    ///
    /// @brief  �W�I���g���V�F�[�_�[�̎擾
    ///
    /// @return �W�I���g���V�F�[�_�[
    ///
    GeometryShader* getGeometryShader() const noexcept { return geometry_shader_; }

    ///
    /// @brief  �s�N�Z���V�F�[�_�\�̃Z�b�g
    ///
    /// @param[in] Shader : �Z�b�g����V�F�[�_�[
    ///
    void setPixelShader( PixelShader* Shader ) noexcept { pixel_shader_ = Shader; }
    ///
    /// @brief  �s�N�Z���V�F�[�_�\�̎擾
    ///
    /// @return �s�N�Z���V�F�[�_�\
    ///
    PixelShader* getPixelShader() const noexcept { return pixel_shader_; }

/*-----------------------------------------------------------------*/
// Component
    bool initialize() override;
    void finalize()   override;
/*-----------------------------------------------------------------*/
private :
    Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> texture_;
    D3D11_RECT trimming_range_;
    VertexShader* vertex_shader_     = nullptr;
    GeometryShader* geometry_shader_ = nullptr;
    PixelShader* pixel_shader_       = nullptr;
};

} // namespace component
END_EGEG
#endif /// !INCLUDED_EGEG_RENDERING2D_COMPONENT_HEADER_
/// EOF
