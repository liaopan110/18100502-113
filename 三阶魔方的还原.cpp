#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
//表示每个面除中间的另外8个的位置
short int cen[6][8]={
    {0,1,2,3,5,6,7,8},{9,10,11,21,23,33,34,35},{12,13,14,24,26,36,37,38},
    {15,16,17,27,29,39,40,41},{18,19,20,30,32,42,43,44},{45,46,47,48,50,51,52,53}
};
//转换数组，12种变换，两两对应，每次转换会更改20个位置
short int change[12][20]={
         {11,23,35,34,33,21,9,10,51,48,45,36,24,12,6,3,0,20,32,44},
         {9,10,11,23,35,34,33,21,36,24,12,6,3,0,20,32,44,51,48,45},
         {14,13,26,38,37,36,24,12,45,46,47,39,27,15,8,7,6,11,23,35},
         {12,24,13,14,26,38,37,36,39,27,15,8,7,6,11,23,35,45,46,47},
         {17,29,41,40,39,27,15,16,47,50,53,42,30,18,2,5,8,14,26,38},
         {15,16,17,29,41,40,39,27,42,30,18,2,5,8,14,26,38,47,50,53},
         {18,19,20,32,44,43,42,30,53,52,51,33,21,9,0,1,2,17,29,41},
         {42,30,18,19,20,32,44,43,33,21,9,0,1,2,17,29,41,53,52,51},
         {0,1,2,5,8,7,6,3,12,13,14,15,16,17,18,19,20,9,10,11},
         {6,3,0,1,2,5,8,7,15,16,17,18,19,20,9,10,11,12,13,14},
         {45,46,47,50,53,52,51,48,44,43,42,41,40,39,38,37,36,35,34,33},
         {51,48,45,46,47,50,53,52,41,40,39,38,37,36,35,34,33,44,43,42}
};
char a[54];  //初始状态
int depth;   //迭代加深搜索的层数
bool flag;   //是否有解
int centre[6]={4,22,25,28,31,49};//每个面中心坐标
int get_h(char *maze){
    int ret=0;
    for(int i=0;i<6;i++){
        int cnt=0;
        for(int j=0;j<8;j++)
            if(maze[cen[i][j]]!=maze[centre[i]])
                cnt++;
        ret=max(ret,cnt);
    }
    return (ret+2)/3;
}
int ans[10];
//调试用的，输出当前的形状
void debug(char *maze){
    int k=0;
    for(int i=0;i<3;i++){
        printf("      ");
        for(int j=0;j<3;j++)
            printf("%c ",maze[k++]);
        printf("\n");
    }
    for(int i=0;i<3;i++){
        for(int j=0;j<12;j++)
            printf("%c ",maze[k++]);
        printf("\n");
    }
    for(int i=0;i<3;i++){
        printf("      ");
        for(int j=0;j<3;j++)
            printf("%c ",maze[k++]);
        printf("\n");
    }

}
void IDAstar(int tmp_depth,char *b,int father){
    if(flag)
        return;
    //A*剪枝
    if(get_h(b)>tmp_depth)
        return;
    if(tmp_depth==0){
        flag=true;
        return;
    }
    for(int i=0;i<12;i++){
        if(flag)
            return;
        if((i^father)==1)
            continue;
        char tmp[54];
        memcpy(tmp,b,54*sizeof(char));
        ans[tmp_depth]=i;
        //转换
        for(int j=0;j<20;j++)
            tmp[change[i][j]]=b[change[i^1][j]];;
        IDAstar(tmp_depth-1,tmp,i);
    }
}
char get_in(){
    char ch;
    while(1){
        ch=getchar();
        if(ch>='a'&&ch<='z')
            return ch;
    }
}
int main(){
    int t;
    scanf("%d",&t);
    while(t--){
        for(int i=0;i<54;i++)
            a[i]=get_in();
        flag=false;
        int Init=get_h(a);
        if(Init==0){
            printf("0\n");
            continue;
        }
        for(depth=Init;depth<=5;depth++){
            IDAstar(depth,a,-1);
            if(flag){
                printf("%d\n",depth);
                printf("%d %d",ans[depth]/2,(ans[depth]&1)?-1:1);
                for(int j=depth-1;j>0;j--)
                    printf(" %d %d",ans[j]/2,(ans[j]&1)?-1:1);
                printf("\n");
                break;
            }
        }
        if(!flag)
            printf("-1\n");
    }
    return 0;
}
