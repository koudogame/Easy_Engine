///
/// @file  shader_factory.hpp
/// @author 板場
///
/// @brief  シェーダーファクトリのインターフェイス
///
#ifndef INCLUDED_EG_EG_SHADER_FACTORY_HEADER_
#define INCLUDED_EG_EG_SHADER_FACTORY_HEADER_
#include "shader.hpp"
BEGIN_EGEG
class IShaderFactory :
    public Interface
{
public :
    ///
    /// @brief  シェーダーの生成処理
    ///
    /// @param[in] ShaderName : 生成するシェーダーの名前
    /// @param[out] ppOutShader : 生成したシェーダーを受け取るインターフェイス
    ///
    virtual bool create( const char* ShaderName, IShader** ppOutShader ) = 0;

protected :
    virtual ~IShaderFactory() = default;
};
END_EGEG
#endif /// !INCLUDED_EG_EG_SHADER_FACTORY_HEADER_
/// EOF
