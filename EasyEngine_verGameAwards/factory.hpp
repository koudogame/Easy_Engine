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
/// @details このクラスにより生成されるクラスは、Factory<Base>::Element<T>を継承して下さい。<br>
///          Factory<Base>::Element<T> のTはそのクラス自身の型を指定します。
///
template <class Base>
class Factory
{
private :
    class Creator
    {
    public :
        virtual std::unique_ptr<Base> create() = 0;
    };

public :
    ///< ファクトリにより生成されるクラス
    template <class Derived>
    class Element :
        public Creator
    {
    public :
        std::unique_ptr<Base> create() override
        {
            return std::make_unique<Derived>();
        }
    };

public :
    ///
    /// @brief  クラスをファクトリにより生成されるオブジェクトとして登録
    ///
    /// @param[in] ID : クラスと紐づけるID
    ///
    template <class Elem>
    static void Register( uint32_t ID )
    {
        if( creator_list_.find( ID ) == creator_list_.end() )
        { // 既に登録されているオブジェクトはここで弾く
            // Attention : メモリ割り当てを避けるためにあえて弾いている。
            creator_list_.emplace( ID, new Element<Elem>() );
        }
    }

    ///
    /// @brief   オブジェクトの生成
    /// @details 登録されていないクラスについては、nullptrを返却します。
    ///
    /// @param[in] ID : 生成するオブジェクトID
    ///
    /// @return 生成したオブジェクト
    ///
    static std::unique_ptr<Base> create( uint32_t ID )
    {
        auto find = creator_list_.find( ID );
        if( find == creator_list_.end() )
        { // 生成処理が登録されていない。
            return nullptr; 
        }
        else
        { // 生成して返却
            return find->second->create();
        }
    }

private :
    static std::unordered_map<uint32_t, std::unique_ptr<Creator>> creator_list_;
};

template <class Base>
std::unordered_map<uint32_t, std::unique_ptr<typename Factory<Base>::Creator>> Factory<Base>::creator_list_;
END_EGEG
#endif /// !INCLUDED_EGEG_FACTORY_HEADER_
/// EOF
