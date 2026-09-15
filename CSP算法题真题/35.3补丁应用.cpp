#include <iostream>
#include <vector>
#include <string>
#include <regex>
#include <algorithm>
#include <sstream>
using namespace std;
 
// 定义补丁块结构体，存储单个补丁块的关键信息
struct PatchBlock {
    int origNN;          // 原文件中该块的起始行号（1-based）
    int origMM;          // 原文件中该块涉及的行数
    int mm;              // 新文件中该块替换后的行数
    vector<string> origContent;  // 原文件中需要匹配的内容（已去除前缀符号）
    vector<string> newContent;   // 替换后的新内容（已去除前缀符号）
};

int main () {
	// 关闭输入输出同步，提高读写效率
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    // -------------------------- 读取原始文件内容 --------------------------
    int n;  // 原始文件的总行数
    cin >> n;
    cin.ignore();  // 忽略输入n后的换行符，避免影响后续getline读取
    
    vector<string> origLines;  // 存储原始文件的所有行（0-based索引）
    for(int i = 1; i <= n; ++i) {  // 行号从1开始计数（符合常规文件行号习惯）
        string line;
        getline(cin, line);  // 读取一行内容
        origLines.push_back(line);
    }
    
    // -------------------------- 读取并处理补丁内容 --------------------------
    vector<string> patchLines;  // 存储过滤后的补丁行（去除注释）
    string line;
    while(getline(cin, line)) {  // 读取所有补丁行，直到EOF
        if(!(!line.empty() && line[0] == '#')) {  
		// 过滤注释行（题目描述1：忽略#开头的行）
            patchLines.push_back(line);
        }
    } 
    
    // -------------------------- 分割补丁为多个块 --------------------------
    vector<PatchBlock> blocks;  // 存储所有有效的补丁块
    int i = 0;
    while(i < patchLines.size()) {
        // 识别块的开头（以"@@"起始）
        if(patchLines[i].substr(0, 2) == "@@") { 
            string header = patchLines[i++];  // 块头部（如"@@ -2,1 +2,1 @@"）
            
            // 提取块内的所有行（直到下一个"@@"或补丁结束）
            vector<string> blockLines;
            while(i < patchLines.size() && patchLines[i].substr(0, 2) != "@@") {
                blockLines.push_back(patchLines[i++]);
            }
            
            // 解析块头信息
            int origNN, origMM, nn, mm, t;
            origNN = origMM = nn = mm = t = 0; 
            // 检查块头开头是否为"@@ -"（避免越界：先检查长度）
            if (header.size() < 6 || header[0] != '@' || header[1] != '@' || 
			    header[2] != ' ' || header[3] != '-')    t = 1;
            int j = 4;
            while (!t && j < header.size()) {  // 解析origNN
                if (isdigit(header[j])) {
                    origNN = origNN * 10 + (header[j] - '0');
                    j++;
                } else if (header[j] == ',') {
                    j++;  break;
                } else  t = 1; 
            }
            if (origNN <= 0) t = 1;  // 验证origNN为正整数
            while (!t && j < header.size()) {   // 解析origMM
                if (isdigit(header[j])) {
                    origMM = origMM * 10 + (header[j] - '0');
                    j++;
                } else if (header[j] == ' ' && j+1 < header.size() && 
				           header[j+1] == '+') {
                       j += 2;  break;
                } else  t = 1; 
            }
            if (origMM <= 0) t = 1;  // 验证origMM为正整数
            while (!t && j < header.size()) {  // 解析nn
                if (isdigit(header[j])) {
                    nn = nn * 10 + (header[j] - '0');
                    j++;
                } else if (header[j] == ',') {
                    j++;  break;
                } else  t = 1; 
            }
            if (nn <= 0) t = 1;  // 验证nn为正整数
            while (!t && j < header.size()) {  // 解析mm
                if (isdigit(header[j])) {
                    mm = mm * 10 + (header[j] - '0');
                    j++;
                } else if (header[j] == ' ') {
                    j++;  break;
                } else  t = 1; 
            }
            if (mm <= 0) t = 1;  // 验证mm为正整数
            // 检查块尾是否为"@@"（避免越界）
            if (!t && (j + 1 >= header.size() || header[j] != '@' || 
			    header[j+1] != '@'))    t = 1;
            if (t) {  // 题目描述4：块头格式错误
                cout << "Patch is damaged." << endl;
                return 0;
            }
            
            // 处理块内的内容行（提取原内容和新内容）
            vector<string> origContent, newContent;
            for(const auto& bline : blockLines) {
                // 检查行前缀是否合法（必须是-、+或空格，题目描述7）
                char prefix = bline[0]; 
                if(prefix != '-' && prefix != '+' && prefix != ' ') {
                    cout << "Patch is damaged." << endl;
                    return 0;
                }
                
                // 提取前缀后的内容（去除-、+或空格）
                string content = bline.substr(1);   
                
                // 原内容：收集-或空格开头的行（题目描述8）
                if(prefix == '-' || prefix == ' ') { 
                    origContent.push_back(content);
                }
                // 新内容：收集+或空格开头的行（题目描述10）
                if(prefix == '+' || prefix == ' ') { 
                    newContent.push_back(content);
                }
            }
            
            // 校验原内容行数是否等于origMM，新内容行数是否等于mm（题目描述9、11）
            if(origContent.size() != origMM || newContent.size() != mm) {
                cout << "Patch is damaged." << endl;
                return 0;
            }
            
            // 校验块的顺序：后一个块的起始行必须 >= 前一个块的结束行（题目描述6）
            if(!blocks.empty()) {  // 第一个块不用检验 
                // 前一个块的结束行 = 前一个块的起始行 + 前一个块的行数
                int prevEnd = blocks.back().origNN + blocks.back().origMM;
                // vector v;  v.back为v中最后一个元素
				// 此时的块为加入blocks，最后一个元素就是上一个块 
                if(origNN < prevEnd) {  
				// 当前块起始行早于前一个块结束行，重叠无效
                    cout << "Patch is damaged." << endl;
                    return 0;
                }
            } 
                
            // 将当前块加入块列表（使用emplace_back直接构造对象，更高效）
            blocks.emplace_back(  // 相当于push_back 
			PatchBlock{origNN, origMM, mm, origContent, newContent} );
			// if判断结束 
        } else { 
            // 忽略块之外的无关文本（如补丁开头/中间的非块内容，题目描述3）
            ++i;
        }
    } 
    
    // 检查是否有有效块（题目描述2：补丁至少包含一个块）
    if(blocks.empty()) { 
        cout << "Patch is damaged." << endl;
        return 0;
    } 
    
    // -------------------------- 应用补丁到原始文件 --------------------------
    int deltaSum = 0;  // 累积偏移量：记录前面所有块导致的行号偏移δ总和
    int prevAdjustedNN = -1;  // 前一个块调整后的起始行号（用于避免块重叠）
    int prevBlockMM = 0;  // 前一个块的原始行数（用于计算位置关系）
    
    // 遍历每个块，计算偏移量并应用补丁
    for(int idx = 0; idx < blocks.size(); idx++) {
        const PatchBlock& block = blocks[idx];
        // 当前块的起始行号 = 原始起始行号 + 前面所有块的累积偏移量δ
        int adjustedNN = block.origNN + deltaSum; 
        
        int MM = block.origMM;  // 当前块在原文件中的行数
        vector<int> validDeltas;  // 存储所有有效的偏移量δ
        
        // 遍历可能的偏移量δ（范围：-(MM-1) ~ MM-1，绝对值小于MM，题目描述13）
        for(int delta = -(MM - 1); delta <= MM - 1; delta++) { 
            // 计算偏移后的起始行号（1-based）
            int start1 = adjustedNN + delta;  // NN + δ 
            if(start1 < 1) continue;  // 行号不能小于1（无效位置）
            
            // 转换为0-based索引（用于访问vector）
            int start0 = start1 - 1; 
            // 检查是否超出原文件范围（起始位置+行数不能超过当前文件总行数）
            if(start0 + MM > origLines.size()) continue; 
            
            // 确保当前块与前一个块不重叠（题目描述13:NN + δ> NN + MM）
            if(idx > 0) {
                // 前一个块的结束位置 = 前一个块调整后的起始行号 + 前一个块的行数
                int requiredStart = prevAdjustedNN + prevBlockMM;  // NN + MM
                if(start1 < requiredStart) continue;  // 重叠则跳过该δ
            }
        
            // 检查原文件中从start0开始的MM行是否与块的原内容匹配
            bool match = true;
            for(int i = 0; i < MM; i++) {
                int lineIdx = start0 + i;  // 当前行的0-based索引
                // 若内容不匹配，标记为无效δ
                if (origLines[lineIdx] != block.origContent[i]) {
                    match = false;
                    break;
                }
            } 
            
            // 匹配成功，记录该δ
            if(match) {
                validDeltas.push_back(delta); 
            } 
        }
        
        // 若没有有效δ，补丁损坏（题目描述13.2）
        if(validDeltas.empty()) {
            cout << "Patch is damaged." << endl;
            return 0;
        }
        
        // 排序有效δ：优先选绝对值最小的，若绝对值相同则选更小的δ（题目描述14）
        sort(validDeltas.begin(), validDeltas.end(), [](int a, int b) {
            if(abs(a) != abs(b)) return abs(a) < abs(b);  // 先按绝对值排序
            return a < b;  // 绝对值相同则按数值排序
        });
        int delta = validDeltas[0];  // 选择最优δ
        
        // 计算应用补丁的起始位置（0-based）
        int start0 = (adjustedNN + delta) - 1; 
        
        // 1. 删除原文件中对应的MM行（origLines定义在28行） 
        origLines.erase(origLines.begin() + start0, 
		                origLines.begin() + start0 + MM);
        // 2. 插入新内容（mm行）
        origLines.insert(origLines.begin() + start0, 
		                 block.newContent.begin(), block.newContent.end());
        // vector的erase和insert操作 
        
        // 更新累积偏移量：当前δ + 新行数与原行数的差值（影响后续块的位置）
        deltaSum += delta + block.mm - block.origMM; 
        // 更新前一个块的调整后起始行号（用于下一个块的重叠检查）
        prevAdjustedNN = adjustedNN + delta + block.mm - block.origMM;
		//  deltaSum和prevAdjustedNN的计算有点奇怪 
        prevBlockMM = block.origMM;  // 更新前一个块的原始行数
    }
    
    // -------------------------- 输出修改后的文件内容 --------------------------
    for (const auto& line : origLines) {
        cout << line << endl;
    }
    
    return 0;
} 