#include <windows.h>
#include <stdio.h>
#include <time.h>
#include "auto_move.h"

int main(void)
{

    int ret;
    int wait = 150;

    // クリップボードコピー
    if ((ret = read_txt()) == -1)
    {
        return 0; // エラー
    }

    SetCursorPos(535, 630); // キー

    Sleep(wait + 200);

    left_click();//左クリック

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
    char fname[] = "code.txt"; // 対象のテキストファイル
    char str1[256];

    fp = fopen(fname, "r"); // ファイルを開く
    if (fp == NULL)
    {
        printf("エラー");
        printf("\n リターンキーを押してください");
        while (getchar() != '\n');
        getchar();
        return -1;
    }

    while (1) // 文字列に移す
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

        EmptyClipboard(); // クリップボードをクリアにする
        return -1;
    }

    handl = GlobalAlloc(GMEM_FIXED, len + 1); // メモリを確保
    if (handl == NULL)
    {
        printf("エラー");
        printf("\n リターンキーを押してください");
        while (getchar() != '\n')
            ;
        getchar();
        return -1;
    }
    //
    //
    char *Buf;
    Buf = (char *)GlobalLock(handl); // 確保したメモリをロックし，アクセス可能にする
    strcpy(Buf, str1);               // 文字列を複写する
    GlobalUnlock(handl);             // メモリのロックを解除する
    //
    //
    ir = OpenClipboard(NULL);
    if (ir == 0)
    {
        printf("エラー");
        printf("\n リターンキーを押してください");
        while (getchar() != '\n')
            ;
        getchar();
        return -1;
    }

    EmptyClipboard();                 // クリップボードをクリアにする
    SetClipboardData(CF_TEXT, handl); // クリップボードにコピー
    CloseClipboard();

    fclose(fp); // ファイルを閉じる

    return 0;
}

static int left_click(void) // マウス左クリック
{

    mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);

    // マウスの左ボタンを離す
    mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);

    return 0;
}

static void key_input(long *inpu_key) // 引数のキーを入力します
{
    keybd_event(*inpu_key, 0, 0, 0);

    keybd_event(*inpu_key, 0, KEYEVENTF_KEYUP, 0);

    return;
}

static int key_peast(void) // クリップボードの内容を貼り付けします
{
    keybd_event(0xA2, 0, 0, 0); // ctrl

    keybd_event(0x56, 0, 0, 0); // v

    keybd_event(0x56, 0, KEYEVENTF_KEYUP, 0);

    keybd_event(0xA2, 0, KEYEVENTF_KEYUP, 0);

    return 0;
}