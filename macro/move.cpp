#include <windows.h>
#include <stdio.h>
#include <time.h>
#include "auto_move.h"

int main(void)
{

    int ret;
    int wait = 150;

    // �N���b�v�{�[�h�R�s�[
    if ((ret = read_txt()) == -1)
    {
        return 0; // �G���[
    }

    SetCursorPos(535, 630); // �L�[

    Sleep(wait + 200);

    left_click();//���N���b�N

    Sleep(wait - 50);

    key_peast(); // PEAST

    SetCursorPos(705, 717); // ACCEPT
    Sleep(wait);
    ret = left_click();
    Sleep(wait + 50);

    SetCursorPos(1728, 1016); // TOP
    Sleep(wait + 200);
    ret = left_click();
    Sleep(wait + 500);

    SetCursorPos(204, 802); // BATTLE
    Sleep(wait);
    ret = left_click();
    Sleep(wait + 200);

    SetCursorPos(241, 883); // READY
    Sleep(wait);
    ret = left_click();
    Sleep(wait);

    return ret;
}

static int read_txt(void)
{
    FILE *fp;
    char fname[] = "code.txt"; // �Ώۂ̃e�L�X�g�t�@�C��
    char str1[256];

    fp = fopen(fname, "r"); // �t�@�C�����J��
    if (fp == NULL)
    {
        printf("�G���[");
        printf("\n ���^�[���L�[�������Ă�������");
        while (getchar() != '\n');
        getchar();
        return -1;
    }

    while (1) // ������Ɉڂ�
    {
        if (fgets(str1, 256, fp) == NULL)
        {
            break;
        }
    }

    memmove(str1, str1 + 3, strlen(str1));

    HGLOBAL handl = NULL;
    int len, ir;

    len = strlen(str1);
    if (len == 0)
    {

        EmptyClipboard(); // �N���b�v�{�[�h���N���A�ɂ���
        return -1;
    }

    handl = GlobalAlloc(GMEM_FIXED, len + 1); // ���������m��
    if (handl == NULL)
    {
        printf("�G���[");
        printf("\n ���^�[���L�[�������Ă�������");
        while (getchar() != '\n')
            ;
        getchar();
        return -1;
    }
    //
    //
    char *Buf;
    Buf = (char *)GlobalLock(handl); // �m�ۂ��������������b�N���C�A�N�Z�X�\�ɂ���
    strcpy(Buf, str1);               // ������𕡎ʂ���
    GlobalUnlock(handl);             // �������̃��b�N����������
    //
    //
    ir = OpenClipboard(NULL);
    if (ir == 0)
    {
        printf("�G���[");
        printf("\n ���^�[���L�[�������Ă�������");
        while (getchar() != '\n')
            ;
        getchar();
        return -1;
    }

    EmptyClipboard();                 // �N���b�v�{�[�h���N���A�ɂ���
    SetClipboardData(CF_TEXT, handl); // �N���b�v�{�[�h�ɃR�s�[
    CloseClipboard();

    fclose(fp); // �t�@�C�������

    return 0;
}

static int left_click(void) // �}�E�X���N���b�N
{

    mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);

    // �}�E�X�̍��{�^���𗣂�
    mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);

    return 0;
}

static void key_input(long *inpu_key) // �����̃L�[����͂��܂�
{
    keybd_event(*inpu_key, 0, 0, 0);

    keybd_event(*inpu_key, 0, KEYEVENTF_KEYUP, 0);

    return;
}

static int key_peast(void) // �N���b�v�{�[�h�̓��e��\��t�����܂�
{
    keybd_event(0xA2, 0, 0, 0); // ctrl

    keybd_event(0x56, 0, 0, 0); // v

    keybd_event(0x56, 0, KEYEVENTF_KEYUP, 0);

    keybd_event(0xA2, 0, KEYEVENTF_KEYUP, 0);

    return 0;
}