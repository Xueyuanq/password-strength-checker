#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

// 检查是否包含大写字母
bool hasUpper(char *pwd) {
    for(int i = 0; i < strlen(pwd); i++) {
        if(isupper(pwd[i])) return true;
    }
    return false; 
}

// 检查是否包含小写字母
bool hasLower(char *pwd) {
    for(int i = 0; i < strlen(pwd); i++) {
        if(islower(pwd[i])) return true;
    }
    return false;
}

// 检查是否包含数字
bool hasDigit(char *pwd) {
    for(int i = 0; i < strlen(pwd); i++) {
        if(isdigit(pwd[i])) return true;
    }
    return false;
}

// 检查是否包含特殊字符
bool hasSpecial(char *pwd) {
    for(int i = 0; i < strlen(pwd); i++) {
        if(strchr("!@#$%^&*", pwd[i])) return true;
    }
    return false;
}

// 检查是否为常见弱密码
bool isCommonWeak(char *pwd) {
    char *weak[] = {"123456", "password", "12345678", "qwerty", "abc123", "admin"};
    for(int i = 0; i < 6; i++) {
        if(strcmp(pwd, weak[i]) == 0) return true;
    }
    return false;
}

// 计算密码强度 (返回1=弱,2=中,3=强)
int checkStrength(char *pwd) {
    if(isCommonWeak(pwd)) return 1;
    
    int len = strlen(pwd);
    if(len < 6) return 1;
    
    int score = 0;
    // 长度评分
    if(len >= 8) score += 2;
    else if(len >= 6) score += 1;
    
    // 字符类型评分
    if(hasUpper(pwd)) score += 1;
    if(hasLower(pwd)) score += 1;
    if(hasDigit(pwd)) score += 1;
    if(hasSpecial(pwd)) score += 2;
    
    if(score <= 2) return 1;
    else if(score <= 4) return 2;
    else return 3;
}

// 给出改进建议
void giveSuggestion(char *pwd) {
    int len = strlen(pwd);
    if(len < 8) printf("建议: 密码长度至少8位\n");
    if(!hasUpper(pwd)) printf("建议: 包含大写字母\n");
    if(!hasLower(pwd)) printf("建议: 包含小写字母\n");
    if(!hasDigit(pwd)) printf("建议: 包含数字\n");
    if(!hasSpecial(pwd)) printf("建议: 包含特殊字符(!@#$%%^&*)\n");
    if(isCommonWeak(pwd)) printf("建议: 不要使用常见弱密码(如123456,password等)\n");
}

int main() {
    char password[100];
    char choice;
    
    printf("====== 密码强度检测器 ======\n");
    
    do {
        printf("\n请输入要检测的密码: ");
        scanf("%s", password);
        
        int strength = checkStrength(password);
        
        printf("\n检测结果:\n");
        switch(strength) {
            case 1: printf("强度等级: 弱\n"); break;
            case 2: printf("强度等级: 中\n"); break;
            case 3: printf("强度等级: 强\n"); break;
        }
        
        printf("\n改进建议:\n");
        giveSuggestion(password);
        
        printf("\n是否继续检测其他密码？(y/n): ");
        scanf(" %c", &choice);
        
    } while(choice == 'y' || choice == 'Y');
    
    printf("\n感谢使用！\n");
    return 0;
}
