#include <iostream>
#include <vector>
#include<algorithm>
using namespace std;

typedef vector<vector<char>> mat;
typedef vector<vector<int>> path;
//path P(4, vector<int>(4, 0));

vector<string> words;

int score;
string longest;
int cnt;

bool flag;

int grade(string word) {
    if (word.length() < 3)
        return 0;
    if (word.length() < 5)
        return 1;
    if (word.length() == 5)
        return 2;
    if (word.length() == 6)
        return 3;
    if (word.length() == 7)
        return 5;
    else
        return 11;
}

//void Boggle(int y, int x, mat M, string word, int idx, path& P) { // P로 path만든 후 방문했던 노드는 재방문 안하게
void Boggle(int y, int x, mat M, string word, int idx) {

    if (!flag)
        return;
    if ((y < 0 || y>3) || (x < 0 || x>3))
        return;
    //if (P[y][x] == 1)
    //    return;
    if (word.length()-1 == idx) {
        score += grade(word);
        if (word.length() >= longest.length())
            longest = word;
        cnt++;
        flag = false;
        return;
    }

    if (M[y][x] == word[idx]) {
        idx++;
        /*P[y][x] = 1;
        Boggle(y - 1, x - 1, M, word, idx, P);
        Boggle(y - 1, x, M, word, idx, P);
        Boggle(y - 1, x + 1, M, word, idx, P);

        Boggle(y, x - 1, M, word, idx, P);
        Boggle(y, x + 1, M, word, idx, P);

        Boggle(y + 1, x - 1, M, word, idx, P);
        Boggle(y + 1, x, M, word, idx, P);
        Boggle(y + 1, x + 1, M, word, idx, P);*/


        Boggle(y - 1, x - 1, M, word, idx);
        Boggle(y - 1, x, M, word, idx);
        Boggle(y - 1, x + 1, M, word, idx);

        Boggle(y, x - 1, M, word, idx);
        Boggle(y, x + 1, M, word, idx);

        Boggle(y + 1, x - 1, M, word, idx);
        Boggle(y + 1, x, M, word, idx);
        Boggle(y + 1, x + 1, M, word, idx);
    }
}

int main() {
    int n;
    int widx = 0;

    cin >> n;
    words.resize(n);
    for (int i = 0; i < n; i++) {
        cin >> words[i];
    }
    sort(words.begin(), words.end(), greater<>());

    int m;
    cin >> m;
    vector<mat> M(m, mat(4, vector<char>(4)));
    for (int q = 0; q < m; q++) {
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                cin >> M[q][i][j];
            }
        }
    }

    for (int k = 0; k < m; k++) {
        score = 0;
        cnt = 0;
        longest.clear();
        for (int q = 0; q < n; q++) {
            flag = true;
            //P.resize(4, vector<int>(4));
            for (int i = 0; i < 4; i++) {
                for (int j = 0; j < 4; j++) {
                    //Boggle(i, j, M[k], words[q], 0, P);
                    Boggle(i, j, M[k], words[q], 0);
                }
            }
        }
        cout << score << " " << longest << " " << cnt << endl;
    }

    return 0;
}