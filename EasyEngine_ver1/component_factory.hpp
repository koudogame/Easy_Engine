///
/// @file   component_factory.hpp
/// @author ��
///
#ifndef INCLUDED_EGEG_COMPONENT_FACTORY_HEADER_
#define INCLUDED_EGEG_COMPONENT_FACTORY_HEADER_
#include "factory.hpp"
#include "component.hpp"
BEGIN_EGEG
///
/// @class   ComponentFactory
///          
/// @brief   �R���|�[�l���g�t�@�N�g��
/// @details �V���O���g���N���X�ł��B�A�N�Z�X�ɂ�instance�֐����g�p���ĉ������B
///
class ComponentFactory :
    public Factory<Component, Component*(*)(Actor*), Actor*>
{
public :
    ///
    /// @brief  �C���X�^���X�̎擾
    ///
    /// @return �C���X�^���X
    ///
    static ComponentFactory* instance() { static ComponentFactory i; return &i; }

private :
    ComponentFactory() = default;
    ComponentFactory( const ComponentFactory& ) = delete;
    ComponentFactory& operator=( const ComponentFactory& ) = delete;
};
END_EGEG
#endif /// !INCLUDED_EGEG_COMPONENT_FACTORY_HEADER_
/// EOF
