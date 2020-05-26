///
/// @file   factory.hpp
/// @author ��
/// 
#ifndef INCLUDED_EGEG_FACTORY_HEADER_
#define INCLUDED_EGEG_FACTORY_HEADER_

#include <unordered_map>
#include <memory>
#include "egeg_def.hpp"


///
/// @def    REGISTER_WITH_FACTORY
/// @brief  �t�@�N�g���ɃI�u�W�F�N�g��o�^
///
/// @param[in] FactoryType  : �o�^����t�@�N�g��
/// @param[in] ObjectType   : �o�^����I�u�W�F�N�g�̌^
/// @param[in] KeyGenerator : �o�^����I�u�W�F�N�g�ɕR�Â���L�[
///
/// @note : �ÓI�����o�ϐ��̒�`���s���Ă���B
///
#define REGISTER_WITH_FACTORY( FactoryType, ObjectType, KeyGenerator ) \
template class FactoryType::ElementCreator<ObjectType, KeyGenerator>


BEGIN_EGEG

///
/// @class  Factory
/// @brief  �ėp�t�@�N�g��
///
/// @tparam KeyType      : �I�u�W�F�N�g�ƕR�Â���L�[�^
/// @tparam BaseType     : ���������I�u�W�F�N�g�������C���^�[�t�F�C�X�^
/// @tparam CtorArgTypes : �I�u�W�F�N�g�̃R���X�g���N�^�ɓn�������^���X�g
///
/// @details �C���X�^���X�����֎~���Ă��܂��B�����o�֐��͐ÓI�֐��ł��B                      <br>
///           �t�@�N�g�����g�p����ۂ̓e���v���[�g�̖����I�ȃC���X�^���X�����s���ĉ������B      <br>
///           �t�@�N�g���ւ̃I�u�W�F�N�g�̓o�^��REGISTER_WITH_FACTORY�}�N�����g�p���ĉ������B <br>
///           �g�p�� )                                                                  <br>
///             �e���v���[�g�̃C���X�^���X��                                               <br>
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
    /// @brief   �I�u�W�F�N�g�̐���
    /// @details �o�^����Ă��Ȃ��I�u�W�F�N�g�ɂ��ẮAnullptr�̕ԋp���s���B
    ///
    /// @param[in] Key  : ��������I�u�W�F�N�g�̃L�[
    /// @param[in] Args : �R���X�g���N�^�ɓn���������X�g
    ///
    template <class ...ArgTypes>
    static std::unique_ptr<BaseType> create( const KeyType& Key, ArgTypes&& ...Args )
    {
        auto find = creator_list_.find( Key );
        if( find == creator_list_.end() ) return nullptr;
        return find->second->create( std::forward<ArgTypes>(Args)... );
    }

    ///
    /// @brief  �N���X���t�@�N�g���ɂ�萶�������I�u�W�F�N�g�Ƃ��ēo�^
    ///
    /// @tparam CreatorType : �N���G�C�^�[�^
    /// @param[in] Key : �N���X�ƕR�Â���L�[
    ///
    template <class CreatorType, class KeyType_>
    static void registration( KeyType_&& Key )
    {
        if( creator_list_.find(Key) == creator_list_.end() )
        { // ���ɓo�^����I�u�W�F�N�g�͂����Œe��
            // note : �]�v�ȃ��������蓖�Ă�����邽��
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


///< �t�@�N�g���̃����o�ϐ���`
template <class KeyType, class BaseType, class ...CtorArgTypes>
std::unordered_map<KeyType, std::unique_ptr<typename Factory<KeyType, BaseType, CtorArgTypes...>::Creator>> Factory<KeyType, BaseType, CtorArgTypes...>::creator_list_{};
///< �G�������g�����҂̃����o�ϐ���`
template <class KeyType, class BaseType, class ...CtorArgTypes>
template <class ObjectType, class KeyGeneratorType>
typename Factory<KeyType, BaseType, CtorArgTypes...>::template ElementCreator<ObjectType, KeyGeneratorType>::Registerer Factory<KeyType, BaseType, CtorArgTypes...>::ElementCreator<ObjectType, KeyGeneratorType>::registerer_{};

END_EGEG
#endif /// !INCLUDED_EGEG_FACTORY_HEADER_
/// EOF
