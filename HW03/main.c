#include <stdio.h>
#include <Windows.h>
#include <math.h>

#define PI 3.141592653589793

void moveCursor(int x, int y)
{
    printf("\x1b[%d;%dH", y, x);
}

// 0: 폭발 전 
// 1: 폭발 후 
void printBomb(int isExploded)
{
    if (isExploded)
    {
        printf("\x1b[A^^^^^^^");
        printf("\x1b[B\x1b[7D!!BAM!!");
        printf("\x1b[B\x1b[7D^^^^^^^");
    }
    else {
        printf("(  b  )");
    }
}

int main()
{
    int centerX = 14, centerY = 9;
    int squares = 3;
    int radiusStep = 2;
    int delay = 200;

    printf("\x1b[2J"); // 화면 지우기
    moveCursor(centerX, centerY);
    printf("*");
    fflush(stdout);

    int x, y; // 마지막 좌표용

    // ------------------ 회오리 그리기 ------------------
    for (int k = 1; k <= squares; k++)
    {
        int size = radiusStep * k;
        int pointsPerSide = size * 2;

        int firstX = centerX - size;
        int firstY = centerY + size;

        for (int i = 0; i < 4 * pointsPerSide; i++)
        {
            double theta = (2 * PI * i) / (4 * pointsPerSide);

            if (theta < PI / 2) { // 아래쪽
                double local = theta / (PI / 2);
                x = centerX - size + (int)round(local * 2 * size);
                y = centerY + size;

                if (x == firstX) continue;
                if (x == centerX - size + 1) continue;
                if (x == centerX - size + 2) {
                    moveCursor(x, y - 1);
                    printf("#");
                    fflush(stdout);
                }
            }
            else if (theta < PI) { // 오른쪽
                double local = (theta - PI / 2) / (PI / 2);
                x = centerX + size;
                y = centerY + size - (int)round(local * 2 * size);
            }
            else if (theta < 3 * PI / 2) { // 위쪽
                double local = (theta - PI) / (PI / 2);
                x = centerX + size - (int)round(local * 2 * size);
                y = centerY - size;
            }
            else { // 왼쪽
                double local = (theta - 3 * PI / 2) / (PI / 2);
                x = centerX - size;
                y = centerY - size + (int)round(local * 2 * size);

                if (k == squares) {
                    // 마지막 사각형의 왼쪽 세로 맨 위 좌표 저장
                    x = centerX - size;
                    y = centerY - size;
                    break; // 맨 위 좌표 결정
                }
            }

            moveCursor(x, y);
            printf("#");
            fflush(stdout);
        }

        if (k != squares) {
            moveCursor(firstX, firstY);
            printf("#");
            fflush(stdout);
        }
    }
    int finalSize2 = radiusStep * squares;
    moveCursor(centerX - finalSize2, centerY - finalSize2);
    printf("#");

    // ------------------ 회오리 끝에 폭탄 출력 ------------------
    // 폭탄 오른쪽 끝이 회오리 끝점과 맞닿도록 조정
    int memor_x = x - 7, memory_y = y;
    moveCursor(memor_x, memory_y);
    printBomb(0);
    fflush(stdout);

    moveCursor(centerX, centerY);
    printf(" ");
    Sleep(200);
    // ------------------ 지우기 ------------------
    for (int k = 1; k <= squares; k++)
    {
        int size = radiusStep * k;
        int pointsPerSide = size * 2;

        int firstX = centerX - size;
        int firstY = centerY + size;


        for (int i = 0; i < 4 * pointsPerSide; i++)
        {
            double theta = (2 * PI * i) / (4 * pointsPerSide);

            if (theta < PI / 2)
            { // 아래쪽
                double local = theta / (PI / 2);
                x = centerX - size + (int)round(local * 2 * size);
                y = centerY + size;

                if (x == firstX) continue;
                if (x == centerX - size + 1) continue;
                if (x == centerX - size + 2)
                {
                    moveCursor(x, y - 1);
                    printf("*");
                    fflush(stdout);
                    Sleep(delay);
                    moveCursor(x, y - 1);
                    printf(" ");
                    fflush(stdout);
                }
            }
            else if (theta < PI)
            { // 오른쪽
                double local = (theta - PI / 2) / (PI / 2);
                x = centerX + size;
                y = centerY + size - (int)round(local * 2 * size);
            }
            else if (theta < 3 * PI / 2)
            { // 위쪽
                double local = (theta - PI) / (PI / 2);
                x = centerX + size - (int)round(local * 2 * size);
                y = centerY - size;
            }
            else
            { // 왼쪽
                double local = (theta - 3 * PI / 2) / (PI / 2);
                x = centerX - size;
                y = centerY - size + (int)round(local * 2 * size);

                if (k == squares) continue;
            }

            moveCursor(x, y);
            printf("*");
            fflush(stdout);
            Sleep(delay);

            moveCursor(x, y);
            printf(" ");
            fflush(stdout);
        }

        if (k != squares)
        {
            moveCursor(firstX, firstY);
            printf("*");
            fflush(stdout);
            Sleep(delay);
            moveCursor(firstX, firstY);
            printf(" ");
            fflush(stdout);
        }
    }



    // 마지막 맨 위 맨 왼쪽도 지우기
    finalSize2 = radiusStep * squares;
    moveCursor(centerX - finalSize2, centerY - finalSize2);
    printf("*");
    fflush(stdout);
    Sleep(delay);
    moveCursor(centerX - finalSize2, centerY - finalSize2);
    printf(" ");
    fflush(stdout);
    moveCursor(memor_x, memory_y);
    printBomb(1);


    moveCursor(10, 20);
    return 0;
}