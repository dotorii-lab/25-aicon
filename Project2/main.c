#include <stdio.h>
#include <math.h>
#include <Windows.h>

#define PI 3.14159226535897

void moveCursor(int x, int y)
{
    printf("\x1b[%d;%dH", y, x);
}

//�Ű����� isExploded
//0: ������ ��ź
//1: ������
void printBomb(int isExploded)
{
    //��ź�� �׻� 7ĭ
    if (isExploded)
    {
        printf("\x1b[A^^^^^^^");
        printf("\x1b[B\x1b[7D!!BAM!!");
        printf("\x1b[B\x1b[7D^^^^^^^");
    }
    else
        printf("(  b  )");
}

int main()
{
    int StartPointX = 10;
    int StartPointY = 5;
    int MoveDirX = -1;
    int MoveDirY = 0;
    double angle = PI;

    //HINT: ��ȭ���κк��� �׸���
    StartPointX += 4;
    StartPointY += 4;
    moveCursor(StartPointX, StartPointY);   //�� �ٴ� ��ȭ�� �κ�
    printf("*");

    int i = 0;
    int iCount = 1;
    int j = 0;
    int k = 0;
    for (k = 0; k < 6; k++)
    {
        for (j = 0; j < 2; j++)
        {
            angle -= PI / 2.0;
            MoveDirX = round(cos(angle));
            MoveDirY = round(sin(angle));
            for (i = 0; i < iCount * 2; i++)
            {
                StartPointX += MoveDirX;
                StartPointY += MoveDirY;
                moveCursor(StartPointX, StartPointY);   //�� �ٴ� ��ȭ�� �κ�
                printf("#");
            }
        }
        iCount++;
    }

    //��ź�׸���
    moveCursor(StartPointX - 7, StartPointY);   //��ź ĭ��ŭ ����
    printBomb(0);

    //StartPointX = 14;
    //StartPointY = 9;

    //moveCursor(StartPointX, StartPointY);   //�� �ٴ� ��ȭ�� �κ�
    //printf("*");
    //
    //Sleep(200);
    //moveCursor(StartPointX, StartPointY);   //�� �ٴ� ��ȭ�� �κ�
    //printf(" ");


    //iCount = 1;
    //
    //for (k = 0; k < 6; k++)
    //{
    //    for (j = 0; j < 2; j++)
    //    {
    //        angle -= PI / 2.0;
    //        MoveDirX = round(cos(angle));
    //        MoveDirY = round(sin(angle));
    //        for (i = 0; i < iCount * 2; i++)
    //        {
    //            StartPointX += MoveDirX;
    //            StartPointY += MoveDirY;
    //            moveCursor(StartPointX, StartPointY);   //�� �ٴ� ��ȭ�� �κ�
    //            printf("*");
    //            Sleep(200);
    //            moveCursor(StartPointX, StartPointY);   //�� �ٴ� ��ȭ�� �κ�
    //            printf(" ");
    //        }
    //    }
    //    iCount++;
    //}

    ////��ź�׸���
    //moveCursor(StartPointX - 7, StartPointY);   //��ź ĭ��ŭ ����
    //printBomb(1);



    moveCursor(10, 20);
    return 0;
}