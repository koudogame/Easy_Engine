// �쐬�� : ��
#include <Windows.h>
#include <crtdbg.h>
#include "game.hpp"
#include "shader_loader_d3d11.hpp"

// �G���g���[�|�C���g
int WINAPI WinMain(
    HINSTANCE hInstance,
    HINSTANCE ,
    LPSTR     lpCmdLine,
    int       nCmdShow )
{
    
#ifdef  _DEBUG
	//���������[�N�̃`�F�b�N
	//_CrtSetBreakAlloc(751);
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif
    using namespace easy_engine;
    Game::instance()->execute();
}
// EOF
