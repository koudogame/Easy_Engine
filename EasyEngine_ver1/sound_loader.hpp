///
/// @file   sound_loader.hpp
/// @author 板場
///
#ifndef INCLUDED_EGEG_SOUND_LOADER_HEADER_
#define INCLUDED_EGEG_SOUND_LOADER_HEADER_
#include <string>
#include "sound.hpp"
BEGIN_EGEG
///
/// @class ISoundLoader
///
/// @brief  サウンドローダー
///
class ISoundLoader
{
public :
    ///
    /// @brief  サウンドデータの読み込み
    ///
    /// @param[in] FilePath : 読み込むサウンドのファイルパス
    /// @param[in] ppSound : 読み込んだサウンドを保持するインターフェイス
    ///
    /// @return 読み込み成功[ true ] 読み込み失敗[ false ]
    ///
    virtual bool load( const std::wstring& FilePath, ISound** ppSound ) = 0;

    virtual ~ISoundLoader() = default;
};
END_EGEG
#endif /// !INCLUDED_EGEG_SOUND_LOADER_HEADER_
/// EOF
