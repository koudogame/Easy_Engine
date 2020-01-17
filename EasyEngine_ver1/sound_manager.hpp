///
/// @file    sound_manager.hpp
/// @author  板場
///          
/// @brief   サウンドマネージャー
/// @details シングルトンクラスです。アクセスにはinstance関数を使用してください。<br>
///          このクラスを使用して読み込んだサウンドは、必ずこのクラスで開放してください。
///
#ifndef INCLUDED_EGEG_SOUND_MANAGER_HEADER_
#define INCLUDED_EGEG_SOUND_MANAGER_HEADER_
#include "easy_engine.hpp"
#include "sound_loader.hpp"
BEGIN_EGEG
class SoundManager
{
public :
    ///
    /// @brief  インスタンスへのアクセス
    ///
    /// @return インスタンス
    ///
    static SoundManager* instance() { return instance_; }

    ///
    /// @brief  インスタンスの生成
    ///
    /// @param[in] Creator : 生成者
    /// @param[in] pLoader : 使用するサウンドローダー
    ///
    static void create( const EasyEngine& Creator, ISoundLoader* pLoader );
    ///
    /// @brief  インスタンスの破棄
    ///
    /// @param[in] Deleter : 破棄者
    ///
    static void destroy( const EasyEngine& Deleter );

private :
    SoundManager( ISoundLoader* );
    ~SoundManager();
    SoundManager( const SoundManager& ) = delete;
    SoundManager& operator=( const SoundManager& ) = delete;
    static SoundManager* instance_;

    ISoundLoader* p_loader_;    /// 使用するサウンドローダー
};
END_EGEG
#endif /// !INCLUDED_EGEG_SOUND_MANAGER_HEADER_
/// EOF
