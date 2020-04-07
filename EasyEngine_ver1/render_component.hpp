///
/// @file   render_component.hpp
/// @author ��
///
#ifndef INCLUDED_EGEG_RENDER_COMPONENT_HEADER_
#define INCLUDED_EGEG_RENDER_COMPONENT_HEADER_
#include "component.hpp"
#include "uid.hpp"
#include "render_batch.hpp"
BEGIN_EGEG
///
/// @class   RenderComponent
///          
/// @brief   �����_�[�R���|�[�l���g
/// @details �`��@�\�������܂��B<br>
///          �����Ɠ�����RenderBatch�N���X�ւ̓o�^���s���܂��B
///
class RenderComponent :
    public Component
{
public :
    ///< ID�̎擾
    static uint32_t getID() { return TypeID<RenderComponent>::getID(); }

    ///
    /// @brief  �R���X�g���N�^
    ///
    /// @param[in] Owner : �I�[�i�[
    ///
    RenderComponent( Actor* Owner ) :
        Component( Owner )
    {
        RenderBatch::instance()->registerComponent( this );
    }
    virtual ~RenderComponent()
    {
        RenderBatch::instance()->unregisterComponent( this );
    }

    ///
    /// @brief   �`�揈��
    /// @details RenderBatch�N���X�ŌĂяo����܂��B
    ///
    virtual void render() = 0;

    ///
    /// @brief  ����Ԃ̃Z�b�g
    ///
    /// @param[in] State : �ݒ肷������
    ///
    void setVisibleState( bool State ) { is_visible_ = State; }
    ///
    /// @brief  ����Ԃ̎擾
    ///
    /// @return �����
    ///
    bool getVisibleState() const { return is_visible_; }

protected :
    bool is_visible_ = false;   ///< ����ԃt���O
};
END_EGEG
#endif /// !INCLUDED_EGEG_RENDER_COMPONENT_HEADER_
/// EOF
