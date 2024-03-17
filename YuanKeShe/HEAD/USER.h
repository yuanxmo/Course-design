#ifndef USER_H_
#define USER_H_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h>

#include "INTERFACE.h"

typedef struct {
    char USER[20];
    char KEY[17];
    char ENROLL[15];
} USER_KEY;

typedef struct Node {
    USER_KEY data;
    struct Node *next;
}Node;

//初始化链表
Node *Node_Init()
{
    Node *head;
    head = (Node*)malloc(sizeof(Node));
    head->next = NULL;
    return head;
}

//将文件内容写入链表中
Node *Node_Input()
{
    printf("\t\t\t\t正在初始化帐号数据...\n");
    FILE *file;
    file = fopen("DATA/USER.txt","r");
    if (file == NULL)  {
        printf("\t\t\t\t打开文件失败!\n\t\t\t\t");
        Sleep(1000);
        exit(-1);
    }
    Node *head,*p,*r;
    head = Node_Init();
    p = head;
    USER_KEY temp;
    while (fscanf(file,"%s %s %s",temp.USER,temp.KEY,temp.ENROLL) != EOF)  {
        r = (Node*)malloc(sizeof(Node));
        r->data = temp;
        p->next = r;
        p = p->next;
    }
    p->next = NULL;
    fclose(file);
    printf("\t\t\t\t初始化帐号数据成功!\n");
    Sleep(500);
    return head;
}
//将链表写入文件中
void OutputFile(Node *head)
{
    FILE *file;
    file = fopen("DATA/USER.txt","w");
    if (file == NULL)  {
        printf("\t\t\t\t打开文件失败!\n");
        Sleep(1000);
        return;
    }
    Node *p;
    p = head->next;
    while (p != NULL)  {
        fprintf(file,"%s %s %s\n",p->data.USER,p->data.KEY,p->data.ENROLL);
        p = p->next;
    }
    fclose(file);
    printf("\t\t\t\t保存成功!\n");
    Sleep(500);
}
//注册账号查重
int Add_Repetion(Node *head,char *user)
{
    Node *p;
    p = head->next;
    while (p != NULL)  {
        if (strcmp(p->data.USER,user) == 0)
            return 0;
        p = p->next;
    }
    return 1;
}
//注册输入账号
int Add_InputUser(Node *head,char *user)
{
    do {
        student_add_2();
        printf("\t\t\t\t请输入账号:");
        scanf("%s",user);
        if (strcmp(user,"back") == 0)
            return 0;
        if (strcmp(user,"exit") == 0)  {
            printf("\t\t\t\t");
            system("pause");
            exit(-1);
        }
        int i = Add_Repetion(head,user);
        if (i)
            return 1;
        printf("\t\t\t\t账号重复,请重试!\n");
        Sleep(750);
    }while(1);
    return -1;
}
//注册输入密码
void Add_InputKey(char *user,char *key)
{
    do {
        student_add_1();
        printf("\t\t\t\t请输入账号:%s\n",user);
        printf("\t\t\t\t请输入密码:");
        scanf("%s",key);
        if (strcmp(key,"back") == 0 || strcmp(key,"exit") == 0)  {
            printf("\t\t\t\t密码不符合规定!\n");
            Sleep(750);
            continue;
        }
        break;
    }while (1);
}
//注册写入文件
int Add_InputFile(char *user,char *key)
{
    printf("\t\t\t\t正在保存中...\n");
    FILE *file;
    file = fopen("DATA/USER.txt","a");
    if (file == NULL)  {
        printf("\t\t\t\t打开文件失败!\n");
        printf("\t\t\t\t注册失败!\n");
        Sleep(750);
        return 0;
    }
    fprintf(file,"%s %s %s\n",user,key,"0");
    fclose(file);
    printf("\t\t\t\t保存文件成功!\n");
    printf("\t\t\t\t注册成功!\n");
    Sleep(500);
    return 1;
}
//为链表添加信息
void Add_InputNode(Node *head,char *user,char *key)
{
    Node *p,*q,*r;
    q = head;
    p = head->next;
    while (p != NULL) {
        q = q->next;
        p = p->next;
    }
    r = (Node*)malloc(sizeof(Node));
    strcpy(r->data.USER,user);
    strcpy(r->data.KEY,key);
    r->next = NULL;
    q->next = r;
}
//注册
void User_Add(Node *head)
{
    student_add_2();
    char user[20];
    char key[17];
    int i = Add_InputUser(head,user);
    if (!i)
        return;
    Add_InputKey(user,key);
    i = Add_InputFile(user,key);
    if (!i)
        return;
    Add_InputNode(head,user,key);
}
//登录输入账号
void Load_InputUser(char *user)
{
    student_load();
    printf("\n");
    printf("\t\t\t\t账号:");
    scanf("%s",user);
}
//登录是否有该账号信息
int Load_FindUser(Node *head,char *user)
{
    Node *p;
    p = head->next;
    while (p != NULL)  {
        if (strcmp(p->data.USER,user) == 0)
            return 1;
        p = p->next;
    }
    return 0;
}
//登录获取正确密码
void Load_TrueKey(Node *head,char *user,char *TrueKey)
{
    Node *p;
    p = head->next;
    while (p != NULL)  {
        if (strcmp(p->data.USER,user) == 0)  {
            strcpy(TrueKey,p->data.KEY);
            return;
        }
        p = p->next;
    }
}
//登录输入密码
void Load_InputKey(char *user,char *key)
{
    student_load();
    printf("\n\t\t\t\t账号:%s\n",user);
    printf("\t\t\t\t密码:");
    scanf("%s",key);
}
//登录验证密码
int Load_YNKey(char *Truekey,char *key)
{
    if (strcmp(key,Truekey) == 0)  {
        printf("\t\t\t\t登录成功!\n");
        Sleep(750);
        return 1;
    }
    printf("\t\t\t\t密码错误,请重试!\n");
    Sleep(1000);
    system("cls");
    return 0;
}
//登录
int User_Load(Node *head,char *USER)
{
    char user[20];
    char key[17];
    char TrueKey[17];
    do {
        Load_InputUser(user);
        if (strcmp(user,"back") == 0)
            return 0;
        if (strcmp(user,"exit") == 0)  {
            printf("\t\t\t\t");
            system("pause");
            exit(-1);
        }
        int i = Load_FindUser(head,user);
        if (i)
            break;
        printf("\t\t\t\t无该账号信息!\n");
        Sleep(1000);
    }while (1);
    Load_TrueKey(head,user,TrueKey);
    do {
        Load_InputKey(user,key);
        if (strcmp(key,"exit") == 0)  {
            printf("\t\t\t\t");
            system("pause");
            exit(-1);
        }
        if (strcmp(key,"back") == 0)
            return 0;
        int i = Load_YNKey(TrueKey,key);
        if (i) {
            strcpy(USER,user);
            break;
        }
            
    }while (1);
    return 1;
}
//忘记密码获取修改密码密钥
int MisRemind_Key(Node *head,char *Key)
{
    FILE *file;
    file = fopen("DATA/KEY.txt","r");
    if (file == NULL)  {
        printf("\t\t\t\t打开文件失败!\n");
        Sleep(1000);
        return 0;
    }
    fscanf(file,"%s",Key);
    fclose(file);
    return 1;
}
//忘记密码输入密钥
void MisRemind_InputKey(char *change_key)
{
    student_password();
    printf("\t\t\t\t请输入密钥:");
    scanf("%s",change_key);
}
//输入密码
void InputKey(char *user,char *Key)
{
    char key_again[17];
    do {
        student_password();
        printf("\n\t\t\t\t请输入账号:%s\n",user);
        printf("\t\t\t\t请输入新密码:");
        scanf("%s",Key);
        printf("\t\t\t\t请再次输入:");
        scanf("%s",key_again);
        if (strcmp(Key,key_again) == 0)
            return;
        printf("\t\t\t\t密码不一致!\n");
        Sleep(750);
        system("cls");
    }while(1);
}
//修改链表内容
void MisRemind_ChangeNode(Node *head,char *user,char *key)
{
    Node *p;
    p = head->next;
    while (p != NULL)  {
        if (strcmp(p->data.USER,user) == 0)  {
            strcpy(p->data.KEY,key);
            return;
        }
        p = p->next;
    }
}
//忘记密码->输入账号
void MisRemind_InputUser(char *user)
{
    student_password();
    printf("\n");
    printf("\t\t\t\t账号:");
    scanf("%s",user);
}
//忘记密码->修改密码
void Misremind_ChangeKey(Node *head)
{
    char user[20];
    do {
        MisRemind_InputUser(user);
        if (strcmp(user,"exit") == 0)  {
            printf("\t\t\t\t");
            system("pause");
            exit(-1);
        }
        if (strcmp(user,"back") == 0)
            return;
        int i = Load_FindUser(head,user);
        if (i)  {
            char key[17];
            InputKey(user,key);
            MisRemind_ChangeNode(head,user,key);
            OutputFile(head);
            return;
        }
        printf("\t\t\t\t未找到信息!\n");
        Sleep(750);
        system("cls");
    }while(1);
}
//忘记密码
void MisRemind(Node *head)
{
    char ChangeKey[20];
    int i = MisRemind_Key(head,ChangeKey);
    if (!i)
        return;
    do {
        char change_key[20];
        MisRemind_InputKey(change_key);
        if (strcmp(change_key,"back") == 0)
            return;
        if (strcmp(change_key,"exit") == 0)  {
            printf("\t\t\t\t");
            system("pause");
            exit(-1);
        }
        if (strcmp(change_key,ChangeKey) == 0) {
            Misremind_ChangeKey(head);
            return;
        }
        printf("\t\t\t\t密钥错误,请重试!\n");
        Sleep(750);
        system("cls");
    }while (1);
}

#endif
