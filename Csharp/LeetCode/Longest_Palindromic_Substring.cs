// 5. Longest Palindromic Substring
// Dynamic programming, O(N^2) time and space complexity

    public class Solution
    {
        public string LongestPalindrome(string s)
        {
            if (string.IsNullOrEmpty(s)) return String.Empty;

            var res = "";
            var reslen = 0;
            var dp = new bool[s.Length, s.Length+1];     


            for (int len = 1; len <= s.Length; len++)
            {
                for (int i = 0; i + len <= s.Length; i++)
                {
                    dp[i, len] = (len - 2 <= 0 || dp[i + 1, len - 2]) && s[i] == s[i + len - 1];
                    if (dp[i, len] && len > reslen)
                    {
                        res = s.Substring(i, len);
                    }
                }
            }
            return res;
        }
    }
