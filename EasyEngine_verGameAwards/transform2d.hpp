///
/// @file   transform2d.hpp
/// @author î¬èÍ
///
#ifndef INCLUDED_EGEG_TRANSFORM2D_COMPONENT_HEADER_
#define INCLUDED_EGEG_TRANSFORM2D_COMPONENT_HEADER_

#include "component2d.hpp"
#include "egeg_math.hpp"
#include "type_id.hpp"

BEGIN_EGEG
namespace component
{

class Transform2D :
    public Component2D
{
public :
    static constexpr TypeID<Transform2D> getID() noexcept { return TypeID<Transform2D>(); }
    
    ///< ç¿ïWÇÃÉZÉbÉg
    void setPosition( const Vector2D& Destination ) noexcept { position_ = Destination; }
    ///< ç¿ïWÇÃéÊìæ
    const Vector2D& getPosition() const noexcept { return position_; }

    ///< ägèkó¶ÇÃê›íË
    void setScale( const Vector2D& Scale ) noexcept { scale_ = Scale; }
    ///< ägèkó¶ÇÃéÊìæ
    const Vector2D& getScale() const noexcept { return scale_; }

    ///< âÒì]ìxêîÇÃÉZÉbÉg
    void setRotation( float Rotation ) noexcept { rotation_ = Rotation; }
    ///< âÒì]ìxêîÇÃéÊìæ
    float getRotation() const noexcept { return rotation_; }

/*-----------------------------------------------------------------*/
// Component
    bool initialize() override;
    void finalize() override;
/*-----------------------------------------------------------------*/
private :
    Vector2D position_;
    Vector2D scale_;
    float rotation_;
};

} // namespace component
END_EGEG
#endif /// !INCLUDED_EGEG_TRANSFORM2D_HEADER_
/// EOF
