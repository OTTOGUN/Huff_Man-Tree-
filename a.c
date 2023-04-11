#include <stdio.h>
#include <stdlib.h>

#define STACK_INIT_SIZE 100         //存储空间初始分配量
#define STACKINCREMENT 10           //存储空间分配增量
#define OK          1
#define ERROR       0
#define OVERFLOW    -2

typedef int Status;
typedef int TElemType;

/*------二叉树的二叉链表存储结构------*/
typedef struct BiTNode
{
    TElemType       data;                    //结点值
    struct BiTNode  *lchild, *rchild;       //左右孩子指针
}BiTNode, *BiTree;                          //定义结构体别名BiTNode和结构体指针BiTree


/*------栈的顺序存储定义------*/
typedef struct{
    TElemType *base;                //在栈构造之前和销毁之后，base的值为NULL
    TElemType *top;                 //栈顶指针
    int stacksize;                  //当前已分配的存储空间，以元素为单位
}SqStack;

/*函数声明*/
Status InitBiTree(BiTree *T);                                                           //构造空二叉树T
Status CreateBiTree(BiTree *T);                                                         //按先序顺序输入二叉树结点的值（一个字符，#字符表示空树），构建二叉链表表示的二叉树T
Status PreOrderTraverse(BiTree T, Status(*Visit)(TElemType e));                         //先序遍历二叉树T，对每个结点调用函数Visit一次且仅一次
Status InOrderTraverse(BiTree T, Status (*Visit)(TElemType e));                         //中序遍历二叉树T，对每个结点调用函数Visit一次且仅一次
Status PostOrderTraverse(BiTree T, Status(*Visit)(TElemType e));                        //后序遍历二叉树T，对每个结点调用函数Visit一次且仅一次
Status PrintElement(TElemType e);                                                       //Visit函数，输出结点的值
Status InitStack(SqStack *S);                                   //构造一个空栈S
Status StackEmpty(SqStack *S);                                  //判断是否为空栈，是则返回TURE，否则返回FALSE
Status Push(SqStack *S,BiTree e);                               //插入元素e为新的栈顶元素
Status Pop(SqStack *S,BiTree *e);                               //若栈不空，删除栈顶元素并用e返回其值，并返回OK；否则返回ERROR

