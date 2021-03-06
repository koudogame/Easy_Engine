///
/// @file   easy_engine.hpp
/// @author 板場
///
#ifndef INCLUDED_EGEG_EASY_ENGINE_HEADER_
#define INCLUDED_EGEG_EASY_ENGINE_HEADER_

#include "result.hpp"
#include "input_device_manager.hpp"
#include "rendering_manager.hpp"
#include "job_scheduler.hpp"
#include "level_manager.hpp"

BEGIN_EGEG

///
/// @class  EasyEngine
/// @brief  エンジン本体
///
class EasyEngine final
{
public :
    static DetailedResult<bool> initialize();
    static void finalize();

    static HWND getWindowHandle() noexcept;
    static InputDeviceManager* getInputDeviceManager() noexcept;
    static RenderingManager* getRenderingManager() noexcept;
    static JobScheduler<Job<void(uint64_t)>>* getTaskManager() noexcept;
    static LevelManager* getLevelManager() noexcept;

private :
    EasyEngine() = default;

    struct Impl;
    static std::unique_ptr<Impl> p_impl_;
};

END_EGEG
#endif /// !INCLUDED_EGEG_EASY_ENGINE_HEADER_
/// EOF
