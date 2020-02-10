///
/// @file   collision_space.hpp
/// @author ��
///
#ifndef INCLUDED_EGEG_COLLISION_SPACE_HEADER_
#define INCLUDED_EGEG_COLLISION_SPACE_HEADER_
#include <unordered_map>
#include "collision_component.hpp"
#include "fullscan_spatial_division.hpp"
#include "job.hpp"
BEGIN_EGEG
///
/// @class   CollisionSpace
/// @brief   �Փˋ�ԃN���X
///          
/// @details �Փ˔�����s����Ԃ̃C���^�[�t�F�C�X�ł��B<br>
///          �V���O���g���N���X�ł��B�A�N�Z�X�ɂ�instance�֐����g�p���ĉ������B
///
class CollisionSpace
{
public :
    ///
    /// @brief   ��ԕ����N���X
    /// @details setSections�֐��ŃZ�N�V�����̐ݒ���s���܂��B<br>
    ///          ���݂�����Z�N�V���������ׂĈ����̃R���e�i�Ɋi�[���郂�m�Ƃ��܂��B<br>
    ///          void setSections( std::vector<->* );<br>
    ///<br>
    ///          createID�֐��Ō`�ɑΉ������Z�N�V����ID�̐������s���܂��B<br>
    ///          setSections�֐��Őݒ肵���Z�N�V������ - 1������Ƃ��܂��B<br>
    ///          uint32_t createID( const Shape* )
    ///
    using SpatialDivision = FullScanSpatialDivision;

    ///< �f�X�g���N�^
    ~CollisionSpace();

    ///
    /// @brief  �C���X�^���X�̎擾
    ///
    /// @return �C���X�^���X
    ///
    static CollisionSpace* instance() { static CollisionSpace i; return &i; }

    ///
    /// @brief  �Փ˔���
    ///
    /// @param[in] : �W���u�Ƃ��ēo�^���邽�߂̃_�~�[
    ///
    void collision( uint64_t );

    ///
    /// @brief  ��Ԃւ̓o�^
    ///
    /// @param[in] pComponent : �o�^����R���|�[�l���g�̃A�h���X
    ///
    void entry( CollisionComponent* pComponent );
    ///
    /// @brief  ��Ԃ���폜
    ///
    /// @param[in] pComponent : �폜����R���|�[�l���g�̃A�h���X
    ///
    void exit( CollisionComponent* pComponent );

private :
    void judgeSectionAndSection( CollisionSection*, CollisionSection* );
    void judgeSameSection( CollisionSection* );
    CollisionSection* nextJudgeSection( CollisionSection* );

    std::vector<CollisionSection> sections_;
    Job job_;

    CollisionSpace();
    CollisionSpace( const CollisionSpace& ) = delete;
    CollisionSpace& operator=( const CollisionSpace& ) = delete;
};
END_EGEG
#endif /// !INCLUDED_EGEG_COLLISION_SPACE_HEADER_
/// EOF
