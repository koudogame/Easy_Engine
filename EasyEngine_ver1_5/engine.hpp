///
/// @file   engine.hpp
/// @author ��
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
/// @brief �G���W��
///
class EasyEngine final
{
public :
    using TaskManagerType = JobScheduler<Job<void(uint64_t)>, 5U>;

    ///
    /// @brief ������
    ///
    /// @return true:�����@false:���s
    ///
    static DetailedReturnValue<bool> initialize();

    ///
    /// @brief �I��
    ///
    static void finalize();

    ///
    /// @brief �E�B���h�E�n���h���̎擾
    ///
    /// @return �E�B���h�E�n���h��
    ///
    static HWND getWindowHandle() noexcept { return window_handle_; }

    ///
    /// @brief �^�X�N�}�l�[�W���[�̎擾
    ///
    /// @return �^�X�N�}�l�[�W���[
    ///
    static TaskManagerType* getTaskManager() noexcept { return task_manager_.get(); }

    ///
    /// @brief ���̓f�o�C�X�}�l�[�W���[�̎擾
    ///
    /// @return ���̓f�o�C�X�}�l�[�W���[
    ///
    static InputDeviceManager* getInputDeviceManager() noexcept { return input_device_manager_.get(); }

    ///
    /// @brief  �`��}�l�[�W���[�̎擾
    ///
    /// @return �`��}�l�[�W���[
    ///
    static RenderingManager* getRenderingManager() noexcept { return rendering_manager_.get(); }

    ///
    /// @brief ���x���}�l�[�W���\�̎擾
    ///
    /// @return ���x���}�l�[�W���\
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
