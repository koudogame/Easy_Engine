///
/// @file   factory.hpp
/// @author ��
///
#ifndef INCLUDED_EGEG_FACTORY_HEADER_
#define INCLUDED_EGEG_FACTORY_HEADER_
#include <cstdint>
#include <unordered_map>
#include <memory>
#include "egeg.hpp"
BEGIN_EGEG
///
/// @class   Factory
/// @brief   �ėp�t�@�N�g��
/// @details �N���G�C�^�[��operator()���I�[�o�[���[�h�����t�@���N�^�ł��B
///
/// @tparam Base        : ��������I�u�W�F�N�g�̊��N���X�^
/// @tparam Creator     : �����������s���N���G�C�^�[�^
/// @tparam CreateArgs  : ���������̈����^
///
template <class Base, class Creator, class ...CreateArgs>
class Factory
{
public :
    ///
    /// @brief   �����t�@���N�^�̓o�^
    /// @details ���ɓ�ID�̃t�@���N�^���o�^����Ă���ꍇ�́A�V�K�ɓo�^���s���܂���B
    ///
    /// @param[in] ID      : �N���G�C�^�[�����ʂ���ID
    /// @param[in] Creator : �N���G�C�^�[
    ///
    void registerCreator( uint32_t ID, const Creator& Creator )
    {
        creators_.emplace( ID, Creator );
    }

    ///
    /// @brief   ��������
    /// @details ID�ɑΉ�����N���G�C�^�[������ꍇ�A�N���G�C�^�[�̎��s���ʂ�ԋp���܂��B<br>
    ///          �Ȃ��ꍇ��nullptr��ԋp���܂��B
    ///
    /// @param[in] ID : �N���G�C�^�[�̎���ID
    /// @param[in] Args : �N���G�C�^�[�̐��������ɓn���������X�g
    ///
    /// @return ���������I�u�W�F�N�g�̏��L�������X�}�[�g�|�C���^
    ///
    std::unique_ptr<Base> create( uint32_t ID, CreateArgs ...Args )
    {
        auto find = creators_.find( ID );
        if( find == creators_.end() )   return nullptr;

        return std::unique_ptr<Base>( find->second() );
    }

private :
    std::unordered_map<uint32_t, Creator> creators_;    /// �����t�@���N�^���X�g
};
END_EGEG
#endif /// !INCLUDED_EGEG_FACTORY_HEADER_
/// EOF
