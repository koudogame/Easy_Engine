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
///
/// @class   BodyComponent
/// @brief   �Փ˔���p�R���|�[�l���g
///
/// @details �Փ˗p�R���|�[�l���g<br>
///          �Փ˔���́A�_�u���f�B�X�p�b�`���g�p���čs���܂��B
///
class BodyComponent :
    public Component
{
public :
    ///< ID�̎擾
    static uint32_t getID() { return UID<BodyComponent>::getID(); }

    virtual ~BodyComponent() = default;

    ///
    /// @brief  �R���X�g���N�^
    ///
    /// @param[in] Owner : �I�[�i�[
    ///
    BodyComponent( Actor* Owner ) : Component( Owner ) {}

    ///
    /// @brief  �A�N�^�[�Ƃ̏Փ˔���
    ///
    /// @param[in] Other : ������s���A�N�^�[
    ///
    /// @return �Փ˂���[ true ]�@�Փ˂Ȃ�[ false ]
    ///
    virtual bool isCollided( Actor* Other );

    ///
    /// @brief   �Փˌ㏈���̒ǉ�
    /// @details ID�ɑΉ��������������ɂ���ꍇ�͏㏑��
    ///
    /// @tparam ActorType : �I�[�i�[�̌^(�ȗ���)
    ///
    /// @param[in] OtherID   : �����ɑΉ�����A�N�^�[��ID
    /// @param[in] pCallBack : �Փˎ��ɌĂяo�����֐��̃A�h���X
    ///
    template <typename ActorType>
    void postCollision( uint32_t OtherID, void(ActorType::*pCallBack)(Actor*) );

protected :
    std::unordered_map<uint32_t, std::function<void(Actor*)> > post_collision_;
};

///< �Փˌ㏈���̒ǉ�
template <typename ActorType>
void BodyComponent::postCollision( uint32_t OtherID, void(ActorType::*pCallBack)(Actor*) )
{
    post_collision_.erase( OtherID );
    post_collision_.emplace( 
        OtherID,
        std::bind<void(Actor*)>(pCallBack, owner_, std::placeholders::_1)
    );
}
END_EGEG
#endif /// !INCLUDED_EGEG_BODY_COMPONENT_HEADER_
/// EOF
