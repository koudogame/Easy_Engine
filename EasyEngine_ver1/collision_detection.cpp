// �쐬�� : ��
#include <cmath>
#include "collision_detection.hpp"

BEGIN_EGEG
// CollisionDetection : �֐��̎���
/*===========================================================================*/
// ��`�Ƌ�` (AABB)
bool CollisionDetection::isCollided( const Rectangle& Rect1, const Rectangle& Rect2 )
{
    // Rect1��4���_���v�Z
    const float kRect1WidthHarf  = Rect1.width * 0.5F;
    const float kRect1HeightHarf = Rect1.height * 0.5F;
    const float kRect1Left   = Rect1.origin.x - kRect1WidthHarf;
    const float kRect1Top    = Rect1.origin.y - kRect1HeightHarf;
    const float kRect1Right  = Rect1.origin.x + kRect1WidthHarf;
    const float kRect1Bottom = Rect1.origin.y + kRect1HeightHarf;

    // Rect2��4���_���v�Z
    const float kRect2WidthHarf  = Rect2.width * 0.5F;
    const float kRect2HeightHarf = Rect2.height * 0.5F;
    const float kRect2Left   = Rect2.origin.x - kRect2WidthHarf;
    const float kRect2Top    = Rect2.origin.y - kRect2HeightHarf;
    const float kRect2Right  = Rect2.origin.x + kRect2WidthHarf;
    const float kRect2Bottom = Rect2.origin.y + kRect2HeightHarf;

    // ����
    if( kRect1Left <= kRect2Right &&
        kRect1Right >= kRect2Left &&
        kRect1Top <= kRect2Bottom &&
        kRect1Bottom >= kRect2Top )
    {
        return true;
    }
    else
        return false;
}

// �~�Ɖ~
bool CollisionDetection::isCollided( const Circle& Cir1, const Circle& Cir2 )
{
    // �~���m�̋������v�Z
    float dist_x = Cir2.origin.x - Cir1.origin.x;
    float dist_y = Cir2.origin.y - Cir1.origin.y;
    float distance = (dist_x * dist_x) + (dist_y * dist_y);

    float dist_coll = Cir1.radius + Cir2.radius;    // �Փ˂��鋗��
    dist_coll *= dist_coll;

    // �������݂��̔��a�����Z�����l������������ΏՓ�
    if( distance <= dist_coll )
    {
        return true;
    }
    else
        return false;
}

// �����Ɛ����@�Q�l�T�C�g : http://marupeke296.com/COL_2D_No10_SegmentAndSegment.html
bool CollisionDetection::isCollided( const Line& Line1, const Line& Line2, float* DivRat1, float* DivRat2 )
{
    // ���s����
    if( Line1.line.cross( Line2.line ) == 0.0F )  
    {
        return false;
    }

    // ��������
    Vector2D vec_s_s = Line2.start - Line1.start;
    float rec_crs_1_2 = 1.F / Line1.line.cross(Line2.line);
    float divrat_2 = vec_s_s.cross(Line1.line) * rec_crs_1_2;
    float divrat_1 = vec_s_s.cross(Line2.line) * rec_crs_1_2;

    if( DivRat1 )   *DivRat1 = divrat_1;
    if( DivRat2 )   *DivRat2 = divrat_2;

    if( divrat_1 >= 0.F && divrat_1 <= 1.00001F &&
        divrat_2 >= 0.F && divrat_2 <= 1.00001F )
    {
        return true;
    }
    else
        return false;
}

// ��`�Ɖ~�`
bool CollisionDetection::isCollided( const Rectangle& Rect, const Circle& Cir )
{
    const float kRectWidthHarf = Rect.width * 0.5F;
    const float kRectHeightHarf = Rect.height * 0.5F;

    // ��`�̊e�ӂƉ~�`�̔���
    Line line;
    line.start = { Rect.origin.x - kRectWidthHarf, Rect.origin.y + kRectHeightHarf };
    line.line  = { 0.F, -Rect.height };
    if( isCollided( Cir, line ) )
        return true;

    line.start = { Rect.origin.x - kRectWidthHarf, Rect.origin.y - kRectHeightHarf };
    line.line  = { Rect.width, 0.F };
    if( isCollided( Cir, line ) )
        return true;

    line.start = { Rect.origin.x + kRectWidthHarf, Rect.origin.y - kRectHeightHarf };
    line.line  = { 0.F, Rect.height };
    if( isCollided( Cir, line ) )
        return true;

    line.start = { Rect.origin.x + kRectWidthHarf, Rect.origin.y + kRectHeightHarf };
    line.line  = { -Rect.width, 0.0F };
    if( isCollided( Cir,line ) )
        return true;
    

    return false;
}

// ��`�Ɛ���
bool CollisionDetection::isCollided( const Rectangle& Rect, const Line& Segment )
{
    const float kRectWidthHarf = Rect.width * 0.5F;
    const float kRectHeightHarf = Rect.height * 0.5F;

    // ��`�̊e�ӂƐ����̔���
    Line line;
    line.start = { Rect.origin.x - kRectWidthHarf, Rect.origin.y + kRectHeightHarf };
    line.line  = { 0.F, -Rect.height };
    if( isCollided( line, Segment ) )
        return true;

    line.start = { Rect.origin.x - kRectWidthHarf, Rect.origin.y - kRectHeightHarf };
    line.line  = { Rect.width, 0.F };
    if( isCollided( line, Segment ) )
        return true;

    line.start = { Rect.origin.x + kRectWidthHarf, Rect.origin.y - kRectHeightHarf };
    line.line  = { 0.F, Rect.height };
    if( isCollided( line, Segment ) )
        return true;

    line.start = { Rect.origin.x + kRectWidthHarf, Rect.origin.y + kRectHeightHarf };
    line.line  = { -Rect.width, 0.0F };
    if( isCollided( line, Segment ) )
        return true;
    
    return false;
}

// �~�`�Ɛ����@�Q�l�T�C�g : http://marupeke296.com/COL_2D_No5_PolygonToCircle.html
bool CollisionDetection::isCollided( const Circle& Cir, const Line& Line )
{
    // �����̎n�_�I�_�Ɖ~�`�̔���
    Circle point;
    point.radius = 0.F;

    point.origin.x = Line.start.x;
    point.origin.y = Line.start.y;
    if( isCollided( Cir, point ) )
        return true;

    point.origin.x = Line.start.x + Line.line.x;
    point.origin.y = Line.start.y + Line.line.y;
    if( isCollided( Cir, point ) )
        return true;

    // �����Ɖ~�`�̔���
    Vector2D linestart_to_circle = Cir.origin - Line.start;
    float distance = Line.start.cross(linestart_to_circle) / std::hypot(Line.start.x, Line.start.y);   // �����Ɖ~�`�̋���
    if( distance <= Cir.radius ) // �Փ˂̉\��������
    {
        float start_circle_dot = linestart_to_circle.dot( Line.line );
        Vector2D lineend_to_circle = Cir.origin - ( Line.start + Line.line );
        float end_circle_dot = lineend_to_circle.dot( Line.line );

        // �~�������ƌ������Ă���
        if( start_circle_dot >= 0 && end_circle_dot >= 0 )
            return true;
    }
    

    return false;
}
END_EGEG
// EOF
