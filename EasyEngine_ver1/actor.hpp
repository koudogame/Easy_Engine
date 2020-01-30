///
/// @file   actor.hpp
/// @author ��
///
#ifndef INCLUDED_EGEG_ACTOR_HEADER_
#define INCLUDED_EGEG_ACTOR_HEADER_
#include <cstdint>
#include <typeinfo>
#include <unordered_map>
#include "system_manager.hpp"
BEGIN_EGEG
class Shape;
class Component;
///
/// @class  Actor
///
/// @brief  �A�N�^�[���N���X
class Actor
{
public :
    virtual ~Actor();

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
    /// @brief  �`�̎擾
    ///
    /// @return �`
    ///
    virtual const Shape* getShape() = 0;

    ///
    /// @brief  �A�N�^�[����ID�擾
    ///
    /// @return ID
    ///
    uint32_t getID() const { return id_; }

    ///
    /// @brief  �R���|�[�l���g�̒ǉ�
    ///
    /// @tparam ComponentType : �ǉ�����R���|�[�l���g�^
    ///
    /// @return �ǉ������R���|�[�l���g
    ///
    template <typename ComponentType>
    ComponentType* addComponent();
    ///
    /// @brief  �R���|�[�l���g�̍폜
    ///
    /// @tparam ComponentType : �폜����R���|�[�l���g�^
    ///
    template <typename ComponentType>
    void removeComponent();
    ///
    /// @brief   �R���|�[�l���g�̎擾
    /// @details �Ή������R���|�[�l���g��ێ����Ă��Ȃ��ꍇ�́Anullptr��ԋp���܂��B
    ///
    /// @tparam ComponentType : �擾����R���|�[�l���g�^
    ///
    /// @return �R���|�[�l���g
    ///
    template <typename ComponentType>
    ComponentType* getComponent();

protected :
    ///
    /// @brief   �R���X�g���N�^
    /// @details �ʏ�t�@�N�g���ȊO�ł̐������֎~���Ă��܂��B
    ///
    /// @param[in] ID : �A�N�^�[����ID
    ///
    Actor( uint32_t ID ) : id_( ID ) {}

private :
    uint32_t id_;                                           /// �A�N�^�[����ID
    std::unordered_map<uint32_t, Component*> components_;   /// �R���|�[�l���g�Q
};

///< �R���|�[�l���g�̒ǉ�
template <typename ComponentType>
ComponentType* Actor::addComponent()
{
    // ���d�o�^�`�F�b�N
    if( components_.find(ComponentType::getID()) != components_.end() )
    {
        SystemManager::instance()->showDialogBox(
            "�R���|�[�l���g�̑��d�o�^�����m���܂����B\n"
            "\n�ꏊ : Actor::addComponent\n"
            "�^ : " + typeid( ComponentType ).name()
        );
        return nullptr;
    }

    // �R���|�[�l���g�̐�����������
    ComponentType* component = new ComponentType( this );
    if( component->initialize() == false )
    {
        delete component;
        SystemManager::instance()->showDialogBox(
            "�R���|�[�l���g�̏������Ɏ��s���܂����B\n"
            "\n�ꏊ : Actor::addComponent\n"
            "�^ : " + typeid( ComponentType ).name()
        );
        return nullptr;
    }

    // �R���|�[�l���g�����X�g�ɒǉ�
    components_.emplace( ComponentType::getID(), component );
    return component;
}

///< �R���|�[�l���g�̍폜
template <typename ComponentType>
void Actor::removeComponent()
{
    if( auto find = components_.find(ComponentType::getID()) != components_.end() )
    {
        find->second->finalize();
        delete find->second;
        components_.erase( find );
    }
}

///< �R���|�[�l���g�̎擾
template <typename ComponentType>
ComponentType* Actor::getComponent()
{
    if( auto find = components_.find(ComponentType::getID()) != components_.end() )
    {
        return dynamic_cast<ComponentType*>( find->second );
    }
    else
        return nullptr;
}
END_EGEG
#endif /// !INCLUDED_EGEG_ACTOR_HEADER_
/// EOF
