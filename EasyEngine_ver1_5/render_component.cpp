// �쐬�� : ��
/******************************************************************************

	include

******************************************************************************/
#include "render_component.hpp"
#include "level_scene.hpp"


BEGIN_EGEG

/******************************************************************************

	declaration & definition

******************************************************************************/
namespace
{
    struct InitializeFunctor
    {
        void operator()( LevelNode* Node )
        {
            if( auto* component = Node->getComponent<RenderComponent>() )
                component->initialize();
        }
    };
    struct FinalizeFunctor
    {
        void operator()( LevelNode* Node )
        {
            if( auto* component = Node->getComponent<RenderComponent>() )
                component->finalize();
        }
    };
    struct EntryFunctor
    {
        void operator()( LevelNode* Node, LevelScene* Scene )
        {
            if( auto* component = Node->getComponent<RenderComponent>() )
                component->entryScene( Scene );
        }
    };
    struct ExitFunctor
    {
        void operator()( LevelNode* Node, LevelScene* Scene )
        {
            if( auto* component = Node->getComponent<RenderComponent>() )
                component->exitScene( Scene );
        }
    };
    
}


/******************************************************************************

	RenderComponent

******************************************************************************/
 // ������
bool RenderComponent::initialize()
{
    is_render_ = true;
    mesh_ = nullptr;
    shader_ = nullptr;
    scenes_.clear();

    getOwner()->forChild( InitializeFunctor{} );

	return true;
}


 // �I��
void RenderComponent::finalize()
{
    getOwner()->forChild( FinalizeFunctor{} );

    for( auto& scene : scenes_ )
        scene->exit( this );
}


 // �V�[���ɓ���
void RenderComponent::entryScene( LevelScene* Scene )
{
    scenes_.emplace( Scene );
    Scene->entry( this );

    getOwner()->forChild( EntryFunctor{}, Scene );
}


 // �V�[������o��
void RenderComponent::exitScene( LevelScene* Scene )
{
    getOwner()->forChild( ExitFunctor{}, Scene );

    Scene->exit( this );
    scenes_.erase( Scene );
}

END_EGEG
// EOF
