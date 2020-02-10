///
/// @file   entry_scene.hpp
/// @author 板場
///
#ifndef INCLUDED_EGEG_ENTRY_SCENE_HEADER_
#define INCLUDED_EGEG_ENTRY_SCENE_HEADER_
#include "scene.hpp"
#include "job.hpp"
BEGIN_EGEG
///
/// @class EntryScene
///
/// @brief  ゲーム開始時に実行されるシーン
///
class EntryScene :
    public Scene
{
public :
/*-----------------------------------------------------------------*/
// Scene
/*-----------------------------------------------------------------*/
    bool initialize() override;
    void finalize() override;
    void update( uint64_t ) override;
private :
    Job job_;
};
END_EGEG
#endif /// !INCLUDED_EGEG_ENTRY_SCENE_HEADER_
/// EOF
