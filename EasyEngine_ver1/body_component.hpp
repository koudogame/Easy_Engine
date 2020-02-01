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

    ///
    /// @brief  �R���X�g���N�^
    ///
    /// @param[in] Owner : �I�[�i�[
    ///
    BodyComponent( Actor* Owner ) : Component( Owner ) {}


    ///
    /// @brief   �Փˌ㏈���̒ǉ�
    /// @details ���ɂ���ꍇ�͏㏑��
    ///
    /// @tparam ActorType : �I�[�i�[�̌^(�ȗ���)
    ///
    /// @param[in] OtherID   : �����ɑΉ�����A�N�^�[��ID
    /// @param[in] pCallBack : �Փˎ��ɌĂяo����鏈��
    ///
    template <typename ActorType>
    void postCollision( uint32_t OtherID, void(ActorType::*pCallBack)(Actor*) );

    ///
    /// @brief   �t�@�[�X�g�f�B�X�p�b�`
    /// @details �����́A�A�N�^�[��BodyComponent��isCollision�֐��ɁA��̓I�Ȍ`��n���ČĂяo���܂��B<br>
    ///          �Փ˂����o�����ꍇ�A�Փˌ�̏������Ăяo����܂��B
    ///
    /// @param[in] Other : �Փ˂𔻒肷��A�N�^�[
    ///
    /// @return �Փ˂���[ true ]�@�Փ˂Ȃ�[ false ]
    ///
    virtual bool isCollided( Actor* Other ) = 0;
    ///
    /// @brief  ��`�Ƃ̏Փ˔���
    ///
    /// @param[in] Rectangle : �Փ˂𔻒肷���`
    ///
    /// @return �Փ˂���[ true ]�@�Փ˂Ȃ�[ false ]
    ///
    virtual bool isCollided( const Rectangle& Rectangle ) = 0;
    ///
    /// @brief  �~�`�Ƃ̏Փ˔���
    ///
    /// @param[in] Circle : �Փ˂𔻒肷��~�`
    ///
    /// @return �Փ˂���[ true ]�@�Փ˂Ȃ�[ false ]
    ///
    virtual bool isCollided( const Circle& Circle ) = 0;
    ///
    /// @brief  �����Ƃ̏Փ˔���
    ///
    /// @param[in] Line : �Փ˂𔻒肷�����
    ///
    /// @return �Փ˂���[ true ]�@�Փ˂Ȃ�[ false ]
    ///
    virtual bool isCollided( const Line& Line ) = 0;

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
