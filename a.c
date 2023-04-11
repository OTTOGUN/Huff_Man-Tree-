#include <stdio.h>
#include <stdlib.h>

#define STACK_INIT_SIZE 100         //�洢�ռ��ʼ������
#define STACKINCREMENT 10           //�洢�ռ��������
#define OK          1
#define ERROR       0
#define OVERFLOW    -2

typedef int Status;
typedef int TElemType;

/*------�������Ķ�������洢�ṹ------*/
typedef struct BiTNode
{
    TElemType       data;                    //���ֵ
    struct BiTNode  *lchild, *rchild;       //���Һ���ָ��
}BiTNode, *BiTree;                          //����ṹ�����BiTNode�ͽṹ��ָ��BiTree


/*------ջ��˳��洢����------*/
typedef struct{
    TElemType *base;                //��ջ����֮ǰ������֮��base��ֵΪNULL
    TElemType *top;                 //ջ��ָ��
    int stacksize;                  //��ǰ�ѷ���Ĵ洢�ռ䣬��Ԫ��Ϊ��λ
}SqStack;

/*��������*/
Status InitBiTree(BiTree *T);                                                           //����ն�����T
Status CreateBiTree(BiTree *T);                                                         //������˳���������������ֵ��һ���ַ���#�ַ���ʾ���������������������ʾ�Ķ�����T
Status PreOrderTraverse(BiTree T, Status(*Visit)(TElemType e));                         //�������������T����ÿ�������ú���Visitһ���ҽ�һ��
Status InOrderTraverse(BiTree T, Status (*Visit)(TElemType e));                         //�������������T����ÿ�������ú���Visitһ���ҽ�һ��
Status PostOrderTraverse(BiTree T, Status(*Visit)(TElemType e));                        //�������������T����ÿ�������ú���Visitһ���ҽ�һ��
Status PrintElement(TElemType e);                                                       //Visit�������������ֵ
Status InitStack(SqStack *S);                                   //����һ����ջS
Status StackEmpty(SqStack *S);                                  //�ж��Ƿ�Ϊ��ջ�����򷵻�TURE�����򷵻�FALSE
Status Push(SqStack *S,BiTree e);                               //����Ԫ��eΪ�µ�ջ��Ԫ��
Status Pop(SqStack *S,BiTree *e);                               //��ջ���գ�ɾ��ջ��Ԫ�ز���e������ֵ��������OK�����򷵻�ERROR

