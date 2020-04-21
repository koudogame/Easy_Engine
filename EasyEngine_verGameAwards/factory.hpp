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

///
/// @def    REGISTER_WITH_FACTORY
/// @brief  ファクトリにオブジェクトを登録
///
/// @param[in] FactoryType   : 登録するファクトリ
/// @param[in] ObjectType    : 登録するクラス型
/// @param[in] IDGenerator   : 登録するクラスに対応させるIDの生成型
///
#define REGISTER_WITH_FACTORY( FactoryType, ObjectType, IDGenerator ) \
template class FactoryType::Element<ObjectType, IDGenerator>

BEGIN_EGEG

///
/// @class   Factory
/// @brief   汎用ファクトリ
///
/// @details ファクトリを使用する際はテンプレートの明示的なインスタンス化を行って下さい。   <br>
///          ファクトリへのオブジェクトの登録はREGISTER_WITH_FACTORYマクロを使用して下さい。<br>
///          ファクトリ定義例 )                                                             <br>
///               class ElementType; ----------------------- 要素型                         <br>
///               template class Factory<ElementType, …>; - ファクトリ                     <br>
///
/// @tparam BaseType     : ファクトリによって生成されるクラスの基底クラス
/// @tparam CtorArgTypes : オブジェクトのコンストラクタに渡す引数型リスト
///
template <class BaseType, class ...CtorArgTypes>
class Factory
{
private :
    class Creator
    {
    public :
        virtual std::unique_ptr<BaseType> create( CtorArgTypes... ) = 0;
    };

    ///
    /// @class  Element
    /// @brief  要素のクリエイター
    ///
    /// @tparam ElementType   : 要素クラス型
    /// @tparam IDGenerator   : IDの生成者
    ///
    template <class ElementType, class IDGenerator>
    class Element :
        public Creator
    {
    public :
        std::unique_ptr<BaseType> create( CtorArgTypes ...Args ) override
        {
            return std::make_unique<ElementType>( Args...);
        }
    private :
        class Registerer :
            public IDGenerator
        {
        public :
            Registerer()
            {
                Factory::registration<Element>( (*this)() );
            }
        };
        static Registerer registerer_;
    };

public :
    ///
    /// @brief  クラスをファクトリにより生成されるオブジェクトとして登録
    ///
    /// @tparam ObjectType : 登録するオブジェクト型
    ///
    /// @param[in] ID : クラスと紐づけるID
    ///
    template <class CreatorType>
    static void registration( uint32_t ID )
    {
        if( creator_list_.find( ID ) == creator_list_.end() )
        { // 既に登録されているオブジェクトはここで弾く
            // Attention : メモリ割り当てを避けるためにあえて弾いている。
            creator_list_.emplace( ID, new CreatorType() );
        }
    }

    ///
    /// @brief   オブジェクトの生成
    /// @details 登録されていないクラスについては、nullptrを返却します。
    ///
    /// @param[in] ID   : 生成するオブジェクトのID
    /// @param[in] Args : コンストラクタに転送する引数リスト
    ///
    /// @return 生成したオブジェクト
    ///
    static std::unique_ptr<BaseType> create( uint32_t ID, CtorArgTypes ...Args )
    {
        auto find = creator_list_.find( ID );
        if( find == creator_list_.end() )
        { // 生成処理が登録されていない
            return nullptr; 
        }
        else
        { // 生成して返却
            return find->second->create( Args... );
        }
    }

private :
    Factory() = default;
    static std::unordered_map<uint32_t, std::unique_ptr<Creator>> creator_list_;
};

template <class BaseType, class ...CtorArgTypes>
std::unordered_map<uint32_t, std::unique_ptr<typename Factory<BaseType, CtorArgTypes...>::Creator>> Factory<BaseType, CtorArgTypes...>::creator_list_;
template <class BaseType, class ...CtorArgTypes>
template <class ObjectType, class IDGenerator>
typename Factory<BaseType, CtorArgTypes...>::template Element<ObjectType, IDGenerator>::Registerer Factory<BaseType, CtorArgTypes...>::Element<ObjectType, IDGenerator>::registerer_;

END_EGEG
#endif /// !INCLUDED_EGEG_FACTORY_HEADER_
/// EOF
