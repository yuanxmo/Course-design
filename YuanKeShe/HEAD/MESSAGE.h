#ifndef MESSAGE_h_
#define MESSAGE_h_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h>

//学生信息结构体
typedef struct {
    int  CLASS;
    char NO[15];
    char NAME[11];
    float SCORE[4];
    char USER[20];
    char PHONE[13];
    char QQ[12];
    char EMAIL[25];
}MESSAGE;

struct node {
    MESSAGE data;
    struct node *next;
};

//链表初始化
struct node *nodeInit()
{
    struct node *head;
    head = (struct node*)malloc(sizeof(struct node));
    head->next = NULL;
    return head;
}
//读取文件内容
struct node *nodeFile()
{
    struct node *head,*p,*r;
    head = nodeInit();
    FILE *file;
    file = fopen("DATA/MESSAGE.txt","r");
    if (file == NULL)  {
        printf("\t\t\t\t打开文件失败!\n");
        system("pause");
        exit(-1);
    }
    p = head;
    while (1) {
        r = (struct node*)malloc(sizeof(struct node));
        if (fscanf(file,"%d %s %s %f %f %f %f %s %s %s %s",
            &(r->data.CLASS),
            r->data.NO,
            r->data.NAME,
            &(r->data.SCORE[0]),
            &(r->data.SCORE[1]),
            &(r->data.SCORE[2]),
            &(r->data.SCORE[3]),
            r->data.USER,
            r->data.PHONE,
            r->data.QQ,
            r->data.EMAIL) != EOF) {
                p->next = r;
                p = p->next;
                continue;
            }
        break;
    }
    p->next = NULL;
    fclose(file);
    return head;
}
//成绩排序
void listInsertionSort(struct node *head) {
    struct node *sorted = NULL;
    struct node *current = head->next;
    while (current != NULL) {
        struct node *next = current->next;
        if (sorted == NULL || sorted->data.SCORE[3] <= current->data.SCORE[3]) {
            current->next = sorted;
            sorted = current;
        } else {
            struct node *temp = sorted;
            while (temp->next != NULL && temp->next->data.SCORE[3] > current->data.SCORE[3]) {
                temp = temp->next;
            }
            current->next = temp->next;
            temp->next = current;
        }
        current = next;
    }
    head->next = sorted;
}
//写入文件
void nodeOutputFile(struct node *head)
{
    FILE *file;
    file = fopen("DATA/MESSAGE.txt","w");
    if (file == NULL)  {
        printf("\t\t\t\t打开文件失败!\n");
        printf("\t\t\t\t保存失败!\n");
        Sleep(1000);
        return;
    }
    listInsertionSort(head);
    struct node *p;
    p = head->next;
    while (p != NULL)  {
        fprintf(file,"%d %s %s %.2f %.2f %.2f %.2f %s %s %s %s\n",
        p->data.CLASS,
        p->data.NO,
        p->data.NAME,
        p->data.SCORE[0],
        p->data.SCORE[1],
        p->data.SCORE[2],
        p->data.SCORE[3],
        p->data.USER,
        p->data.PHONE,
        p->data.QQ,
        p->data.EMAIL);
        p = p->next;
    }
    fclose(file);
}
//显示信息:全部
void DisplayMessageTotal(struct node *head)
{
    int num = 1;
    int rank = 1;
    struct node *p,*r;
    r = head;
    p = head->next;
    while (p != NULL)  {
        if (num != 1 && r->data.SCORE[3] != p->data.SCORE[3])
            rank = num;
        printf("\t\t\t\t第%d名\n",rank);
        printf("\t\t\t\t班级:%d\n",p->data.CLASS);
        printf("\t\t\t\t学号:%s\n",p->data.NO);
        printf("\t\t\t\t姓名:%s\n",p->data.NAME);
        printf("\t\t\t\t语文成绩:%.2f\n",p->data.SCORE[0]);
        printf("\t\t\t\t英语成绩:%.2f\n",p->data.SCORE[1]);
        printf("\t\t\t\t数学成绩:%.2f\n",p->data.SCORE[2]);
        printf("\t\t\t\t总    分:%.2f\n\n",p->data.SCORE[3]);
        num++;
        r = r->next;
        p = p->next;
    }
    printf("\t\t\t\t");
    system("pause");
}
//显示信息:班级
void DisplayMessageClass(struct node *head,int CLASS)
{
    struct node *p,*r;
    p = head->next;
    int num = 1;
    int rank = 1;
    while (p != NULL) {
        if (p->data.CLASS == CLASS)  {
            if (num != 1 && p->data.SCORE[3] != r->data.SCORE[3])
                rank = num;
            printf("\t\t\t\t第%d名\n",rank);
            printf("\t\t\t\t班级:%d\n",p->data.CLASS);
            printf("\t\t\t\t学号:%s\n",p->data.NO);
            printf("\t\t\t\t姓名:%s\n",p->data.NAME);
            printf("\t\t\t\t语文成绩:%.2f\n",p->data.SCORE[0]);
            printf("\t\t\t\t英语成绩:%.2f\n",p->data.SCORE[1]);
            printf("\t\t\t\t数学成绩:%.2f\n",p->data.SCORE[2]);
            printf("\t\t\t\t总    分:%.2f\n\n",p->data.SCORE[3]);
            r = p;
            num++;
        }
        p = p->next;
    }
    printf("\t\t\t\t");
    system("pause");
}
//显示信息:个人
void DisplayMessagePerson(struct node *head,char *NO,int CLASS)
{
    struct node *p,*r;
    r = head;
    p = head->next;
    int num = 1;
    int rank = 1;
    while (p != NULL) {
        if (p->data.CLASS == CLASS)  {
            if (num != 1 && p->data.SCORE[3] != r->data.SCORE[3])
                rank = num;
            if (strcmp(p->data.NO,NO) == 0)  {
                printf("\t\t\t\t班级:%d\n",p->data.CLASS);
                printf("\t\t\t\t学号:%s\n",p->data.NO);
                printf("\t\t\t\t姓名:%s\n",p->data.NAME);
                printf("\t\t\t\t语文成绩:%.2f\n",p->data.SCORE[0]);
                printf("\t\t\t\t英语成绩:%.2f\n",p->data.SCORE[1]);
                printf("\t\t\t\t数学成绩:%.2f\n",p->data.SCORE[2]);
                printf("\t\t\t\t总    分:%.2f\n\n",p->data.SCORE[3]);
                printf("\t\t\t\t班级第%d名\n",rank);
                printf("\t\t\t\t年级第%d名\n",num);
                printf("\t\t\t\t");
                system("pause");
                return;
            }
            r = p;
        }
        num++;
        p = p->next;
    }
    printf("\t\t\t\t未找到相关信息\n");
    system("pause");
}
//删除元素
void RemoveMessage(struct node *head,char *NO)
{
    struct node *p,*r;
    p = head->next;
    r = head;
    while (p != NULL)  {
        if (strcmp(p->data.NO,NO) == 0)  {
            r->next = p->next;
            return;
        }
        p = p->next;
        r = r->next;
    }
    printf("\t\t\t\t未找到相关信息!\n");
}
//查找元素
void FindMessageNO(struct node *head,char *NO,int CLASS)
{
    struct node *p,*r;
    r = head;
    p = head->next;
    int num = 1;
    int rank = 1;
    while (p != NULL) {
        if (p->data.CLASS == CLASS)  {
            if (num != 1 && p->data.SCORE[3] != r->data.SCORE[3])
                rank = num;
            if (strcmp(p->data.NO,NO) == 0)  {
                printf("\t\t\t\t班级:%d\n",p->data.CLASS);
                printf("\t\t\t\t学号:%s\n",p->data.NO);
                printf("\t\t\t\t姓名:%s\n",p->data.NAME);
                printf("\t\t\t\t语文成绩:%.2f\n",p->data.SCORE[0]);
                printf("\t\t\t\t英语成绩:%.2f\n",p->data.SCORE[1]);
                printf("\t\t\t\t数学成绩:%.2f\n",p->data.SCORE[2]);
                printf("\t\t\t\t总    分:%.2f\n",p->data.SCORE[3]);
                printf("\t\t\t\t班级第%d名\n",rank);
                printf("\t\t\t\t年级第%d名\n",num);
                printf("\t\t\t\t绑定账号:%s\n",p->data.USER);
                printf("\t\t\t\t手 机 号:%s\n",p->data.PHONE);
                printf("\t\t\t\t   QQ   :%s\n",p->data.QQ);
                printf("\t\t\t\t邮箱    :%s\n",p->data.EMAIL);
                printf("\t\t\t\t");
                system("pause");
                return;
            }
            r = p;
        }
        num++;
        p = p->next;
    }
    printf("\t\t\t\t未找到相关信息!\n\t\t\t\t");
    system("pause");
}

#endif
