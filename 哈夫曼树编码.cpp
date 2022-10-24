#include<iostream>
#include<stdio.h>
using namespace std;
 
 typedef struct{
     int weight;
     int rchild,lchild;
     int parent;
 }HTNode;
typedef struct{
    HTNode*HTree;
    int root;
}HuffmanTree;
void Select(HTNode*t,int n,int &s1,int &s2);

//构建哈夫曼树
void Create_HUffmanTree(HuffmanTree &HT,int *w,int n)//w[]用来存放权重，n是叶子个数
{
if(n<=1)
return;//当只有一个节点或者为空树时候
int m=2*n-1;
HT.HTree=new HTNode[m];
int i=0;
//初始化
for(HTNode*p=HT.HTree; i<m;i++)
{
    p[i].weight=-1;
    p[i].lchild=-1;
    p[i].rchild=-1;
    p[i].parent=-1;
}
//暂且赋值权重值
int j=0;
for(HTNode*q=HT.HTree;j<n;j++)
q[j].weight=w[j];
//构建哈夫曼树
for(int i=n;i<m;i++)
{
int s1,s2;//存储两个最小的权重节点
Select(HT.HTree,i-1,s1,s2);//从0到i-1个节点中选取最小的两个节点，较大的存在s1中，较小的存在s2中,存的都是下标！！！
HT.HTree[i].lchild=s1;
HT.HTree[i].rchild=s2;
HT.HTree[i].weight=HT.HTree[s1].weight+HT.HTree[s2].weight;
HT.HTree[s1].parent=i;
HT.HTree[s2].parent=i;
}//for
HT.root=m-1;
}//Create_HUffmanTree

//挑选两个最小的数值（未选择过的，即HTNode.parent==-1;)
void Select(HTNode*t,int n,int &s1,int &s2)
{
    
    HTNode*p=t;
    s1=-1;
    s2=-1;
    //筛选出一个最小的数值
    for(int i=0;i<=n;i++)//细节“=”号，因为传参是n-1
    {
     if((s1 == -1 || p[i].weight<p[s1].weight) && p[i].parent==-1)//即没有连接为子树的
     s1=i;
    }
     
    for(int j=0;j<=n;j++)
    {
      if((s2 == -1 || p[j].weight<p[s2].weight) && j != s1 && p[j].parent==-1)
      s2=j;
    }

}

//栈
const  int STACK_INIT_SIZE = 100;
const  int STACKINCREMENT = 10;
typedef char SElemType;
typedef struct {
    SElemType* elem;//存储数据元素的数组
    int top;//栈顶指针
    int stacksize;//当前分配的最大容量
    int incrementsize;//约定增补容量
}SqStack;
void InitStack_Sq(SqStack& S)
{
    S.elem = new SElemType[STACK_INIT_SIZE];
    S.top = -1;
    S.stacksize = STACK_INIT_SIZE;
    S.incrementsize = STACKINCREMENT;
}
int StackEmpty_Sq(SqStack S)
{
    if (S.top == -1)
        return 1;
    else
        return 0;
}
int StackLength_Sq(SqStack S)//无用函数
{
    return(S.top + 1);
}
void incrementStackSize_Sq(SqStack& S)//无用函数，不看
{
    int i;
    SElemType* e = new SElemType[STACK_INIT_SIZE + STACKINCREMENT];
    for (i = 0;i < S.top;i++)
        e[i] = S.elem[i];
    S.elem = e;
}
void Push_Sq(SqStack& S, SElemType& e)
{
    if (S.top == S.stacksize - 1)
        incrementStackSize_Sq(S);
    S.elem[++S.top] = e;

}
int Pop_Sq(SqStack& S, SElemType& e)
{
    if (S.top == -1)
        return 0;
    else
    {
        e = S.elem[S.top--];
        return 1;
    }
}

//哈夫曼编码

typedef char* *HuffmanCode;

//怎么把栈中的元素转换为字符串输出
void StackCopyToArry(SqStack S,char*&c);//这里用引用，是因为对指针数组构成的数组中的元素修改
void Coding(HuffmanTree T,int i,SqStack &S,HuffmanCode&Hc,int*ex);


void HuffmanCoding(HuffmanTree HT,HuffmanCode &Hc,int n,int *ex)
{
    SqStack S;
    Hc=new char*[n];
    InitStack_Sq(S);
    Coding(HT,HT.root,S,Hc,ex);
}
void Coding(HuffmanTree T,int i,SqStack &S,HuffmanCode&Hc,int*ex)
{
    
    if(T.HTree)
    {
        if(T.HTree[i].lchild==-1&&T.HTree[i].rchild==-1)
        {
            ex[i]=StackLength_Sq(S);
            Hc[i]=new char[StackLength_Sq(S)];
            StackCopyToArry(S,Hc[i]);
        }
    
    else
    {   
        char e,t1='0',t2='1';
        Push_Sq(S,t1);
        Coding(T,T.HTree[i].lchild,S,Hc,ex);
        Pop_Sq(S,e);
        Push_Sq(S,t2);
        Coding(T,T.HTree[i].rchild,S,Hc,ex);
        Pop_Sq(S,e);
    }
    }
}
void StackCopyToArry(SqStack S,char*&c)//这里用引用，是因为对指针数组构成的数组中的元素修改
{    
     int i;
     for( i=0;i<StackLength_Sq(S);i++)
     {
        c[i]=S.elem[i];
     }
}
void Result(char*pro,HuffmanCode Hc,int num,int *ex)
{   
    cout<<"***************Result************"<<endl;
    for(int i=0;i<num;i++)
    {
        cout<<pro[i]<<":";
        for(int j=0;j<num;j++)
        cout<<Hc[i][j];
        cout<<endl;
    }
}
int main()
{
int num;//需要编码的个数
cout<<"***********Input************"<<endl;
cout<<"请输入需要编码的个数：";
cin>>num;//需要编码的个数
int*wei=new int[num];//存放的权重值
char*pro=new char[num];//需要编码的字母
int i;
cout<<"请输入各个编码的名称以及权重值："<<endl;
for(i=0;i<num;i++)
{
printf("第%d个编码：",i+1);
cin>>pro[i];
cout<<"其权重值为：";
cin>>wei[i];
cout<<endl;
}
HuffmanTree HT;
HuffmanCode Hc;
int*ex=new int[num];//特征量数组
Create_HUffmanTree(HT,wei,num);
HuffmanCoding(HT,Hc,num,ex);
Result(pro,Hc,num,ex);
}


