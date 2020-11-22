/**
::Throttling Gateway::

Non-critical requests for a transaction system are routed through a throttling gateway to ensure that the network is not choked by non-essential requests.

The gateway has the following limits:

The number of transactions in any given second cannot exceed 3.
The number of transactions in any given 10 second period cannot exceed 20. A ten-second period includes all requests arriving from any time max(1, T-9) to T (inclusive of both) for any valid time T.
The number of transactions in any given minute cannot exceed 60.   Similar to above, 1 minute is from max(1, T-59) to T.
 
Any request that exceeds any of the above limits will be dropped by the gateway. Given the times at which different requests arrive sorted ascending, find how many requests will be dropped.

Note: Even if a request is dropped it is still considered for future calculations. Although, if a request is to be dropped due to multiple violations, it is still counted only once.

Example

n = 27

requestTime = [1, 1, 1, 1, 2, 2, 2, 3, 3, 3, 4, 4, 4, 5, 5, 5, 6, 6, 6, 7, 7, 7, 7, 11, 11, 11, 11 ]

Request 1 - Not Dropped.
Request 1 - Not Dropped.
Request 1 - Not Dropped.
Request 1 - Dropped. At most 3 requests are allowed in one second.
No request will be dropped till 6 as all comes at an allowed rate of 3 requests per second and the 10-second clause is also not violated.
Request 7 - Not Dropped. The total number of requests has reached 20 now.
Request 7 - Dropped. At most 20 requests are allowed in ten seconds.
Request 7 - Dropped. At most 20 requests are allowed in ten seconds.
Request 7 - Dropped. At most 20 requests are allowed in ten seconds. Note that the 1-second limit is also violated here.
Request 11 - Not Dropped. The 10-second window has now become 2 to 11. Hence the total number of requests in this window is 20 now.
Request 11 - Dropped. At most 20 requests are allowed in ten seconds.
Request 11 - Dropped. At most 20 requests are allowed in ten seconds.
Request 11 - Dropped. At most 20 requests are allowed in ten seconds. Also, at most 3 requests are allowed per second.
Hence, a total of 7 requests are dropped.


Function Description

Complete the droppedRequests function in the editor below.

droppedRequests has the following parameter(s):
    int requestTime[n]: an ordered array of integers that represent the times of various requests
Returns
    int:  the total number of dropped requests

Constraints

1 = n = 106
1 = requestTime[i] = 109
 
Input Format For Custom Testing
The first line contains an integer, n, the size of requestTime.

Each line i of the n subsequent lines (where 0 = i < n) contains an integer, requestTime[i].

Sample Case 0
Sample Input For Custom Testing

STDIN     Function 
-----     --------
5    ?    requestTime[] size n = 5
1    ?    requestTime = [ 1, 1, 1, 1, 2 ] 
1
1
1
2

Sample Output
1

Explanation

There are 4 requests that arrive at second 1. This exceeds the per second limit so one packet is dropped. No other limits are exceeded.

Sample Case 1
Sample Input For Custom Testing

STDIN     Function
-----     --------
21   ?   requestTime[] size n = 21
1    ?   requestTime = [1, 1, 1, 1, 2, 2, 2, 3, 3, 3, 4, 4, 4, 5, 5, 5, 6, 6, 6, 7, 7]
1
1
1
2
2
2
3
3
3
4
4
4
5
5
5
6
6
6
7
7

Sample Output
2

Explanation
In the first second, 4 requests arrive so one request is dropped. Within 10 seconds, all request times from second 1 to 7, a total of 21 requests arrive. The last request is dropped. The total number of dropped requests is 2.

**/

#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <algorithm>
#include <functional>
#include <unordered_map>

using namespace std;

#define MAX_PER_SECOND  3
#define MAX_TEN_SECONDS 20
#define MAX_PER_MINUTE 60
string ltrim(const string&);
string rtrim(const string&);



/*
 * Complete the 'droppedRequests' function below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts INTEGER_ARRAY requestTime as parameter.
 */

vector<int>& operator+=(vector<int>& v, int x) {
    for (auto a = begin(v); a != end(v); ++a) {
        *a += x;
    }
    return v;
}

int droppedRequests(vector<int> requestTime) {
    for_each(requestTime.begin(), requestTime.end(), [](int x) {
        std::cout << x <<"\t";
    });
    std::cout << std::endl<< requestTime.size()<<std::endl;

    int ans = 0;

    for (int nIndex = 3; nIndex < requestTime.size(); ++nIndex) {
        if (requestTime[nIndex - 3] == requestTime[nIndex]) {
            ans += 1;
            continue;
        }
        if ((nIndex > 19) && (requestTime[nIndex] - requestTime[nIndex - 20]) < 10) {
            ans += 1;
            continue;
        }
        if ((nIndex > 59) && (requestTime[nIndex] - requestTime[nIndex - 60]) < 60) {
            ans += 1;
            continue;
        }
    }

    return ans;
}

int main()
{
	//ofstream fout(getenv_s("OUTPUT_PATH"));
    string requestTime_count_temp;
    getline(cin, requestTime_count_temp);

    int requestTime_count = stoi(ltrim(rtrim(requestTime_count_temp)));

    vector<int> requestTime(requestTime_count);

    for (int i = 0; i < requestTime_count; i++) {
        string requestTime_item_temp;
        getline(cin, requestTime_item_temp);

        int requestTime_item = stoi(ltrim(rtrim(requestTime_item_temp)));

        requestTime[i] = requestTime_item;
    }

    int result = droppedRequests(requestTime);

    cout << "result: " << result << "\n";
    //fout << result << "\n";

    //fout.close();

    return 0;
}

string ltrim(const string& str) {
    string s(str);

    s.erase(
        s.begin(),
        find_if(s.begin(), s.end(), not1(ptr_fun<int, int>(isspace)))
    );

    return s;
}

string rtrim(const string& str) {
    string s(str);

    s.erase(
        find_if(s.rbegin(), s.rend(), not1(ptr_fun<int, int>(isspace))).base(),
        s.end()
    );

    return s;
}