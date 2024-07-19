/**
 * @file homework.cpp
 * @author your name (you@domain.com)
 * @brief  LeetCode.127
 * @version 0.1
 * @date 2024-07-19
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include <cpp58.hpp>

/**
 * @brief BFS算法
 * 
 */

class Solution
{
public:
    int ladderLength(string beginWord, string endWord, vector<string>& wordList)
    {   
        // 使用无序集合是为了加快查找string的速度
        unordered_set<string> wordSet(wordList.begin(), wordList.end());

        // 由题意beginWord可以不在wordList中 但是endWord必须在
        if(wordSet.find(endWord) == wordSet.end()) return 0;

        // 无序表的key代表当前已经访问过的结点 int代表从beginWord出发到该店的距离
        unordered_map<string, int> wordMap;

        wordMap.insert({beginWord, 1});

        queue<string> q;

        q.push(beginWord);

        // BFS遍历图
        while(!q.empty())
        {
            string curWord = q.front();

            q.pop();

            int distance = wordMap[curWord];

            for(size_t i = 0; i < curWord.size(); i++)
            {
                string replaceWord = curWord;

                // 因为只差一个字母 所以遍历26个字母进行替换
                for(int j = 0; j < 26; j++)
                {
                    replaceWord[i] = j + 'a';
                    
                    if(replaceWord == endWord)return distance + 1;

                    bool in_wordSet = wordSet.find(replaceWord) != wordSet.end();
                    bool not_visit = wordMap.find(replaceWord) == wordMap.end();
                    
                    // 如果是替换后的单词是wordList中的单词且没有被访问过
                    // 进行BFS入队
                    if(in_wordSet && not_visit)
                    {
                        wordMap.insert({replaceWord, distance + 1});
                        q.push(replaceWord);
                    }
                }
            }
        }

        return 0;
    }
};

int main(void)
{
    Solution s;

    vector<string> wordList = {"hot", "dot", "dog", "lot", "cog"};
    
    int distance = s.ladderLength("hit", "cog", wordList);

    cout << distance << endl;

    return 0;
}