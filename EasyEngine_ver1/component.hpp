///
/// @file    component.hpp
/// @author  ��
///          
/// @brief   �R���|�[�l���g
/// @details �e�h���N���X�� static uint16_t getComponentID() ���������Ă��������B<br>
///          DECL_GETCOMPONENTID�}�N�����g�p����Ɗy�ł��B
///
#ifndef INCLUDED_EGEG_COMPONENT_HEADER_
#define INCLUDED_EGEG_COMPONENT_HEADER_
#include <cstdint>
#include "egeg_common.hpp"
///
/// @def    DECL_GETCOMPONENTID
/// @brief  ID�̎擾�֐���inline�Œ�`���܂��B
///
#define DECL_GETCOMPONENTID inline static uint16_t getComponentID()

BEGIN_EGEG
class IComponent
{
public :
    virtual ~IComponent() = default;

    ///
    /// @brief  ������
    ///
    /// @return ����������[ true ] ���������s[ false ]
    ///
    virtual bool initialize() = 0;
    ///
    /// @brief  �I��
    ///
    virtual void finalize() = 0;
};
END_EGEG
#endif /// !INCLUDED_EGEG_COMPONENT_HEADER_
/// EOF
