#ifndef INCLUDED_EG_EG_VERTEX_SHADER_HEADER
#define INCLUDED_EG_EG_VERTEX_SHADER_HEADER
// �쐬�� : ��
#include "easy_engine.hpp"

BEGIN_EG_EG
//
// ���_�V�F�[�_�[
//
class IVertexShader
{
public:
    virtual ~IVertexShader() = default;

    virtual void release() = 0;
};
END_EG_EG
#endif
// EOF
