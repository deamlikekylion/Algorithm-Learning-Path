#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <string>
#include <climits>
using namespace std;

int main() {
    int n, m;  cin >> n >> m;  
	// n：输入的单词数量；m：期望的词汇表长度
    vector<pair<string, long long>> words(n);  
	// 存储每个单词及其出现频率（string:单词，long long:频率）
    set<char> charSet;  
	// 收集所有出现的字符（自动去重且按字典序排序）

    // 第一步：读取单词及其频率，并收集所有出现的字符
    for (int i = 0; i < n; ++i) {
        cin >> words[i].first >> words[i].second;
        for (char c : words[i].first) {
            charSet.insert(c);  
			// 将单词中的每个字符插入集合，实现去重和字典序排序
        }
    }

    // 第二步：初始化词汇表（单字母，按字典序）
    vector<string> vocab;
    for (char c : charSet) {
        vocab.push_back(string(1, c));  
		// 将每个字符转为单字母字符串，加入词汇表
		// string(int n, char c)
		// 它的功能是：生成一个由n个重复的字符c组成的字符串
    }

    // 第三步：初始化每个单词的分词序列（拆分为单字母）
    vector<vector<string>> splits(n);  // splits[i]存储第i个单词的分词结果
    for (int i = 0; i < n; ++i) {
        for (char c : words[i].first) {
            splits[i].push_back(string(1, c));  // 每个字符作为独立词汇
        }
    }

    // 第四步：循环合并词汇对，直到词汇表长度达到m或无法合并
    while (vocab.size() < m) {
        // 统计所有相邻词汇对的出现频率
        map<pair<string, string>, long long> pairFreq;  
		// 键：(前词汇, 后词汇)；值：总频率
        bool hasPairs = false;  
		// 标记是否存在可合并的相邻词汇对

        // 遍历每个单词的分词序列，统计相邻词汇对的频率
        for (int i = 0; i < n; ++i) {
            const auto& sp = splits[i];  // 当前单词的分词序列
            long long freq = words[i].second;  // 该单词的出现频率（用于累加）
            int len = sp.size();
            for (int j = 0; j < len - 1; ++j) {  // 遍历相邻的两个词汇
                pair<string, string> p = {sp[j], sp[j + 1]};  // p为pairFreq的键 
                pairFreq[p] += freq;  // 累加该词汇对的总频率
                hasPairs = true;  // 标记存在可合并的对
            }
        }

        // 如果没有可合并的词汇对，提前终止循环
        if (!hasPairs) break;

        // 选择“最优”的词汇对（按优先级：频率→拼接长度→前词汇长度→字典序）
        pair<string, string> bestPair;  // 存储最终选中的词汇对（前，后）
        long long maxFreq = -1;         // 记录最大频率
        int maxCombLen = -1;            // 记录拼接后的最大长度
        int minPrevLen = INT_MAX;       // 记录前一个词汇的最小长度
        string minCombStr;              // 记录拼接后字典序最小的字符串

        for (const auto& entry : pairFreq) {
            const auto& p = entry.first;  // 当前候选的词汇对 (prev, next)
            long long freq = entry.second;  // 该词汇对的总频率
            string prev = p.first, next = p.second;
            string comb = prev + next;  // 拼接后的词汇
            int combLen = comb.size();  // 拼接后的长度
            int prevLen = prev.size();  // 前一个词汇的长度

            // 优先级1：频率更高的对更优
            if (freq > maxFreq) {
                maxFreq = freq;
                maxCombLen = combLen;
                minPrevLen = prevLen;
                minCombStr = comb;
                bestPair = p;
            } else if (freq == maxFreq) {  
			// 优先级2：频率相同，选拼接后更短的
                if (combLen < maxCombLen) {
                    maxCombLen = combLen;
                    minPrevLen = prevLen;
                    minCombStr = comb;
                    bestPair = p;
                } else if (combLen == maxCombLen) {  
				// 优先级3：长度相同，选前词汇更短的
                    if (prevLen < minPrevLen) {
                        minPrevLen = prevLen;
                        minCombStr = comb;
                        bestPair = p;
                    } else if (prevLen == minPrevLen && comb < minCombStr) {  
					// 优先级4：前长度相同，选字典序更小的
					// string字符串可直接用<比较字典序 
                        minCombStr = comb;
                        bestPair = p;
                    }
                }
            }
        }

        // 将选中的词汇对拼接后，加入词汇表
        vocab.push_back(bestPair.first + bestPair.second);

        // 更新所有单词的分词序列：将相邻的“最优对”替换为新词汇
        for (auto& sp : splits) {
            vector<string> newSp;  // 存储更新后的分词序列
            int len = sp.size();
            for (int j = 0; j < len; ) {  // j的步进由是否匹配决定
                // 如果当前位置和下一个位置能匹配“最优对”
                if (j + 1 < len && sp[j] == bestPair.first && sp[j + 1] 
				== bestPair.second) {
                    newSp.push_back(bestPair.first + bestPair.second);  
					// 替换为新词汇
                    j += 2;  // 跳过这两个被合并的词汇
                } else {
                    newSp.push_back(sp[j]);  // 不匹配，保留原词汇
                    j += 1;
                }
            }
            sp = newSp;  // 更新当前单词的分词序列
                         // 同类型的vector可以直接用=赋值
        }

        // 检查是否所有单词都已合并为一个词汇（若全合并则无法继续，退出循环）
        bool allMerged = true;
        for (const auto& sp : splits) {
            if (sp.size() != 1) {  // 存在未合并为单个词汇的单词
                allMerged = false;
                break;
            }
        }
        if (allMerged) break;
        
    }  // while循环结束 

    // 按顺序输出词汇表中的所有词汇
    for (const string& v : vocab) {
        cout << v << '\n';
    }

    return 0;
}