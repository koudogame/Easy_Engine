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
    using RetValType = DetailedReturnValue<std::unique_ptr<ReturnType>>;

    template <class DeviceType>
    ShaderLoader( DeviceType&& Device ) :
        Loader( std::forward<DeviceType>(Device) ) {}

    ///
    /// @brief  頂点シェーダ―のロード
    ///
    /// @tparam VertexShaderType : 読み込む頂点シェーダ―型
    ///
    /// @return シェーダー
    ///
    template <class VertexShaderType>
    RetValType<VertexShaderType> loadVertexShader()
    {
        using VSTy = VertexShaderType;
        using RetTy = RetValType<VSTy>;

        // ファイルからバイトコードを読み込む
        auto blob = loadBinary( VSTy::kVSFileName );
        if( !blob ) 
        { // ファイルの読み込みに失敗
            return RetTy( false, nullptr, "ファイルの読み込みに失敗" );
        }

        // シェーダーオブジェクトの生成
        ID3D11VertexShader* vs = nullptr;
        if( !createVS(blob.get(), &vs) )
        { // シェーダーオブジェクトの生成に失敗
            return RetTy( false, nullptr, "シェーダーオブジェクトの生成に失敗" );
        }

        // 入力レイアウトオブジェクトの生成
        ID3D11InputLayout* il = nullptr;
        if( !createIL(blob.get(), VSTy::kInputElementDescs, getArraySize(VSTy::kInputElementDescs), &il) )
        { // 入力レイアウトオブジェクトの生成に失敗
            vs->Release();
            return RetTy( false, nullptr, "入力レイアウトオブジェクトの生成に失敗" );
        }
        
        RetTy shader( true, std::make_unique<VSTy>(vs, il) );
        vs->Release();
        il->Release();
        return shader;
    }

    ///
    /// @brief  ジオメトリシェーダーのロード
    ///
    /// @tpararm GeometryShaderType : 読み込むジオメトリシェーダ―
    ///
    /// @return シェーダ―
    ///
    template <class GeometryShaderType>
    RetValType<GeometryShaderType> loadGeometryShader()
    {
        using GSTy = GeometryShaderType;
        using RetTy = RetValType<GSTy>;

        // ファイルからバイトコードを読み込む
        auto blob = loadBinary( GSTy::kGSFileName );
        if( !blob )
        { // ファイルの読み込みに失敗
            return RetTy( false, nullptr, "ファイルの読み込みに失敗" );
        }

        // シェーダ―オブジェクトの生成
        ID3D11GeometryShader* gs = nullptr;
        if( !createGS(blob.get(), &gs) )
        { // シェーダ―オブジェクトの生成に失敗
            return RetTy( false, nullptr, "シェーダ―オブジェクトの生成に失敗" );
        }

        RetTy shader( true, std::make_unique<GSTy>(gs) );
        gs->Release();
        return shader;
    }

    ///
    /// @brief  ピクセルシェーダ―のロード
    ///
    /// @tparam PixelShaderType
    ///
    /// @return シェーダ―
    ///
    template <class PixelShaderType>
    RetValType<PixelShaderType> loadPixelShader()
    {
        using PSTy = PixelShaderType;
        using RetTy = RetValType<PSTy>;

        // ファイルからバイトコードを読み込む
        auto blob = loadBinary( PSTy::kPSFileName );
        if( !blob )
        { // ファイルの読み込みに失敗
            return RetTy( false, nullptr, "ファイルの読み込みに失敗" );
        }

        // シェーダーオブジェクトの生成
        ID3D11PixelShader* ps = nullptr;
        if( !createPS(blob.get(), &ps) )
        { // シェーダ―オブジェクトの生成に失敗
            return RetTy( false, nullptr, "シェーダ―オブジェクトの生成に失敗" );
        }

        RetTy shader( true, std::make_unique<PSTy>(ps) );
        ps->Release();
        return shader;
    }

private :
    struct BinaryData
    {
        ~BinaryData() { delete[] bytecode; }
        BinaryData( const BinaryData& ) = delete;
        BinaryData& operator=( const BinaryData& ) = delete;
        BinaryData( BinaryData&& Rhs ) :
            bytecode( Rhs.bytecode ),
            length( length )
        {
            Rhs.bytecode = nullptr;
        }
        BinaryData& operator=( BinaryData&& Rhs )
        {
            this->bytecode = Rhs.bytecode;
            this->length = Rhs.length;
            Rhs.bytecode = nullptr;
        }

        char* bytecode = nullptr;
        size_t length;
    };
    DetailedReturnValue<BinaryData> loadBinary( const char* );
    bool createIL( const BinaryData&, const D3D11_INPUT_ELEMENT_DESC*, UINT, ID3D11InputLayout** );
    bool createVS( const BinaryData&, ID3D11VertexShader** );
    bool createGS( const BinaryData&, ID3D11GeometryShader** );
    bool createPS( const BinaryData&, ID3D11PixelShader** );
    /*
public :
    template <class ReturnType>
    using ReturnValue = DetailedReturnValue<std::unique_ptr<ReturnType>>;

    template <class DeviceType>
    ShaderLoader( DeviceType&& Device ) :
        Loader( std::forward<DeviceType>(Device) )
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

    */
};
END_EGEG
#endif /// !INCLUDED_EGEG_SHADER_LOADER_HEADER_
/// EOF
