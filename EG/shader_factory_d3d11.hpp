///
/// @file    shader_factory_d3d11.hpp
/// @author  板場
///          
/// @brief   D3D11用シェーダーファクトリ
/// @details シングルトンクラスです。アクセスにはinstance関数を使用して下さい。<br>
///          新しいシェーダーの登録はREGISTER_SHADERマクロを使用して下さい。
///
#ifndef INCLUDED_EG_EG_SHADER_FACTORY_D3D11_HEADER_
#define INCLUDED_EG_EG_SHADER_FACTORY_D3D11_HEADER_
#include <unordered_map>
#include "shader_factory.hpp"
BEGIN_EGEG
class ShaderFactoryD3D11 :
    public IShaderFactory
{
public : 
    ///
    /// @brief  インスタンスを取得します。
    ///
    /// @return インスタンスのアドレス
    ///
    static ShaderFactoryD3D11* instance() { static ShaderFactoryD3D11 i; return &i; }

    ///
    /// @brief  シェーダーの登録
    ///
    /// @param[in] Name : シェーダーの名前
    /// @param[in] pCreateFunction : シェーダーの生成関数のアドレス
    ///
    void registerShader( const char* Name, IShader*(*pCreateFunction)() )
    {
        creators_[Name] = pCreateFunction;
    }
   
// IShaderFactory
/*-----------------------------------------------------------------*/
    bool create( const char* Name, IShader** ppOutShader ) override
    {
        auto find = creators_.find( Name );
        if( find == creators_.end() ) return false;

        *ppOutShader = find->second();
        if( *ppOutShader == nullptr)  return false;

        return true;
    }

private :
    std::unordered_map<const char*, IShader*(*)()> creators_;
};


class REGISTER_SHADER_D3D11
{
public :
    REGISTER_SHADER_D3D11( const char* Name, IShader*(*pFunc)() )
    {
        ShaderFactoryD3D11::instance()->registerShader(Name, pFunc);
    }
};
///
/// @def     REGISTER_SHADER_D3D11
/// @brief   シェーダーをD3D11のシェーダーファクトリに登録します。
/// @details ヘッダーで呼び出さないでください。
///
/// @param[in] Name : 登録するシェーダーの名前
/// @param[in] pCreateFunction : 生成処理を実装した関数のアドレス
///
#define REGISTER_SHADER_D3D11( Name, pCreateFunction ) \
BEGIN_EGEG \
namespace impl{} namespace { namespace impl { \
REGISTER_SHADER_D3D11 register_the_shader( Name, pCreateFunction ); \
}} END_EGEG

END_EGEG
#endif /// !INCLUDED_EG_EG_SHADER_FACTORY_D3D11_HEADER_
/// EOF
