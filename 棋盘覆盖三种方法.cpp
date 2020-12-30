/*
题目：棋盘覆盖
时间：2020.4
姓名：asphyxia
*/
#include<stdio.h>
#include<math.h>
#include<malloc.h>
#define STACK_INIT_SIZE 20
#define STACKINCREMENT 5

typedef struct Node {
    int tr, tc, dr, dc, size;//棋盘地址
    struct Node* next;
}Node;

typedef struct {
    Node* front;//队头
    Node* rear;//队尾
}LinkQueue;

typedef struct {
    int tr, tc, dr, dc, size;
}SElemType;

typedef struct {
    SElemType* base;
    SElemType* top;
    int stacksize;
}SqStack;

int board[8][8];
int tile = 1;
int chessBoard(int tr, int tc, int dr, int dc, int size);//递归方法
int chessBoardQL(LinkQueue* Q, int x, int y);//队列算法实现
void InitQueue(LinkQueue* Q);//队列初始化
void InsertQueue(LinkQueue* Q, int tr, int tc, int dr, int dc, int size);//进队列
void DeleteQueue(LinkQueue* Q);//出队列
int LQEmpty(LinkQueue* Q);//队列判空
void Print();//打印棋盘
bool InitStack(SqStack* S);//初始化栈
bool StackEmpty(SqStack* S);//判空
bool StackFull(SqStack* S);//判满
bool Push(SqStack* S, int tr, int tc, int dr, int dc, int size);//入栈
bool Pop(SqStack* S);//出栈
void DestoryStack(SqStack* S);//销毁栈
int chessBoardSS(SqStack* S, int x, int y);//栈实现



int main()
{
    int x, y;
    printf("请输入特殊方格的位置：");
    scanf_s("%d%d", &x, &y);
    board[x][y] = 0;
    chessBoard(0, 0, x, y, 8);
    printf("递归实现：\n");
    Print();
    LinkQueue Q;
    InitQueue(&Q);
    chessBoardQL(&Q, x, y);
    printf("队列实现：\n");
    Print();
    SqStack S;
    chessBoardSS(&S, x, y);
    DestoryStack(&S);
    printf("栈实现：\n");
    Print();

    return 0;

}


int chessBoard(int tr, int tc, int dr, int dc, int size)//递归算法
{
    if (size == 1)return 0;
    int t = tile++;//L型骨牌号
    int s = size / 2;//分割棋盘；
    //1.覆盖左上子棋盘
    if (dr < tr + s && dc < tc + s)//特殊方格在此子棋盘中
        chessBoard(tr, tc, dr, dc, s);
    else {//特殊方格不在此子棋盘中
        board[tr + s - 1][tc + s - 1] = t;//用t号骨牌覆盖右下角
        chessBoard(tr, tc, tr + s - 1, tc + s - 1, s);//覆盖其他方格
    }
    //2.覆盖右上子棋盘
    if (dr < tr + s && dc >= tc + s)//特殊方格在此子棋盘中
        chessBoard(tr, tc + s, dr, dc, s);
    else {//特殊方格不在此子棋盘中
        board[tr + s - 1][tc + s] = t;//用t号骨牌覆盖左下角
        chessBoard(tr, tc + s, tr + s - 1, tc + s, s);//覆盖其他方格
    }
    //3.覆盖左下子棋盘
    if (dr >= tr + s && dc < tc + s)//特殊方格在此子棋盘中
        chessBoard(tr + s, tc, dr, dc, s);
    else {//特殊方格不在此子棋盘中
        board[tr + s][tc + s - 1] = t;//用t号骨牌覆盖右上角
        chessBoard(tr + s, tc, tr + s, tc + s - 1, s);//覆盖其他方格
    }
    //4.覆盖右下子棋盘
    if (dr >= tr + s && dc >= tc + s)//特殊方格在此子棋盘中
        chessBoard(tr + s, tc + s, dr, dc, s);
    else {//特殊方格不在此子棋盘中
        board[tr + s][tc + s] = t;//用t号骨牌覆盖左上角
        chessBoard(tr + s, tc + s, tr + s, tc + s, s);//覆盖其他方格
    }
    return 0;
}

int chessBoardQL(LinkQueue* Q, int x, int y)//队列算法实现
{
    int s, tr, tc, dr, dc;
    int t = 0;
    InsertQueue(Q, 0, 0, x, y, 8);
    Node* p;
    while (Q->front->next != NULL)
    {
        p = Q->front->next;
        if (p->size == 1) {

        }
        else {
            s = p->size / 2;
            t++;
            tr = p->tr;
            tc = p->tc;
            dr = p->dr;
            dc = p->dc;
            //1.覆盖左上子棋盘
            if (dr < tr + s && dc < tc + s)//特殊方格在此子棋盘中
                InsertQueue(Q, tr, tc, dr, dc, s);//入队
            else {//特殊方格不在此子棋盘中
                board[tr + s - 1][tc + s - 1] = t;//用t号骨牌覆盖右下角
                InsertQueue(Q, tr, tc, tr + s - 1, tc + s - 1, s);
            }
            //2.覆盖右上子棋盘
            if (dr < tr + s && dc >= tc + s)//特殊方格在此子棋盘中
                InsertQueue(Q, tr, tc + s, dr, dc, s);
            else {//特殊方格不在此子棋盘中
                board[tr + s - 1][tc + s] = t;//用t号骨牌覆盖左下角
                InsertQueue(Q, tr, tc + s, tr + s - 1, tc + s, s);
            }
            //3.覆盖左下子棋盘
            if (dr >= tr + s && dc < tc + s)//特殊方格在此子棋盘中
                InsertQueue(Q, tr + s, tc, dr, dc, s);
            else {//特殊方格不在此子棋盘中
                board[tr + s][tc + s - 1] = t;//用t号骨牌覆盖右上角
                InsertQueue(Q, tr + s, tc, tr + s, tc + s - 1, s);
            }
            //4.覆盖右下子棋盘
            if (dr >= tr + s && dc >= tc + s)//特殊方格在此子棋盘中
                InsertQueue(Q, tr + s, tc + s, dr, dc, s);
            else {//特殊方格不在此子棋盘中
                board[tr + s][tc + s] = t;//用t号骨牌覆盖左上角
                InsertQueue(Q, tr + s, tc + s, tr + s, tc + s, s);
            }
        }
        DeleteQueue(Q);//出队
    }
    return 0;
}

