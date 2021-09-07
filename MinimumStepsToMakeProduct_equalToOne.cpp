/*Minimum steps to make product equal to one 
Given an array arr[] containing N integers. In one step, any element of the array can either be increased or decreased by one. Find minimum steps required such that the product of the array elements becomes 1.

Example 1:

Input:
N = 3
arr[] = {-2, 4, 0}
Output:
5
Explanation:
We can change -2 to -1, 0 to -1 and 4 to 1.
So, a total of 5 steps are required
to update the elements such that
the product of the final array is 1. 
Example 2:
Input:
N = 3
arr[] = {-1, 1, -1} 
Output :
0
Explanation:
Product of the array is already 1.
So, we don't need to change anything.

Your Task:  
You don't need to read input or print anything. Your task is to complete the function makeProductOne() which takes an integer N and an array arr of size N as input and returns the minimum steps required.


Constraints:
1 ≤ N ≤ 105
-103 ≤ arr[i] ≤ 103

*/
#include <bits/stdc++.h>
using namespace std;

//User function Template for C++

class Solution {
  public:
    int makeProductOne(int arr[], int N) {
        int res = 0, k = 0;
        int lastInput = -1;
        if (N > 0)
        {
            if (N == 1){
                if (arr[0] == -1)   return 2;
                else if (arr[0] == 0)    return 1;
                else{
                    while ((arr[0] <= -2)||(arr[0] >= 2)) {
                        if (arr[0] < -1){ arr[0] += 1;  ++res; }
                        else if (arr[0] > 1){ arr[0] -= 1;   ++res; }
                    }

                    if (-1 == arr[0])
                        return res+2;
                }
            }
            else
            {
                k=1;
                for(int i=0; i<N;++i){
                    k *= arr[i];
                }
    
                if(1==k)
                    return 0;
        
                for(int i=0; i<N;++i){
                    if (0 == arr[i])
                    {
                        arr[i] -= 1;
                        ++res;
                    }
                    while ((arr[i] <= -2)||(arr[i] >= 2)) {
                        if (arr[i] < -1){ arr[i] += 1;  ++res; }
                        else if (arr[i] > 1){ arr[i] -= 1;   ++res; }
                    }
        
                    if (-1 == arr[i]){   ++k; lastInput = i;  }
                }
            }
        }

        if ((0!= k)&&(0!=(k%2)))
            res += 2;

        return res;
    }
};

int main() {
    int t;
    cin >> t;
    while (t--) {
        int N;
        cin>>N;
        
        int arr[N];
        for(int i=0; i<N; i++)
            cin>>arr[i];

        Solution ob;
        cout << ob.makeProductOne(arr,N) << endl;
    }
    return 0;
}
