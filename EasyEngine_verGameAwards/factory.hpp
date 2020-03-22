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
/// @details このクラスにより生成されるクラスは、Factory<BaseType>::Element<T, ID>を継承して下さい。<br>
///          Factory<BaseType>::Element<T, ID> のTはそのクラス自身の型を指定します。IDはオブジェクトと紐づけるIDファンクタを指定します。<br>
///          このファクトリにより生成されるクラスは、必ず引数を受け取らないコンストラクタを定義して下さい。
///
template <class BaseType>
class Factory
{
private :
    class Creator
    {
    public :
        virtual std::unique_ptr<BaseType> create() = 0;
    };

public :
    ///
    /// @class  このファクトリの要素であることを示す
    ///
    /// @tparam DerivedType   : 継承先のクラス型
    /// @tparam IDFunctorType : クラス型に対応したIDを返却するファンクタ
    ///
    template <class DerivedType, class IDFunctorType>
    class Element :
        public Creator
    {
    public :
        std::unique_ptr<BaseType> create() override
        {
            return std::make_unique<DerivedType>();
        }
    private :
        class Registerer
        {
        public :
            Registerer()
            {
                IDFunctorType id;
                Factory::registration( id() );
            }
        };
        static Registerer register_;
    };

public :
    ///
    /// @brief  クラスをファクトリにより生成されるオブジェクトとして登録
    ///
    /// @tparam ObjectType : 登録するオブジェクト型
    ///
    /// @param[in] ID : クラスと紐づけるID
    ///
    template <class ObjectType>
    static void registration( uint32_t ID )
    {
        if( creator_list_.find( ID ) == creator_list_.end() )
        { // 既に登録されているオブジェクトはここで弾く
            // Attention : メモリ割り当てを避けるためにあえて弾いている。
            creator_list_.emplace( ID, new typename ObjectType::Element() );
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
    static std::unique_ptr<BaseType> create( uint32_t ID )
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
    Factory() = default;
    static std::unordered_map<uint32_t, std::unique_ptr<Creator>> creator_list_;
};

///
/// @def    REGISTER_WITH_FACTORY
/// @brief  ファクトリにオブジェクトを登録
///
/// @param[in] BaseType      : ファクトリが生成する基底クラス型名
/// @param[in] ObjectType    : ファクトリに登録するクラス型名
/// @param[in] IDFunctorType : 登録するクラスに対応させるIDファンクタ
///
#define REGISTER_WITH_FACTORY( BaseType, ObjectType, IDFunctorType ) \
template class Factory<BaseType>::Element<ObjectType, IDFunctorType>

template <class BaseType>
std::unordered_map<uint32_t, std::unique_ptr<typename Factory<BaseType>::Creator>> Factory<BaseType>::creator_list_;
template <class BaseType>
template <class ObjectType, class IDFunctorType>
typename Factory<BaseType>::template Element<ObjectType, IDFunctorType>::Registerer Factory<BaseType>::Element<ObjectType, IDFunctorType>::register_;
END_EGEG
#endif /// !INCLUDED_EGEG_FACTORY_HEADER_
/// EOF
