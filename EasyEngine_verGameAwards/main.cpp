// �쐬�� : ��
#include <Windows.h>
#ifdef _DEBUG
#include <crtdbg.h>
#endif // !_DEBUG
#include "egeg_math.hpp"

// �G���g���[�|�C���g
int WINAPI WinMain(
    HINSTANCE hInstance,
    HINSTANCE,
    LPSTR     lpCmdLine,
    INT       nCmdShow )
{
#ifdef  _DEBUG
    //_CrtSetBreakAlloc(  );
    _CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
#endif

    USING_NS_EGEG;

    Vector2D vec{ 1.0F };
    Vector2D vec_1{ vec };

    Vector3D vec_3;

    vec += vec_3;
    DirectX::XMVector2Dot( vec, vec_1 );
}
// EOF