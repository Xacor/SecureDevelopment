#include<stdio.h>  
#include<time.h>
#include<string.h>

int main() {
    FILE* file;
    const size_t len = 1024;

    if (fopen_s(&file, "text.rkd", "r+")) {
        printf_s("Error opening file!");
        getchar();
        return 0;
    }

    char buffer[len] = { 0 };
    fread_s(buffer, len, sizeof(char), len, file);
    printf_s("%s\n", buffer);

    time_t rawtime;
    struct tm info;
    time(&rawtime);
    localtime_s(&info, &rawtime);

    memset(buffer, '\0', len);
    strftime(buffer, len, "%Y-%m-%d %H:%M:%S ", &info);
    strcat_s(buffer, "Hello, World!\n");

    fseek(file, 0, SEEK_SET);
    fwrite(buffer, sizeof(char), len, file);

    fclose(file);

    getchar();

    return 0;


}