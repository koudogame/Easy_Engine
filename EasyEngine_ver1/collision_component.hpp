///
/// @file   body_component.hpp
/// @author ��
///
#ifndef INCLUDED_EGEG_BODY_COMPONENT_HEADER_
#define INCLUDED_EGEG_BODY_COMPONENT_HEADER_
#include <functional>
#include <unordered_map>
#include "component.hpp"
#include "uid.hpp"
#include "rectangle.hpp"
#include "circle.hpp"
#include "line.hpp"

BEGIN_EGEG
class CollisionSection;

///
/// @class   CollisionComponent
/// @brief   �Փ˔���p�R���|�[�l���g
///
/// @details �Փ˗p�R���|�[�l���g<br>
///          �Փ˔���́A�_�u���f�B�X�p�b�`���g�p���čs���܂��B
///
class CollisionComponent :
    public Component
{
public :
    ///< ID�̎擾
    static uint32_t getID() { return UID<CollisionComponent>::getID(); }

    virtual ~CollisionComponent() = default;

    ///
    /// @brief  �R���X�g���N�^
    ///
    /// @param[in] pOwner : �I�[�i�[
    ///
    CollisionComponent( Actor* pOwner ) : Component( pOwner ) {}

    ///
    /// @brief  �Փ˂�ʒm
    ///
    /// @param[in] pOther : �Փ˂����o�����R���|�[�l���g
    ///
    virtual void notifyCollision( const CollisionComponent* pOther );

    ///
    /// @brief   �Փˌ㏈���̐ݒ�
    /// @details ID�ɑΉ��������������ɂ���ꍇ�͏㏑�����܂��B
    ///
    /// @tparam ActorType : �I�[�i�[�̌^(�ȗ���)
    ///
    /// @param[in] OtherID   : �����ɑΉ�����A�N�^�[��ID
    /// @param[in] pOwner    : �֐��̎��s��
    /// @param[in] pCallBack : �Փˎ��ɌĂяo�����֐��̃A�h���X
    ///
    template <typename ActorType>
    void setPostCollision( uint32_t OtherID, ActorType* pOwner, void(ActorType::*pCallBack)(Actor*) );

    ///
    /// @brief  �`�̎擾
    ///
    /// @return �I�[�i�[�̌`
    ///
    const Shape* getShape() const { return owner_->getShape(); }

    ///
    /// @brief  �����Z�N�V�����̐ݒ�
    ///
    /// @param[in] pSection : �Z�N�V����
    ///
    void setBelongSection( CollisionSection* pSection ) { section_ = pSection; }
    ///
    /// @brief  �����Z�N�V�����̎擾
    ///
    /// @return �����Z�N�V����
    ///
    CollisionSection* getBelongSection() const { return section_; }

/*-----------------------------------------------------------------*/
// Component
/*-----------------------------------------------------------------*/
    bool initialize() override;
    void finalize() override;

protected :
    std::unordered_map<uint32_t, std::function<void(Actor*)> > post_collision_;

private :
    CollisionSection* section_ = nullptr;   /// ���g�̏��������ԃZ�N�V����
};

///< �Փˌ㏈���̒ǉ�
template <typename ActorType>
void CollisionComponent::setPostCollision( uint32_t OtherID, ActorType* pOwner, void(ActorType::*pCallBack)(Actor*) )
{
    post_collision_.erase( OtherID );
    post_collision_.emplace( 
        OtherID,
        std::bind(pCallBack, pOwner, std::placeholders::_1)
    );
}
END_EGEG
#endif /// !INCLUDED_EGEG_BODY_COMPONENT_HEADER_
/// EOF
