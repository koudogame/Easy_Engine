///
/// @file   actor.hpp
/// @author ��
/// 
#ifndef INCLUDED_EGEG_ACTOR_HEADER_
#define INCLUDED_EGEG_ACTOR_HEADER_

#include <cstdint>
#include <unordered_map>
#include <memory>
#include <DirectXMath.h>
#include "factory.hpp"
#include "name.hpp"
#include "id.hpp"

BEGIN_EGEG

class Level;     ///< ���x���O���錾( �z�Q�Ɖ�� )
class Component; ///< �R���|�[�l���g�O���錾( �z�Q�Ɖ�� )


///
/// @def    REGISTER_ACTOR
/// @brief  �A�N�^�[���t�@�N�g���ɓo�^
///
/// @param[in] ActorType : �o�^����A�N�^�[�^
/// @param[in] ActorName : �A�N�^�[�̖��O( .lvl�t�@�C���Ŏg�p���܂��B)
///
#define REGISTER_ACTOR( ActorType, ActorName ) \
static constexpr const char ActorType ## Name[] = #ActorName; \
REGISTER_WITH_FACTORY( ActorFactory, ActorType, Name<ActorType ## Name> )


///
/// @class Actor
/// @brief �I�u�W�F�N�g�P��
///
class Actor
{
public :
    ///
    /// @brief �R���X�g���N�^
    ///
    /// @param[in] ID : �A�N�^�[ID
    ///
    Actor( uint32_t ID ) noexcept :
        id_{ ID },
        affiliation_level_{ nullptr }
    {}
    virtual ~Actor() = default;

    ///
    /// @brief ������
    ///
    /// @param[in] DataStream : �f�[�^�𒊏o����X�g���[��
    ///
    /// @return true:�����@false:���s
    ///
    virtual bool initialize( std::istream& DataStream ) = 0;

    ///
    /// @brief �I��
    ///
    virtual void finalize() = 0;


    ///
    /// @brief �A�N�^�[ID�̎擾
    ///
    /// @return �A�N�^�[ID
    ///
    uint32_t getID() const noexcept { return id_; }

    ///
    /// @brief �����惌�x���̎擾
    ///
    /// @return �����惌�x��
    ///
    Level* getAffiliationLevel() const noexcept { return affiliation_level_; }

    ///
    /// @brief �R���|�[�l���g�̎擾
    ///
    /// @tparam ComponentType : �擾����R���|�[�l���g�̌^
    ///
    /// @return �R���|�[�l���g
    ///
    /// @details �Ή�����R���|�[�l���g��ێ����Ă��Ȃ��ꍇ�Anullptr��ԋp���܂��B
    ///
    template <class ComponentType>
    ComponentType* getComponent() const;

    ///
    /// @brief �R���|�[�l���g�̍폜
    ///
    /// @tparam ComponentType : �폜����R���|�[�l���g�̌^
    ///
    /// @details �Ή�����R���|�[�l���g��ێ����Ă��Ȃ��ꍇ�A�����s���܂���B
    ///
    template <class ComponentType>
    void removeComponent() noexcept;


    ///
    /// @brief ���[���h�ϊ��s����v�Z
    ///
    /// @return ���[���h�ϊ��s��
    ///
    /// @details Actor2D, Actor3D�ɂ���Ď�������܂��B
    ///
    virtual DirectX::XMMATRIX calcWorldMatrix() const = 0;

    ///
    /// @brief �������郌�x���̃Z�b�g
    ///
    /// @param[in] Affiliation : �����惌�x��
    ///
    /// @details ���x���ɂ��Ăяo�����֐��ł��B
    ///
    void setAffiliationLevel( Level& Affiliation ) noexcept { affiliation_level_ = &Affiliation;}
protected :
    ///< �R���|�[�l���g�̃f���[�^�[
    struct ComponentDeleter
    {
        void operator()( Component* ) const;
    };
    std::unordered_map<uint32_t, std::unique_ptr<Component, ComponentDeleter>> components_;
private :
    uint32_t id_;
    Level* affiliation_level_;
};


///< �A�N�^�[�t�@�N�g���̑O���錾
template class Factory<std::string, Actor>;
using ActorFactory = Factory<std::string, Actor>;


///< �R���|�[�l���g�̎擾�֐���`
template <class ComponentType>
ComponentType* Actor::getComponent() const
{
    auto find_itr = components_.find( TypeID<ComponentType>{} );
    if( find_itr == components_.end() ) return nullptr;

    return static_cast<ComponentType*>( find_itr->second.get() );
}

///< �R���|�[�l���g�̍폜�֐���`
template <class ComponentType>
void Actor::removeComponent() noexcept
{
    components_.erase( TypeID<ComponentType>{} );
}


END_EGEG
#endif /// !INCLUDED_EGEG_ACTOR_HEADER_
/// EOF
