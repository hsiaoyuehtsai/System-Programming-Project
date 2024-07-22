#define _GNU_SOURCE

#include <stdio.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <assert.h>
#include <time.h>
 
int main(int argc, char* argv[]) {
 
    int inputFd, outputFd;
    char *inputPtr, *outputPtr;
    ssize_t numIn, numOut;
    ssize_t fileSize=0,dataSize=0;
    //char buffer[BUF_SIZE];
    off_t data_off=0, hole_off=0, cur_off=0;
    //只可讀取模式打開
    inputFd = open (argv [1], O_RDONLY);
    if (inputFd == -1) {
        perror ("cannot open the file for read"); exit(1); }
    //open後可對該檔案＊＊『可讀可寫』＊＊（因為mmap的需求），如果沒有該檔案，就建立該檔案。如果要建立，設定該檔案的屬性為owner可讀可寫
    outputFd = open(argv[2], O_RDWR | O_CREAT, S_IRUSR| S_IWUSR);
    if(outputFd == -1){
        perror("canot open the file for write"); exit(1); }
    //🍏 🍎 拿到檔案大小的方法，用lseek移到檔案尾巴，看回傳值
    fileSize = lseek(inputFd, 0, SEEK_END);
    printf("file size = %ld\n", fileSize);
    
    inputPtr = mmap(NULL, fileSize, PROT_READ, MAP_SHARED , inputFd , 0);//🐶 🐱 🐭 🐹 🐰 🦊
    perror("mmap");
    printf("inputPtr = %p\n", inputPtr);

    ftruncate(outputFd, fileSize);  //🐶 🐱 🐭 🐹 🐰 🦊
    outputPtr = mmap(NULL, fileSize, PROT_WRITE, MAP_SHARED , outputFd , 0); //🐶 🐱 🐭 🐹 🐰 🦊
    perror("mmap, output");
    printf("outputPtr = %p\n", outputPtr);
    
    //🍏 🍎 讀到大小後記得用lseek回到原位（0）
    lseek(inputFd, 0, SEEK_SET);
    while(lseek(inputFd,0,SEEK_CUR)< fileSize){
        cur_off = lseek(inputFd, cur_off, SEEK_DATA);
        data_off = cur_off;
		cur_off = lseek(inputFd, cur_off, SEEK_HOLE);
        hole_off = cur_off;
        dataSize = hole_off - data_off;
        inputPtr += data_off;
        outputPtr += data_off;
        printf("memory copy\n");
        time_t timer1, timer2;
        timer1 = time(NULL);
        memcpy(outputPtr, inputPtr, dataSize);//🐶 🐱 🐭 🐹 🐰 🦊
        timer2 = time(NULL);
        printf("time(memcpy) = %ld sec \n", timer2 - timer1);
        lseek(inputFd,hole_off,SEEK_SET);
    }
    assert(munmap(inputPtr, fileSize) == 0);
    assert(munmap(outputPtr, fileSize) == 0);
    assert(close (inputFd) == 0);
    assert(close (outputFd) == 0);

    return (EXIT_SUCCESS);
}