#include"min_edict_dist.h"

int Cal_dist(const char* pstr1, int len1, const char* pstr2, int len2)
{
	int dp[len1+1][len2+1];
	for(int i = 0; i <= len1; i++)
	{
		dp[i][0] = i;
	}
	for(int j = 0; j <= len2; j++)
	{
		dp[0][j] = j;
	}
	for(int i = 1; i <= len1; i++)
	{
		for(int j = 1; j <= len2; j++)
		{
			if(pstr1[i-1] == pstr2[j-1])
				dp[i][j] = dp[i-1][j-1];
			else
			{
				int t1 = dp[i-1][j];
				t1 = t1 < dp[i][j-1] ? t1 : dp[i][j-1];
				t1 = t1 < dp[i-1][j-1] ? t1 : dp[i-1][j-1];
				dp[i][j] = t1 + 1;
				//cout << "(" << i << ", " << j << ")" << "= " << dp[i][j] << endl;
			}
		}
	}
	return dp[len1][len2];
}
