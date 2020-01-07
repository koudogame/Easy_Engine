///
/// @file    face.hpp
/// @author  板場
///          
/// @brief   フェース構造体
///
/// @details 頂点を複数(可変)個持ちます。
///
#ifndef INCLUDED_EG_EG_FACE_HEADER_
#define INCLUDED_EG_EG_FACE_HEADER_
#include <vector>
#include "vertex_data.hpp"
BEGIN_EG_EG
struct Face
{
    std::vector<VertexData> vertices_;  ///< 頂点
};
END_EG_EG
#endif /// INCLUDED_EG_EG_FACE_HEADER_
/// EOF
