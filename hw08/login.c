#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <pwd.h>
#include <grp.h>
#include <limits.h>
#include <stdlib.h>
#include <assert.h>
#include <sys/wait.h>
#include <crypt.h>    // for crypt()
#include <shadow.h>   // for getspnam()

// 去掉字串開頭的空白字符
char *ltrim(char *s) {
    while (isspace(*s)) s++;
    return s;
}

// 去掉字串結尾的空白字符
char *rtrim(char *s) {
    char *back = s + strlen(s);
    while (isspace(*--back));
    *(back + 1) = '\0';
    return s;
}

// 去掉字串開頭和結尾的空白字符
char *trim(char *s) {
    return rtrim(ltrim(s));
}

int main(int argc, char *argv[]) {
    char username[1024];
    char *namePtr;
    char passwordStr[sysconf(_SC_PASS_MAX)];
    struct passwd passwd_ent;
    struct passwd *result;
    struct spwd *shadow_entry;
    char *encrypted_password, *input_encrypted;
    struct group *gr;
    char buffer[1024];
    long ngroups_max;
    gid_t gid;
    gid_t groups[sysconf(_SC_NGROUPS_MAX)];
    int nGroup = sysconf(_SC_NGROUPS_MAX);
    int ret;
    pid_t pid;
    int wstat;



relogin:
    printf("請輸入名稱\n");
    namePtr = fgets(username, 1024, stdin);
    printf("名稱輸入: %s\n", namePtr);

    printf("請輸入密碼\n");
    strncpy(passwordStr, getpass("請輸入密碼"), sysconf(_SC_PASS_MAX));
    
    // 將字串前後的空白字符去掉
    namePtr = trim(namePtr);

    // 查詢使用者是否存在
    ret = getpwnam_r(namePtr, &passwd_ent, buffer, 1024, &result);
    if (ret != 0) {
        perror("發生錯誤：");
        goto relogin;
    }
    if (result == NULL)
    {
        printf("找不到使用者%s\n",namePtr);
        goto relogin;
    }

    // 從 /etc/shadow 中獲取該使用者的加密密碼
    shadow_entry = getspnam(namePtr);
    if (shadow_entry == NULL) {
        perror("getspnam");
        return 1;
    }

    // 將使用者輸入的密碼使用 shadow 中的值進行加密
    encrypted_password = shadow_entry->sp_pwdp;
    input_encrypted = crypt(passwordStr, encrypted_password);

    // 比較加密後的密碼和 shadow 中的密碼是否匹配
    if (strcmp(input_encrypted, encrypted_password) == 0) {
        printf("密碼正確！\n");
    } else {
        printf("密碼錯誤！\n");
        goto relogin;
    }

    pid = fork();
    if(pid > 0) {
        printf("這是parent\n");
        wait(&wstat);
        printf("回到parent\n");
    }else { 
        // 查詢使用者所屬的群組
        ret = getgrouplist(namePtr, passwd_ent.pw_gid, groups, &nGroup);
        printf("getgrouplist = %d\n", ret);
        printf("使用者編號: %d\n", passwd_ent.pw_uid);
        printf("使用者名稱: %s\n", passwd_ent.pw_name);
        printf("群組編號: %d\n", passwd_ent.pw_gid);
        printf("家目錄: %s\n", passwd_ent.pw_dir);
        printf("其他訊息: %s\n", buffer);
        printf("所隸屬的所有群組：共 %d 個\n", nGroup);
        
        for (int i = 0; i < nGroup; i++) {
            gr = getgrgid(groups[i]);
            printf("%s, ", gr->gr_name);
        }
        printf("\n");

        // 設定使用者的群組和工作目錄
        assert(setgid(passwd_ent.pw_gid) == 0);
        assert(chdir(passwd_ent.pw_dir) == 0);
        setenv("HOME", passwd_ent.pw_dir, 1);
        
        // 設定擴充群組
        setgroups(sysconf(_SC_NGROUPS_MAX), groups);
        
        // 放棄 root 權限，設定使用者的 UID
        assert(setuid(passwd_ent.pw_uid) == 0);

        char *arg[] = {"bash", NULL};
        if(execvp("bash", arg) == -1)
            exit(1);
    }
    goto relogin;
    return 0;
}
