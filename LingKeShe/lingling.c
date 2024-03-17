#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>

//定义学生成绩信息的结构体
typedef struct score
{
	int class_num;
	char person[15];
	char name[15];
    //各科满分均为100
	float  num_chinese;
    float  num_english;
    float  num_math;
    float  sum;
}stu;

//程序使用链表储存数据
//定义链表
struct Node  {
    stu data;
    struct Node *next;
};

//
//将学生信息储存到链表中
/**************************************************************/
struct Node *Head_Init()
{
    //初始化链表
    struct Node *head,*p,*r;
    head = (struct Node*)malloc(sizeof(struct Node));
    p = head;
    //以只读方式打开文件
    FILE *file;
    file = fopen("score.txt","r");
    if (file == NULL)  {
        printf("文件打开失败!\n");
        exit(-1);
    }
    while (1)  {
        int class_num_temp;
        char person_temp[15];
        char name_temp[11];
        float num_chinese_temp;
        float num_english_temp;
        float num_math_temp;
        float sum_temp;

        r =  (struct Node*)malloc(sizeof(struct Node));
        if (fscanf(file,"%d %s %s %f %f %f %f",
        &class_num_temp,
        person_temp,
        name_temp,
        &num_chinese_temp,
        &num_english_temp,
        &num_math_temp,
        &sum_temp) != EOF)  {
            r->data.class_num = class_num_temp;
            strcpy(r->data.person,person_temp);
            strcpy(r->data.name,name_temp);
            r->data.num_chinese = num_chinese_temp;
            r->data.num_english = num_english_temp;
            r->data.num_math = num_math_temp;
            r->data.sum = sum_temp;
            r->next = NULL;
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
//将链表写入文件
void Node_Input(struct Node *head_std)
{
    struct Node *p;
    p = head_std->next;
    FILE *file;
    file = fopen("score.txt","w");
    if (file == NULL)  {
        printf("打开文件失败!");
        Sleep(500);
        exit(-1);
    }
    while (p != NULL)  {
        fprintf(file,"%d %s %s %.2f %.2f %.2f %.2f\n",
        p->data.class_num,
        p->data.person,
        p->data.name,
        p->data.num_chinese,
        p->data.num_english,
        p->data.num_math,
        p->data.sum);
        p = p->next;
    }
    fclose(file);
}

/**************************************************************/

//增加
/**************************************************************/
//输入的班级保证在1-5班
void justy_class(int *class_num)
{
    printf("\t\t\t输入班级(输入-1退出):");
    scanf("%d",class_num);
    if (*class_num >= 1 && *class_num <= 5 || *class_num == -1)  
        return;
    while (1)  {
        printf("\t\t\t输入有误,请重新输入(输入-1退出):");
        scanf("%d",class_num);
        if ((*class_num >= 1 && *class_num <= 5) || *class_num == -1)  
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
        printf("\t\t\t输入有误,请重新输入:");
        scanf("%f",score);
        if (*score >= 0 && *score <= 100)  
            return;
    }
}
//学号查重
int no_repitiion(struct Node *head_stu,char *no)
{
    struct Node *p;
    p = head_stu->next;
    while (p != NULL)  {
        if (strcmp(p->data.person,no) == 0)
            return 0;
        p = p->next;
    }
    return 1;
}
//输入信息并储存到文件中
void Enter(struct Node *head_stu)
{
    //以追加模式打开文件
    //即在文件末尾追加内容
    FILE *file;
    file = fopen("score.txt","a");
    if (file == NULL)  {
        printf("打开文件失败!\n");
        system("pause");
        return;
    }

    //声明储存信息的变量
    int class_num;
    char person_no[15];
    char name[11];
    float  num_chinese;
    float  num_english;
    float  num_math;

    do {
        printf("\n\n\n\n");
        puts("\t\t********************** ******************\t\n");
        justy_class(&class_num);
        if(class_num == -1)
            break;
        printf("\t\t\t请输入学号:");
        scanf("%s",person_no);
        int i = no_repitiion(head_stu,person_no);
        if (!i)  {
            printf("\t\t\t学号重复!\n");
            Sleep(500);
            system("cls");
            continue;
        }
        printf("\t\t\t请输入姓名:");
        scanf("%s",name);
        printf("\t\t\t请输入语文成绩:");
        justy_ok(&num_chinese);
        printf("\t\t\t请输入英语成绩:");
        justy_ok(&num_english);
        printf("\t\t\t请输入数学成绩:");
        justy_ok(&num_math);
        float sum = num_chinese + num_english + num_math;
        //将输入的信息写入文件
        fprintf(file,"%d %s %s %.2f %.2f %.2f %.2f\n",
            class_num,
            person_no,
            name,
            num_chinese,
            num_english,
            num_math,
            sum);
        printf("\n\n\n");
        printf("\t\t\t录入成绩成功!\n");
        struct Node *p;
        p = (struct Node*)malloc(sizeof(struct Node));
        p->data.class_num = class_num;
        strcpy(p->data.person,person_no);
        strcpy(p->data.name,name);
        p->data.num_chinese = num_chinese;
        p->data.num_english = num_english;
        p->data.num_math = num_math;
        p->next = head_stu->next;
        head_stu->next = p;

        Sleep(600);
        system("cls");
    } while (class_num != -1);

    //关闭文件
    fclose(file);
}
/****************************************************************/

//删除
/***************************************************/
//按学号删除学生成绩
void remove_no(struct Node *head_stu)
{
    system("cls");
    struct Node *p,*r;
    r = head_stu;
    p = head_stu->next;
    char no[15];
    printf("\n\n\n\n");
    puts("\t\t********************** ******************\t\n");
    printf("\t\t\t请输入要删除成绩学生的学号:");
    scanf("%s",no);
    while (p != NULL)  {
        if (strcmp(p->data.person,no) == 0)  {
            r->next = p->next;
            Node_Input(head_stu);
            printf("\t\t删除成功!\n");
            Sleep(500);
            return;
        }
        r = r->next;
        p = p->next;
    }
    printf("\t\t未找到相关信息!\n\t\t");
    system("pause");
    system("cls");
}
/***************************************************/

//查找
/****************************************************/
//获取学生排名
void Rank_No(struct Node *head_stu,int class_num,char *no,int *rank_total,int *rank_class)
{
    *rank_total = 1;
    *rank_class = 1;
    struct Node *p;
    p = head_stu->next;
    int sum;
    int tank_total_temp = 0;
    int rank_class_temp = 0;
    //获取学生总分
    int i = 0;
    while (p != NULL)  {
        if (strcmp(no,p->data.person) == 0) {
            sum = p->data.sum;
            i = 1;
            break;
        }
        p = p->next;
    }
    if (!i)  {
        printf("\t\t\t未找到相关信息!\n");
        Sleep(500);
        return;
    }
    p = head_stu->next;
    while(p != NULL)  {
        if (p->data.sum > sum)
            rank_total++;
        if (p->data.class_num == class_num)  {
            if (p->data.sum > sum)
                rank_class++;
        }
        p = p->next;
    }
}
//按学号查找学生成绩
void Find_no(struct Node *head_stu)
{
    puts("\t\t*************查找学生成绩*************\t\n");
    int class_num;
    printf("\t\t\t请输入班级:");
    scanf("%d",&class_num);
    char no[15];
    printf("\t\t\t请输入学号:");
    scanf("%s",no);
    int rank_total;
    int rank_class;
    Rank_No(head_stu,class_num,no,&rank_total,&rank_class);
    struct Node *p;
    p = head_stu->next;
    while (p != NULL)  {
        if (strcmp(p->data.person,no) == 0)  {
            printf("\t\t班级:%d\n\t\t学号:%s\n\t\t姓名:%s\n\t\t语文成绩: %.2f\n\t\t英语成绩: %.2f\n\t\t数学成绩: %.2f\n\t\t",
            p->data.class_num,p->data.person,p->data.name,
            p->data.num_chinese,p->data.num_english,p->data.num_math);
            printf("总分:     %.2f\n\t\t班级排名:%d\n\t\t年级排名:%d\n\t\t",
            p->data.sum,rank_class,rank_total);
            system("pause");
            return;
        }
        p = p->next;
    }
    printf("\t\t\t未找到相关信息!\n");
    Sleep(500);
    system("cls");
}
//按姓名查找学生成绩
void Find_name(struct Node *head_stu)
{
    puts("\t\t*************查找学生成绩*************\t\n");
    int class_num;
    char name[11];
    printf("\t\t\t请输入班级:");
    scanf("%d",&class_num);
    printf("\t\t\t请输入姓名:");
    scanf("%s",name);
    int rank_total;
    int rank_class;
    struct Node *p;
    p = head_stu->next;
    while (p != NULL)  {
        if (strcmp(p->data.name,name) == 0 && p->data.class_num == class_num)  {
            Rank_No(head_stu,class_num,p->data.person,&rank_total,&rank_class);
            printf("\t\t班级:%d\n\t\t学号:%s\n\t\t姓名:%s\n\t\t语文成绩: %.2f\n\t\t英语成绩: %.2f\n\t\t数学成绩: %.2f\n\t\t",
            p->data.class_num,p->data.person,p->data.name,
            p->data.num_chinese,p->data.num_english,p->data.num_math);
            printf("总分:    %.2f\n\t\t班级排名:%d\n\t\t年级排名:%d\n\t\t",
            p->data.sum,rank_class,rank_total);
            printf("\n");
        }
        p = p->next;
    }
    printf("\t\t以上是相关信息!\n\t\t");
    system("pause");
    system("cls");
}
//查找界面
void Find(struct Node *head_stu)
{
    int i;
	do {
        printf("\n\n\n\n");
        puts("\t\t********************** ******************\t\n");
        puts("\t\t\t\t1.学号查找                               \n");
        puts("\t\t\t\t2.姓名查找                               \n");
        puts("\t\t**********************************************\t\n");
        printf("\t\t\t  请选择(1-2):[ ]\b\b");
	    scanf("%d",&i);
	    system("cls");
        if (i == 1 || i == 2)
            break;
        printf("\t\t请输入正确序号!\n");
        Sleep(500);
    } while (1);
    if (i == 1)
        Find_no(head_stu);
    else  
        Find_name(head_stu);
}
/****************************************************/

//更改学生成绩
/****************************************************/
void Change(struct Node *head_stu)
{
    system("cls");
    printf("\n\n\n\n");
    puts("\t\t********************** ******************\t\n");
    char no[15];
    printf("\t\t请输入要更改成绩学生的学号:");
    scanf("%s",no);
    struct Node *p;
    p = head_stu->next;
    while (p != NULL)  {
        if (strcmp(p->data.person,no) == 0)  {
            printf("\t\t\t班级:%d\n",p->data.class_num);
            printf("\t\t\t学号:%s\n",p->data.person);
            printf("\t\t\t姓名:%s\n",p->data.name);
            printf("\t\t\t请输入语文成绩:");
            justy_ok(&(p->data.num_chinese));
            printf("\t\t\t请输入数学成绩:");
            justy_ok(&(p->data.num_english  ));
            printf("\t\t\t请输入英语成绩:");
            justy_ok(&(p->data.num_math));
            p->data.sum = p->data.num_chinese + p->data.num_english + p->data.num_math;
            Node_Input(head_stu);
            printf("\t\t\t修改成功!\n");
            Sleep(500);
            return;
        }
        p = p->next;
    }
    printf("\t\t未找到相关信息!\n\t\t");
    system("pause");
    system("cls");
}
/****************************************************/

//获取平均分,班级平均分数据
/**************************************************************/
//平均分
float average_every(struct Node *head_stu,float aver_every[])
{
    int aver = 0;
    float sum[3] = {0};
    struct Node *p;
    p = head_stu->next;
    int num = 0;
    //遍历链表,求各科分数总和
    while (p != NULL)  {
        num++;
        sum[0] += p->data.num_chinese;
        sum[1] += p->data.num_english;
        sum[2] += p->data.num_math;
        p = p->next;
    }
    //求各科平均成绩
    for (int i = 0; i < 3; i++)  {
        aver_every[i] = sum[i] / num;
        aver += aver_every[i];
    }
    //求总分平均分
    aver /= 3;
    return aver;
}
//班级平均分
void average_class(struct Node *head_stu,float aver_class[][3],int num[])
{
    float sum[5][3] = {0};
    struct Node *p;
    p = head_stu->next;
    while (p != NULL)  {
        switch(p->data.class_num)  {
            case 1:
                num[0]++;
                sum[0][0] += p->data.num_chinese;
                sum[0][1] += p->data.num_english;
                sum[0][2] += p->data.num_math;
                break;
            case 2:
                num[1]++;
                sum[1][0] += p->data.num_chinese;
                sum[1][1] += p->data.num_english;
                sum[1][2] += p->data.num_math;
                break;
            case 3:
                num[2]++;
                sum[2][0] += p->data.num_chinese;
                sum[2][1] += p->data.num_english;
                sum[2][2] += p->data.num_math;
                break;
            case 4:
                num[3]++;
                sum[3][0] += p->data.num_chinese;
                sum[3][1] += p->data.num_english;
                sum[3][2] += p->data.num_math;
                break;
            case 5:
                num[4]++;
                sum[4][0] += p->data.num_chinese;
                sum[4][1] += p->data.num_english;
                sum[4][2] += p->data.num_math;
                break;
        }
        p = p->next;
    }
    for (int i = 0; i < 5;i++)  
        for (int j = 0; j < 3; j++)  
            aver_class[i][j] = sum[i][j] / num[i];
}
/**************************************************************/
//输出汇总成绩
void Display_total(float aver, float aver_every[],float aver_class[][3],int people[])
{
    int num = 0;
    for (int i = 0; i < 5; i++)
        num += people[i];
    printf("\n\n");
    puts("\t\t****************成绩汇总***************\t\n");
    printf("\t年级共%d人\n",num);
    printf("\t");
    for (int i = 0; i < 5; i++) 
        printf("%d班共%d人;",i+1,people[i]);
    printf("\n");
    printf("\t\t\t年级语文平均分:%.2f\n",aver_every[0]);
    for (int i = 0; i < 5; i++)  
        printf("\t\t\t%d班语文平均分: %.2f\n",i+1,aver_class[i][0]);
    printf("\n");
    printf("\t\t\t年级英语平均分:%.2f\n",aver_every[0]);
    for (int i = 0; i < 5; i++)
        printf("\t\t\t%d班英语平均分: %.2f\n",i+1,aver_class[i][0]);
    printf("\n");
    printf("\t\t\t年级数学平均分:%.2f\n",aver_every[0]);
    for (int i = 0; i < 5; i++)  
        printf("\t\t\t%d班数学平均分: %.2f\n",i+1,aver_class[i][0]);
    printf("\n");
    puts("\t\t**********************************************\t\n");
    printf("\t\t");
    system("pause");
}
//班级成绩查看
void Display_class(struct Node *head_stu)
{
    system("cls");
    int i;
    printf("\n\n\n\n");
    puts("\t\t********************** ******************\t\n");
    printf("\t\t请输入要查询的班级:");
    scanf("%d",&i);
    struct Node *p;
    p = head_stu->next;
    //生成班级链表
    while (p != NULL)  {
        if (p->data.class_num == i)  {
            printf("\t\t班级:%d\n\t\t学号:%s\n\t\t姓名:%s\n\t\t语文成绩: %.2f\n\t\t英语成绩: %.2f\n\t\t数学成绩: %.2f\n\t\t",
            p->data.class_num,p->data.person,p->data.name,
            p->data.num_chinese,p->data.num_english,p->data.num_math);
            printf("总分:    %.2f\n\t\t",
            p->data.sum);
        }
        p = p->next;
    }
    system("pause");
    system("cls");
}
//年级成绩查看
void Display_nianji(struct Node *head)
{
    struct Node *p;
    p = head->next;
    while (p != NULL)  {
        printf("\t\t班级:%d\n\t\t学号:%s\n\t\t姓名:%s\n\t\t语文成绩: %.2f\n\t\t英语成绩: %.2f\n\t\t数学成绩: %.2f\n\t\t",
        p->data.class_num,p->data.person,p->data.name,
        p->data.num_chinese,p->data.num_english,p->data.num_math);
        printf("总分:    %.2f\n\t\t",
        p->data.sum);
        p = p->next;
    }
    system("pause");
    system("cls");
}
//二级菜单
void Display(struct Node *head_stu)
{
    printf("正在初始化数据...\n");
    Sleep(250);
    float aver_every[3] = {0};
    int num[5] = {0};
    float aver_class[5][3] = {0};
    //总平均分
    float aver = average_every(head_stu,aver_every);
    //班级平均分
    average_class(head_stu,aver_class,num);
    printf("初始化完成!\n");
    Sleep(500);
    system("cls");

    int i;
    do {
        printf("\n\n\n\n");
        puts("\t\t********************** ******************\t\n");
        puts("\t\t\t\t1.成绩汇总                               \n");
        puts("\t\t\t\t2.班级成绩查看                               \n");
        puts("\t\t\t\t3.年级成绩查看                               \n");
        puts("\t\t**********************************************\t\n");
        printf("\t\t\t  请选择(1-3):[ ]\b\b");
        scanf("%d",&i);
        if (i >= 1 && i <= 3)
            break;
        printf("输入有误,请重新输入!\n");
        Sleep(500);
        system("cls");
    } while (1);
    switch (i) {
        case 1:
            Display_total(aver,aver_every,aver_class,num);
            break;
        case 2:
            Display_class(head_stu);
            break;
        case 3:
            Display_nianji(head_stu);
            break;
        default:
            printf("\t\t无功能\n\t\t");
            system("pause");
            break;
    }
}

/**************************************************************/


//开始界面选择
int welcome()
{
	printf("\n\n");
    printf("  \t┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓\n");
    printf("  \t┃**********************************************************┃\n");
    printf("  \t┃***┏━━━━━━━━━━━━━━━━━━━━━━━━┓***┃\n");
    printf("  \t┃***┃************************************************┃***┃\n");
    printf("  \t┃***┃***                                         ****┃***┃\n");
    printf("  \t┃***┃***        欢迎使用学生成绩管理系统         ****┃***┃\n");
    printf("  \t┃***┃***                                         ****┃***┃\n");
    printf("  \t┃***┃***                                         ****┃***┃\n");
    printf("  \t┃***┃***                              ****┃***┃\n");
    printf("  \t┃***┃***                                         ****┃***┃\n");
    printf("  \t┃***┃***                              ****┃***┃\n");
    printf("  \t┃***┃***                                         ****┃***┃\n");
    printf("  \t┃***┃************************************************┃***┃\n");
    printf("  \t┃***┗━━━━━━━━━━━━━━━━━━━━━━━━┛***┃\n");
    printf("  \t┃**********************************************************┃\n");
    printf("  \t┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛\n");
    puts("  \n\t                        ① 教师登陆!                         \n");
    puts("  \n\t                        ② 学生登陆!                         \n");
    printf("\n请选择登陆（1 or 2）:[ ]\b\b");   
    int i;
    scanf("%d",&i);
    return i;
}
//教师菜单界面和功能选择
int teacher_menu()
{
    system("cls");
    int i;
	printf("\n\n\n\n");
    puts("\t\t********************** ******************\t\n");
    puts("\t\t\t\t1.学生信息输入                               \n");
    puts("\t\t\t\t2.学生信息浏览                               \n");
    puts("\t\t\t\t3.学生信息检索                               \n");
    puts("\t\t\t\t4.学生信息修改                               \n");
    puts("\t\t\t\t5.学生信息删除                               \n");
    puts("\t\t\t\t6. 退 出 系 统                               \n");
    puts("\t\t**********************************************\t\n");
    printf("\t\t\t  请选择(1-6):[ ]\b\b");
	scanf("%d",&i);
	system("cls");
	return i;
}
//学生菜单界面
void student_menu(struct Node *head_stu)
{
    system("cls");
	printf("\n\n\n\n");
    puts("\t\t********************** ******************\t\n");
    Find_no(head_stu);
    printf("\t\t");
}
/****************************************************************/
//教师功能
void teacher(struct Node *head_stu)
{
    FILE *file;
    file = fopen("key.txt","r");
    if (file == NULL)  {
        printf("\t\t\t打开文件失败!\n");
        Sleep(500);
        exit(-1);
    }
    char key[20];
    char KEY[20];
    fscanf(file,"%s",KEY);
    fclose(file);
    do {
        system("cls");
        printf("\n\n\n\n");
        puts("\t\t********************** ******************\t\n");
        printf("\t\t\t请输入教师端登录密钥:");
        scanf("%s",key);
        if (strcmp(key,KEY) == 0)
            break;
        printf("\t\t输入错误!\n");
        Sleep(500);
    } while (1);

    printf("\t\t\t登录成功!\n");
    Sleep(500);
    system("pause");
    int i;
    do {
        i = teacher_menu();
        switch(i)  {
            case -1:
                return;
            case 1:
                Enter(head_stu);
                break;
            case 2:
                Display(head_stu);
                break;
            case 3:
                Find(head_stu);
                break;
            case 4:
                Change(head_stu);
                break;
            case 5:
                remove_no(head_stu);
                break;
            case 6:
                exit(-1);
                break;
            default:
                printf("/t/t更多功能敬请期待...\n");
                Sleep(500);
                break;
        } 
    }while(1);
}

int main()
{
    printf("初始化数据中...\n");
    Sleep(300);
    struct Node *head_stu;
    head_stu = Head_Init();
    printf("初始化完成!\n");
    Sleep(500);
    system("cls");

    int i;
    do {
        i = welcome();
        if (i == 1 || i == 2)
            break;
    } while (1);
    if (i == 1)
        teacher(head_stu);
    else 
        student_menu(head_stu);
    
    return 0;
}