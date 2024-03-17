#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h>

#include "HEAD/INTERFACE.h"
#include "HEAD/USER.h"
#include "HEAD/STUDENT.h"
#include "HEAD/TEACHER.h"
#include "HEAD/MESSAGE.h"

//菜单
void menu1(struct node *head_mess,Node *head)
{
    welcome();
    int i;
    do {
        i = menu();
        switch(i) {
            case 1:
                teacher(head_mess);
                break;
            case 2:
                student(head,head_mess);
                break;
            case 3:
                exit(-1);
                break;
            default:
                printf("\t\t\t\t更多功能敬请期待!\n");
                Sleep(750);
        }
    }while(1);
}

int main() 
{   welcome();
    Node *head;
    head = Node_Input();
    char user[20];
    printf("\t\t\t\t正在初始化学生信息...\n");
    struct node *head_mess;
    head_mess = nodeFile();
    printf("\t\t\t\t初始化学生信息成功!\n");
    Sleep(500);
    menu1(head_mess,head);
    system("pause");
    return 0;
}

/*
 * 1.在屏幕上输出1 2 3 三个数字，每个数字站一行
 * 2.在屏幕上输出1 2 3 三个数字，三个数字在同一行，中间用制表符分开
 * 3.以%d形式输出字符 1
 * 4.以%c形式输出数字 1 
*/