///
/// @file   circlebody_component.hpp
/// @author 板場
///
#ifndef INCLUDED_EGEG_CIRCLEBODY_COMPONENT_HEADER_
#define INCLUDED_EGEG_CIRCLEBODY_COMPONENT_HEADER_
#include "body_component.hpp"
BEGIN_EGEG
///
/// @class  CirclebodyComponent
/// @brief  円形ボディ
///
class CirclebodyComponent :
    public BodyComponent
{
public :


/*-----------------------------------------------------------------*/
// BodyComponent
    bool isCollided( Actor* ) override;
    bool isCollided( const Rectangle& ) override;
    bool isCollided( const Circle& ) override;
    bool isCollided( const Line& ) override;
/*-----------------------------------------------------------------*/
private :
    Circle body_;   /// 形
};
END_EGEG
#endif /// !INCLUDED_EGEG_CIRCLEBODY_COMPONENT_HEADER_
/// EOF
