// �쐬�� : ��
#include "actor.hpp"
#include "system_manager.hpp"
#include "component_factory.hpp"

BEGIN_EGEG
// Actor : �֐��̎���
/*===========================================================================*/
// �f�X�g���N�^
Actor::~Actor()
{
    // �ێ����Ă���R���|�[�l���g�̉��
    for( auto& component : components_ )
    {
        component.second->finalize();
        delete component.second;
    }
}

// �R���|�[�l���g�̒ǉ�
Component* Actor::addComponent( uint32_t ComponentID )
{
    auto find = components_.find( ComponentID );
    if( find != components_.end() )
    {
        SystemManager::instance()->showDialogBox(
            "�R���|�[�l���g�̑��d�o�^�����m���܂����B\n"
            "\n�ꏊ : Actor::addComponent"
        );
        return nullptr;
    }

    // �R���|�[�l���g�̐�����������
    Component* component = ComponentFactory::instance()->create( ComponentID, this );
    if( component == nullptr )
    {
        SystemManager::instance()->showDialogBox(
            "�R���|�[�l���g�̐����Ɏ��s���܂����B\n"
            "\n�ꏊ : Actor::addComponent"
        );
        return nullptr;
    }
    if( component->initialize() == false )
    {
        SystemManager::instance()->showDialogBox(
            "�R���|�[�l���g�̏������Ɏ��s���܂����B\n"
            "\n�ꏊ : Actor::addComponent"
        );
        delete component;
        return nullptr;
    }

    // �R���|�[�l���g�����X�g�ɒǉ�
    components_.emplace( ComponentID, component );
    return component;
}

// �R���|�[�l���g�̍폜
void Actor::removeComponent( uint32_t ComponentID )
{
    auto find = components_.find( ComponentID );
    if( find != components_.end() )
    {
        find->second->finalize();
        delete find->second;
        components_.erase( find );
    }
}

// �R���|�[�l���g�̎擾
Component* Actor::getComponent( uint32_t ComponentID )
{
    auto find = components_.find( ComponentID );
    if( find != components_.end() )
        return find->second;
    else
        return nullptr;
    
}
END_EGEG
// EOF
