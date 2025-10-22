#include <stdio.h>
#include <stdlib.h>
#include <time.h> // srand()�� time() �Լ��� ���� �ʿ��ؿ�!

#define ALPHABET_SIZE (122 - 97 + 1) // 'a' ���� 'z' ���� �� 26���� ���ĺ�

// �� ������ ���� ���� ��ȯ�ϴ� swap �Լ�
void swap(char* a, char* b) {
    char temp = *a; // �ӽ� ������ ù ��° ���ڸ� ����
    *a = *b;       // ù ��° ���ڿ� �� ��° ���ڸ� ����
    *b = temp;     // �� ��° ���ڿ� �ӽ� ������ �����ߴ� ù ��° ���ڸ� ����
}

int main() {
    char random_alphabets[ALPHABET_SIZE]; // ���ĺ��� ������ �迭

    // 1. 'a'���� 'z'���� ������� �迭�� ä�� �ֱ� (�ʱ� ����)
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        random_alphabets[i] = 'a' + i; // 'a', 'b', ..., 'z'
    }

    // 2. ������ �õ� �ʱ�ȭ (���α׷� ���ึ�� �ٸ� ����� ��������)
    srand(time(NULL));

    // 3. �Ǽ�-������ ���� �˰������� �迭 �������� ���� (������ ����/���ø�)
    // �迭�� ������ ��Һ��� ù ��° ��ұ��� ��ȸ�ϸ鼭 �������� ��ġ�� �ٲ��.
    for (int i = ALPHABET_SIZE - 1; i > 0; i--) {
        // 0���� i������ ������ �ε��� ����
        int rand_index = rand() % (i + 1);

        // ���� ��� (random_alphabets[i])�� �������� ���õ� ��� (random_alphabets[rand_index])�� ��ġ�� ��ȯ
        swap(&random_alphabets[i], &random_alphabets[rand_index]);
    }

    // 4. ����� ���η� ���
    printf("�������� ���� ���ĺ� ��� (����):\n");
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        printf("%c\n", random_alphabets[i]); // �� ���ڸ��� �ٹٲ��ؼ� ���η� ���
    }

    return 0; // main �Լ��� int�� ��ȯ�ؾ� �մϴ�.
}