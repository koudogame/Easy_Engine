///
/// @file	factory.hpp
/// @autohr ��
///
#ifndef	INCLUDED_EGEG_FACTORY_HEADER_
#define INCLUDED_EGEG_FACTORY_HEADER_
#include <unordered_map>
#include "egeg_common.hpp"
BEGIN_EGEG
///
/// @class  Factory
///
/// @brief	�ėp�t�@�N�g��
///
/// @tparam BaseType      : ��������I�u�W�F�N�g�ɋ��ʂ�����N���X�^
///	@tparam Creator   : �����������s���I�u�W�F�N�g�^
/// @tparam Arguments : �N���G�C�^�[�̐����֐��ɓn�������^���X�g
///
template <typename BaseType, typename Creator, typename ...Arguments>
class Factory
{
public :
	///
	/// @brief	 �N���G�C�^�[�̓o�^
	///	@details ���ɃN���G�C�^�[���o�^����Ă���ꍇ�́A�V�K�ɓo�^���s���܂���B
	///
	/// @param[in] ID      : �o�^����I�u�W�F�N�g�̎���ID
	/// @param[in] Creator : �N���G�C�^�[
	///
	void registerCreator( uint32_t ID, const Creator& Creator)
    {
		if( creators_.find( ID ) == creators_.end() )
			creators_.emplace( ID, Creator );
    }

	///
	/// @brief	 ����
	/// @details �����Ɏ��s�����ꍇ�Anullptr��ԋp���܂��B
	///
	/// @param[in] ID   : ��������I�u�W�F�N�g�̎���ID
    /// @param[in] Args : ID�ȊO�̈���
	///
	/// @return ���������I�u�W�F�N�g
	///
	BaseType* create( uint32_t ID, Arguments ...Args )
    {
		auto find = creators_.find( ID );
		if( find != creators_.end() )
        {
			return find->second( Args... );
        }

		return nullptr;
    }

private :
	std::unordered_map<uint32_t, Creator> creators_;
};
END_EGEG
#endif /// !INCLUDED_EGEG_FACTORY_HEADER_
/// EOF
