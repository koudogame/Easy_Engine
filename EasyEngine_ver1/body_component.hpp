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
///
/// @def    DEF_FIRST_DISPATCH
/// @brief  �t�@�[�X�g�f�B�X�p�b�`���`���܂��B
///
#define DEG_FIRST_DISPATCH  bool isCollision( Actor* Other ) override { if( auto com = Other->getComponent<BodyComponent>() ) { return com->isCollision( this ); } return false; }

BEGIN_EGEG 
///
/// @class   BodyComponent
/// @details �Փ˗p�R���|�[�l���g<br>
///          �Փ˔���́A�_�u���f�B�X�p�b�`���g�p���čs���܂��B<br>
///          �t�@�[�X�g�f�B�X�p�b�`�֐��̓}�N�����g�p���Ē�`���ĉ������B<br>
///          �K�v�ɉ����āA��̓I�Ȍ^�Ƃ̏Փˏ�����ǉ����ĉ������B<br>
///          �Փ˔���֐��̃V�O�l�`���� bool isCollision( Type* )�ł��B
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
    /// @brief  �t�@�[�X�g�f�B�X�p�b�`
    ///
    /// @param[in] Other : �Փ˂𔻒肷��A�N�^�[
    ///
    /// @return �Փ˂���[ true ]�@�Փ˂Ȃ�[ false ]
    ///
    virtual bool isCollision( Actor* Other ) = 0;

    ///
    /// @brief  �s���Ȍ`�Ƃ̏Փ˔���
    ///
    /// @return ���[ false ]
    ///
    bool isCollision( BodyComponent* ) { return false; }
private :
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
