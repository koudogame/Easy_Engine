///
/// @file	factory.hpp
/// @autohr 板場
///
/// @brief	ファクトリ
///
/// @tparam Base    : 生成するオブジェクトに共通する基底クラス型
///	@tparam Creator : 生成処理を担うクラス型
///
#ifndef	INCLUDED_EGEG_FACTORY_HEADER_
#define INCLUDED_EGEG_FACTORY_HEADER_
#include <unordered_map>
#include "egeg_common.hpp"
BEGIN_EGEG
template <class Base, class Creator>
class Factory
{
public :
	///
	/// @brief	 クリエイターの登録
	///	@details 既にクリエイターが登録されている場合は新規に登録を行いません。<br>
	///			 クリエイターを上書きしたい場合は、unregisterCreator関数を使用して下さい。
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
	/// @brief	クリエイターの登録解除
	///
	/// @param[in] ID : 登録を解除するオブジェクトの識別ID
	///
	void unregisterCreator( uint32_t ID )
    {
		creators_.erase( ID );
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
