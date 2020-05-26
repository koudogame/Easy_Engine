///
/// @file   sprite.hpp
/// @author ��
///
#ifndef INCLUDED_EGEG_SPRITE_HEADER_
#define INCLUDED_EGEG_SPRITE_HEADER_

#include "actor2d.hpp"
#include "egeg_math.hpp"
#include "task.hpp"
#include "mesh.hpp"
#include "shader.hpp"

BEGIN_EGEG

///
/// @class  Sprite
/// @brief  �X�v���C�g�A�摜
///
/// @details ���������ɃX�g���[������󂯎��f�[�^�� <br>
///           std::string : �ǂݍ��މ摜�t�@�C���p�X <br>
///                                         �@�ł��B
///
class Sprite :
    public Actor2D
{
public :
    Sprite() : Actor2D{ TypeID<Sprite>{} }
    {}

    ///
    /// @brief �؂���͈͂̊�_���Z�b�g
    ///
    /// @param[in] BasePoint : ��_
    ///
    void setTrimmingBasePoint( const Vector2D& BasePoint ) noexcept { trim_base_point_ = BasePoint; }
    ///
    /// @brief �؂���͈͂̊����擾
    ///
    /// @return ��_
    ///
    const Vector2D& getTrimmingBasePoint() const noexcept { return trim_base_point_; }

    ///
    /// @brief �������Z�b�g
    ///
    /// @param[in] Width : ����
    ///
    void setWidth( float Width ) noexcept { width_ = Width; }
    ///
    /// @brief �������擾
    ///
    /// @return ����
    ///
    float getWidth() const noexcept { return width_; }

    ///
    /// @brief �c�����Z�b�g
    ///
    /// @param[in] Height : �c��
    ///
    void setHeight( float Height ) noexcept { height_ = Height; }
    ///
    /// @brief �c�����擾
    ///
    /// @return �c��
    ///
    float getHeight() const noexcept { return height_; }

    ///
    /// @brief �X�V
    ///
    void update( uint64_t );

// override
    bool initialize( std::istream& ) override;
    void finalize() override;
    DirectX::XMMATRIX calcWorldMatrix() const override;

private :
    bool createMesh();
    bool loadTexture( const std::string& );
    void initComponent();
    void registerTask();

    Task task_;
    Mesh mesh_;
    std::unique_ptr<IShader> shader_;
    Vector2D trim_base_point_;
    float width_ = 0.0F;
    float height_= 0.0F;
    float texture_width_ = 0.0F;
    float texture_height_= 0.0F;
};

REGISTER_ACTOR( Sprite, Sprite );

END_EGEG
#endif /// !INCLUDED_EGEG_SPRITE_HEADER_
/// EOF
