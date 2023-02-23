#include <iostream>
#include <stdio.h>
#include <string.h>
#include <time.h>

char* reverseStringC(char str[], const int size) {
    char* resStr = new char[size + 1];
    for (int i = 0; i < size; i++) {
        resStr[i] = str[size - i - 1];
    }
    resStr[size] = '\0';
    return resStr;
}

char* reverseStringASM(char str[], const int strSize) {
    char* resStr = new char[strSize + 1];
    __asm {
        mov ecx, strSize
        mov esi, str        ;source index
        mov edi, resStr     ;destination index
        add edi, strSize
        mov [edi], 0
        dec edi
    L1:
        movs
        sub edi, 2
            loop L1
    }
    return resStr;
}

char* generateStr(int size) {
    char* str = new char[size + 1];
    for (int i = 0; i < size; i++) {
        str[i] = (char)(rand() % 92 + 33);
    }
    str[size] = '\0';
    return str;
}

void assemblyHelloWorld(char message[], char printFormat[]) {
     
    //int message = 65;
    __asm {
        ;message db "Hello World!", 10
        ;message_length equ $ - message
        ;mov eax, message[0]
        ;mov charTest[0], eax
        mov eax, message
        push eax
        mov eax, printFormat
        push eax
        call printf
        pop ebx
        pop ebx
    }
    //std::cout << charTest << std::endl;
}

int main()
{
    //std::cout << "Hello World!" << std::endl;
    char str[] = "Hello World!";
    //char printFormat[] = "%s\n";
    //assemblyHelloWorld(str, printFormat);
    //std::cout << (char)65 << std::endl;
    gets_s(str);
    //std::cout << strlen(str) << std::endl;
    //std::cout << str << std::endl;
    std::cout << "ASM: " << reverseStringASM(str, strlen(str)) << std::endl;
    std::cout << "C: " << reverseStringC(str, strlen(str)) << std::endl << std::endl;

    std::cout << "ASM ";
    char * str1 = generateStr(256);
    clock_t time = clock();
    for (int i = 0; i < 1000000; i++) {
        reverseStringASM(str1, 256);
    }
    std::cout << clock() - time << " ms" << std::endl;

    std::cout << "C ";
    time = clock();
    for (int i = 0; i < 1000000; i++) {
        reverseStringC(str1, 256);
    }
    std::cout << clock() - time << " ms" << std::endl;

}

