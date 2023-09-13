#include <bits/stdc++.h>
#define MAX_SIZE 50011
using namespace std;

/*


https://codeforces.com/contest/716/problem/B

yes case:
ABC??FGHIJK???OPQR?TUVWXY?
??????????????????????????

no case:
WELCOMETOCODEFORCESROUNDTHREEHUNDREDANDSEVENTYTWO
AABCDEFGHIJKLMNOPQRSTUVW??M

*/


char s[MAX_SIZE];
// tol is the total number of letters in the window
// dist is the total number of unique letters in the window
// AAABB dist = 2
int tol = 0, dist = 0;
// cnt[i] is the total number of occurences of 'A' + i in the window
int cnt[27];

// add a letter to our window
void add(char ch) {
    if (ch == '?') return;
    cnt[ch - 'A']++;
    tol++;
    // A 0->1 there's a new letter 'A'
    if (cnt[ch - 'A'] == 1) {
        dist++;
    }
}

// delete a letter from our window
void del(char ch) {
    if (ch == '?') return;
    cnt[ch - 'A']--;
    tol--;
    // A has a count 1, when the count is 0 1->0, A is no longer in the window
    // the number of unique letters no longer contains 'A'
    if (cnt[ch - 'A'] == 0) {
        dist--;
    }
}

// judge whether the window contains only distinct letters
bool query() {
    return dist == tol;
}

int main() {
    scanf("%s", s);
    int i, j, N = strlen(s), ok = false;
    for (i = 0; i < N; ++i) {
        add(s[i]);
        // window range [i-25, i]
        if (i >= 25 && query()) {
            ok = true;
            vector<char> rem;
            // complete the string
            for (j = 0; j < 26; ++j) {
                if (cnt[j] == 0) {
                    rem.push_back('A' + j);
                    //printf("%c\n", 'A' + j);
                }
            }

            for (j = i - 25; j <= i; ++j) {
                if (s[j] == '?') {
                    
                    s[j] = rem.back();
                    rem.pop_back();
                    // printf("%s\n", s);
                }
            }
            break;
        }

        if (i >= 25) {
            del(s[i-25]);
        }
    }

    if (ok) {
        for (i = 0; i < N; ++i) {
            if (s[i] == '?') {
                s[i] = 'A';
            }
        }
        printf("%s\n", s);
    } else {
        printf("-1\n");
    }
    return 0;
}