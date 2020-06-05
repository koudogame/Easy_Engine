///
/// @brief  move3d_component.hpp
/// @author 板場
///
#ifndef INCLUDED_EGEG_MOVE3D_COMPONENT_HEADER_
#define INCLUDED_EGEG_MOVE3D_COMPONENT_HEADER_

#include <functional>
#include "component3d.hpp"
#include "egeg_math.hpp"
#include "task.hpp"
#include "easing.hpp"

BEGIN_EGEG

///
/// @class Move3DComponent
/// @brief 3D用移動コンポーネント
///
class Move3DComponent :
    public Component3D
{
public :
    using AnimationFunction = std::function<float(float)>;
    enum class AnimationControl : uint8_t
    {
        kUnspecified,
        kNoStop,
        kOnce,
        kLoop,
        kBack,
        kLoopBack
    };

    Move3DComponent( Actor3D* Owner ) :
        Component3D( Owner )
    {}

    void move( float Speed, const Vector3D& Direction );
    void move( float StartSpeed, float EndSpeed, uint64_t TimeRequired, const Vector3D& Direction, const AnimationFunction& Animation = easing::linear, AnimationControl AnimationType = AnimationControl::kOnce );
    void move( const Vector3D& StartPoint, const Vector3D& EndPoint, uint64_t TimeRequired, const AnimationFunction& Animation = easing::linear, AnimationControl AnimationType = AnimationControl::kOnce );
    void stop();

    void update( uint64_t );
// override
    bool initialize() override;
    void finalize() override;

private :
    float calcCurrentTime( uint64_t );

    Task task_;
    Vector3D last_moved_;

    AnimationFunction animation_func_;
    AnimationControl animation_type_;
    bool is_speed_animated_;
    Vector3D start_point_;
    Vector3D direction_;
    float  start_speed_;
    float  displacement_speed_;
    uint64_t time_required_;
    float r_time_required_;
    int64_t time_elapsed_;
    bool is_back_;
};

END_EGEG
#endif /// !INCLUDED_EGEG_MOVE3D_COMPONENT_HEADER_
/// EOF
