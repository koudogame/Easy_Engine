///
/// @file   level.hpp
/// @author ��
///
#ifndef INCLUDED_EGEG_LEVEL_HEADER_
#define INCLUDED_EGEG_LEVEL_HEADER_

#include <wrl.h>
#include <d3d11.h>
#include "non_copyable.hpp"
#include "level_manager.hpp"
#include "factory.hpp"
#include "name.hpp"
#include "scene.hpp"
#include "actor.hpp"


BEGIN_EGEG

///
/// @def     REGISTER_LEVEL
/// @brief   ���x�����t�@�N�g���ɓo�^
///
/// @param[in] LevelType : �o�^���郌�x���^
/// @param[in] LevelName : ���x���̖��O( .lvl�t�@�C���Ŏg�p���܂��B)
///
/// @details level.hpp��86�s�ڂɁALevel�̓o�^���s���Ă��܂��B�Q�l�ɂ��ĉ������B
///
#define REGISTER_LEVEL( LevelType, LevelName ) \
static constexpr const char LevelType ## Name[] = #LevelName; \
REGISTER_WITH_FACTORY( LevelFactory, LevelType, Name<LevelType ## Name> )


///
/// @class Level
/// @brief ���x��
///
class Level :
    NonCopyable<Level>
{
public :
    virtual ~Level() = default;
    ///
    /// @brief ������
    ///
    /// @param[in] LevelDataStream
    ///
    /// @return true:�����@false:���s
    ///
    virtual bool initialize( std::istream& LevelDataStream );

    ///
    /// @brief �I��
    ///
    virtual void finalize();

    ///
    /// @brief �V�[���`��
    ///
    void render( uint64_t );

    ///
    /// @brief �V�[���̎擾
    ///
    /// @return �`��Ώۂ̃V�[��
    ///
    Scene* getScene() noexcept{ return &scene_; }

protected :
    bool initScene();
    bool loadActor( std::istream& );

    Microsoft::WRL::ComPtr<IDXGISwapChain> swap_chain_;
    Task task_;
    Scene scene_;
    std::vector<std::unique_ptr<Actor>> actors_;
};


///< ���x���t�@�N�g���̐錾
template class Factory<std::string, Level>;
using LevelFactory = Factory<std::string, Level>;


///< ���x���̓o�^
REGISTER_LEVEL( Level, Default );

END_EGEG
#endif /// !INCLUDED_EGEG_LEVEL_HEADER_
/// EOF
