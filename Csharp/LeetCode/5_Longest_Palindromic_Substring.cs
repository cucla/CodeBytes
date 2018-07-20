// https://miafish.wordpress.com/category/algorithm/string-algorithm/ 

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

// Manacher’s algorithm, O(N) time
// EXPLANATION: http://www.zrzahid.com/longest-palindromic-substring-in-linear-time/
    public class Solution
    {
        public string LongestPalindrome(string s)
        {
            var res = string.Empty;
            var reslen = 0;
            var swithpounds = preprocess(s);
            var maxR = 0;
            var maxC = 0;
            var dp = new int[swithpounds.Length];
            for (int i = 0; i < swithpounds.Length; i++)
            {
                dp[i] = maxR > i ? Math.Min(dp[2 * maxC - i], maxR - i) : 0;

                // attempt to expand it
                while (i + 1 + dp[i] < swithpounds.Length && i - 1 - dp[i] >= 0 && swithpounds[i + 1 + dp[i]] == swithpounds[i - 1 - dp[i]])
                {
                    dp[i]++;
                }

                if (dp[i] + i > maxR)
                {
                    maxR = dp[i] + i;
                    maxC = i;
                }

                if (dp[i] > reslen)
                {
                    reslen = dp[i];
                    res = s.Substring((i - dp[i]) / 2, reslen);
                }
            }
            return res;
        }

        private string preprocess(string s)
        {
            var stringbuilder = new StringBuilder();
            foreach (char ch in s)
            {
                stringbuilder.Append("#");
                stringbuilder.Append(ch);
            }
            stringbuilder.Append("#");
            return stringbuilder.ToString();
        }
    }
