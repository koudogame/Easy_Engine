#ifndef INCLUDED_EG_EG_APPLICATION_HEADER_
#define INCLUDED_EG_EG_APPLICATION_HEADER_

// �쐬�� : ��

#include <memory>
#include "easy_engine.hpp"

BEGIN_EG_EG

//
// �A�v���P�[�V�����N���X
//
// �V���O���g���N���X�B�A�N�Z�X�ɂ� instance�֐����g�p����B
// �Q�[���̎��s�ɍۂ��āA�v���b�g�t�H�[�����ɈقȂ�d�l���z������B
// �ÓI�ȃA�N�Z�X��񋟂���B
// �C���X�^���X�����֎~���Ă���B
//
class Application
{
public :
    //
    // �C���X�^���X�ւ̃A�h���X���擾
    //
    static Application* instance();

    //
    // ���s
    //
    void execute();

private :
    Application();
    class Impl;
    std::unique_ptr<Impl> p_impl_;
};

END_EG_EG
#endif // INCLUDED_EG_EG_APPLICATION_HEADER_
// EOF