void InitQueue(LinkQueue* Q)//队列初始化
{
    Q->front = (Node*)malloc(sizeof(Node));
    if (!Q->front)
        return;
    Q->front->next = NULL;
    Q->rear = Q->front;
}

void InsertQueue(LinkQueue* Q, int tr, int tc, int dr, int dc, int size)//进队列
{
    Node* p;
    p = (Node*)malloc(sizeof(Node));
    if (!p) return;
    p->next = NULL;
    p->tr = tr;
    p->tc = tc;
    p->dr = dr;
    p->dc = dc;
    p->size = size;
    p->next = Q->rear->next;
    Q->rear->next = p;
    Q->rear = Q->rear->next;
}

void DeleteQueue(LinkQueue* Q)//出队列
{
    Node* p;
    if (Q->front == Q->rear)
        return;
    p = Q->front->next;
    Q->front->next = p->next;
    free(p);
}

int LQEmpty(LinkQueue* Q)//队列判空
{
    if (Q->front == Q->rear)
        return true;
    return false;
}

void Print() {//打印棋盘
    printf("-------------------------\n");
    for (int i = 0; i < 8; i++) {
        printf("|");
        for (int j = 0; j < 8; j++)
            printf("%2d|", board[i][j]);
        printf("\n-------------------------\n");
    }
}

int chessBoardSS(SqStack* S, int x, int y)
{
    if (InitStack(S) == false)
        return 0;
    Push(S, 0, 0, x, y, 8);
    int s, tr, tc, dr, dc;
    int t = 0;
    while (!StackEmpty(S))//栈不空
    {

        if (S->top->size == 1) {
            Pop(S);//出栈
        }
        else {
            t++;
            s = S->top->size / 2;
            tr = S->top->tr;
            tc = S->top->tc;
            dr = S->top->dr;
            dc = S->top->dc;
            Pop(S);//出栈
            //1.覆盖左上子棋盘
            if (dr < tr + s && dc < tc + s)//特殊方格在此子棋盘中
                Push(S, tr, tc, dr, dc, s);//入栈
            else {//特殊方格不在此子棋盘中
                board[tr + s - 1][tc + s - 1] = t;//用t号骨牌覆盖右下角
                Push(S, tr, tc, tr + s - 1, tc + s - 1, s);
            }
            //2.覆盖右上子棋盘
            if (dr < tr + s && dc >= tc + s)//特殊方格在此子棋盘中
                Push(S, tr, tc + s, dr, dc, s);
            else {//特殊方格不在此子棋盘中
                board[tr + s - 1][tc + s] = t;//用t号骨牌覆盖左下角
                Push(S, tr, tc + s, tr + s - 1, tc + s, s);
            }
            //3.覆盖左下子棋盘
            if (dr >= tr + s && dc < tc + s)//特殊方格在此子棋盘中
                Push(S, tr + s, tc, dr, dc, s);
            else {//特殊方格不在此子棋盘中
                board[tr + s][tc + s - 1] = t;//用t号骨牌覆盖右上角
                Push(S, tr + s, tc, tr + s, tc + s - 1, s);
            }
            //4.覆盖右下子棋盘
            if (dr >= tr + s && dc >= tc + s)//特殊方格在此子棋盘中
                Push(S, tr + s, tc + s, dr, dc, s);
            else {//特殊方格不在此子棋盘中
                board[tr + s][tc + s] = t;//用t号骨牌覆盖左上角
                Push(S, tr + s, tc + s, tr + s, tc + s, s);
            }
        }

    }
    return 0;
}

bool InitStack(SqStack* S)//初始化栈
{
    S->base = (SElemType*)malloc(STACK_INIT_SIZE * sizeof(SElemType));
    if (!S->base)
        return false;
    S->top = S->base;
    S->stacksize = STACK_INIT_SIZE;
    return true;
}

bool StackEmpty(SqStack* S)//判空
{
    if (S->top == S->base)
        return true;
    return false;
}

bool StackFull(SqStack* S)//判满
{
    if (S->top - S->base >= S->stacksize)
        return true;
    return false;
}

bool Realloc(SqStack* S)//重新分配空间
{
    S->base = (SElemType*)realloc(S->base, (STACK_INIT_SIZE + STACKINCREMENT) * sizeof(SElemType));
    if (!S->base)
        return false;
    S->top = S->base + S->stacksize;
    S->stacksize += STACKINCREMENT;
    return true;
}

bool Push(SqStack* S, int tr, int tc, int dr, int dc, int size)//入栈
{
    if (StackFull(S) == int(true))
        if (Realloc(S) == int(false))
            return false;
    S->top++;
    S->top->tr = tr;
    S->top->tc = tc;
    S->top->dr = dr;
    S->top->dc = dc;
    S->top->size = size;
    //*S->top++ = elem;
    return true;
}

bool Pop(SqStack* S)//出栈
{
    if (StackEmpty(S) == true)
        return false;
    S->top--;
    return true;
}

void DestoryStack(SqStack* S)//销毁栈
{
    S->top = S->base;
    S->base = NULL;
    S->stacksize = 0;
    free(S->base);
}