int main()
{
    BiTree T;
    TElemType x;
    InitBiTree(&T);
    printf("��������ʼ���ɹ�!\n");
    printf("������������������˳���Խ���һ�ö���������#�ַ���ʾ������:\n");
    CreateBiTree(&T);
    printf("�������Ӧ���ѡ�������������˳��1.����2.����3.����0.�˳�����");
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
//�������ܣ�����ն�����T
//������������������������ָ��T
//����ֵ���ɹ�����OK��ʧ�ܷ���OVERFLOW
Status InitBiTree(BiTree *T)
{
    (*T)=(BiTree)malloc(sizeof(BiTNode));                   //Ϊ��������ռ�
    if(!(*T)) exit(OVERFLOW);                               //�洢����ʧ��
    (*T)->lchild = NULL;                                    //�����ÿ�
    (*T)->rchild = NULL;                                    //�Һ����ÿ�
    return OK;
}
//�������ܣ�������˳���������������ֵ��һ���ַ���#�ַ���ʾ���������������������ʾ�Ķ�����T
//������������������������ָ��T
//����ֵ���ɹ�����OK��ʧ�ܷ���OVERFLOW
Status CreateBiTree(BiTree *T)
{
    char ch = getchar();                //�Ӽ��̶�ȡ�ַ�
    if(ch == '#')                       //#�ַ���ʾ����
        *T = NULL;
    else
    {
        *T=(BiTree)malloc(sizeof(BiTNode));
        if(!(*T)) exit(OVERFLOW);
        (*T)->data = ch;                            //���ɸ����
        CreateBiTree(&((*T)->lchild));              //����������
        CreateBiTree(&((*T)->rchild));              //����������
    }
    return OK;
}
//�������ܣ��������������T����ÿ�������ú���Visitһ���ҽ�һ��
//���������������������ָ��T��������Ԫ�ز�����Ӧ�ú���Visit
//����ֵ���ɹ�����OK��ʧ�ܷ���ERROR
Status PreOrderTraverse(BiTree T, Status(*Visit)(TElemType e))
{
    SqStack q,*S;
    S = &q;
    InitStack(S);       //����һ����ջ
    BiTree p;
    Push(S,T);          //�������ջ
    while(!StackEmpty(S))                   //ջ�գ��˳�ѭ��
    {
        Pop(S,&p);      //������ջ
        while(p)
        {
            if(!Visit(p->data))     return ERROR;           //���ʸ����
            if(p->rchild)               //�Һ����п�
            {
                Push(S,p->rchild);              //���Һ��Ӳ�Ϊ�գ��Һ�����ջ
            }
            p = p->lchild;              //����������
        }
    }
    printf("\nInput Again:");
    return OK;
}
//�������ܣ��������������T����ÿ�������ú���Visitһ���ҽ�һ��
//���������������������ָ��T��������Ԫ�ز�����Ӧ�ú���Visit
//����ֵ���ɹ�����OK��ʧ�ܷ���ERROR
Status InOrderTraverse(BiTree T, Status (*Visit)(TElemType e))
{
    SqStack q,*S;
    S = &q;
    InitStack(S);       //����һ����ջ
    BiTree p;
    p = T;              //pָ������
    while(p || !StackEmpty(S))
    {
        if(p)
        {
            Push(S,p);          //�������ջ
            p = p->lchild;      //����������
        }
        else
        {
            Pop(S,&p);          //������ջ
            if(!Visit(p->data))     return ERROR;               //���ʸ����
            p = p->rchild;                              //����������
        }
    }
    printf("\nInput Again:");
    return OK;
}
//�������ܣ��������������T����ÿ�������ú���Visitһ���ҽ�һ��
//���������������������ָ��T��������Ԫ�ز�����Ӧ�ú���Visit
//����ֵ���ɹ�����OK��ʧ�ܷ���ERROR
Status PostOrderTraverse(BiTree T, Status(*Visit)(TElemType e))
{
    SqStack q,*S;
    S = &q;
    InitStack(S);       //����һ����ջ
    TElemType i=-1;                           //ָ������r�±꣬��ʼ��Ϊ-1
    BiTree p,r[STACK_INIT_SIZE];              //����ָ������r�����ڼ�¼�Һ��Ӳ�Ϊ�յĽ��
    p = T;
    while(p || !StackEmpty(S))
    {
        if(p)
        {
            Push(S,p);                      //�������ջ
            p = p->lchild;                  //����������
        }
        else
        {
            Pop(S,&p);                      //������ջ
            if(!p->rchild)                  //�Һ����п�
            {
                if(!Visit(p->data))     return ERROR;          //���Һ���Ϊ�գ����ʸ����
                p = NULL;                                       //ָ��p��ʽ��Ϊ�գ�������һ��ѭ���ĳ�ջ����
            }
            else if(p == r[i])                                 //�жϳ�ջ������Ƿ�Ϊ�ڶ��γ�ջ���Һ��ӷǿյĸ����
            {
                if(!Visit(p->data))     return ERROR;          //���ǣ����ʸ����
                i--;                                            //ָ�������±��1
                p = NULL;                                       //ָ��p��ʽ��Ϊ�գ�������һ��ѭ���ĳ�ջ����
            }
            else
            {
                r[++i] = p;                                     //���Һ��Ӳ�Ϊ�գ�ָ������r�±��1����¼�����
                Push(S,p);                                      //������ٴ���ջ
                p = p->rchild;                                  //����������
            }
        }
    }
    printf("\nInput Again:");
    return OK;
}
//�������ܣ�Visit�������������ֵ
//�������������ֵe
//����ֵ���ɹ�����OK
Status PrintElement(TElemType e)
{
    printf("%c ",e);
    return OK;
}
//�������ܣ�����һ����ջ
//����������ջS
//����ֵ������ɹ�����OK��ʧ�ܷ���OVERFLOW
Status InitStack(SqStack *S)
{
    S->base = (TElemType *)malloc(STACK_INIT_SIZE * sizeof(TElemType));
    if(!S->base) exit(OVERFLOW);     //�洢����ʧ��
    /*printf("Arrive!\n");*/
    S->top = S->base;                   //ջ����ջ����ͬ
    S->stacksize = STACK_INIT_SIZE;             //ջ����󳤶ȵ��ڳ�ʼ����
    return OK;
}
//�������ܣ��ж��Ƿ�Ϊ��ջ
//����������ջS
//����ֵ�����򷵻�OK�����򷵻�ERROR
Status StackEmpty(SqStack *S)
{
    if (S->top == S->base)
    {
        return OK;
    }
    return ERROR;
}
//�������ܣ�����Ԫ��eΪ�µ�ջ��Ԫ��
//����������ջS��������ַe
//����ֵ������ɹ�����OK��ʧ�ܷ���OVERFLOW
Status Push(SqStack *S,BiTree e)
{
    if(S->top - S->base >= S->stacksize)                //ջ����׷�Ӵ洢�ռ�
    {
        S->base = (TElemType *)realloc(S->base,(S->stacksize + STACKINCREMENT) * sizeof(TElemType));
        if(!S->base) exit(OVERFLOW);                       //�洢����ʧ��
        S->top = S->base + S->stacksize;                // ջ��ָ��Ϊջ��ָ�����ջ֮ǰ����󳤶�
        S->stacksize += STACKINCREMENT;                 // ջ��ǰ����󳤶ȵ���ջ֮ǰ����󳤶������ӵĳ���֮��
    }
    *(S->top++) = e;                                      //�ȸ�ֵ��ջ�д�ŵ�Ϊ�����ĵ�ַ������ջ��ָ������
    return OK;
}
//�������ܣ���ջ���գ�ɾ��ջ��Ԫ�ز���e������ֵ��
//����������ջS����������ָ��e
//����ֵ�������ɹ�����OK�����򷵻�ERROR
Status Pop(SqStack *S,BiTree *e)
{
    if(S->top == S->base) return ERROR;                     //ջ�գ�����ERROR
    *e = *(--S->top);                                         // ջ��ָ�������ƣ���ֵ��*eΪ�����ָ���ŵĵ�ֵַ����ֵ���ı�����ָ���ָ��
    return OK;
}
