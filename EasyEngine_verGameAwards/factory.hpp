///
/// @file   factory.hpp
/// @author 板場
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
/// @brief   汎用ファクトリ
/// @details クリエイターはoperator()をオーバーロードしたファンクタです。
///
/// @tparam Base        : 生成するオブジェクトの基底クラス型
/// @tparam Creator     : 生成処理を行うクリエイター型
/// @tparam CreateArgs  : 生成処理の引数型
///
template <class Base, class Creator, class ...CreateArgs>
class Factory
{
public :
    ///
    /// @brief   生成ファンクタの登録
    /// @details 既に同IDのファンクタが登録されている場合は、新規に登録を行いません。
    ///
    /// @param[in] ID      : クリエイターを識別するID
    /// @param[in] Creator : クリエイター
    ///
    void registerCreator( uint32_t ID, const Creator& Creator )
    {
        creators_.emplace( ID, Creator );
    }

    ///
    /// @brief   生成処理
    /// @details IDに対応するクリエイターがある場合、クリエイターの実行結果を返却します。<br>
    ///          ない場合はnullptrを返却します。
    ///
    /// @param[in] ID : クリエイターの識別ID
    /// @param[in] Args : クリエイターの生成処理に渡す引数リスト
    ///
    /// @return 生成したオブジェクトの所有権を持つスマートポインタ
    ///
    std::unique_ptr<Base> create( uint32_t ID, CreateArgs ...Args )
    {
        auto find = creators_.find( ID );
        if( find == creators_.end() )   return nullptr;

        return std::unique_ptr<Base>( find->second() );
    }

private :
    std::unordered_map<uint32_t, Creator> creators_;    /// 生成ファンクタリスト
};
END_EGEG
#endif /// !INCLUDED_EGEG_FACTORY_HEADER_
/// EOF
