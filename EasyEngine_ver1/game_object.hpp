///
/// @file   game_object.hpp
/// @author ��
///
/// @brief  �Q�[�����ɑ��݂���I�u�W�F�N�g�̊��N���X
///
#ifndef INCLUDED_EGEG_GAME_OBJECT_HEADER_
#define INCLUDED_EGEG_GAME_OBJECT_HEADER_
#ifdef _DEBUG
#include <cassert>
#endif /// !_DEBUG
#include <unordered_map>
#include "component.hpp"
BEGIN_EGEG
class GameObject
{
public :
    virtual ~GameObject();

    ///
    /// @brief  ����������
    /// 
    /// @return ����������[ true ] ���������s[ false ]
    ///
    virtual bool initialize() = 0;
    ///
    /// @brief  �I������
    ///
    virtual void finalize() = 0;
    ///
    /// @brief  �X�V����
    ///
    /// @param[in] DeltaTimeMS : �O��Ăяo������̌o�ߎ���(: �~���b)
    ///
    virtual void update( uint64_t DeltaTimeMS ) = 0;

    ///
    /// @brief   �R���|�[�l���g�̒ǉ�
    /// @details �ǉ��Ɏ��s�����ꍇ�Anullptr��ԋp���܂��B
    ///
    /// @tparam Component : �ǉ�����R���|�[�l���g�̌^
    ///
    /// @return �ǉ������R���|�[�l���g�̃A�h���X
    ///
    template <typename Component>
    Component* addComponent();
    ///
    /// @brief   �R���|�[�l���g�̍폜
    ///
    /// @tparam Component : �폜�̑ΏۂƂȂ�R���|�[�l���g�̌^
    ///
    template <typename Component>
    void removeComponent();
    ///
    /// @brief   �R���|�[�l���g�̎擾
    /// @details �Ή�����R���|�[�l���g�����������ꍇ�Anullptr��ԋp���܂��B
    ///
    /// @tparam Component : �擾����R���|�[�l���g�̌^
    ///
    /// @return �擾���ꂽ�R���|�[�l���g�̃A�h���X
    ///
    template <typename Component>
    Component* getComponent();

protected :
    std::unordered_map<uint16_t, IComponent*> components_;  ///< �o�^����Ă���R���|�[�l���g�Q
};

///< GameObject : �f�X�g���N�^
GameObject::~GameObject()
{
    /// �������Ă��Ȃ��R���|�[�l���g�̉��
    for( auto& component : components_ )
    {
        component.second->finalize();
    }
}

///< GameObject : �R���|�[�l���g�̒ǉ�
template <typename Component>
Component* GameObject::addComponent()
{
#ifdef _DEBUG
    assert( components_.find(Component::getComponentID()) == components_.end() &&
            "�R���|�[�l���g�̑��d�o�^�����o���܂����B" );
#endif /// !_DEBUG
    Component* add = new Component();
    if( add->initialize() == false )
    {
        delete add;
        return nullptr;
    }

    components_.emplace( Component::getComponentID(), add );
}

///< GameObject : �R���|�[�l���g�̍폜
template <typename Component>
void GameObject::removeComponent()
{
    auto find = components_.find( Component::getComponentID() );
    if( find != components_.end() )
    {
        find.second->finalize();
        delete find->second;
        components_.erase( find );
    }
}

///< GameObject : �R���|�[�l���g�̎擾
template <typename Component>
Component* GameObject::getComponent()
{
    auto find = components_.find( Component::getComponentID() );
    
    ///< �R���|�[�l���g���o�^����Ă���
    if( find != components_.end() )
    {
        return find.second;
    }
    ///< �R���|�[�l���g���o�^����Ă��Ȃ�
    else
    {
        return nullptr;
    }
}
END_EGEG
#endif /// !INCLUDED_EGEG_GAME_OBJECT_HEADER_
/// EOF
