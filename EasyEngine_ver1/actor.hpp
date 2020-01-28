///
/// @file   actor.hpp
/// @author ��
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
/// @brief  �A�N�^�[���N���X
class Actor
{
public :
    virtual ~Actor() = default;

    ///
    /// @brief  ����������
    ///
    /// @return ����������[ true ]�@���������s[ false ]
    ///
    virtual bool initialize() = 0;
    ///
    /// @brief  �I������
    ///
    virtual void finalize() = 0;

    ///
    /// @brief  �X�V����
    ///
    /// @param[in] DeltaTimeMS : �O��Ăяo��������̎��Ԃ̍�(: �~���b)
    ///
    virtual void update( uint64_t DeltaTimeMS ) = 0;

    ///
    /// @brief  �A�N�^�[����ID�Z�b�g
    ///
    void setID( uint32_t ID ) { id_ = ID; }
    ///
    /// @brief  �A�N�^�[����ID�擾
    ///
    /// @return ID
    ///
    uint32_t getID() const { return id_; }

    ///
    /// @brief  �R���|�[�l���g�̒ǉ�
    ///
    /// @param[in] ComponentID : �ǉ�����R���|�[�l���g�̎���ID
    ///
    /// @return �ǉ������R���|�[�l���g�̃A�h���X
    ///
    Component* addComponent( uint32_t ComponentID );
    ///
    /// @brief  �R���|�[�l���g�̍폜
    ///
    /// @param[in] ComponentID : �폜����R���|�[�l���g�̎���ID
    ///
    void removeComponent( uint32_t ComponentID );
    ///
    /// @brief   �R���|�[�l���g�̎擾
    /// @details ID�ɑΉ������R���|�[�l���g��ێ����Ă��Ȃ��ꍇ�́Anullptr��ԋp���܂��B
    ///
    /// @param[in] ComponentID : �擾����R���|�[�l���g�̎���ID
    ///
    /// @return ID�ɑΉ������R���|�[�l���g
    ///
    Component* getComponent( uint32_t ComponentID );

private :
    uint32_t id_ = 0U;                                      /// �A�N�^�[����ID
    std::unordered_map<uint32_t, Component*> components_;   /// �R���|�[�l���g�Q
};
END_EGEG
#endif /// !INCLUDED_EGEG_ACTOR_HEADER_
/// EOF
