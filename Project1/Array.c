#include <stdio.h>
#include <stdlib.h>
#include <time.h> // srand()와 time() 함수를 위해 필요해요!

#define ALPHABET_SIZE (122 - 97 + 1) // 'a' 부터 'z' 까지 총 26개의 알파벳

// 두 문자의 값을 서로 교환하는 swap 함수
void swap(char* a, char* b) {
    char temp = *a; // 임시 변수에 첫 번째 문자를 저장
    *a = *b;       // 첫 번째 문자에 두 번째 문자를 저장
    *b = temp;     // 두 번째 문자에 임시 변수에 저장했던 첫 번째 문자를 저장
}

int main() {
    char random_alphabets[ALPHABET_SIZE]; // 알파벳을 저장할 배열

    // 1. 'a'부터 'z'까지 순서대로 배열에 채워 넣기 (초기 정렬)
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        random_alphabets[i] = 'a' + i; // 'a', 'b', ..., 'z'
    }

    // 2. 무작위 시드 초기화 (프로그램 실행마다 다른 결과가 나오도록)
    srand(time(NULL));

    // 3. 피셔-예이츠 셔플 알고리즘으로 배열 무작위로 섞기 (무작위 정렬/셔플링)
    // 배열의 마지막 요소부터 첫 번째 요소까지 순회하면서 무작위로 위치를 바꿔요.
    for (int i = ALPHABET_SIZE - 1; i > 0; i--) {
        // 0부터 i까지의 무작위 인덱스 선택
        int rand_index = rand() % (i + 1);

        // 현재 요소 (random_alphabets[i])와 무작위로 선택된 요소 (random_alphabets[rand_index])의 위치를 교환
        swap(&random_alphabets[i], &random_alphabets[rand_index]);
    }

    // 4. 결과를 세로로 출력
    printf("무작위로 섞인 알파벳 목록 (세로):\n");
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        printf("%c\n", random_alphabets[i]); // 한 문자마다 줄바꿈해서 세로로 출력
    }

    return 0; // main 함수는 int를 반환해야 합니다.
}