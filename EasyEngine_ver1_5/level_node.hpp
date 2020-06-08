///
/// @file   level_node.hpp
/// @author 板場
///
#ifndef INCLUDED_EGEG_LEVEL_NODE_HEADER_
#define INCLUDED_EGEG_LEVEL_NODE_HEADER_

#ifdef _DEBUG
#include <cassert>
#endif
#include <vector>
#include <unordered_map>
#include <istream>
#include <memory>
#include "factory.hpp"
#include "id.hpp"
#include "name.hpp"

BEGIN_EGEG

///
/// @def    REGISTER_LEVEL_NODE
/// @brief  ファクトリにレベルノードを登録
///
/// @param[in] Type     : 登録するノードクラス型
/// @param[in] NodeName : ノード名
///
#define REGISTER_LEVEL_NODE( Type, NodeName ) \
static constexpr const char Type##NodeName[] = #NodeName; \
REGISTER_WITH_FACTORY( LevelNodeFactory, Type, Name<Type##NodeName> )

class Level;
class Component;

///
/// @class  LevelNode
/// @brief  レベルノード
///
/// @details 要件 <br>
///             このクラスを直接継承したノードは、 <br>
///             static constexpr NodeType 型の kNodeType を定義してください。  <br>
///          注意点
///             finalize関数を実装する際、その中でleaveFromParent関数を呼び出してください。 <br>
///             デストラクタにも同様の処理が記述されていますが、必ずしもfinalizeと解放が同時に行われるとは限りません
///
class LevelNode
{
public :
    enum class NodeType
    {
        kScene,
        kSpace,
        kActor,
        kCamera,
        kLight
    };

    virtual ~LevelNode();

    ///
    /// @brief  初期化
    /// 
    /// @param[in] DataStream : 初期データストリーム
    ///
    /// @return true:成功 　false:失敗
    ///
    virtual bool initialize( std::istream& DataStream ) = 0;
    ///
    /// @brief  終了
    ///
    virtual void finalize() = 0;

    ///
    /// @brief  インスタンスのノード型を取得
    ///
    /// @return ノード型
    ///
    virtual NodeType getNodeType() const noexcept = 0;


    ///
    /// @brief  所属するレベルのセット
    ///
    /// @param[in] Level : レベル
    ///
    void setLevel( Level* Level ) noexcept { level_ = Level; }
    ///
    /// @brief  所属するレベルの取得
    ///
    /// @return レベル
    ///
    Level* getLevel() const noexcept { return level_; }

    ///
    /// @brief  親ノードのセット
    ///
    /// @param[in] Parent : 親ノード
    ///
    void setParent( LevelNode* Parent ) noexcept { parent_ = Parent; }
    ///
    /// @brief  親ノードの取得
    ///
    /// @return 親ノード
    ///
    LevelNode* getParent() const noexcept { return parent_; }
    ///
    /// @brief     親ノードから抜ける
    ///
    /// @details   親ノードがない場合、何も行われません。
    ///
    void leaveFromParent();

    ///
    /// @brief     子ノードの追加
    ///
    /// @param[in] Child : 子ノード
    ///
    /// @details   追加した順序で格納されていきます。
    ///
    void addChild( std::unique_ptr<LevelNode>&& Child ) { childs_.push_back(std::move(Child)); }
    ///
    /// @brief     子ノードの取得
    /// 
    /// @param[in] 先頭からのインデックス
    ///
    /// @return    インデックスに対応した子ノード
    ///
    /// @details   インデックスが子ノードの数より多い場合、nullptrを返却します。
    ///
    LevelNode* getChild( size_t Index=0 ) const noexcept { return Index<childs_.size() ? childs_[Index].get() : nullptr; }
    ///
    /// @brief     子ノードの取得
    ///
    /// @tparam    NodeType_ : 取得するノードの型
    /// @param[in] Index     : インデックス
    ///
    /// @return    インデックスに対応した子ノード
    ///
    /// @details   インデックスは先頭からのインデックスではなく、対応した型の中のオフセットです。
    ///
    template <class NodeType_>
    NodeType_* getChild( size_t Index=0 ) const noexcept;
    ///
    /// @brief     子ノードの削除
    ///
    /// @param[in] Child : 削除する子ノード
    ///
    void removeChild( LevelNode* Child );
    ///
    /// @brief     子ノードに対する処理の実行
    ///
    /// @tparam    FunctionType : 呼び出す関数のラッパー
    /// @param[in] Function     : 関数オブジェクト
    /// @param[in] Args...      : 呼び出す関数に渡す引数リスト( 第二引数以降 )
    ///
    /// @details   呼び出す関数は、 <br>
    ///            戻り値　 void       : 子ノードをループするので戻り値は意味がない <br>
    ///            第一引数 LevelNode* :  処理の対象となる子ノード <br>
    ///            以降任意の引数 <br>
    //             の形です。
    ///
    template <class FunctionType, class ...ArgTypes>
    void forChild( FunctionType Function, ArgTypes ...Args );

    ///
    /// @brief     再帰呼び出しのエントリー
    ///
    /// @tparam ReturnType  : 呼び出す関数の戻り値
    /// @tparam ArgTypes    : 呼び出す関数の引数リスト
    /// @param[in] Function : 呼び出す関数のアドレス
    /// @param[in] Args     : 呼び出す関数に渡すパラメータ
    ///
    template <class ReturnType, class ...ArgTypes>
    void recursizeEntry( ReturnType(LevelNode::*Function)(ArgTypes...), ArgTypes ...Args );

    ///
    /// @brief     コンポーネントの追加
    ///
    /// @tparam    ComponentType : 追加するコンポーネントの型
    ///
    /// @return    追加したコンポーネント型
    ///
    /// @details   追加に失敗した場合、nullptrを返却します。
    ///
    template <class ComponentType>
    ComponentType* addComponent();
    ///
    /// @brief     コンポーネントの取得
    ///
    /// @tparam    ComponentType : 取得するコンポーネントの型
    ///
    /// @return    対応したコンポーネント
    ///
    /// @details   対応したコンポーネントを保持していない場合、nullptrを返却します。
    ///
    template <class ComponentType>
    ComponentType* getComponent() const;

private :
    ///< コンポーネントのデリーター
    struct ComponentDeleter
    {
        void operator()( Component* ) const;
    };

    Level* level_ = nullptr;
    LevelNode* parent_ = nullptr;
    std::vector<std::unique_ptr<LevelNode>> childs_;
    std::unordered_map<uint32_t, std::unique_ptr<Component, ComponentDeleter>> components_;
};


// 子ノードの取得関数( 型指定 )
template <class NodeType>
NodeType* LevelNode::getChild( size_t Index ) const noexcept
{
    size_t count = 0;
    for( auto& child : childs_ )
    {
        if( child->getNodeType()==NodeType::kNodeType &&
            count++ ==Index )
        {
            return static_cast<NodeType*>(child);
        }
    }
    return nullptr;
}


// コンポーネントの追加関数
template <class ComponentType>
ComponentType* LevelNode::addComponent()
{
#ifdef _DEBUG
    assert( getComponent<ComponentType>()==nullptr &&
            "コンポーネントの多重登録はできません" );
#endif
    auto component = std::unique_ptr<ComponentType, ComponentDeleter>
        { new ComponentType{this}, ComponentDeleter{} };
    if( !component->initialize() ) { return nullptr; }

    auto* ptr = component.get();
    components_.emplace( TypeID<ComponentType>{}, std::move(component) );

    return ptr;
}


// コンポーネントの取得関数
template <class ComponentType>
ComponentType* LevelNode::getComponent() const
{
    auto find_itr = components_.find( TypeID<ComponentType>{} );
    if( find_itr==components_.end() ) return nullptr;

    return static_cast<ComponentType*>( find_itr->second.get() );
}


// 子ノードに対する処理の実行
template <class FunctionType, class ...ArgTypes>
void LevelNode::forChild( FunctionType F, ArgTypes ...Args )
{
    for( auto& child : childs_ )
    {
        F( child.get(), Args... );
    }
}


// 再帰処理エントリー
template <class ReturnType, class ...ArgTypes>
void LevelNode::recursizeEntry( ReturnType(LevelNode::*Function)(ArgTypes...), ArgTypes ...Args )
{
    (this->*Function)( Args... );
    for( auto& child : childs_ )
        child->recursizeEntry( Function, Args... );
}


// ファクトリを定義
template class Factory<uint32_t, LevelNode>;
using LevelNodeFactory = Factory<uint32_t, LevelNode>;

END_EGEG
#endif /// !INCLUDED_EGEG_LEVEL_NODE_HEADER_
/// EOF
