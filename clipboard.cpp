#include <stdio.h>
#include <string>
#include <windows.h>

int main(void)
{
  FILE *fp;
  char fname[] = "code.txt"; // 対象のテキストファイル
  char str1[256];

  fp = fopen(fname, "r"); // ファイルを開く
  if (fp == NULL)
  {
    printf("エラー");
    printf("\n リターンキーを押してください");
    while (getchar() != '\n')
      ;
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
    while (getchar() != '\n') ;
    getchar();
    return -1;
  }
//
//
char *Buf;
Buf = (char *)GlobalLock( handl ); //確保したメモリをロックし，アクセス可能にする
strcpy( Buf, str1 );   //文字列を複写する
GlobalUnlock( handl ); //メモリのロックを解除する
//
//
  ir = OpenClipboard(NULL);
  if (ir == 0)
  {
    printf("エラー");
    printf("\n リターンキーを押してください");
    while (getchar() != '\n');
    getchar();
    return -1;
  }

  EmptyClipboard();                  // クリップボードをクリアにする
  SetClipboardData(CF_TEXT, handl); // クリップボードにコピー
  CloseClipboard();

  fclose(fp); // ファイルを閉じる

  return 0;
}