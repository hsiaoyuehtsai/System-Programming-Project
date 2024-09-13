#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libgen.h>  // for basename

int main(int argc, char *argv[]) {
    // 使用 argv[0] 判斷當前的命令名稱
    char *cmd = basename(argv[0]);  // 取得當前程式的名稱

    // 構造需要執行的命令字串
    char command[512] = {0};  // 存儲完整命令
    strcat(command, cmd);     // 將命令名稱加入到字串中

    // 將其餘的命令引數加到字串中
    for (int i = 1; i < argc; i++) {
        strcat(command, " ");
        strcat(command, argv[i]);
    }

    // 執行最終的命令
    int ret = system(command);  // 調用外部命令
    if (ret == -1) {
        perror("system");
        return 1;
    }

    return 0;
}
