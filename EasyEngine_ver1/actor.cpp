// �쐬�� : ��
#include "actor.hpp"
#include "component.hpp"

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
END_EGEG
// EOF
