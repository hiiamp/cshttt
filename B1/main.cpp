#include <bits/stdc++.h>
using namespace std;
int user, item;
int k;
float D[100][100];
float aveI;
//for user-base
float SimUser[100][100];
float ResBaseUser[100][100];
vector < pair<int, float> > arrayKofUser[100];
//for item-base
float SimItem[100][100];
float ResBaseItem[100][100];
vector < pair<int, float> > arrayKofItem[100];
/*--------------*/
bool sortBySecondDesc(const pair<int, float> &a, const pair<int, float> &b)
{
    return a.second > b.second;
}
void printArray2(float (*M)[100], int a, int b)
{
    for(int i = 0; i < a; i++)
    {
        for(int j = 0; j < b; j++)
        {
            cout << setprecision(3) << fixed << M[i][j] << " ";
        }
        cout << endl;
    }
    cout << "______________________" << endl;
}
// block funtion for user-base
float calSimU(int a, int b)
{
    float mulR = 0;
    float FA = 0, FB = 0;
    for(int i = 0; i < item; i++)
    {
        if (D[a][i]*D[b][i] != 0) {
            mulR += D[a][i]*D[b][i];
            FA += D[a][i]*D[a][i];
            FB += D[b][i]*D[b][i];
        }
    }
    return mulR/(sqrt(FA)*sqrt(FB));
}
void calValueForSimUser()
{
    int a, b;
    for(a = 0; a < user; a++)
    {
        for(b = 0; b < user; b++)
        {
            if(a == b) {
                SimUser[a][b] = 1;
            } else {
                SimUser[a][b] = calSimU(a, b);
                arrayKofUser[a].push_back(make_pair(b, SimUser[a][b]));
            }
        }
        sort( arrayKofUser[a].begin(),  arrayKofUser[a].end(), sortBySecondDesc);
        //cout << a << ":" << endl << arrayKofUser[a][0].second << endl << arrayKofUser[a][1].second << endl;
    }
}
float calResBU(int a, int b)
{
    float t = 0;
    float m = 0;
    for(int i = 0; i < k; i++)
    {
        t += SimUser[a][arrayKofUser[a][i].first] * D[arrayKofUser[a][i].first][b];
        m += abs(SimUser[a][arrayKofUser[a][i].first]);
    }
    return t/m;
}
void fillResBaseUser(float (*M)[100])
{
    calValueForSimUser();
    cout << "Sim between user:" << endl;
    printArray2(SimUser, user, user);
    for(int i = 0; i < user; i++)
    {
        for(int j = 0; j < item; j++)
        {
            if(int(M[i][j]) != 0) {
                ResBaseUser[i][j] = M[i][j];
            } else {
                ResBaseUser[i][j] = calResBU(i, j);
            }
        }
    }
    cout << "Output: " << endl;
    printArray2(ResBaseUser, user, item);
}
/*------end-block-----*/
// block function for item-base
float calSimI(int a, int b)
{
    float mulR = 0;
    float FA = 0, FB = 0;
    for(int u = 0; u < user; u++)
    {
        if (D[u][a]*D[u][b] != 0) {
            mulR += (D[u][a]-aveI)*(D[u][b]-aveI);
            FA += (D[u][a]-aveI)*(D[u][a]-aveI);
            FB += (D[u][b]-aveI)*(D[u][b]-aveI);
        }
    }
    return mulR/(sqrt(FA)*sqrt(FB));
}
void calValueForSimItem()
{
    int a, b;
    for(a = 0; a < item; a++)
    {
        for(b = 0; b < item; b++)
        {
            if(a == b) {
                SimItem[a][b] = 1;
            } else {
                SimItem[a][b] = calSimI(a, b);
                arrayKofItem[a].push_back(make_pair(b, SimItem[a][b]));
            }
        }
        sort( arrayKofItem[a].begin(),  arrayKofItem[a].end(), sortBySecondDesc);
    }
}
float calResBI(int a, int b)
{
    float t = 0;
    float m = 0;
    for(int i = 0; i < k; i++)
    {
        t += SimItem[b][arrayKofItem[b][i].first] * (D[a][arrayKofItem[a][i].first]-aveI);
        m += abs(SimItem[b][arrayKofItem[b][i].first]);
    }
    return aveI + (t/m);
}
void fillResBaseItem(float (*M)[100])
{
    calValueForSimItem();
    cout << "Sim between item:" << endl;
    printArray2(SimItem, item, item);
    for(int i = 0; i < user; i++)
    {
        for(int j = 0; j < item; j++)
        {
            if(int(M[i][j]) != 0) {
                ResBaseItem[i][j] = M[i][j];
            } else {
                ResBaseItem[i][j] = calResBI(i, j);
            }
        }
    }
    cout << "Output: " << endl;
    printArray2(ResBaseItem, user, item);
}
/*------end-block-----*/
int main()
{
    ios::sync_with_stdio(false); cin.tie(NULL);
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
    int k_temp;
    cin >> user >> item;
    cin >> k >> k_temp;
    aveI = 0;
    int c = 1;
    for(int i = 0; i < user; i++)
        for(int j = 0; j < item; j++)
        {
            cin >> D[i][j];
            if(D[i][j] != 0) {
                aveI += D[i][j];
                c++;
            }
        }
    cout << "Input: " << endl;
    printArray2(D, user, item);
    aveI = aveI/c++;
    k = min(user, k);
    fillResBaseUser(D);
    k = min(item, k_temp);
    fillResBaseItem(D);
    return 1;
}
