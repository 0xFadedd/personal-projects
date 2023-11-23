#include <vector>
#include <string>

using namespace std;

class Solution {
public:
    string longestCommonPrefix(vector<string>& strs) {
        if(strs.size() == 0) {
            return "";
        }
        string prefix = strs[0];
        for(int i = 1; i < strs.size(); i++) {
            // while occurence of substring is not present ie flower in flow until you search for flow in flow
                // prefix = slice of prefix from char 0 to prefix length -1 

            while (strs[i].find(prefix) != 0) {
                prefix = prefix.substr(0, prefix.length() - 1);
                if (prefix == "") {
                    return "";
                }
            }
        }
        return prefix;
    }
};