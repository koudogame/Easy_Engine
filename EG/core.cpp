// ì¬ŽÒ : ”Âê
#include "core.hpp"
#include "platform_factory.hpp"

BEGIN_EGEG
// ŠÖ”‚ÌŽÀ‘•
/*===========================================================================*/
// ‰Šú‰»ˆ—
bool Core::initialize( PlatformID Platform )
{
    if( PlatformFactory::instance()->create(Platform, &p_platform_) == false )
        return false;

    return true;
}
// I—¹ˆ—
void Core::finalize()
{
    if( p_platform_ ) p_platform_->release();
}
END_EGEG
// EOF
