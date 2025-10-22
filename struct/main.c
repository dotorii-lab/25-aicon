#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <time.h>

// ����� ����ü ����
struct Fish {
    const char* name;
    const char* talk;      // ���� ����
    int answer;            // ���� ��ȣ
    const char* talk_O;    // ���� �� ���
    const char* talk_X;    // ���� �� ���
};

// ���� ���� �Լ�
void setColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

// ���� �ʱ�ȭ
void resetColor() {
    setColor(7); // �⺻ ����
}

// �� �ִϸ��̼� �Լ�
void showBaitAnimation() {
    int i;
    for (i = 0; i < 5; i++) {
        printf(".");
        Sleep(500);
    }
    printf("\n");
}

// ���� ó�� �Լ�
int handleFishQuiz(struct Fish fish) {
    int userAnswer;
    int result;
    printf("\n%s : %s\n", fish.name, fish.talk);
    printf("����� ������? (1~3) > ");
    result = scanf_s("%d", &userAnswer);
    while (getchar() != '\n'); // ���� ����

    if (result != 1 || userAnswer < 1 || userAnswer > 3) {
        setColor(12);
        printf("�߸��� �Է��Դϴ�. ���� 1~3 ���̷� �Է��ϼ���.\n");
        resetColor();
        return 0;
    }

    if (userAnswer == fish.answer) {
        setColor(11);
        printf("\n%s\n", fish.talk_O);
        resetColor();
        return 1;
    }
    else {
        setColor(12);
        printf("\n%s\n", fish.talk_X);
        resetColor();
        return 0;
    }
}

// ��� ��� �Լ�
void printStats() {
    FILE* fp = fopen("log.txt", "r");
    int games = 0;
    int correct = 0;
    char line[100];

    if (fp != NULL) {
        while (fgets(line, sizeof(line), fp)) {
            if (line[0] == 'O') correct++;
            if (line[0] == 'O' || line[0] == 'X') games++;
        }
        fclose(fp);
    }

    printf("\n%d��° �����Դϴ�!\n", games + 1);
    if (games > 0) {
        printf("�����: %d/%d\n\n", correct, games);
    }
    else {
        printf("�����: ���� ��� ����\n\n");
    }
}

// �α� ��� �Լ�
void writeLog(const char* fishName, int isCorrect) {
    FILE* fp = fopen("log.txt", "a");
    if (fp != NULL) {
        fprintf(fp, "%s\n", fishName);
        fprintf(fp, "%s\n", isCorrect ? "O" : "X");
        fclose(fp);
    }
}

int main() {
    // ����� �迭
    struct Fish fishes[5] = {
        {"���ڸ�", "���ڸ��� ��� ���� ����̾�����?\n1) ����Ʈ\n2) ������\n3) �θ�", 3, "���豸��! �ȶ��ϳ�~", "�ƽ���, �ٽ� ���� ���γ� �Ͻð�!"},
        {"�ϸ�", "�ϸ�� � ������ϱ�?\n1) �򵿰���\n2) ����\n3) ��ġ", 1, "�ϸ� �� �ƴ±�!", "�Ƴ�~ �ϸ�� �򵿰�����~"},
        {"��ũ", "���� �������ϱ�?\n1) ��\n2) �ƴϿ�\n3) ������ ģ��", 2, "����� �����е� �˰� �ֱ�!", "���� �����~"},
        {"����", "������ �Ҿ���� ��?\n1) ����\n2) �Ȱ�\n3) �� ��", 1, "������ ����~ ��������!", "�ʵ� ����ó�� ������ �� ������?"},
        {"��ũ��", "��ũ���� � ĳ�����ϱ�?\n1) �����\n2) ����\n3) ���", 2, "��ũ�� �� ���ݾ�~", "���� �Ʊ���� ��ũ���� �����~"}
    };

    // ���� ��� ���
    printStats();

    // Y/N �Է� �ޱ�
    char yn;
    while (1) {
        printf("� ������ (Y/N) > ");
        yn = _getch();
        printf("%c\n", yn);
        if (yn == 'Y' || yn == 'y') {
            break;
        }
        else if (yn == 'N' || yn == 'n') {
            printf("������ �����մϴ�.\n");
            return 0;
        }
        else {
            printf("Y �Ǵ� N�� �Է��ϼ���.\n");
        }
    }

    // �� ������
    showBaitAnimation();

    // ���� ���
    setColor(10); // �ʷϻ�
    printf("������ �Դ�!!!!\n");
    resetColor();

    // ���� ����� ����
    srand((unsigned int)time(NULL));
    int index = rand() % 5;
    int isCorrect = handleFishQuiz(fishes[index]);

    // ��� ���
    writeLog(fishes[index].name, isCorrect);

    printf("\n������ ����Ǿ����ϴ�. �����մϴ�!\n");

    return 0;
}
