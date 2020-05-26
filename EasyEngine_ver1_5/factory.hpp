///
/// @file   factory.hpp
/// @author 板場
/// 
#ifndef INCLUDED_EGEG_FACTORY_HEADER_
#define INCLUDED_EGEG_FACTORY_HEADER_

#include <unordered_map>
#include <memory>
#include "egeg_def.hpp"


///
/// @def    REGISTER_WITH_FACTORY
/// @brief  ファクトリにオブジェクトを登録
///
/// @param[in] FactoryType  : 登録するファクトリ
/// @param[in] ObjectType   : 登録するオブジェクトの型
/// @param[in] KeyGenerator : 登録するオブジェクトに紐づけるキー
///
/// @note : 静的メンバ変数の定義を行っている。
///
#define REGISTER_WITH_FACTORY( FactoryType, ObjectType, KeyGenerator ) \
template class FactoryType::ElementCreator<ObjectType, KeyGenerator>


BEGIN_EGEG

///
/// @class  Factory
/// @brief  汎用ファクトリ
///
/// @tparam KeyType      : オブジェクトと紐づけるキー型
/// @tparam BaseType     : 生成したオブジェクトを扱うインターフェイス型
/// @tparam CtorArgTypes : オブジェクトのコンストラクタに渡す引数型リスト
///
/// @details インスタンス化を禁止しています。メンバ関数は静的関数です。                      <br>
///           ファクトリを使用する際はテンプレートの明示的なインスタンス化を行って下さい。      <br>
///           ファクトリへのオブジェクトの登録はREGISTER_WITH_FACTORYマクロを使用して下さい。 <br>
///           使用例 )                                                                  <br>
///             テンプレートのインスタンス化                                               <br>
///              class ElementType;                                                     <br>
///              template class Factory<uint32_t, ElementType, ...>;
///
template <class KeyType, class BaseType, class ...CtorArgTypes>
class Factory
{
public :
    using KeyTy = KeyType;
    using InterfaceTy = BaseType;

    ///
    /// @brief   オブジェクトの生成
    /// @details 登録されていないオブジェクトについては、nullptrの返却を行う。
    ///
    /// @param[in] Key  : 生成するオブジェクトのキー
    /// @param[in] Args : コンストラクタに渡す引数リスト
    ///
    template <class ...ArgTypes>
    static std::unique_ptr<BaseType> create( const KeyType& Key, ArgTypes&& ...Args )
    {
        auto find = creator_list_.find( Key );
        if( find == creator_list_.end() ) return nullptr;
        return find->second->create( std::forward<ArgTypes>(Args)... );
    }

    ///
    /// @brief  クラスをファクトリにより生成されるオブジェクトとして登録
    ///
    /// @tparam CreatorType : クリエイター型
    /// @param[in] Key : クラスと紐づけるキー
    ///
    template <class CreatorType, class KeyType_>
    static void registration( KeyType_&& Key )
    {
        if( creator_list_.find(Key) == creator_list_.end() )
        { // 既に登録するオブジェクトはここで弾く
            // note : 余計なメモリ割り当てを避けるため
            creator_list_.emplace( std::forward<KeyType_>(Key), std::make_unique<CreatorType>() );
        }
    }

private :
    class Creator
    {
    public :
        virtual ~Creator() = default;
        virtual std::unique_ptr<BaseType> create( CtorArgTypes... ) const = 0;
    };
    template <class ElementType, class KeyGenerator>
    class ElementCreator : public Creator
    {
    public :
        std::unique_ptr<BaseType> create( CtorArgTypes ...Args ) const override
        {
            return std::make_unique<ElementType>( Args... );
        }
    private :
        class Registerer
        {
        public :
            Registerer()
            {
                KeyGenerator key_gen{};
                Factory::registration<ElementCreator>( key_gen() );
            }
        };
        static Registerer registerer_;
    };

    Factory() = default;
    static std::unordered_map<KeyType, std::unique_ptr<Creator>> creator_list_;
};


///< ファクトリのメンバ変数定義
template <class KeyType, class BaseType, class ...CtorArgTypes>
std::unordered_map<KeyType, std::unique_ptr<typename Factory<KeyType, BaseType, CtorArgTypes...>::Creator>> Factory<KeyType, BaseType, CtorArgTypes...>::creator_list_{};
///< エレメント生成者のメンバ変数定義
template <class KeyType, class BaseType, class ...CtorArgTypes>
template <class ObjectType, class KeyGeneratorType>
typename Factory<KeyType, BaseType, CtorArgTypes...>::template ElementCreator<ObjectType, KeyGeneratorType>::Registerer Factory<KeyType, BaseType, CtorArgTypes...>::ElementCreator<ObjectType, KeyGeneratorType>::registerer_{};

END_EGEG
#endif /// !INCLUDED_EGEG_FACTORY_HEADER_
/// EOF
