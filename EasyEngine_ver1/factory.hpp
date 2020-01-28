///
/// @file	factory.hpp
/// @autohr 板場
///
#ifndef	INCLUDED_EGEG_FACTORY_HEADER_
#define INCLUDED_EGEG_FACTORY_HEADER_
#include <unordered_map>
#include "egeg_common.hpp"
BEGIN_EGEG
///
/// @class  Factory
///
/// @brief	汎用ファクトリ
///
/// @tparam Base    : 生成するオブジェクトに共通する基底クラス型
///	@tparam Creator : 生成処理を行うオブジェクト型
///
template <typename Base, typename Creator>
class Factory
{
public :
	///
	/// @brief	 クリエイターの登録
	///	@details 既にクリエイターが登録されている場合は、新規に登録を行いません。
	///
	/// @param[in] ID      : 登録するオブジェクトの識別ID
	/// @param[in] Creator : クリエイター
	///
	void registerCreator( uint32_t ID, const Creator& Creator)
    {
		if( creators_.find( ID ) == creators_.end() )
			creators_.emplace( ID, Creator );
    }

	///
	/// @brief	 生成
	/// @details 生成に失敗した場合、nullptrを返却します。
	///
	/// @param[in] ID : 生成するオブジェクトの識別ID
	///
	/// @return 生成したオブジェクト
	///
	Base* create( uint32_t ID )
    {
		auto find = creators_.find( ID );
		if( find != creators_.end() )
        {
			return find.second();
        }

		return nullptr;
    }

private :
	std::unordered_map<uint32_t, Creator> creators_;
};
END_EGEG
#endif /// !INCLUDED_EGEG_FACTORY_HEADER_
/// EOF
