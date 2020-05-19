#include <bits/stdc++.h>
using namespace std;
int n;
int check;
float data[100][100];
float temp[100][100];
float RI[16] = {0, 0, 0, 0.52, 0.89, 1.11, 1.25, 1.35, 1.4, 1.45, 1.49, 1.52, 1.54, 1.56, 1.58, 1.59};

float sumCot[100];
float tong_cac_hang;
float sumHang[100];
float TrongSo[100];
float VectoTongTrongSo[100];
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
    cout << "-----------------" << endl;
}
void cleanData()
{
    for(int i = 0; i < n; i++)
    {
        sumHang[i] = 0;
        sumCot[i] = 0;
    }
    tong_cac_hang = 0;
}
void resetDataByTrongSo()
{
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n; j++)
        {
            data[i][j] = TrongSo[i]/TrongSo[j];
            sumCot[j] += data[i][j];
        }
    }
}
int PPChuanHoaMaTran()
{
    cout << "PP Chuan Hoa Ma Tran" << endl;
    cout << "Tong cot:" << endl;
    for(int i = 0; i < n; i++)
    {
        cout << setprecision(3) << fixed << sumCot[i] << " ";
    }
    cout << endl << "-----------------" << endl;
    tong_cac_hang = 0;
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n; j++)
        {
            temp[i][j] = data[i][j]/sumCot[j];
            sumHang[i] += temp[i][j];
        }
        tong_cac_hang += sumHang[i];
    }
    cout << "Ma tran chuan hoa:" << endl;
    printArray2(temp, n, n);
    cout << "Tong hang:" << endl;
    for(int i = 0; i < n; i++)
    {
        cout << setprecision(3) << fixed << sumHang[i] << endl;
        TrongSo[i] = sumHang[i]/tong_cac_hang;
    }
    cout << "Trong So:" << endl;
    for(int i = 0; i < n; i++)
    {
        cout << setprecision(3) << fixed << TrongSo[i] << endl;
    }
    cout << "Vector tong trong so:" << endl;
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n; j++)
        {
            VectoTongTrongSo[i] += data[i][j]*TrongSo[j];
        }
        cout << VectoTongTrongSo[i] << endl;
    }
    float lamda = 0;
    float CI = 0;
    float CR = 0;
    cout << "Vector nhat quan:" << endl;
    for(int i = 0; i < n; i++)
    {
        cout << VectoTongTrongSo[i]/TrongSo[i] << endl;
        lamda += VectoTongTrongSo[i]/TrongSo[i];
    }
    lamda /= n;
    cout << endl;
    cout << "Lamda max : " << lamda << endl;
    CI = (lamda - n)/(n - 1);
    CR = (CI/RI[n]);
    cout << "CI : " << CI << endl;
    cout << "CR : " << CR << endl;
    return CR;
}
int main()
{
    ios::sync_with_stdio(false); cin.tie(NULL);
	freopen("input.txt", "r", stdin);
	//freopen("output.txt", "w", stdout);

    cin >> n >> check;
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n; j++)
        {
            cin >> data[i][j];
            sumCot[j] += data[i][j];
        }
    }
    cout << "data: " << endl;
    printArray2(data, n, n);
    int c = 0;
    int CR = 0;
    do {
        c++;
        CR = PPChuanHoaMaTran();
        cleanData();
        resetDataByTrongSo();
    } while (c < 5 && CR > 0.1);
    
    
}