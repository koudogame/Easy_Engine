///
/// @file   easy_engine.hpp
/// @author î¬èÍ
///
#ifndef INCLUDED_EGEG_EASY_ENGINE_HEADER_
#define INCLUDED_EGEG_EASY_ENGINE_HEADER_
#include "detailed_returnvalue.hpp"
#include "rendering_manager.hpp"
#include "job_scheduler.hpp"

BEGIN_EGEG

class Task;

///
/// @class  EasyEngine
/// @brief  ÉGÉìÉWÉìñ{ëÃ
///
class EasyEngine final
{
public :
    static DetailedReturnValue<bool> initialize();
    static void finalize();

    static HWND getWindowHandle() noexcept;
    static std::shared_ptr<RenderingManager> getRenderingManager() noexcept;
    static JobScheduler<Task>* getTaskManager() noexcept;

private :
    EasyEngine() = default;

    struct Impl;
    static std::unique_ptr<Impl> p_impl_;
};

END_EGEG
#endif /// !INCLUDED_EGEG_EASY_ENGINE_HEADER_
/// EOF
