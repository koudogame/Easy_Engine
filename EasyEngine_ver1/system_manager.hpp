///
/// @file    system_manager.hpp
/// @author  板場
///          
/// @brief   システムマネージャー
/// @details シングルトンクラスです。アクセスにはinstance関数を使用して下さい。
///
#ifndef INCLUDED_EGEG_SYSTEM_MANAGER_HEADER_
#define INCLUDED_EGEG_SYSTEM_MANAGER_HEADER_
#include "easy_engine.hpp"
#include "platform.hpp"
BEGIN_EGEG
class SystemManager
{
public :
    ///
    /// @brief  インスタンスへのアクセス
    ///
    /// @return インスタンス
    ///
    static SystemManager* instance() { return instance_; }

    ///
    /// @brief  ダイアログボックスの表示
    ///
    /// @param[in] Message : 表示するメッセージ
    ///
    void showDialogBox( const std::string& Message );

    ///
    /// @brief  インスタンスの生成
    ///
    /// @param[in] Creator : 生成者
    /// @param[in] pPlatform : 使用するプラットフォーム
    ///
    static void create( const EasyEngine& Creator, IPlatform* pPlatform );
    ///
    /// @brief  インスタンスの破棄
    ///
    /// @param[in] Deleter : 破棄者
    ///
    static void destroy( const EasyEngine& Deleter );

    SystemManager( const SystemManager& ) = delete;
    SystemManager& operator=( const SystemManager& ) = delete;
private :
    SystemManager( IPlatform* );
    ~SystemManager();
    static SystemManager* instance_;
    IPlatform* p_platform_;
};
END_EGEG
#endif /// !INCLUDED_EGEG_SYSTEM_MANAGER_HEADER_
/// EOF
