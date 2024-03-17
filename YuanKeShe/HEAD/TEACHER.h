#ifndef TEACHER_H_
#define TEACHER_H_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h>

#include "INTERFACE.h"
#include "USER.h"
#include "MESSAGE.h"


void TEALoad()
{
    char temp[20];
    char KEY[20];
    FILE *file;
    file = fopen("DATA/KEY.txt","r");
    if (file == NULL)  {
        printf("\t\t\t\t打开文件失败!\n");
        Sleep(750);
        exit(-1);
    }
    fscanf(file,"%s %s",temp,KEY);
    do {
        teacher_welcome();
        printf("\t\t\t\t请输入登录代码:");
        scanf("%s",temp);

        if (strcmp(temp,KEY) == 0) {
            return;
        }
        printf("\t\t\t\t输入错误,请重试!\n");
        Sleep(750);
    }while(1);
}
//添加学生信息
//输入的班级保证在1-5班
void justy_class(int *class_num)
{
    printf("\t\t\t\t请输入班级:");
    scanf("%d",class_num);
    if (*class_num >= 1 && *class_num <= 5)  
        return;
    while (1)  {
        printf("\t\t\t\t输入有误,请重新输入");
        scanf("%d",class_num);
        if ((*class_num >= 1 && *class_num <= 5))  
            return;
    }
}
//输入成绩保证范围在0-100
void justy_ok(float *score)
{
    scanf("%f",score);
    if (*score >= 0 && *score <= 100)  
        return;
    while (1)  {
        printf("\t\t\t\t输入有误,请重新输入:");
        scanf("%f",score);
        if (*score >= 0 && *score <= 100)  
            return;
    }
}
//学号重复
int no_repition(struct node *head,char *no)
{
    struct node *p;
    p = head->next;
    while (p != NULL)  {
        if (strcmp(p->data.NO,no) == 0)
            return 0;
        p = p->next;
    }
    return 1;
}
//单个添加
void AddMessage1(struct node *head)
{
    teacheradd();
    FILE *file;
    file = fopen("DATA/MESSAGE.txt","a");
    if (file == NULL)  {
        printf("\t\t\t\t打开文件失败!\n\t\t\t\t添加失败!\n");
        Sleep(1000);
        return;
    }
    int class_num;
    char NO[15];
    char NAME[11];
    float SCORE[4];
    char USER[20];
    char PHONE[13];
    char QQ[12];
    char EMAIL[25];
    int i;
    justy_class(&class_num);
    do {
        teacheradd();
        printf("\t\t\t\t请输入班级:%d\n",class_num);
        printf("\t\t\t\t请输入学号:");
        scanf("%s",NO);
        i = no_repition(head,NO);
        if (!i)  {
            printf("\t\t\t\t学号重复!\n");
            Sleep(500);
            continue;
        }
        break;
    }while(1);
    printf("\t\t\t\t请输入姓名:");
    scanf("%s",NAME);
    printf("\t\t\t\t请输入语文成绩:");
    justy_ok(&SCORE[0]);
    printf("\t\t\t\t请输入英语成绩:");
    justy_ok(&SCORE[1]);
    printf("\t\t\t\t请输入数学成绩:");
    justy_ok(&SCORE[2]);
    SCORE[3] = SCORE[0] + SCORE[1] +SCORE[2];
    fprintf(file,"%d %s %s %.2f %.2f %.2f %.2f %s %s %s %s\n",
    class_num,NO,NAME,SCORE[0],SCORE[1],SCORE[2],SCORE[3],"未填写","未填写","未填写","未填写");
    fclose(file);
    Sleep(500);
}
void AddMessage3(struct node *head,int j)
{
    teacheradd();
    FILE *file;
    file = fopen("DATA/MESSAGE.txt","a");
    if (file == NULL)  {
        printf("\t\t\t\t打开文件失败!\n\t\t\t\t添加失败!\n");
        Sleep(1000);
        return;
    }
    int year;
    int class_num;
    char NO[15];
    char NAME[11];
    float SCORE[4];
    char USER[20];
    char PHONE[13];
    char QQ[12];
    char EMAIL[25];
    int i;
    printf("\t\t\t\t第%d次输入\n",j+1);
    justy_class(&class_num);
    do {
        teacheradd();
        printf("\t\t\t\t第%d次输入\n",j+1);
        printf("\t\t\t\t请输入班级:%d\n",class_num);
        printf("\t\t\t\t请输入学号:");
        scanf("%s",NO);
        i = no_repition(head,NO);
        if (!i)  {
            printf("\t\t\t\t学号重复!\n");
            Sleep(500);
            continue;
        }
        break;
    }while(1);
    printf("\t\t\t\t请输入姓名:");
    scanf("%s",NAME);
    printf("\t\t\t\t请输入语文成绩:");
    justy_ok(&SCORE[0]);
    printf("\t\t\t\t请输入英语成绩:");
    justy_ok(&SCORE[1]);
    printf("\t\t\t\t请输入数学成绩:");
    justy_ok(&SCORE[2]);
    SCORE[3] = SCORE[0] + SCORE[1] +SCORE[2];
    fprintf(file,"%d %s %s %.2f %.2f %.2f %.2f %s %s %s %s\n",
    class_num,NO,NAME,SCORE[0],SCORE[1],SCORE[2],SCORE[3],"未填写","未填写","未填写","未填写");
    fclose(file);
    Sleep(500);
}
//批量添加
void AddMessage2(struct node *head)
{
    teacheradd();
    printf("\t\t\t\t请输入数量:");
    int num;
    scanf("%d",&num);
    for (int i = 0; i < num; i++)  {
        teacheradd();
        printf("\t\t\t\t第%d次输入\n",i + 1);
        AddMessage3(head,i);
    }
}
//删除学生信息
void RemoveMessageTEA(struct node *head)
{
    teacherremove();
    printf("\t\t\t\t请输入要删除的学号:");
    char NO[15];
    scanf("%s",NO);
    RemoveMessage(head,NO);
    nodeOutputFile(head);
    head = nodeFile();
}
//查找学生信息
void FindMessageTEA(struct node *head)
{
    teacherfind();
    int CLASS;
    char NO[15];
    printf("\t\t\t\t请输入班级:");
    scanf("%d",&CLASS);
    printf("\t\t\t\t请输入学号:");
    scanf("%s",NO);
    FindMessageNO(head,NO,CLASS);
}
//修改学生信息
void ChangeMessageTEA(struct node *head)
{
    int i;
    teacherchange();
    char NO[15];
    printf("\t\t\t\t请输入学号:");
    scanf("%s",NO);
    struct node *p;
    p = head->next;
    while (p != NULL)  {
        if (strcmp(p->data.NO,NO) == 0)  {
            printf("\t\t\t\t查找到相关信息!\n");
            justy_class(&(p->data.CLASS));
            do {
                teacherchange();
                printf("\t\t\t\t请输入学号:%s\n",NO);
                printf("\t\t\t\t查找到相关信息!\n");
                printf("\t\t\t\t请输入班级:%d\n",p->data.CLASS);
                printf("\t\t\t\t请输入学号:");
                char NO1[15];
                scanf("%s",NO1);
                i = no_repition(head,NO1);
                if (!i)  {
                    printf("\t\t\t\t学号重复!\n");
                    Sleep(500);
                    continue;
                }
                break;
            }while(1);
            printf("\t\t\t\t请输入姓名:");
            scanf("%s",p->data.NAME);
            printf("\t\t\t\t请输入语文成绩:");
            justy_ok(&(p->data.SCORE[0]));
            printf("\t\t\t\t请输入英语成绩:");
            justy_ok(&(p->data.SCORE[1]));
            printf("\t\t\t\t请输入数学成绩:");
            justy_ok(&(p->data.SCORE[2]));
            p->data.SCORE[3] = p->data.SCORE[0] + p->data.SCORE[1] + p->data.SCORE[2];
            nodeOutputFile(head);
            printf("\t\t\t\t修改成功!\n");
            Sleep(250);
            return;
        }
        p = p->next;
    }
    printf("\t\t\t\t未找到相关信息!\n");
    Sleep(750);
}
//汇总
void teacherTotal(struct node *head)
{
    int i = teachertotal(); 
    switch (i) {
        case 1:
            int CLASS;
            printf("\t\t\t\t请输入班级:");
            scanf("%d",&CLASS);
            DisplayMessageClass(head,CLASS);
            break;
        case 2:
            DisplayMessageTotal(head);
            break;
        default:
            printf("\t\t\t\t更多功能敬请期待!\n");
    }
}
//教师端
void teacher(struct node *head)
{
    TEALoad();
    printf("\t\t\t\t登录成功!\n");
    Sleep(500);
    int i;
    int j;
    do {
        i = teachermenu();
        switch (i) {
            case 1:
                teacherTotal(head);
                break;
            case 2:
                j = teacheraddmenu();
                switch (j) {
                    case 1:
                        AddMessage1(head);
                        head = nodeFile();
                        nodeOutputFile(head);
                        break;
                    case 2:
                        AddMessage2(head);
                        head = nodeFile();
                        nodeOutputFile(head);
                        break;
                    case 3:
                        break;
                    default :
                        printf("\t\t\t\t更多功能敬请期待!\n");
                        Sleep(750);
                }
                break;
            case 3:
                FindMessageTEA(head);
                break;
            case 4:
                ChangeMessageTEA(head);
                head = nodeFile();
                break;
            case 5:
                RemoveMessageTEA(head);
                head = nodeFile();
    nodeOutputFile(head);
    head = nodeFile();
                break;
            case 6:
                exit(-1);
                break;
            default:
                printf("\t\t\t\t更多功能敬请期待\n");
                Sleep(500);
                break;
        }
    }while(1);
}

#endif
