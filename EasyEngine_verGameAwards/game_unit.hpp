///
/// @file   game_unit.hpp
/// @author ��
///
#ifndef INCLUDED_EGEG_GAME_UNIT_HEADER_
#define INCLUDED_EGEG_GAME_UNIT_HEADER_
#include <cstdint>
#include "egeg.hpp"
BEGIN_EGEG
///
/// @class  GameUnit
/// @brief  �I�u�W�F�N�g�P��
///
class GameUnit
{
public :
    virtual ~GameUnit() = default;

    ///
    /// @brief  ����������
    ///
    /// @return ����[ true ]�@���s[ false ]
    ///
    virtual bool initialize() = 0;
    ///
    /// @brief  �I������
    ///
    virtual void finalize() = 0;
    ///
    /// @brief  �X�V����
    ///
    /// @param[in] DeltaTimeMS : �O��Ăяo��������̎���(�~���b)
    ///
    virtual void update( uint64_t DeltaTimeMS ) = 0;
};
END_EGEG
#endif /// INCLUDED_EGEG_GAME_UNIT_HEADER_
/// EOF
