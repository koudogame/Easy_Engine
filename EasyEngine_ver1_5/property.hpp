///
/// @file   property.hpp
/// @author 板場
/// 
#ifndef INCLUDED_EGEG_PROPERTY_HEADER_
#define INCLUDED_EGEG_PROPERTY_HEADER_

#include <type_traits>
#include <tuple>
#include "egeg_def.hpp"

BEGIN_EGEG

///
/// @class  Tag
/// @brief  Propertyの要素となるタグ
///
/// @tparam ElementType : タグに対応する要素の型
/// @tparam Index       : 同一の要素型を持つタグを識別するインデックス
///
template <class ElementType, size_t Index=0U>
class Tag
{
public :
    using ElemTy = ElementType;

    template <class ElemType>
    void set( ElemType&& Element )
    {
        element_ = std::forward<ElemType>( Element );
    }
    const ElemTy& get() const noexcept
    {
        return element_;
    }

private :
    ElemTy element_;
};


///
/// @class  Property
/// @brief  プロパティ
///
/// @tparam  TagTypes : プロパティの要素となるタグリスト
///
/// @details タグリストに渡す型は Tag<T,N>です。                                     <br>
///           使用例 )                                                              <br>
///             宣言                                                                <br>
///              Property<Tag<std::string, 0U>, Tag<std::string, 1U>> property;    <br>
///             要素のセット                                                         <br>
///              property.set<Tag<std::string, 0U>>( "texture1.png" );              <br>
///              property.set<Tag<std::string, 1U>>( "texture2.png" );              <br>
///             要素の取得                                                           <br>
///              auto texture = property.get<Tag<std::string, 1U>>();
///
template <class ...TagTypes>
class Property
{
public :
    template <class TagType>
    void set( const typename TagType::ElemTy& Element )
    {
        std::get<TagType>(property_).set( Element );
    }
    template <class TagType>
    void set( typename TagType::ElemTy&& Element )
    {
        std::get<TagType>(property_).set( std::move(Element) );
    }
    template <class TagType>
    typename TagType::ElemTy& get() noexcept
    {
        return std::get<TagType>(property_).get();
    }
    template <class TagType>
    const typename TagType::ElemTy& get() const noexcept
    {
        return std::get<TagType>(property_).get();
    }

    ///
    /// @brief  プロパティの抽出
    ///
    /// @tparam ExtractionTypes : 抽出するタグリスト
    ///
    /// @return 抽出したデータを保持したプロパティ
    ///
    template <class ...ExtractionTypes>
    Property<ExtractionTypes...> extraction() const noexcept
    {
        Property<ExtractionTypes...> extracted;
        extraction<decltype(extracted), ExtractionTypes...>( extracted );
        return extracted;
    }

private :
    template <class PropertyType, class FirstTagType, class ...RestTagTypes>
    void extraction( PropertyType& Destination ) const noexcept
    {
        Destination.set<FirstTagType>( this->get<FirstTagType>() );
        extraction<PropertyType, RestTagTypes...>( Destination );
    }
    template <class PropertyType>
    void extraction( PropertyType& ) const noexcept {}

    std::tuple<TagTypes...> property_;
};

END_EGEG
#endif /// !INCLUDED_EGEG_PROPERTY_HEADER_
/// EOF
