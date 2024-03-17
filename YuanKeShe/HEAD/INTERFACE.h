#ifndef INTERFACE_H_
#define INTERFACE_H_
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h>

void welcome()
{
    system("cls");
    printf("\t\t\t\t**********************************************\n");
    printf("\t\t\t\t*              学生信息管理系统              *\n");
    printf("\t\t\t\t**********************************************\n");
}
int menu()
{
    int i;
    welcome();
    printf("\t\t\t\t\t\t1.教师登录\n");
    printf("\t\t\t\t\t\t2.学生登录\n");
    printf("\t\t\t\t\t\t3.退    出\n");
    printf("\t\t\t\t请输入功能序号:");
    scanf("%d",&i);
    return i;
}
//学生端界面
void student_welcome()
{
    system("cls");
    printf("\t\t\t\t**********************************************\n");
    printf("\t\t\t\t*              学生信息管理系统(学生端)      *\n");
    printf("\t\t\t\t**********************************************\n");
}
//学生端登录注册界面
int student_LoadAdd()
{
    int i;
    student_welcome();
    printf("\t\t\t\t\t\t1.登录\n");
    printf("\t\t\t\t\t\t2.注册\n");
    printf("\t\t\t\t\t\t3.忘记密码\n");
    printf("\t\t\t\t\t\t4.退出\n");
    printf("\t\t\t\t请输入功能序号:");
    scanf("%d",&i);
    return i;
}
//学生端注册界面
void student_add_1()
{
    student_welcome();
    printf("\t\t\t\t\t\t*注册*\n");
}
void student_add_2()
{
    student_add_1();
    printf("\t\t\t\t*输入back返回上一级\n");
    printf("\t\t\t\t*输入exit退出\n");
}
//学生端登录界面
void student_load()
{
    student_welcome();
    printf("\t\t\t\t\t\t*登录*\n");
    printf("\t\t\t\t*输入back返回上一级\n");
    printf("\t\t\t\t*输入exit退出\n");
}
//学生端忘记密码界面
void student_password()
{
    student_welcome();
    printf("\t\t\t\t\t\t*忘记密码*\n");
    printf("\t\t\t\t*输入back返回上一级\n");
    printf("\t\t\t\t*输入exit退出\n");
}
//学生端学生信息绑定
void student_bound()
{
    student_welcome();
    printf("\t\t\t\t\t\t*绑定学生信息*\n");
}
//学生信息查看
void student_print()
{
    student_welcome();
    printf("\t\t\t\t\t\t*查看学生信息*\n");
}
//学生信息修改
void student_change()
{
    student_welcome();
    printf("\t\t\t\t\t\t*修改学生信息*\n");
}
//账号信息
void student_user()
{
    student_welcome();
    printf("\t\t\t\t\t\t*帐号信息*\n");
}
//学生端功能选择
int student_switch()
{
    int i;
    student_welcome();
    printf("\t\t\t\t\t\t1.绑定学生信息\n");
    printf("\t\t\t\t\t\t2.查看学生信息\n");
    printf("\t\t\t\t\t\t3.修改学生信息\n");
    printf("\t\t\t\t\t\t4.帐号信息\n");
    printf("\t\t\t\t\t\t5.退出\n");
    printf("\t\t\t\t请输入功能序号:");
    scanf("%d",&i);
    return i;
}
//教师端开始界面
void teacher_welcome()
{
    system("cls");
    printf("\t\t\t\t**********************************************\n");
    printf("\t\t\t\t*              学生信息管理系统(教师端)      *\n");
    printf("\t\t\t\t**********************************************\n");
}
//教师端菜单
int teachermenu()
{
    teacher_welcome();
    int i;
    teacher_welcome();
    printf("\t\t\t\t\t\t1.学生信息汇总\n");
    printf("\t\t\t\t\t\t2.添加学生信息\n");
    printf("\t\t\t\t\t\t3.查找学生信息\n");
    printf("\t\t\t\t\t\t4.修改学生信息\n");
    printf("\t\t\t\t\t\t5.删除学生信息\n");
    printf("\t\t\t\t\t\t6.退出\n");
    printf("\t\t\t\t请输入功能序号:");
    scanf("%d",&i);
    return i;
}
//教师端添加学生信息
int teacheraddmenu()
{
    int i;
    teacher_welcome();
    printf("\t\t\t\t\t\t1.添加一个\n");
    printf("\t\t\t\t\t\t2.批量添加\n");
    printf("\t\t\t\t\t\t3.退出\n");
    printf("\t\t\t\t请输入功能序号:");
    scanf("%d",&i);
    return i;
}
void teacheradd()
{
    teacher_welcome();
    printf("\t\t\t\t\t\t*添加*\n");
}
//教师端查找学生信息
void teacherfind()
{
    teacher_welcome();
    printf("\t\t\t\t\t\t*查找*\n");
}
//教师端修改学生信息
void teacherchange()
{
    teacher_welcome();
    printf("\t\t\t\t\t\t*修改*\n");
}
//教师端删除学生信息
void teacherremove()
{
    teacher_welcome();
    printf("\t\t\t\t\t\t*删除*\n");
}
//教师端汇总
int teachertotal()
{
    int i;
    teacher_welcome();
    printf("\t\t\t\t\t\t1.成绩班级排名\n");
    printf("\t\t\t\t\t\t2.成绩年级排名\n");
    printf("\t\t\t\t\t\t3.退出\n");
    printf("\t\t\t\t请输入功能序号:");
    scanf("%d",&i);
    return i;
}

#endif