///
/// @file   engine.hpp
/// @author 板場
///
#ifndef INCLUDED_EGEG_ENGINE_HEADER_
#define INCLUDED_EGEG_ENGINE_HEADER_

#include <memory>
#include <Windows.h>
#include "return_value.hpp"
#include "job_scheduler.hpp"
#include "input_device_manager.hpp"
#include "rendering_manager.hpp"
#include "level_manager.hpp"

BEGIN_EGEG

///
/// @class EasyEngine
/// @brief エンジン
///
class EasyEngine final
{
public :
    using TaskManagerType = JobScheduler<Job<void(uint64_t)>, 5U>;

    ///
    /// @brief 初期化
    ///
    /// @return true:成功　false:失敗
    ///
    static DetailedReturnValue<bool> initialize();

    ///
    /// @brief 終了
    ///
    static void finalize();

    ///
    /// @brief ウィンドウハンドルの取得
    ///
    /// @return ウィンドウハンドル
    ///
    static HWND getWindowHandle() noexcept { return window_handle_; }

    ///
    /// @brief タスクマネージャーの取得
    ///
    /// @return タスクマネージャー
    ///
    static TaskManagerType* getTaskManager() noexcept { return task_manager_.get(); }

    ///
    /// @brief 入力デバイスマネージャーの取得
    ///
    /// @return 入力デバイスマネージャー
    ///
    static InputDeviceManager* getInputDeviceManager() noexcept { return input_device_manager_.get(); }

    ///
    /// @brief  描画マネージャーの取得
    ///
    /// @return 描画マネージャー
    ///
    static RenderingManager* getRenderingManager() noexcept { return rendering_manager_.get(); }

    ///
    /// @brief レベルマネージャ―の取得
    ///
    /// @return レベルマネージャ―
    ///
    static LevelManager* getLevelManager() noexcept { return level_manager_.get(); }

private :
    EasyEngine();
    static DetailedReturnValue<bool> initializeWindow();
    static DetailedReturnValue<bool> initializeManager();

    static HWND window_handle_;
    static std::unique_ptr<TaskManagerType> task_manager_;
    static std::unique_ptr<InputDeviceManager> input_device_manager_;
    static std::unique_ptr<RenderingManager> rendering_manager_;
    static std::unique_ptr<LevelManager> level_manager_;
    static Level level_;
};

END_EGEG
#endif /// !INCLUDED_EGEG_ENGINE_HEADER_
/// EOF
