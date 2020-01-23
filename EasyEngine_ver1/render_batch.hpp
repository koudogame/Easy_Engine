///
/// @file    render_batch.hpp
/// @author  ��
///          
/// @brief   �����_�[�o�b�`
/// @details �V���O���g���N���X�ł��B�A�N�Z�X�ɂ�instance�֐����g�p���ĉ������B<br>
///          render�֐��œo�^���ꂽ�����_�[�R���|�[�l���g�̕`��֐�����x�ɌĂяo���܂��B
///
#ifndef INCLUDED_EGEG_RENDER_BATCH_HEADER_
#define INCLUDED_EGEG_RENDER_BATCH_HEADER_
#include <unordered_set>
#include "render_component.hpp"
BEGIN_EGEG
class RenderBatch
{
public :
    ///
    /// @brief  �C���X�^���X�̎擾
    ///
    /// @return �C���X�^���X
    ///
    static RenderBatch* instance() { static RenderBatch i; return &i; }

    ///
    /// @brief   �R���|�[�l���g�̓o�^
    ///
    /// @param[in] pComponent : �o�^���郌���_�[�R���|�[�l���g
    ///
    void registerComponent( RenderComponent* pComponent ) { components_.insert( pComponent ); }
    ///
    /// @brief  �R���|�[�l���g�̍폜
    ///
    /// @param[in] pComponent : �폜�Ώۂ̃R���|�[�l���g
    ///
    void unregisterComponent( RenderComponent* pComponent ) { components_.erase( pComponent ); }

    ///
    /// @brief  �o�^����Ă���R���|�[�l���g��render�֐����Ăяo���܂��B
    ///
    void render();

private :
    RenderBatch() = default;
    RenderBatch( const RenderBatch& ) = delete;
    RenderBatch& operator=( const RenderBatch& ) = delete;

    std::unordered_set<RenderComponent*> components_;
};
END_EGEG
#endif /// !INCLUDED_EGEG_RENDER_BATCH_HEADER_
/// EOF
