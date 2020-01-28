///
/// @file   render_component.hpp
/// @author ��
///
/// @brief  �`��R���|�[�l���g
///
#ifndef INCLUDED_EGEG_RENDER_COMPONENT_HEADER_
#define INCLUDED_EGEG_RENDER_COMPONENT_HEADER_
#include "component.hpp"
BEGIN_EGEG
class RenderComponent :
    public Component
{
public :
    RenderComponent();
    virtual ~RenderComponent();

    ///
    /// @brief  �`�揈��
    ///
    virtual void render() = 0;

    ///
    /// @brief   �`��X�e�[�^�X�ݒ�
    /// @details ������[ true ]��ݒ肵���ꍇ�A�`�悳��܂��B
    ///
    /// @param[in] Visible : �����
    ///
    void setVisible( bool Visible );
};
END_EGEG
#endif /// !INCLUDED_EGEG_RENDER_COMPONENT_HEADER_
/// EOF
