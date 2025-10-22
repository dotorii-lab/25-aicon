#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <time.h>

// 물고기 구조체 정의
struct Fish {
    const char* name;
    const char* talk;      // 퀴즈 질문
    int answer;            // 정답 번호
    const char* talk_O;    // 정답 시 대사
    const char* talk_X;    // 오답 시 대사
};

// 색상 설정 함수
void setColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

// 색상 초기화
void resetColor() {
    setColor(7); // 기본 색상
}

// 점 애니메이션 함수
void showBaitAnimation() {
    int i;
    for (i = 0; i < 5; i++) {
        printf(".");
        Sleep(500);
    }
    printf("\n");
}

// 퀴즈 처리 함수
int handleFishQuiz(struct Fish fish) {
    int userAnswer;
    int result;
    printf("\n%s : %s\n", fish.name, fish.talk);
    printf("당신의 선택은? (1~3) > ");
    result = scanf_s("%d", &userAnswer);
    while (getchar() != '\n'); // 버퍼 비우기

    if (result != 1 || userAnswer < 1 || userAnswer > 3) {
        setColor(12);
        printf("잘못된 입력입니다. 정수 1~3 사이로 입력하세요.\n");
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

// 통계 출력 함수
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

    printf("\n%d번째 게임입니다!\n", games + 1);
    if (games > 0) {
        printf("정답률: %d/%d\n\n", correct, games);
    }
    else {
        printf("정답률: 아직 기록 없음\n\n");
    }
}

// 로그 기록 함수
void writeLog(const char* fishName, int isCorrect) {
    FILE* fp = fopen("log.txt", "a");
    if (fp != NULL) {
        fprintf(fp, "%s\n", fishName);
        fprintf(fp, "%s\n", isCorrect ? "O" : "X");
        fclose(fp);
    }
}

int main() {
    // 물고기 배열
    struct Fish fishes[5] = {
        {"세자르", "세자르는 어느 나라 사람이었을까?\n1) 이집트\n2) 프랑스\n3) 로마", 3, "맞췄구나! 똑똑하네~", "아쉽군, 다시 역사 공부나 하시게!"},
        {"니모", "니모는 어떤 물고기일까?\n1) 흰동가리\n2) 고등어\n3) 참치", 1, "니모를 잘 아는군!", "아냐~ 니모는 흰동가리야~"},
        {"샤크", "상어는 포유류일까?\n1) 예\n2) 아니오\n3) 돌고래랑 친구", 2, "상어의 생물학도 알고 있군!", "상어는 어류야~"},
        {"도리", "도리가 잃어버린 건?\n1) 기억력\n2) 안경\n3) 갈 길", 1, "기억력이 좋아~ 도리보다!", "너도 도리처럼 기억력이 안 좋구나?"},
        {"핑크퐁", "핑크퐁은 어떤 캐릭터일까?\n1) 고양이\n2) 여우\n3) 상어", 2, "핑크퐁 잘 알잖아~", "상어는 아기상어고 핑크퐁은 여우야~"}
    };

    // 게임 통계 출력
    printStats();

    // Y/N 입력 받기
    char yn;
    while (1) {
        printf("찌를 던진다 (Y/N) > ");
        yn = _getch();
        printf("%c\n", yn);
        if (yn == 'Y' || yn == 'y') {
            break;
        }
        else if (yn == 'N' || yn == 'n') {
            printf("게임을 종료합니다.\n");
            return 0;
        }
        else {
            printf("Y 또는 N만 입력하세요.\n");
        }
    }

    // 찌 던지기
    showBaitAnimation();

    // 입질 출력
    setColor(10); // 초록색
    printf("입질이 왔다!!!!\n");
    resetColor();

    // 랜덤 물고기 등장
    srand((unsigned int)time(NULL));
    int index = rand() % 5;
    int isCorrect = handleFishQuiz(fishes[index]);

    // 결과 기록
    writeLog(fishes[index].name, isCorrect);

    printf("\n게임이 종료되었습니다. 감사합니다!\n");

    return 0;
}