int main()
{
    BiTree T;
    TElemType x;
    InitBiTree(&T);
    printf("二叉树初始化成功!\n");
    printf("输入二叉树的先序遍历顺序以建立一棵二叉树（以#字符表示空树）:\n");
    CreateBiTree(&T);
    printf("请输入对应序号选择遍历二叉树的顺序（1.先序；2.中序；3.后序；0.退出）：");
    do{
        scanf("%d",&x);
        switch(x)
        {
            case 1:PreOrderTraverse(T,PrintElement);break;
            case 2:InOrderTraverse(T,PrintElement);break;
            case 3:PostOrderTraverse(T,PrintElement);break;
            case 0:printf("Exit!\n");break;
            default:
                printf("Input Error!\nPlease Input Again:");
        }
    }while(x!=0);
    return 0;
}
//函数功能：构造空二叉树T
//函数参数：二叉树根结点二级指针T
//返回值：成功返回OK，失败返回OVERFLOW
Status InitBiTree(BiTree *T)
{
    (*T)=(BiTree)malloc(sizeof(BiTNode));                   //为根结点分配空间
    if(!(*T)) exit(OVERFLOW);                               //存储分配失败
    (*T)->lchild = NULL;                                    //左孩子置空
    (*T)->rchild = NULL;                                    //右孩子置空
    return OK;
}
//函数功能：按先序顺序输入二叉树结点的值（一个字符，#字符表示空树），构建二叉链表表示的二叉树T
//函数参数：二叉树根结点二级指针T
//返回值：成功返回OK，失败返回OVERFLOW
Status CreateBiTree(BiTree *T)
{
    char ch = getchar();                //从键盘读取字符
    if(ch == '#')                       //#字符表示空树
        *T = NULL;
    else
    {
        *T=(BiTree)malloc(sizeof(BiTNode));
        if(!(*T)) exit(OVERFLOW);
        (*T)->data = ch;                            //生成根结点
        CreateBiTree(&((*T)->lchild));              //构造左子树
        CreateBiTree(&((*T)->rchild));              //构造右子树
    }
    return OK;
}
//函数功能：先序遍历二叉树T，对每个结点调用函数Visit一次且仅一次
//函数参数：二叉树根结点指针T，对数据元素操作的应用函数Visit
//返回值：成功返回OK，失败返回ERROR
Status PreOrderTraverse(BiTree T, Status(*Visit)(TElemType e))
{
    SqStack q,*S;
    S = &q;
    InitStack(S);       //构造一个空栈
    BiTree p;
    Push(S,T);          //根结点入栈
    while(!StackEmpty(S))                   //栈空，退出循环
    {
        Pop(S,&p);      //根结点出栈
        while(p)
        {
            if(!Visit(p->data))     return ERROR;           //访问根结点
            if(p->rchild)               //右孩子判空
            {
                Push(S,p->rchild);              //若右孩子不为空，右孩子入栈
            }
            p = p->lchild;              //遍历左子树
        }
    }
    printf("\nInput Again:");
    return OK;
}
//函数功能：中序遍历二叉树T，对每个结点调用函数Visit一次且仅一次
//函数参数：二叉树根结点指针T，对数据元素操作的应用函数Visit
//返回值：成功返回OK，失败返回ERROR
Status InOrderTraverse(BiTree T, Status (*Visit)(TElemType e))
{
    SqStack q,*S;
    S = &q;
    InitStack(S);       //构造一个空栈
    BiTree p;
    p = T;              //p指向根结点
    while(p || !StackEmpty(S))
    {
        if(p)
        {
            Push(S,p);          //根结点入栈
            p = p->lchild;      //遍历左子树
        }
        else
        {
            Pop(S,&p);          //根结点出栈
            if(!Visit(p->data))     return ERROR;               //访问根结点
            p = p->rchild;                              //遍历右子树
        }
    }
    printf("\nInput Again:");
    return OK;
}
//函数功能：后序遍历二叉树T，对每个结点调用函数Visit一次且仅一次
//函数参数：二叉树根结点指针T，对数据元素操作的应用函数Visit
//返回值：成功返回OK，失败返回ERROR
Status PostOrderTraverse(BiTree T, Status(*Visit)(TElemType e))
{
    SqStack q,*S;
    S = &q;
    InitStack(S);       //构造一个空栈
    TElemType i=-1;                           //指针数组r下标，初始化为-1
    BiTree p,r[STACK_INIT_SIZE];              //辅助指针数组r，用于记录右孩子不为空的结点
    p = T;
    while(p || !StackEmpty(S))
    {
        if(p)
        {
            Push(S,p);                      //根结点入栈
            p = p->lchild;                  //遍历左子树
        }
        else
        {
            Pop(S,&p);                      //根结点出栈
            if(!p->rchild)                  //右孩子判空
            {
                if(!Visit(p->data))     return ERROR;          //若右孩子为空，访问根结点
                p = NULL;                                       //指针p格式化为空，满足下一次循环的出栈条件
            }
            else if(p == r[i])                                 //判断出栈根结点是否为第二次出栈的右孩子非空的根结点
            {
                if(!Visit(p->data))     return ERROR;          //若是，访问根结点
                i--;                                            //指针数组下标减1
                p = NULL;                                       //指针p格式化为空，满足下一次循环的出栈条件
            }
            else
            {
                r[++i] = p;                                     //若右孩子不为空，指针数组r下标加1，记录根结点
                Push(S,p);                                      //根结点再次入栈
                p = p->rchild;                                  //遍历右子树
            }
        }
    }
    printf("\nInput Again:");
    return OK;
}
//函数功能：Visit函数，输出结点的值
//函数参数：结点值e
//返回值：成功返回OK
Status PrintElement(TElemType e)
{
    printf("%c ",e);
    return OK;
}
//函数功能：构造一个空栈
//函数参数：栈S
//返回值：分配成功返回OK，失败返回OVERFLOW
Status InitStack(SqStack *S)
{
    S->base = (TElemType *)malloc(STACK_INIT_SIZE * sizeof(TElemType));
    if(!S->base) exit(OVERFLOW);     //存储分配失败
    /*printf("Arrive!\n");*/
    S->top = S->base;                   //栈顶与栈底相同
    S->stacksize = STACK_INIT_SIZE;             //栈的最大长度等于初始长度
    return OK;
}
//函数功能：判断是否为空栈
//函数参数：栈S
//返回值：是则返回OK，否则返回ERROR
Status StackEmpty(SqStack *S)
{
    if (S->top == S->base)
    {
        return OK;
    }
    return ERROR;
}
//函数功能：插入元素e为新的栈顶元素
//函数参数：栈S，根结点地址e
//返回值：插入成功返回OK，失败返回OVERFLOW
Status Push(SqStack *S,BiTree e)
{
    if(S->top - S->base >= S->stacksize)                //栈满，追加存储空间
    {
        S->base = (TElemType *)realloc(S->base,(S->stacksize + STACKINCREMENT) * sizeof(TElemType));
        if(!S->base) exit(OVERFLOW);                       //存储分配失败
        S->top = S->base + S->stacksize;                // 栈顶指针为栈底指针加上栈之前的最大长度
        S->stacksize += STACKINCREMENT;                 // 栈当前的最大长度等于栈之前的最大长度与增加的长度之和
    }
    *(S->top++) = e;                                      //先赋值（栈中存放的为根结点的地址），后栈顶指针上移
    return OK;
}
//函数功能：若栈不空，删除栈顶元素并用e返回其值，
//函数参数：栈S，根结点二级指针e
//返回值：弹出成功返回OK，否则返回ERROR
Status Pop(SqStack *S,BiTree *e)
{
    if(S->top == S->base) return ERROR;                     //栈空，返回ERROR
    *e = *(--S->top);                                         // 栈顶指针先下移，后赋值（*e为根结点指针存放的地址值，赋值即改变根结点指针的指向）
    return OK;
}
