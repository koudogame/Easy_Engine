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

BEGIN_EGEG
///
/// @class   Factory
/// @brief   �ėp�t�@�N�g��
/// @details ���̃N���X�ɂ�萶�������N���X�́AFactory<BaseType>::Element<T, ID>���p�����ĉ������B<br>
///          Factory<BaseType>::Element<T, ID> ��T�͂��̃N���X���g�̌^���w�肵�܂��BID�̓I�u�W�F�N�g�ƕR�Â���ID�t�@���N�^���w�肵�܂��B<br>
///          ���̃t�@�N�g���ɂ�萶�������N���X�́A�K���������󂯎��Ȃ��R���X�g���N�^���`���ĉ������B
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
    /// @class  ���̃t�@�N�g���̗v�f�ł��邱�Ƃ�����
    ///
    /// @tparam DerivedType   : �p����̃N���X�^
    /// @tparam IDFunctorType : �N���X�^�ɑΉ�����ID��ԋp����t�@���N�^
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
    /// @brief   �I�u�W�F�N�g�̐���
    /// @details �o�^����Ă��Ȃ��N���X�ɂ��ẮAnullptr��ԋp���܂��B
    ///
    /// @param[in] ID : ��������I�u�W�F�N�gID
    ///
    /// @return ���������I�u�W�F�N�g
    ///
    static std::unique_ptr<BaseType> create( uint32_t ID )
    {
        auto find = creator_list_.find( ID );
        if( find == creator_list_.end() )
        { // �����������o�^����Ă��Ȃ��B
            return nullptr; 
        }
        else
        { // �������ĕԋp
            return find->second->create();
        }
    }

private :
    Factory() = default;
    static std::unordered_map<uint32_t, std::unique_ptr<Creator>> creator_list_;
};

///
/// @def    REGISTER_WITH_FACTORY
/// @brief  �t�@�N�g���ɃI�u�W�F�N�g��o�^
///
/// @param[in] BaseType      : �t�@�N�g��������������N���X�^��
/// @param[in] ObjectType    : �t�@�N�g���ɓo�^����N���X�^��
/// @param[in] IDFunctorType : �o�^����N���X�ɑΉ�������ID�t�@���N�^
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
