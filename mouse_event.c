#include <windows.h>
#include <stdio.h>
int main()
{
    POINT pos;
    for (;;)
    {
        if (GetAsyncKeyState(0x11) & 0x01 /*ctrl*/)
        {

            GetCursorPos(&pos); // カーソル位置を取得
            printf("(%d,%d)\n", pos.x, pos.y);
        }
        else if (GetAsyncKeyState(0x1B) & 0x01 /*escape*/)
        {
            break;
        }
    }

    return 0;
}