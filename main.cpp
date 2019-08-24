#include <iostream>
#include <iomanip>
#include <vector>
#include <cmath>
using namespace std;

void chazhaoxiaochu(int xxl[5][5]){
    int num = 1;
    int flag_new = 0;
    int liantong[5][5] = {0};//使用连通数组将连通部分（相同值相邻区域）用同样的数字表示
    
    //求取连通数组
    for (int i = 0; i<5; i++) {
        for (int j = 0; j<5; j++) {
            if(xxl[i][j] == 0)//为后续消除数字变0作准备，为0无需处理
                continue;
            flag_new = 0;
            if(liantong[i][j] == 0){
                if(i != 0){
                    if(xxl[i][j] == xxl[i-1][j]){
                        liantong[i][j] = liantong[i-1][j];
                        flag_new = 1;
                        if(j != 0){
                            if(xxl[i][j-1] == xxl[i][j]){
                                if(liantong[i][j-1] > liantong[i][j] && liantong[i][j] != 0){
                                    for(int i2 = 0; i2<5; i2++)
                                        for (int j2 = 0; j2<5; j2++) {
                                            if(liantong[i2][j2] == liantong[i][j-1])
                                                liantong[i2][j2] = liantong[i][j];
                                        }
                                }
                                else if(liantong[i][j-1] < liantong[i][j] && liantong[i][j] != 0){
                                    for(int i2 = 0; i2<5; i2++)
                                        for (int j2 = 0; j2<5; j2++) {
                                            if(liantong[i2][j2] == liantong[i][j])
                                                liantong[i2][j2] = liantong[i][j-1];
                                        }
                                }
                            }
                        }
                    }
                }
                if(j != 0)
                {
                    if(xxl[i][j] == xxl[i][j-1]){
                        liantong[i][j] = liantong[i][j-1];
                        flag_new = 1;
                    }
                }
                if(flag_new == 0){
                    liantong[i][j] = num;
                    num++;
                }
            }
        }
    }
    //打印连通数组
    for (int i = 0; i<5; i++) {
        for (int j = 0; j<5; j++) {
            //cout << liantong[i][j] << " ";
        }
        //cout << endl;
    }
    //cout << endl;
    
    //找出最大连通部分，（连通数组中数字出现次数最多的部分，数字位置即连通位置）
    int liantong_max = 0, xiaochu = 0;
    int liantong_cnt[25] = {0};
    for (int liantong_num = 1; liantong_num < num; liantong_num++) {
        for (int i = 0; i<5; i++) {
            for (int j =0; j<5; j++) {
                if(liantong[i][j] == liantong_num)
                    liantong_cnt[liantong_num]++;
            }
        }
        if(liantong_cnt[liantong_num] > liantong_max){
            liantong_max = liantong_cnt[liantong_num];
            xiaochu = liantong_num;
        }
    }
    //cout << liantong_max << " " << xiaochu << endl;//查看最大连通部分结果
    
    if(liantong_max<3)
        return;//最大连通部分小于3，说明消除结束
    
    //将最大连通部分的xxl数组变成0
    for(int i = 0; i<5; i++){
        for(int j=0; j<5; j++){
            if(liantong[i][j] == xiaochu)
                xxl[i][j] = 0;
            if(j == 0)
                cout << endl;
            cout << xxl[i][j] << " ";
        }
    }
    
    //添加重力元素，重新整理xxl数组
    cout << endl;
    for(int j = 0; j<5; j++){
        int i = 4;
        for (int num = 4; num>0; num--) {
            if(xxl[i][j] == 0){
                for (int i2 = i; i2>0; i2--) {
                    xxl[i2][j] = xxl[i2-1][j];
                }
                xxl[0][j] = 0;
            }
            else
                i--;
        }
    }
    //输出消除之后的xxl数组
    for(int i = 0; i<5; i++){
        for(int j=0; j<5; j++){
            if(j == 0)
                cout << endl;
            cout << xxl[i][j] << " ";
        }
    }
    cout << endl;
    cout << endl;
    
    chazhaoxiaochu(xxl);//递归调用，直到消除结束
}



int main(int argc, const char * argv[]) {
    
    cout << "hello" << endl;
    int xxl[5][5] = {0};
    int data;
    int i = 0,j = 0;
    while (cin >> data) {
        xxl[i][j] = data;
        j++;
        if(j == 5)
        {
            i++;
            j=0;
        }
    }
    
    
    chazhaoxiaochu(xxl);//消除过程
    
    //计算剩余未消除部分
    int sum = 0;
    for(i = 0; i<5; i++){
        for(j = 0; j<5; j++)
        {
            if(xxl[i][j] != 0)
                sum++;
        }
    }
    
    cout << "result: " << sum << endl;
    return 0;
}


