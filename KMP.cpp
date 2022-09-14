#include<iostream>
#include<cstring>
using namespace std;
//BF
int BF(const char s[],const char t[])
{
    int index=0;
    int i=0,j=0;
    while(s[i]!='\0'&&t[j]!='\0')
    {
        if(s[i]==t[j])
        {   i++;
            j++;}
        else
        {index++,i=index,j=0;}
    }
    if(t[j]=='\0')
        return index+1;//不是下标
    else
        return index;
}

//KMP
void GetNext(int next[],const char t[])
{
    int i,j,len;
    next[0]=-1;
    for(j=1;t[j]!='\0';j++)
    {
        for(len=j-1;len>=1;len--)//长度肯定要比当前字符串小1个。
        {
            for(i=0;i<len;i++)
            {
                if(t[i]!=t[j-len+i])
                    break;
            }
            if(i==len)
            {
                next[j]=len;
                break;
            }

        }
        if(len<1)
            next[j]=0;
    }
}

int KMP(const char s[],const char t[])
{
    int i=0, j=0;
    int next[80];
    GetNext(next,t);
    while(s[i]!='\0'&&t[j]!='\0')
    {
        if(s[i]==t[j])
        {
            i++;
            j++;
        }
        else
        {
            j=next[j];
            if(j==-1)
            {
                i++;
                j++;
            }
        }
    }
    if(t[j]=='\0')
        return(i-strlen(t)+1);
    else
        return 0;

}
//BM
void get_badchar(int* badchar, char* t)
{

    for(int i=0;i<256;i++)
    {
        badchar[i]=-1;
    }
    for(int i=0;i<strlen(t);i++)
    {
        badchar[t[i]]=i;
    }
}
void get_goodsuffix(int* goodsuffix,int t_len,bool* ispre,const char* t)
{
    for(int i=0;i<t_len+1;i++)
    {
        goodsuffix[i]=-1;
    }
    for(int i=0;i<t_len-1;i++)
    {
        int j=i;
        int k=t_len-1;
        while(j>=0&&t[j]==t[k])
        {
            goodsuffix[t_len-k]=j;
            k--;
            j--;
        }
        if(j==-1)
            ispre[i+1]=true;
    }
}
int BM( char s[],  char t[])//s为主串，t为模式串
{
    int s_len=strlen(s);
    int t_len=strlen(t);

    int badchar[256];
    int* goodsuffix=new int[t_len+1];
    bool* ispre =new bool[t_len+1];
    get_badchar(badchar,t);
    get_goodsuffix(goodsuffix,t_len,ispre,t);
    if(s_len<t_len)
        return 0;
    int idx1=t_len-1;
    int idx2=t_len-1;
    while(idx1<s_len)
    {

        while(idx2>=0&&s[idx1]==t[idx2])
        {
            idx1--;
            idx2--;
        }
        if(idx2==-1)
            return idx1+2;
        int way1=idx2-badchar[s[idx1]],way2=0;
        if(idx2<t_len-1)
        {
            if(goodsuffix[t_len-idx2-1]!=-1)
                way2=idx2-goodsuffix[t_len-idx2-1]+1;
            else{
                bool flag=0;
                for(int i=t_len-idx2-2;i>0;i--)
                {
                    if(ispre[i])
                    {
                        flag=1;
                        way2=t_len-i-1;
                        break;
                    }
                }
                if(!flag)
                    way2=t_len;
            }
        }
        int choose=max(way1,way2);
        idx1+=t_len-1-idx2+choose;
        idx2=t_len-1;
    }
    return 0;

}

int main()
{
    char s1[]="ababaababcb";
    char s2[]="ababc";
    int result1=BF(s1,s2);
    int result2=KMP(s1,s2);
    int result3=BM(s1,s2);
    cout<<"主串是:"<<s1<<endl;
    cout<<"匹配串是:"<<s2<<endl;
    cout<<"BF算法得出的结果是:"<<result1<<endl;
    cout<<"KMP算法得出的结果是:"<<result2<<endl;
    cout<<"BM算法得出的结果是:"<<result3<<endl;//加入BM算法的结果

}