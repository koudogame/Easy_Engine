///
/// @file   scene.hpp
/// @author ��
///
#ifndef INCLUDED_EGEG_SCENE_HEADER_
#define INCLUDED_EGEG_SCENE_HEADER_
#include <cstdint>
#include "egeg_common.hpp"
BEGIN_EGEG
///
/// @class  Scene
///
/// @brief  �V�[�����N���X
///
class Scene
{
public :
    virtual ~Scene() = default;

    ///
    /// @brief  �V�[������������
    ///
    /// @return ����������[ true ]�@���������s[ false ]
    ///
    virtual bool initialize() = 0;
    ///
    /// @brief  �V�[���I������
    ///
    virtual void finalize() = 0;

    ///
    /// @brief  �X�V����
    ///
    /// @param[in] DeltaTimeMS : �O��Ăяo��������̎��ԍ�(:�~���b)
    ///
    virtual void update( uint64_t DeltaTimeMS ) = 0;
    
    ///
    /// @brief  �A�N�e�B�u��Ԃ̃Z�b�g
    ///
    /// @param[in] State : �ݒ肷����
    ///
    void setActiveState( bool State ) { is_active_ = State; }
    ///
    /// @brief  �A�N�e�B�u��Ԃ̎擾
    ///
    /// @return ���
    ///
    bool isActive() const { return is_active_; }

protected :
    Scene() = default;  ///< �ʏ�t�@�N�g���ȊO�ł̐������֎~���Ă��܂��B

private :
    bool is_active_ = false;
};
END_EGEG
#endif /// !INCLUDED_EGEG_SCENE_HEADER_
/// EOF
