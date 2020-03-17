///
/// @file   shader_loader.hpp
/// @author ��
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
/// @brief  �V�F�[�_�[���[�_�[
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
    /// @brief  ���_�V�F�[�_�\�̃��[�h
    ///
    /// @tparam VertexShaderType : �ǂݍ��ޒ��_�V�F�[�_�\�^
    ///
    /// @return �V�F�[�_�[
    ///
    template <class VertexShaderType>
    RetValType<VertexShaderType> loadVertexShader()
    {
        using VSTy = VertexShaderType;
        using RetTy = RetValType<VSTy>;

        // �t�@�C������o�C�g�R�[�h��ǂݍ���
        auto blob = loadBinary( VSTy::kVSFileName );
        if( !blob ) 
        { // �t�@�C���̓ǂݍ��݂Ɏ��s
            return RetTy( false, nullptr, "�t�@�C���̓ǂݍ��݂Ɏ��s" );
        }

        // �V�F�[�_�[�I�u�W�F�N�g�̐���
        ID3D11VertexShader* vs = nullptr;
        if( !createVS(blob.get(), &vs) )
        { // �V�F�[�_�[�I�u�W�F�N�g�̐����Ɏ��s
            return RetTy( false, nullptr, "�V�F�[�_�[�I�u�W�F�N�g�̐����Ɏ��s" );
        }

        // ���̓��C�A�E�g�I�u�W�F�N�g�̐���
        ID3D11InputLayout* il = nullptr;
        if( !createIL(blob.get(), VSTy::kInputElementDescs, getArraySize(VSTy::kInputElementDescs), &il) )
        { // ���̓��C�A�E�g�I�u�W�F�N�g�̐����Ɏ��s
            vs->Release();
            return RetTy( false, nullptr, "���̓��C�A�E�g�I�u�W�F�N�g�̐����Ɏ��s" );
        }
        
        RetTy shader( true, std::make_unique<VSTy>(vs, il) );
        vs->Release();
        il->Release();
        return shader;
    }

    ///
    /// @brief  �W�I���g���V�F�[�_�[�̃��[�h
    ///
    /// @tpararm GeometryShaderType : �ǂݍ��ރW�I���g���V�F�[�_�\
    ///
    /// @return �V�F�[�_�\
    ///
    template <class GeometryShaderType>
    RetValType<GeometryShaderType> loadGeometryShader()
    {
        using GSTy = GeometryShaderType;
        using RetTy = RetValType<GSTy>;

        // �t�@�C������o�C�g�R�[�h��ǂݍ���
        auto blob = loadBinary( GSTy::kGSFileName );
        if( !blob )
        { // �t�@�C���̓ǂݍ��݂Ɏ��s
            return RetTy( false, nullptr, "�t�@�C���̓ǂݍ��݂Ɏ��s" );
        }

        // �V�F�[�_�\�I�u�W�F�N�g�̐���
        ID3D11GeometryShader* gs = nullptr;
        if( !createGS(blob.get(), &gs) )
        { // �V�F�[�_�\�I�u�W�F�N�g�̐����Ɏ��s
            return RetTy( false, nullptr, "�V�F�[�_�\�I�u�W�F�N�g�̐����Ɏ��s" );
        }

        RetTy shader( true, std::make_unique<GSTy>(gs) );
        gs->Release();
        return shader;
    }

    ///
    /// @brief  �s�N�Z���V�F�[�_�\�̃��[�h
    ///
    /// @tparam PixelShaderType
    ///
    /// @return �V�F�[�_�\
    ///
    template <class PixelShaderType>
    RetValType<PixelShaderType> loadPixelShader()
    {
        using PSTy = PixelShaderType;
        using RetTy = RetValType<PSTy>;

        // �t�@�C������o�C�g�R�[�h��ǂݍ���
        auto blob = loadBinary( PSTy::kPSFileName );
        if( !blob )
        { // �t�@�C���̓ǂݍ��݂Ɏ��s
            return RetTy( false, nullptr, "�t�@�C���̓ǂݍ��݂Ɏ��s" );
        }

        // �V�F�[�_�[�I�u�W�F�N�g�̐���
        ID3D11PixelShader* ps = nullptr;
        if( !createPS(blob.get(), &ps) )
        { // �V�F�[�_�\�I�u�W�F�N�g�̐����Ɏ��s
            return RetTy( false, nullptr, "�V�F�[�_�\�I�u�W�F�N�g�̐����Ɏ��s" );
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
    /// @brief  ���_�V�F�[�_�\�̐���
    ///
    /// @tparam VertexShaderType : ��������V�F�[�_�[�^
    ///
    /// @return �V�F�[�_�[�I�u�W�F�N�g
    ///
    template <class VertexShaderType>
    ReturnValue<VertexShaderType> createVertexShader()
    {
        using VSTy = VertexShaderType;
        using RetTy = ReturnValue<VSTy>;

        // �t�@�C���I�[�v��
        std::fstream stream( VSTy::kVSFileName, std::ios::binary | std::ios::in );
        if( !stream ) return RetTy( false, nullptr, "�t�@�C���I�[�v�����s" );

        // �V�F�[�_�\�ǂݍ���
        size_t filesize = getFileSize( stream );
        char* blob = new char[ filesize ];
        stream.read( blob, filesize );
        stream.close();

        // �I�u�W�F�N�g����
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
            return RetTy( false, nullptr, "�V�F�[�_�[�I�u�W�F�N�g�̐������s" );
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
            return RetTy( false, nullptr, "���̓��C�A�E�g�I�u�W�F�N�g�̐������s" );
        }

        RetTy created( true, std::make_unique<VSTy>(vs, il) );
        vs->Release();
        il->Release();
        return created;
    }

    ///
    /// @brief  �W�I���g���V�F�[�_�\�̐���
    ///
    /// @tparam GeometryShaderType : ��������V�F�[�_�\�^
    ///
    /// @return �V�F�[�_�[�I�u�W�F�N�g
    ///
    template <class GeometryShaderType>
    ReturnValue<GeometryShaderType> createGeometryShader()
    {
        using GSTy = GeometryShaderType;
        using RetTy = ReturnValue<GSTy>;

        // �t�@�C���I�[�v��
        std::fstream stream( GSTy::kGSFileName, std::ios::binary | std::ios::in );
        if( !stream ) return RetTy( false, nullptr, "�t�@�C���I�[�v�����s" );

        // �V�F�[�_�\�ǂݍ���
        size_t filesize = getFileSize( stream );
        char* blob = new char[ filesize ];
        stream.read( blob, filesize );
        stream.close();

        // �I�u�W�F�N�g�̐���
        ID3D11GeometryShader* gs = nullptr;
        HRESULT hr = device_->CreateGeometryShader(
            blob,
            filesize,
            nullptr,
            gs
        );
        delete[] blob;
        if( FAILED(hr) ) return RetTy( false, nullptr, "�V�F�[�_�\�I�u�W�F�N�g�̐������s" );
        
        RetTy created( true, std::make_unique<GSTy>(gs) );
        gs->Release();
        return created;
    }

    ///
    /// @brief  �s�N�Z���V�F�[�_�\�̐���
    ///
    /// @tparam PixelShaderType : ��������V�F�[�_�\�^
    ///
    /// @return �V�F�[�_�[�I�u�W�F�N�g
    ///
    template <class PixelShaderType>
    ReturnValue<PixelShaderType> createPixelShader()
    {
        using PSTy = PixelShaderType;
        using RetTy = ReturnValue<PSTy>;

        // �t�@�C���I�[�v��
        std::fstream stream( PSTy::kPSFileName, std::ios::binary | std::ios::in );
        if( !stream ) return RetTy( false, nullptr, "�t�@�C���I�[�v�����s" );

        // �V�F�[�_�\�ǂݍ���
        size_t filesize = getFileSize( stream );
        char* blob = new char[ filesize ];
        stream.read( blob, filesize );
        stream.close();

        // �V�F�[�_�[�I�u�W�F�N�g�̐���
        ID3D11PixelShader* ps = nullptr;
        HRESULT hr = device_->CreatePixelShader(
            blob,
            filesize,
            nullptr,
            &ps
        );
        delete[] blob;
        if( FAILED(hr) ) return RetTy( false, nullptr, "�V�F�[�_�\�I�u�W�F�N�g�̐������s" );

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
