///
/// @file   collision_space.hpp
/// @author 板場
///
#ifndef INCLUDED_EGEG_COLLISION_SPACE_HEADER_
#define INCLUDED_EGEG_COLLISION_SPACE_HEADER_
#include <unordered_map>
#include "collision_component.hpp"
#include "fullscan_spatial_division.hpp"
#include "job.hpp"
BEGIN_EGEG
///
/// @class   CollisionSpace
/// @brief   衝突空間クラス
///          
/// @details 衝突判定を行う空間のインターフェイスです。<br>
///          シングルトンクラスです。アクセスにはinstance関数を使用して下さい。
///
class CollisionSpace
{
public :
    ///
    /// @brief   空間分割クラス
    /// @details setSections関数でセクションの設定を行います。<br>
    ///          存在しうるセクションをすべて引数のコンテナに格納するモノとします。<br>
    ///          void setSections( std::vector<->* );<br>
    ///<br>
    ///          createID関数で形に対応したセクションIDの生成を行います。<br>
    ///          setSections関数で設定したセクション数 - 1を上限とします。<br>
    ///          uint32_t createID( const Shape* )
    ///
    using SpatialDivision = FullScanSpatialDivision;

    ///< デストラクタ
    ~CollisionSpace();

    ///
    /// @brief  インスタンスの取得
    ///
    /// @return インスタンス
    ///
    static CollisionSpace* instance() { static CollisionSpace i; return &i; }

    ///
    /// @brief  衝突判定
    ///
    /// @param[in] : ジョブとして登録するためのダミー
    ///
    void collision( uint64_t );

    ///
    /// @brief  空間への登録
    ///
    /// @param[in] pComponent : 登録するコンポーネントのアドレス
    ///
    void entry( CollisionComponent* pComponent );
    ///
    /// @brief  空間から削除
    ///
    /// @param[in] pComponent : 削除するコンポーネントのアドレス
    ///
    void exit( CollisionComponent* pComponent );

private :
    void judgeSectionAndSection( CollisionSection*, CollisionSection* );
    void judgeSameSection( CollisionSection* );
    CollisionSection* nextJudgeSection( CollisionSection* );

    std::vector<CollisionSection> sections_;
    Job job_;

    CollisionSpace();
    CollisionSpace( const CollisionSpace& ) = delete;
    CollisionSpace& operator=( const CollisionSpace& ) = delete;
};
END_EGEG
#endif /// !INCLUDED_EGEG_COLLISION_SPACE_HEADER_
/// EOF
