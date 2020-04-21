///
/// @file   body.hpp
/// @author 板場
///
#ifndef INCLUDED_EGEG_BODY3D_COMPONENT_HEADER_
#define INCLUDED_EGEG_BODY3D_COMPONENT_HEADER_

#include <functional>
#include "component3d.hpp"
#include "sphere.hpp"
#include "cuboid.hpp"
#include "line3d.hpp"

BEGIN_EGEG
namespace component {

class SphereBody;
class CuboidBody;
class Line3DBody;

///< Body3D共通の基底クラス
class Body3D :
    public Component3D
{
public :
    static uint32_t getID() noexcept { return ComponentID::kBody3D; }

    Body3D( Actor3D* Owner ) :
        Component3D( Owner )
    {
    }

    template <class OwnerType, class FunctionType>
    void setCollisionCallback( OwnerType* Owner, FunctionType Function ) { collision_enter_ = std::bind(Owner, Function, std::placeholders::_1); }
    void collisionEnter( Actor3D* Other ) const { if( collision_enter_ ) collision_enter_( Other ); }


    virtual bool isCollided( const Body3D* ) const = 0;
    virtual bool isCollided( const SphereBody& ) const = 0;
    virtual bool isCollided( const CuboidBody& ) const = 0;
    virtual bool isCollided( const Line3DBody& ) const = 0;

protected :
    std::function<void(Actor3D*)> collision_enter_;
};

///
/// @class  SphereBody
/// @brief  ボディ「球」
///
class SphereBody :
    public Body3D
{
public :
    SphereBody( Actor3D* Owner ) :
        Body3D( Owner )
    {
    }

    void setShape( const EGEG Sphere& Shape ) noexcept { shape_ = Shape; }
    const EGEG Sphere& getShape() const noexcept { return shape_; }

// overrides
    bool isCollided( const Body3D* Other ) const override { return Other->isCollided(*this); }
    bool isCollided( const SphereBody& Other ) const override { return false; }
    bool isCollided( const CuboidBody& Other ) const override { return false; }
    bool isCollided( const Line3DBody& Other ) const override { return false; }

    bool initialize() override;
    void finalize() override;

private :
     EGEG Sphere shape_;
};

///
/// @class  CuboidBody
/// @brief  ボディ「直方体」
///
class CuboidBody :
    public Body3D
{
public :
    CuboidBody( Actor3D* Owner ) :
        Body3D( Owner )
    {
    }
    
    void setShape( const EGEG Cuboid& Shape ) noexcept { shape_ = Shape; }
    const EGEG Cuboid& getShape() const noexcept { return shape_; }

// overrides
    bool isCollided( const Body3D* Other ) const override { return Other->isCollided(this); }
    bool isCollided( const SphereBody& Other ) const override { return false; }
    bool isCollided( const CuboidBody& Other ) const override { return false; }
    bool isCollided( const Line3DBody& Other ) const override { return false; }

    bool initialize() override;
    void finalize() override;

private :
    EGEG Cuboid shape_;
};

///
/// @class  Line3DBody
/// @brief  ボディ「線分(3D)」
///
class Line3DBody :
    public Body3D
{
public :
    Line3DBody( Actor3D* Owner ) :
        Body3D( Owner )
    {
    }

    void setShape( const EGEG Line3D& Shape ) noexcept { shape_ = Shape; }
    const EGEG Line3D& getShape() const noexcept { return shape_; }

// overrides
    bool isCollided( const Body3D* Other ) const override { return Other->isCollided(this); }
    bool isCollided( const SphereBody& Other ) const override { return false; }
    bool isCollided( const CuboidBody& Other ) const override { return false; }
    bool isCollided( const Line3DBody& Other ) const override { return false; }

    bool initialize() override;
    void finalize() override;

private :
    EGEG Line3D shape_;
};

} /// namespace component
END_EGEG
#endif /// !INCLUDED_EGEG_BODY3D_COMPONENT_HEADER_
/// EOF
