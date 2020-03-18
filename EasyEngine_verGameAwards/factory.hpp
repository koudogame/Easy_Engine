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
/// @details ���̃N���X�ɂ�萶�������N���X�́AFactory<Base>::Element<T>���p�����ĉ������B<br>
///          Factory<Base>::Element<T> ��T�͂��̃N���X���g�̌^���w�肵�܂��B
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
    ///< �t�@�N�g���ɂ�萶�������N���X
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
    /// @brief  �N���X���t�@�N�g���ɂ�萶�������I�u�W�F�N�g�Ƃ��ēo�^
    ///
    /// @param[in] ID : �N���X�ƕR�Â���ID
    ///
    template <class Elem>
    static void Register( uint32_t ID )
    {
        if( creator_list_.find( ID ) == creator_list_.end() )
        { // ���ɓo�^����Ă���I�u�W�F�N�g�͂����Œe��
            // Attention : ���������蓖�Ă�����邽�߂ɂ����Ēe���Ă���B
            creator_list_.emplace( ID, new Element<Elem>() );
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
    static std::unique_ptr<Base> create( uint32_t ID )
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
    static std::unordered_map<uint32_t, std::unique_ptr<Creator>> creator_list_;
};

template <class Base>
std::unordered_map<uint32_t, std::unique_ptr<typename Factory<Base>::Creator>> Factory<Base>::creator_list_;
END_EGEG
#endif /// !INCLUDED_EGEG_FACTORY_HEADER_
/// EOF
