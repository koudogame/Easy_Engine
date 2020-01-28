///
/// @file   game_object.hpp
/// @author ��
///
/// @brief  �Q�[�����ɑ��݂���I�u�W�F�N�g�̊��N���X
///
#ifndef INCLUDED_EGEG_GAME_OBJECT_HEADER_
#define INCLUDED_EGEG_GAME_OBJECT_HEADER_
#include <cstdint>
#include "component.hpp"
BEGIN_EGEG
class GameObject
{
public :
    virtual ~GameObject() = default;

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

protected :
    Component
};
END_EGEG
#endif /// !INCLUDED_EGEG_GAME_OBJECT_HEADER_
/// EOF
