///
/// @file   vertex_binder.hpp
/// @author 板場
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
/// @brief  頂点データバインダー
///
class VertexBinder
{
public :
    using RetValue = DetailedReturnValue<VertexData>;

    ///
    /// @brief   バインドオブジェクト生成
    /// @details 引数の入力の順番が、バッファの入力の順番になります。
    ///
    /// @param[in] Semantic : 対応するセマンティック( 文字列 )
    ///
    template <class ...Args>
    VertexBinder( Args&& ...Semantic )
    {
        corresponds_.push_back( Semantic );
    }

    ///
    /// @brief   頂点データをバインド
    /// @details 出力構造体に出力するバッファオブジェクトの参照はカウントしていません。弱参照です。
    ///
    /// @param[in] Source : バインド元のデータ
    ///
    /// @return バインド成功[ true ]  バインド失敗[ false ]
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
                return RetValue( false, std::move(output), "バインド失敗　対応していないデータ : " + semantic );
#else
                return RetValue( false, std::move(output) );
#endif
            }
            buffer->Release();

            // 出力
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
