///
/// @file   physical_collision_component.hpp
/// @author Âê
///
#ifndef INCLUDED_EGEG_PHYSICAL_COLLISION_COMPONENT_HEADER_
#define INCLUDED_EGEG_PHYSICAL_COLLISION_COMPONENT_HEADER_
#include "collision_component.hpp"
BEGIN_EGEG
///
/// @class  PhysicalCollisionComponent
/// @brief  ¨KÕË»èpR|[lg
///
class PhysicalCollisionComponent :
    public CollisionComponent
{
public :
    ///< IDÌæ¾
    static uint32_t getID() { return TypeID<PhysicalCollisionComponent>::getID(); }

    ///
    /// @brief  RXgN^
    ///
    /// @param[in] pOwner : I[i[
    ///
    PhysicalCollisionComponent( Actor* pOwner ) : CollisionComponent( pOwner ) {}

    ///
    /// @brief  AN^[ÆÌÕË»è
    ///
    /// @param[in] pOther : »èðs¤AN^[
    ///
    /// @return ÕË è[ true ]@ÕËÈµ[ false ]
    ///
    bool isCollided( Actor* pOther ) override;

    ///
    /// @brief  Xe[^XÌÝè
    ///
    /// @param[in] Mass : ¿Ê
    /// @param[in] Restitution : ½­W
    /// @param[in] StaticFriction : Ã~CW
    /// @param[in] KineticFriction : ®CW
    ///
    void setStatuc( float Mass, float Restitution, float StaticFriction, float KineticFriction )
    {
        setMass( Mass );
        setRestitution( Restitution );
        setStaticFriction( StaticFriction );
        setKineticFriction( KineticFriction );
    }
    ///
    /// @brief  ¿ÊÌÝè
    ///
    /// @param[in] Mass : ¿Ê
    ///
    void setMass( float Mass ) { mass_ = Mass; }
    ///
    /// @brief  ½­WÌÝè
    ///
    /// @param[in] Restitution : ½­W
    ///
    void setRestitution( float Restitution ) { restitution_ = Restitution; }
    ///
    /// @brief  Ã~CWÌÝè
    ///
    /// @param[in] StaticFriction : Ã~CW
    ///
    void setStaticFriction( float StaticFriction ) { static_friction_ = StaticFriction; }
    ///
    /// @brief  ®CWÌÝè
    ///
    /// @param[in] KineticFriction : ®CW
    ///
    void setKineticFriction( float KineticFriction ) { kinetic_friction_ = KineticFriction; } 
    
private :
    float mass_ = 0.0F;             /// ¿Ê
    float restitution_ = 0.0F;      /// ½­W
    float static_friction_ = 0.0F;  /// Ã~CW
    float kinetic_friction_ = 0.0F; /// ^®CW
};
END_EGEG
#endif /// !INCLUDED_EGEG_PHYSICAL_COLLISION_COMPONENT_HEADER_
/// EOF
