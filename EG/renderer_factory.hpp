#ifndef INCLUDED_EG_EG_RENDERER_FACTORY_HEADER_
#define INCLUDED_EG_EG_RENDERER_FACTORY_HEADER_
// �쐬�� : ��
#include <unordered_map>
#include "renderer.hpp"

// �v���b�g�t�H�[���̒ǉ�
#define ADD_RENDERER( ID, pCreateFunction ) \
BEGIN_EG_EG \
namespace impl{} namespace { namespace impl { \
AddRenderer add_renderer( ID, pCreateFunction ); \
}} END_EG_EG


BEGIN_EG_EG
//
// �����_���[�p�t�@�N�g��
// �V���O���g���N���X�ł��B�A�N�Z�X�ɂ�instance�֐����g�p���Ă��������B
//
class RendererFactory
{
public :
    // �C���X�^���X�ւ̃A�N�Z�X
    static RendererFactory* instance() { static RendererFactory i; return &i; }

    //
    // �����_���[�̓o�^
    //
    // in ID : �����_���[ID
    // in pCreateFunction : �������������������֐��ւ̃|�C���^
    //
    void registerRenderer( RendererID ID, IRenderer*(*pCreateFunction)() )
    {
        functions_[ID] = pCreateFunction;
    }
    
    //
    // �����_���[�̐���
    //
    // in ID : �������郌���_���[��ID
    // in pOutPtr : ���������I�u�W�F�N�g�ւ̃|�C���^���i�[����ϐ��̃A�h���X
    //
    // out true  : ��������
    // out false : �������s
    //
    bool create( RendererID ID, IRenderer** pOutPtr )
    {
        auto function = functions_.find(ID);
        if( function == functions_.end() ) return false;

        *pOutPtr = function->second();
        return true;
    }

private :
    RendererFactory() = default;
    std::unordered_map<RendererID, IRenderer*(*)()> functions_;
};

class AddRenderer
{
public :
    AddRenderer( RendererID ID, IRenderer*(*pFunc)() )
    {
        RendererFactory::instance()->registerRenderer( ID, pFunc );
    }
};
END_EG_EG
#endif // INCLUDED_EG_EG_RENDERER_FACTORY_HEADER_
// EOF
