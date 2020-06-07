///
/// @file   level_node.hpp
/// @author ��
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

BEGIN_EGEG

class Level;
class LevelWorld;
class LevelScene;
class LevelSpace;
class Component;

///
/// @class  LevelNode
/// @brief  ���x���m�[�h
///
/// @details ���̃N���X�𒼐ڌp�������m�[�h�́A <br>
///          static constexpr NodeType �^�� kNodeType ���`���Ă��������B
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

    virtual ~LevelNode() = default;

    ///
    /// @brief  ������
    /// 
    /// @param[in] DataStream : �����f�[�^�X�g���[��
    ///
    /// @return true:���� �@false:���s
    ///
    virtual bool initialize( std::istream& DataStream ) = 0;
    ///
    /// @brief  �I��
    ///
    virtual void finalize() = 0;

    ///
    /// @brief  �C���X�^���X�̃m�[�h�^���擾
    ///
    /// @return �m�[�h�^
    ///
    virtual NodeType getNodeType() const noexcept = 0;


    ///
    /// @brief  �������郌�x���̃Z�b�g
    ///
    /// @param[in] Level : ���x��
    ///
    void setLevel( Level* Level ) noexcept { level_ = Level; }
    ///
    /// @brief  �������郌�x���̎擾
    ///
    /// @return ���x��
    ///
    Level* getLevel() const noexcept { return level_; }

    ///
    /// @brief  �e�m�[�h�̃Z�b�g
    ///
    /// @param[in] Parent : �e�m�[�h
    ///
    void setParent( LevelNode* Parent ) noexcept { parent_ = Parent; }
    ///
    /// @brief  �e�m�[�h�̎擾
    ///
    /// @return �e�m�[�h
    ///
    LevelNode* getParent() const noexcept { return parent_; }

    ///
    /// @brief     �q�m�[�h�̒ǉ�
    ///
    /// @param[in] Child : �q�m�[�h
    ///
    /// @details   �ǉ����������Ŋi�[����Ă����܂��B
    ///
    void addChild( LevelNode* Child ) { childs_.push_back(Child); }
    ///
    /// @brief     �q�m�[�h�̎擾
    /// 
    /// @param[in] �擪����̃C���f�b�N�X
    ///
    /// @return    �C���f�b�N�X�ɑΉ������q�m�[�h
    ///
    /// @details   �C���f�b�N�X���q�m�[�h�̐���葽���ꍇ�Anullptr��ԋp���܂��B
    ///
    LevelNode* getChild( size_t Index=0 ) const noexcept { return Index<childs_.size() ? childs_[Index] : nullptr; }
    ///
    /// @brief     �q�m�[�h�̎擾
    ///
    /// @tparam    NodeType_ : �擾����m�[�h�̌^
    /// @param[in] Index     : �C���f�b�N�X
    ///
    /// @return    �C���f�b�N�X�ɑΉ������q�m�[�h
    ///
    /// @details   �C���f�b�N�X�͐擪����̃C���f�b�N�X�ł͂Ȃ��A�Ή������^�̒��̃I�t�Z�b�g�ł��B
    ///
    template <class NodeType_>
    NodeType_* getChild( size_t Index=0 ) const noexcept;
    ///
    /// @brief     �q�m�[�h�̍폜
    ///
    /// @param[in] Child : �폜����q�m�[�h
    ///
    void removeChild( LevelNode* Child );

    ///
    /// @brief     �R���|�[�l���g�̒ǉ�
    ///
    /// @tparam    ComponentType : �ǉ�����R���|�[�l���g�̌^
    ///
    /// @return    �ǉ������R���|�[�l���g�^
    ///
    /// @details   �ǉ��Ɏ��s�����ꍇ�Anullptr��ԋp���܂��B
    ///
    template <class ComponentType>
    ComponentType* addComponent();
    ///
    /// @brief     �R���|�[�l���g�̎擾
    ///
    /// @tparam    ComponentType : �擾����R���|�[�l���g�̌^
    ///
    /// @return    �Ή������R���|�[�l���g
    ///
    /// @details   �Ή������R���|�[�l���g��ێ����Ă��Ȃ��ꍇ�Anullptr��ԋp���܂��B
    ///
    template <class ComponentType>
    ComponentType* getComponent() const;

    ///
    /// @brief     �q�m�[�h�ɑ΂���ċA�I�ȏ����̎��s
    ///
    /// @tparam    FunctionType : �Ăяo���֐��̃��b�p�[
    /// @param[in] Function     : �֐��I�u�W�F�N�g
    /// @param[in] Args...      : �Ăяo���֐��ɓn���������X�g( �������ȍ~ )
    ///
    /// @details   �Ăяo���֐��́A <br>
    ///            �߂�l�@ void       : �q�m�[�h�����[�v����̂Ŗ߂�l�͈Ӗ����Ȃ� <br>
    ///            ������ LevelNode* :  �����̑ΏۂƂȂ�q�m�[�h <br>
    ///            �ȍ~�C�ӂ̈���  �@�ł��B
    ///
    template <class FunctionType, class ...ArgTypes>
    void forChild( FunctionType Function, ArgTypes ...Args );

private :
    ///< �R���|�[�l���g�̃f���[�^�[
    struct ComponentDeleter
    {
        void operator()( Component* ) const;
    };

    Level* level_ = nullptr;
    LevelNode* parent_ = nullptr;
    std::vector<LevelNode*> childs_;
    std::unordered_map<uint32_t, std::unique_ptr<Component, ComponentDeleter>> components_;
};


// �q�m�[�h�̎擾�֐�( �^�w�� )
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


// �R���|�[�l���g�̒ǉ��֐�
template <class ComponentType>
ComponentType* LevelNode::addComponent()
{
#ifdef _DEBUG
    assert( getComponent<ComponentType>()==nullptr &&
            "�R���|�[�l���g�̑��d�o�^�͂ł��܂���" );
#endif
    auto component = std::unique_ptr<ComponentType, ComponentDeleter>
        { new ComponentType{this}, ComponentDeleter{} };
    if( !component->initialize() ) { return nullptr; }

    auto* ptr = component.get();
    components_.emplace( TypeID<ComponentType>{}, std::move(component) );

    return ptr;
}


// �R���|�[�l���g�̎擾�֐�
template <class ComponentType>
ComponentType* LevelNode::getComponent() const
{
    auto find_itr = components_.find( TypeID<ComponentType>{} );
    if( find_itr==components_.end() ) return nullptr;

    return static_cast<ComponentType*>( find_itr->second.get() );
}


// �q�m�[�h�ɑ΂���ċA�I�ȏ����̎��s
template <class FunctionType, class ...ArgTypes>
void LevelNode::forChild( FunctionType F, ArgTypes ...Args )
{
    for( auto& child : childs_ )
    {
        F( child, Args );
    }
}


// �t�@�N�g�����`
template class Factory<uint32_t, LevelNode>;
using LevelNodeFactory = Factory<uint32_t, LevelNode>;

END_EGEG
#endif /// !INCLUDED_EGEG_LEVEL_NODE_HEADER_
/// EOF
