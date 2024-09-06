/*
目的：了解如何調整優先權
用法：nice 接一個數字（可以是正整數，或者負整數）
測試：
nice 10	//優先權降低10
nice -10	//優先權提高10，如果不是超級使用者無法提高優先權，因此要用sudo nice -10
*/
#define _GNU_SOURCE
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <sched.h>
#include <signal.h>
#include <sched.h>
#include <stdlib.h>

long long int cpp = 0;

void alarmHandler(int signo){
    printf("cpp:%lld\n",cpp);
    exit(0);
}


int main(int argc, char **argv) {
    cpu_set_t mask; //CPU核的集合
    CPU_ZERO(&mask);
    CPU_SET(1, &mask); //先做好參數設定，綁在第一顆處理器 
    sched_setaffinity(0, sizeof(mask), &mask);//使用 sched_setaffinity 函式將程序執行限制在特定的 CPU 上

     // 檢查是否有傳入參數
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <number>\n", argv[0]);
        return 1;
    }
    // 宣告變數
    char *endptr;
    long niceValue;
    // 清除 errno，確保後續錯誤檢查的準確性
    errno = 0;
    // 將 argv[1] 轉換為 long 型別
    niceValue = strtol(argv[1], &endptr, 10);

    int childPid = fork();
    if(childPid > 0){
        nice(niceValue);
    }else{}
    signal(SIGALRM,alarmHandler);
    alarm(3);
    while(1){
        cpp++;
    }
    
	return 0;
}
