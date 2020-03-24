///
/// @file   factory.hpp
/// @author ��
///
#ifndef INCLUDED_EGEG_FACTORY_HEADER_
#define INCLUDED_EGEG_FACTORY_HEADER_
#include <cstdint>
#include <unordered_map>
#include <memory>
#include "egeg.hpp"

///
/// @def    REGISTER_WITH_FACTORY
/// @brief  �t�@�N�g���ɃI�u�W�F�N�g��o�^
///
/// @param[in] FactoryType   : �o�^����t�@�N�g��
/// @param[in] ObjectType    : �o�^����N���X�^
/// @param[in] IDFunctorType : �o�^����N���X�ɑΉ�������ID�t�@���N�^
///
#define REGISTER_WITH_FACTORY( FactoryType, ObjectType, IDFunctorType ) \
template class FactoryType::Element<ObjectType, IDFunctorType>

BEGIN_EGEG

///
/// @class   Factory
/// @brief   �ėp�t�@�N�g��
///
/// @details �t�@�N�g���ւ̃I�u�W�F�N�g�̓o�^��REGISTER_WITH_FACTORY�}�N�����g�p���ĉ������B
///
/// @tparam BaseType     : �t�@�N�g���ɂ���Đ��������N���X�̊��N���X
/// @tparam CtorArgTypes : �I�u�W�F�N�g�̃R���X�g���N�^�ɓn�������^���X�g
///
template <class BaseType, class ...CtorArgTypes>
class Factory
{
private :
    class Creator
    {
    public :
        virtual std::unique_ptr<BaseType> create( CtorArgTypes&&... ) = 0;
    };

    ///
    /// @class  Element
    /// @brief  �v�f�̃N���G�C�^�[
    ///
    /// @tparam ElementType   : �v�f�N���X�^
    /// @tparam IDFunctorType : �N���X�^�ɑΉ�����ID��ԋp����t�@���N�^
    ///
    template <class ElementType, class IDFunctorType>
    class Element :
        public Creator
    {
    public :
        std::unique_ptr<BaseType> create( CtorArgTypes&& ...Args ) override
        {
            return std::make_unique<ElementType>(std::forward<CtorArgTypes>(Args)...);
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
    /// @brief  �N���X���t�@�N�g���ɂ�萶�������I�u�W�F�N�g�Ƃ��ēo�^
    ///
    /// @tparam ObjectType : �o�^����I�u�W�F�N�g�^
    ///
    /// @param[in] ID : �N���X�ƕR�Â���ID
    ///
    template <class ObjectType>
    static void registration( uint32_t ID )
    {
        if( creator_list_.find( ID ) == creator_list_.end() )
        { // ���ɓo�^����Ă���I�u�W�F�N�g�͂����Œe��
            // Attention : ���������蓖�Ă�����邽�߂ɂ����Ēe���Ă���B
            creator_list_.emplace( ID, new typename ObjectType::Element() );
        }
    }

    ///
    /// @brief   �I�u�W�F�N�g�̐���( ID�Ŏ��� )
    /// @details �o�^����Ă��Ȃ��N���X�ɂ��ẮAnullptr��ԋp���܂��B
    ///
    /// @param[in] ID   : ��������I�u�W�F�N�gID
    /// @param[in] Args : �R���X�g���N�^�ɓ]������������X�g
    ///
    /// @return ���������I�u�W�F�N�g
    ///
    static std::unique_ptr<BaseType> create( uint32_t ID, CtorArgTypes&& ...Args )
    {
        auto find = creator_list_.find( ID );
        if( find == creator_list_.end() )
        { // �����������o�^����Ă��Ȃ�
            return nullptr; 
        }
        else
        { // �������ĕԋp
            return find->second->create(std::forward<CtorArgTypes>(Args)...);
        }
    }

private :
    Factory() = default;
    static std::unordered_map<uint32_t, std::unique_ptr<Creator>> creator_list_;
};

template <class BaseType, class ...CtorArgTypes>
std::unordered_map<uint32_t, std::unique_ptr<typename Factory<BaseType, CtorArgTypes...>::Creator>> Factory<BaseType, CtorArgTypes...>::creator_list_;
template <class BaseType, class ...CtorArgTypes>
template <class ObjectType, class IDFunctorType>
typename Factory<BaseType, CtorArgTypes...>::template Element<ObjectType, IDFunctorType>::Registerer Factory<BaseType, CtorArgTypes...>::Element<ObjectType, IDFunctorType>::register_;

END_EGEG
#endif /// !INCLUDED_EGEG_FACTORY_HEADER_
/// EOF
