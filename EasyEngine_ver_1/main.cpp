// �쐬�� : ��
#include <Windows.h>
#ifdef _DEBUG
#include <crtdbg.h>
#endif // !_DEBUG
//#include "application.hpp"

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
	//_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif
    //EGEG Application::instance()->execute();
}
// EOF
