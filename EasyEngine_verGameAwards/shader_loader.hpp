///
/// @file   shader_loader.hpp
/// @author 板場
///
#ifndef INCLUDED_EGEG_SHADER_LOADER_HEADER_
#define INCLUDED_EGEG_SHADER_LOADER_HEADER_
#include <fstream>
#include <memory>
#include <unordered_map>
#include "loader.hpp"
#include "utility_function.hpp"
#include "detailed_returnvalue.hpp"
BEGIN_EGEG
///
/// @class  ShaderLoader
/// @brief  シェーダーローダー
///
class ShaderLoader :
    public Loader
{
public :
    template <class ReturnType>
    using ReturnValue = DetailedReturnValue<std::unique_ptr<ReturnType>>;

    ShaderLoader( Microsoft::WRL::ComPtr<ID3D11Device> Device ) :
        Loader( Device )
    {}

    ///
    /// @brief  頂点シェーダ―の生成
    ///
    /// @tparam VertexShaderType : 生成するシェーダー型
    ///
    /// @return シェーダーオブジェクト
    ///
    template <class VertexShaderType>
    ReturnValue<VertexShaderType> createVertexShader()
    {
        using VSTy = VertexShaderType;
        using RetTy = ReturnValue<VSTy>;

        // ファイルオープン
        std::fstream stream( VSTy::kVSFileName, std::ios::binary | std::ios::in );
        if( !stream ) return RetTy( false, nullptr, "ファイルオープン失敗" );

        // シェーダ―読み込み
        size_t filesize = getFileSize( stream );
        char* blob = new char[ filesize ];
        stream.read( blob, filesize );
        stream.close();

        // オブジェクト生成
        ID3D11VertexShader* vs = nullptr;
        HRESULT hr = device_->CreateVertexShader(
            blob,
            filesize,
            nullptr,
            &vs
        );
        if( FAILED(hr) )
        {
            delete[] blob;
            return RetTy( false, nullptr, "シェーダーオブジェクトの生成失敗" );
        }

        ID3D11InputLayout* il = nullptr;
        hr = device_->CreateInputLayout(
            VSTy::kInputElementDescs,
            getArraySize(VSTy::kInputElementDescs),
            blob,
            filesize,
            &il
        );
        delete[] blob;
        if( FAILED(hr) )
        {
            vs->Release();
            return RetTy( false, nullptr, "入力レイアウトオブジェクトの生成失敗" );
        }

        RetTy created( true, std::make_unique<VSTy>(vs, il) );
        vs->Release();
        il->Release();
        return created;
    }

    ///
    /// @brief  ジオメトリシェーダ―の生成
    ///
    /// @tparam GeometryShaderType : 生成するシェーダ―型
    ///
    /// @return シェーダーオブジェクト
    ///
    template <class GeometryShaderType>
    ReturnValue<GeometryShaderType> createGeometryShader()
    {
        using GSTy = GeometryShaderType;
        using RetTy = ReturnValue<GSTy>;

        // ファイルオープン
        std::fstream stream( GSTy::kGSFileName, std::ios::binary | std::ios::in );
        if( !stream ) return RetTy( false, nullptr, "ファイルオープン失敗" );

        // シェーダ―読み込み
        size_t filesize = getFileSize( stream );
        char* blob = new char[ filesize ];
        stream.read( blob, filesize );
        stream.close();

        // オブジェクトの生成
        ID3D11GeometryShader* gs = nullptr;
        HRESULT hr = device_->CreateGeometryShader(
            blob,
            filesize,
            nullptr,
            gs
        );
        delete[] blob;
        if( FAILED(hr) ) return RetTy( false, nullptr, "シェーダ―オブジェクトの生成失敗" );
        
        RetTy created( true, std::make_unique<GSTy>(gs) );
        gs->Release();
        return created;
    }

    ///
    /// @brief  ピクセルシェーダ―の生成
    ///
    /// @tparam PixelShaderType : 生成するシェーダ―型
    ///
    /// @return シェーダーオブジェクト
    ///
    template <class PixelShaderType>
    ReturnValue<PixelShaderType> createPixelShader()
    {
        using PSTy = PixelShaderType;
        using RetTy = ReturnValue<PSTy>;

        // ファイルオープン
        std::fstream stream( PSTy::kPSFileName, std::ios::binary | std::ios::in );
        if( !stream ) return RetTy( false, nullptr, "ファイルオープン失敗" );

        // シェーダ―読み込み
        size_t filesize = getFileSize( stream );
        char* blob = new char[ filesize ];
        stream.read( blob, filesize );
        stream.close();

        // シェーダーオブジェクトの生成
        ID3D11PixelShader* ps = nullptr;
        HRESULT hr = device_->CreatePixelShader(
            blob,
            filesize,
            nullptr,
            &ps
        );
        delete[] blob;
        if( FAILED(hr) ) return RetTy( false, nullptr, "シェーダ―オブジェクトの生成失敗" );

        RetTy created( true, std::make_unique<PSTy>(ps) );
        ps->Release();
        return created;
    }

private :
    size_t getFileSize( ::std::fstream& );
};
END_EGEG
#endif /// !INCLUDED_EGEG_SHADER_LOADER_HEADER_
/// EOF
