///
/// @file    renderer_factory.hpp
/// @author  ��
///
/// @brief   �����_���[�̃t�@�N�g��
/// @details �V���O���g���N���X�ł��B�A�N�Z�X�ɂ�instance�֐����g�p���ĉ������B<br>
///          �V���������_���[�̓o�^��ADD_RENDERER�}�N�����g���ƊȒP�ɍς݂܂��B
///
#ifndef INCLUDED_EG_EG_RENDERER_FACTORY_HEADER_
#define INCLUDED_EG_EG_RENDERER_FACTORY_HEADER_
#include <unordered_map>
#include "renderer.hpp"

///
/// @def     ADD_RENDERER
/// @brief   �����_���[�̓o�^����
/// @details �w�b�_�[�t�@�C���ŌĂяo���Ȃ��ł��������B
///
/// @param[in] ID : �o�^���郌���_���[����ID
/// @param[in] pCreateFunction : �������������������֐��̃A�h���X
///
#define ADD_RENDERER( ID, pCreateFunction ) \
BEGIN_EG_EG \
namespace impl{} namespace { namespace impl { \
AddRenderer add_renderer( ID, pCreateFunction ); \
}} END_EG_EG

BEGIN_EG_EG
class RendererFactory
{
public :
    ///
    /// @brief  �C���X�^���X���擾���܂��B
    ///
    /// @return �C���X�^���X�̃A�h���X
    ///
    static RendererFactory* instance() { static RendererFactory i; return &i; }

    ///
    /// @brief  �����_���[�̓o�^
    ///
    /// @param[in]  ID : �����_���[����ID
    /// @param[in]  pCreateFunction : �����_���[�����֐��ւ̃|�C���^
    ///
    void registerRenderer( RendererID ID, IRenderer*(*pCreateFunction)() )
    {
        functions_[ID] = pCreateFunction;
    }
    
    ///
    /// @brief  �����_���[�̐���
    ///
    /// @param[in]  ID : �������郌���_���[�̎���ID
    /// @param[out] ppOutRenderer : �������������_���[���󂯎��C���^�[�t�F�C�X�̃A�h���X
    ///
    /// @return �����ɐ��������ꍇ[ true ] ���s�����ꍇ[ false ]��ԋp���܂��B
    ///
    bool create( RendererID ID, IRenderer** ppOutRenderer )
    {
        auto function = functions_.find(ID);
        if( function == functions_.end() ) return false;

        *ppOutRenderer = function->second();
        return true;
    }

private :
    RendererFactory() = default;
    std::unordered_map<RendererID, IRenderer*(*)()> functions_; /// �����_���[���������֐��̃A�h���X�Q
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
#endif /// INCLUDED_EG_EG_RENDERER_FACTORY_HEADER_
/// EOF
