///
/// @file   game_object.hpp
/// @author ��
///
#ifndef INCLUDED_EGEG_GAME_OBJECT_HEADER_
#define INCLUDED_EGEG_GAME_OBJECT_HEADER_
#include <cstdint>
#include "egeg_common.hpp"
BEGIN_EGEG
///
/// @class  GameObject
/// @brief  �Q�[����̃I�u�W�F�N�g�̊��N���X
///
class GameObject
{
public :
    virtual ~GameObject() = default;

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
};
END_EGEG
#endif /// !INCLUDED_EGEG_GAME_OBJECT_HEADER_
/// EOF
