#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <time.h>
#include <string.h>
#include <unistd.h>

void printFileContent(const char *filename) {
    // 使用 system() 呼叫 cat 來顯示檔案內容
    char command[512];
    snprintf(command, sizeof(command), "cat %s", filename);
    system(command);
}

int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    const char *filename = argv[1];
    struct stat fileStat;
    time_t lastModifiedTime, currentModifiedTime;

    // 初始讀取檔案狀態
    if (stat(filename, &fileStat) == -1) {
        perror("stat");
        exit(EXIT_FAILURE);
    }

    // 取得初始的修改時間
    lastModifiedTime = fileStat.st_mtime;
    printf("Initial modification time: %s", ctime(&lastModifiedTime));
    
    // 初始顯示檔案內容
    printf("Initial file content:\n");
    printFileContent(filename);
    
    // 進入監控迴圈
    while (1) {
        sleep(1); // 每秒檢查一次

        // 再次檢查檔案狀態
        if (stat(filename, &fileStat) == -1) {
            perror("stat");
            exit(EXIT_FAILURE);
        }

        // 檢查檔案修改時間是否更新
        currentModifiedTime = fileStat.st_mtime;
        if (difftime(currentModifiedTime, lastModifiedTime) != 0) {
            printf("\n\nFile modified!\n");
            printf("Last modification time: %s", ctime(&lastModifiedTime));
            printf("Current modification time: %s", ctime(&currentModifiedTime));

            // 更新最後修改時間
            lastModifiedTime = currentModifiedTime;

            // 顯示最新的檔案內容
            printf("Updated file content:\n");
            printFileContent(filename);
        }
    }

    return 0;
}
