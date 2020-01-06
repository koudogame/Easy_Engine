#ifndef INCLUDED_EG_EG_PIXEL_SHADER_HEADER_
#define INCLUDED_EG_EG_PIXEL_SHADER_HEADER_
// 作成者 : 板場
#include "shader.hpp"

BEGIN_EG_EG
//
// ピクセルシェーダー
//
class PixelShader :
    public IShader
{
public :
    uint16_t getID() const override { return ShaderID::kPixelShader; }
    void setShader( void* pShader ) override { p_shader_ = pShader; }
    void* getShader() const override { return p_shader_; }

private :
    void* p_shader_;
};
END_EG_EG
#endif // INCLUDED_EG_EG_PIXEL_SHADER_HEADER_
// EOF