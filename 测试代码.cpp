#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;

// 常量定义：M是小朋友数量上限(题目中m≤50)，N是糖果数量上限(题目中n≤100)
const int M = 51, N = 101;

// 全局变量说明：
// n: 糖果的总包数
// m: 小朋友的总人数
// w[N]: 糖果重量的前缀和数组，w[i]表示前i包糖果的总重量
// f[M][N][N]: DP数组，核心状态
//   f[i][j][k] 含义：前i个小朋友分配完成，最后一个用了1颗糖的位置在j，最后一个
//用了2颗糖的位置在k，此时所有区间的最大重量的最小值
// st[N]: 单调栈数组，用于优化DP转移的时间复杂度
// ans: 最终答案（最大重量-最小重量的最小差值），初始化为int最大值(0x7fffffff)
int n, m, w[N], f[M][N][N], st[N], ans = 0x7fffffff;

int main(){
    // 输入糖果数量n和小朋友数量m
    scanf("%d%d", &n, &m);
    // 读入每包糖果的重量，并计算前缀和
    for(int i = 1; i <= n; i++){
        scanf("%d", &w[i]);
        w[i] += w[i - 1]; // 前缀和：w[i] = w[1]+w[2]+...+w[i]
    }

    // 枚举每个可能的「区间最小重量」minw，上界设为2*总重量/m（题解中给出的优化上界，
	//控制复杂度）
    for(int minw = 1; minw <= 2 * w[n] / m; minw++){
        // 每次枚举新的minw时，将DP数组初始化为无穷大（0x7f对应大数，代表不可达状态）
        memset(f, 0x7f, sizeof(f));
        // 初始状态：0个小朋友分配、位置j=0/k=0时，最大重量初始化为当前枚举的minw
        f[0][0][0] = minw;

        // 第一层循环：枚举分配给第i个小朋友（i从1到m）
        for(int i = 1; i <= m; i++) {
            // 第二层循环：枚举「最后一个用了1颗糖的位置」j（j从0到n）
            for(int j = 0; j <= n; j++){
                // 单调栈指针初始化：st数组的有效长度置0
                *st = 0;
                // p：当前满足区间和≥minw的左端点；pst：单调栈中「最佳转移点」
				//的指针（初始为1）
                int p = 0, pst = 1;

                // 第三层循环：枚举「最后一个用了2颗糖的位置」k（k从j到n）
                for(int k = j; k <= n; k++){
                    // 转移1：继承j-1位置的状态（f[i][j][k] ← f[i][j-1][k]）
                    if(j > 0) f[i][j][k] = f[i][j - 1][k];

                    // 找到所有满足「区间和w[k]-w[p] ≥ minw」的左端点p
                    while(w[k] - w[p] >= minw){
                        // 仅当p≥j时，才将p加入单调栈（保证转移合法性）
                        if(p >= j){
                            // 单调栈维护：若栈顶元素的f值≥当前p的f值，栈顶
							//元素无意义，弹出
                            while(*st && f[i - 1][j][p] <= 
								f[i - 1][j][st[*st]])
                                (*st)--;
                            // 将当前p压入单调栈（栈中元素f值单调递减）
                            st[++*st] = p;
                        }
                        p++; // 左端点右移，继续找满足条件的p
                    }

                    // 若单调栈非空，利用栈中最优转移点更新DP状态
                    if(*st){
                        // 缩小最佳转移点范围：取pst和栈长度的最小值
                        pst = min(pst, *st);
                        // 找更优的转移点：若下一个点的max(f,区间和)更小，
						//则右移pst
                        while(pst < *st && f[i - 1][j][st[pst + 1]] < w[k]-
							 w[st[pst + 1]])
                            pst++;
                        // 回退无效转移点：若当前点的max(f,区间和)更大，
						//则左移pst
                        while(pst > 1 && f[i - 1][j][st[pst]] > w[k] - 
							w[st[pst]])
                            pst--;
                        
                        // 用最佳转移点更新f[i][j][k]：取当前值和max(前驱f值, 
						//区间和)的最小值
                        f[i][j][k] = min(f[i][j][k], max(f[i - 1][j][st[pst]], 
							w[k] - w[st[pst]]));
                        // 检查下一个转移点，取更优值（题解中提到最佳转移点可能
						//是相邻两点）
                        if(pst < *st)
                            f[i][j][k] = min(f[i][j][k], 
								max(f[i - 1][j][st[pst + 1]],
									 w[k] - w[st[pst + 1]]));
                    }

                    // 转移2：处理「第i个小朋友用了上一次pp+1开始的区间」的情况
                    // pp是p-1和j的最小值，保证转移合法性
                    int pp = min(p - 1, j);
                    if(pp >= 0)
                        f[i][j][k] = min(f[i][j][k], max(f[i - 1][pp][j],
							 w[k] - w[pp]));
                }
            }
        }
        // 更新答案：当前minw对应的「最大重量-最小重量」的差值，取全局最小值
        ans = min(ans, f[m][n][n] - minw);
    }
    // 输出最终的最小差值
    printf("%d", ans);
    return 0;
}

#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;
const int M = 51, N = 101;

int n, m, w[N], f[M][N][N], st[N], ans = 0x7fffffff;

int main(){
    scanf("%d%d", &n, &m);
    for(int i = 1; i <= n; i++){
        scanf("%d", &w[i]);
        w[i] += w[i - 1];
    }
    for(int minw = 1; minw <= 2 * w[n] / m; minw++){
        memset(f, 0x7f, sizeof(f));
        f[0][0][0] = minw;
        for(int i = 1; i <= m; i++) {
            for(int j = 0; j <= n; j++){
                *st = 0;
                int p = 0, pst = 1;
                for(int k = j; k <= n; k++){
                    if(j > 0) f[i][j][k] = f[i][j - 1][k];
                    while(w[k] - w[p] >= minw){
                        if(p >= j){
                            while(*st && f[i - 1][j][p] <=
								 f[i - 1][j][st[*st]])
                                (*st)--;
                            st[++*st] = p;
                        }
                        p++;
                    }
                    if(*st){
                        pst = min(pst, *st);
                        while(pst < *st && f[i - 1][j][st[pst + 1]] < 
							w[k] - w[st[pst + 1]])
                            pst++;
                        while(pst > 1 && f[i - 1][j][st[pst]] > 
							w[k] - w[st[pst]])
                            pst--;
                        f[i][j][k] = min(f[i][j][k], 
							max(f[i - 1][j][st[pst]], w[k] - w[st[pst]]));
                        if(pst < *st)
                            f[i][j][k] = min(f[i][j][k], 
								max(f[i - 1][j][st[pst + 1]], 
									w[k] - w[st[pst + 1]]));
                    }
                    int pp = min(p - 1, j);
                    if(pp >= 0)
                        f[i][j][k] = min(f[i][j][k], max(f[i - 1][pp][j], 
							w[k] - w[pp]));
                }
            }
        }
        ans = min(ans, f[m][n][n] - minw);
    }
    printf("%d", ans);
    return 0;
}
