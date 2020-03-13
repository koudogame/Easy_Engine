///
/// @file   vertex_binder.hpp
/// @author ��
///
#ifndef INCLUDED_EGEG_VERTEX_BINDER_HEADER_
#define INCLUDED_EGEG_VERTEX_BINDER_HEADER_
#include <vector>
#include <string>
#include "vertex_data.hpp"
#include "egeg_utility.hpp"
BEGIN_EGEG
struct BindedVertexData
{
    std::vector<ID3D11Buffer*> buffers;
    std::vector<UINT>          strides;
    std::vector<UINT>          offsets;
};
///
/// @class  VertexBinder
/// @brief  ���_�f�[�^�o�C���_�[
///
class VertexBinder
{
public :
    using RetValue = DetailedReturnValue<VertexData>;

    ///
    /// @brief   �o�C���h�I�u�W�F�N�g����
    /// @details �����̓��͂̏��Ԃ��A�o�b�t�@�̓��͂̏��ԂɂȂ�܂��B
    ///
    /// @param[in] Semantic : �Ή�����Z�}���e�B�b�N( ������ )
    ///
    template <class ...Args>
    VertexBinder( Args&& ...Semantic )
    {
        corresponds_.push_back( Semantic );
    }

    ///
    /// @brief   ���_�f�[�^���o�C���h
    /// @details �o�͍\���̂ɏo�͂���o�b�t�@�I�u�W�F�N�g�̎Q�Ƃ̓J�E���g���Ă��܂���B��Q�Ƃł��B
    ///
    /// @param[in] Source : �o�C���h���̃f�[�^
    ///
    /// @return �o�C���h����[ true ]  �o�C���h���s[ false ]
    ///
    RetValue bind( VertexData* Source )
    {
        BindedVertexData output;

        for( auto& semantic : corresponds_ )
        {
            auto buffer = Source->getVertexBuffer( semantic.c_str() );
            if( buffer == nullptr )
            {
                for( auto& buffer : output.buffers )
                    buffer = nullptr;
#ifdef _DEBUG
                return RetValue( false, std::move(output), "�o�C���h���s�@�Ή����Ă��Ȃ��f�[�^ : " + semantic );
#else
                return RetValue( false, std::move(output) );
#endif
            }
            buffer->Release();

            // �o��
            output.buffers.push_back( buffer );
            output.strides.push_back(
                semantic == kVertexPositionSemantic ? sizeof( VertexPositionType ) :
                semantic == kVertexUVSemantic ? sizeof( VertexUVType ) :
                sizeof( VertexNormalType )
            );
            output.offsets.push_back( 0U );
        }

        return RetValue( true, std::move(output) );
    }

private :
    VertexBinder() = default;
    std::vector<std::string> corresponds_;
};
END_EGEG
#endif /// !INCLUDED_EGEG_VERTEX_BINDER_HEADER_
/// EOF
