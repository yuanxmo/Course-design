#ifndef STUDENT_H_
#define STUDENT_H_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h>

#include "INTERFACE.h"
#include "MESSAGE.h"
#include "TEACHER.h"
#include "USER.h"

//学生端开始菜单
void student_menu(Node *head,char *user)
{
    int j = 0;
    int k = 1;
    char i;
    do {
        i = student_LoadAdd();
        switch(i) {
            case 1:
                j = User_Load(head,user);
                if (j)  {
                    k = 0;
                }
                break;
            case 2:
                User_Add(head);
                break;
            case 3:
                MisRemind(head);
                break;
            case 4:
                exit(-1);
                break;
            default:
                printf("\t\t\t更多功能敬请期待!\n");
                Sleep(750);
        }
    }while (k);
}
//绑定学生信息
//检查是否绑定
int BoundOK(Node *head,char *user,char *NO)
{
    Node *p;
    p = head->next;
    while (p != NULL)  {
        if (strcmp(p->data.USER,user) == 0) {
            if (strcmp(p->data.ENROLL,"0") == 0) {
                strcpy(NO,p->data.ENROLL);
                return 0;
            }
            else {
                strcpy(NO,p->data.ENROLL);
                return 1;
            }
        }
        p = p->next;
    }
    return 0;
}
//更改用户名密码文件
void ChangeUserFile(Node *head,char *user,char *NO)
{
    Node *p;
    p = head->next;
    while (p != NULL) {
        if (strcmp(p->data.USER,user) == 0)  {
            strcpy(p->data.ENROLL,NO);
            break;
        }
        p = p->next;
    }
    OutputFile(head);
}
//更改学生信息文件
void ChangeMessageFile(struct node *head,char *NO,char *USER,char *PHONE,char *QQ,char *EMAIL)
{
    struct node *p;
    p = head->next;
    while (p != NULL)  {
        if (strcmp(p->data.NO,NO) == 0)  {
            strcpy(p->data.USER,USER);
            strcpy(p->data.PHONE,PHONE);
            strcpy(p->data.QQ,QQ);
            strcpy(p->data.EMAIL,EMAIL);
            break;
        }
        p = p->next;
    }
    nodeOutputFile(head);
}
void BoundMessageInit(Node *head,struct node *head_mess,char *user,char *NO)
{
    int CLASS;
    char no[15];
    char PHONE[13];
    char QQ[12];
    char EMAIL[25];
    do {
        //班级
        printf("\t\t\t\t请输入班级:");
        scanf("%d",&CLASS);
        //学号
        printf("\t\t\t\t请输入学号:");
        scanf("%s",no);
        //查找学号是否存在
        int i = no_repition(head_mess,no);
        if (!i) 
            break;
        printf("\t\t\t\t学号不存在!\n");
        Sleep(750);
        system("cls");
    }while(1);
    //手机号
    printf("\t\t\t\t请输入手机号:");
    scanf("%s",PHONE);
    //qq号
    printf("\t\t\t\t请输入QQ:");
    scanf("%s",QQ);
    //邮箱
    printf("\t\t\t\t请输入邮箱:");
    scanf("%s",EMAIL);
    ChangeUserFile(head,user,no);
    ChangeMessageFile(head_mess,no,user,PHONE,QQ,EMAIL);
    strcpy(NO,no);
    //绑定成功
    printf("\t\t\t\t绑定成功!\n\t\t\t\t");
    system("pause");
}
//完善学生信息
void BoundMessage(Node *head_user,struct node *head_mess,char *user,char *NO)
{
    student_bound();
    int i = BoundOK(head_user,user,NO);
    if (i)  {
        printf("\t\t\t\t账号已绑定!\n\t\t\t\t");
        system("pause");
        return;
    }
    BoundMessageInit(head_user,head_mess,user,NO);
}
//查看学生信息
void DisplayStudent(struct node *head,char *NO)
{
    int CLASS;
    struct node *p;
    p = head->next;
    while (p != NULL) {
        if (strcmp(p->data.NO,NO) == 0) {
            CLASS = p->data.CLASS;
            break;
        }
        p = p->next;
    }
    FindMessageNO(head,NO,CLASS);
}
//修改学生信息
void ChangeStudent(struct node *head,char *NO)
{
    struct node *p;
    p = head->next;
    int i = 0;
    while (p != NULL)  {
        if (strcmp(p->data.NO,NO) == 0) {
            printf("\t\t\t\t找到相关信息!\n");
            printf("\t\t\t\t请输入手机号:");
            scanf("%s",p->data.PHONE);
            printf("\t\t\t\t请输入  QQ  :");
            scanf("%s",p->data.QQ);
            printf("\t\t\t\t请输入邮  箱:");
            scanf("%s",p->data.EMAIL);
            i = 1;
            break;
        }
        p = p->next;
    }
    if (!i) {
        printf("\t\t\t\t未修改!\n\t\t\t\t");
        Sleep(750);
        return;
    }
    nodeOutputFile(head);
    printf("\t\t\t\t修改成功!\n");
    Sleep(500);
}
//查看账号信息
void DisplayUser(Node *head,char *user)
{
    printf("\t\t\t\t帐号:%s\n",user);
    printf("\t\t\t\t密码:");
    Node *p;
    p = head->next;
    while (p != NULL)  {
        if(strcmp(p->data.USER,user) == 0)  {
            int i = 0;
            while(p->data.KEY[i]) {
                printf("*");
                i++;
            }
            printf("\n");
            return;
        }
        p = p->next;
    }
}
//输入新密码
void InputKEY1(char *key)
{
    char key_again[17];
    do {
        printf("\t\t\t\t请输入新密码:");
        scanf("%s",key);
        printf("\t\t\t\t请再次输入:");
        scanf("%s",key_again);
        if (strcmp(key,key_again) == 0)
            return;
        printf("\t\t\t\t密码不一致!\n");
        Sleep(750);
        system("cls");
    }while(1);
}
//储存信息
void NodeFile(Node *head,char *user,char *key)
{
    Node *p;
    p = head->next;
    while (p != NULL) {
        if (strcmp(p->data.USER,user) == 0)  {
            strcpy(p->data.KEY,key);
            break;
        }
        p = p->next;
    }
    OutputFile(head);
    head = Node_Input();
}
//修改密码
void ChangeKey(Node *head,char *user)
{
    char key[17];
    char oldkey[17];
    Node *p;
    p = head->next;
    while (p != NULL)  {
        if (strcmp(p->data.USER,user) == 0)  {
            strcpy(oldkey,p->data.KEY);
            break;
        }
        p = p->next;
    }
    do {
        printf("\t\t\t\t请输入旧密码(输入back退出):");
        scanf("%s",key);
        if (strcmp(key,"back") == 0)
            return;
        if (strcmp(oldkey,key) == 0) {
            InputKEY1(key);
            NodeFile(head,user,key);
            return;
        }
        printf("\t\t\t\t密码错误!\n");
        Sleep(750);
    }while(1);
}
//帐号信息
void UserMessage(Node *head,char *user)
{
    int i;
    do {
        student_user();
        DisplayUser(head,user);
        printf("\t\t\t\t1.修改密码\n");
        printf("\t\t\t\t2.退出\n");
        printf("\t\t\t\t请输入功能序号:");
        scanf("%d",&i);
        if (i == 1) {
            ChangeKey(head,user);
            return;
        }
        else if (i == 2)  {
            return;
        }
        printf("\t\t\t\t更多功能敬请期待...\n");
        Sleep(500);
        system("cls");
    }while(1);
}

void student(Node *head,struct node *head_mess)
{
    char user[20];
    char NO[15];
    student_menu(head,user);
    int i;
    do {
        i = student_switch();
        switch (i) {
            case 1:
                BoundMessage(head,head_mess,user,NO);
                break;
            case 2:
                DisplayStudent(head_mess,NO);
                break;
            case 3:
                ChangeStudent(head_mess,NO);
                break;
            case 4:
                UserMessage(head,user);
                break;
            case 5:
                exit(-1);
                break;
            default:
                printf("\t\t\t\t更多功能敬请期待...\n");
                Sleep(500);
                break;
        }
    }while(1);
}

#endif