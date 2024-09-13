#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <time.h>

int main(int argc, char* argv[]) {
    // 打開 file.db 以進行讀取和寫入
    int fd = open("flock.db", O_RDWR);
    if (fd == -1) {
        printf("無法打開 file.db。\n");
        return 1;
    }

    // 讀取數值
    char buffer[20];
    int value;

	int id = 0;
	sscanf(argv[1],"%d",&id);
	printf("Run number : %d \n",id);
	
    for (int i = 0; i < 1000; ++i) {
        // 鎖定檔案
        if (flock(fd, LOCK_EX) == -1) {
            perror("無法鎖定檔案");
            close(fd);
            return 1;
        }
		printf("Run number : %d ,Round : %d\n",id,i);

        lseek(fd, 0, SEEK_SET);
        read(fd, buffer, sizeof(buffer));
        sscanf(buffer, "%d", &value);
        printf("原始數值：%d\n", value);

        // 將新數值寫回 file.db
        sprintf(buffer, "%d", ++value);
        lseek(fd, 0, SEEK_SET);
        write(fd, buffer, sizeof(buffer));

        printf("加一後的數值：%d\n", value);

        // 解鎖檔案
        if (flock(fd, LOCK_UN) == -1) {
            perror("無法解鎖檔案");
        }

        // 等待 0.1 秒
        struct timespec delay;
        delay.tv_sec = 0;
        delay.tv_nsec = 100000; // 0.1 秒
        nanosleep(&delay, NULL);
    }
	printf("Number : %d Done \n",id);
    // 關閉檔案
    close(fd);

    return 0;
}
