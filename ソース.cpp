#include <iostream>
#include <random>
#include <vector>
#include <chrono>
#include <algorithm>
using namespace std;
using namespace std::chrono;

int main() {
    random_device red;
    mt19937_64 R(red());
    uniform_real_distribution<> Rand1(1, 1000000000000), Rand2(0, 99999999);
    vector<unsigned long long>A, B,Serch,Ans1,Ans2;
    for (unsigned long long i = 0; i < 100000000; i++) {
        A.push_back(Rand1(R));
    }
    for (unsigned long long i = 0; i < 100; i++) {
        Serch.push_back(A[Rand2(R)]);
    }
    B = A;
    cout << "線形探索スタート"<< endl;
    auto start = system_clock::now();
    for (int i = 0; i < 100; i++) {
        for (unsigned long long j = 0; j < 100000000; j++) {
            if (A[j] == Serch[i]) {
                Ans1.push_back(j);
            }
        }
    }
    auto end = system_clock::now();
    auto msec = duration_cast<milliseconds>(end - start).count();
    cout <<"線形探索にかかった時間:" << msec << "ミリ秒" << endl;
    cout << "ソートスタート" << endl;
    start = system_clock::now();
    sort(B.begin(), B.end());
    end = system_clock::now();;
    auto sms = duration_cast<milliseconds>(end - start).count();
    cout << "二分探索スタート" << endl;
    start = system_clock::now();
    for (int i = 0; i < 100; i++) {
        unsigned long long Left = 0, Right = 99999999;
        while (Left < Right) {
            unsigned long long Middle = Left + (Right - Left) / 2;
            if (B[Middle] > Serch[i])Right = Middle - 1;
            else if (B[Middle] < Serch[i])Left = Middle + 1;
            else {
                Left = Middle;
                break;
            }
        }
        Ans2.push_back(Left);
    }
    end = system_clock::now();
    msec = duration_cast<milliseconds>(end - start).count();
    cout << "二分探索にかかった時間:" << msec << "ミリ秒" << endl;
    cout << "ソートにかかった時間を入れると:" << msec + sms << "ミリ秒" << endl;
    cout << "線形探索で出た答えの箱の中の数" << endl;
    for (int i = 0; i < 100; i++) {
        cout << A[Ans1[i]] << " ";
    }
    cout << endl;
    cout << "二分探索で出た答えの箱の中の数" << endl;
    for (int i = 0; i < 100; i++) {
        cout << B[Ans2[i]] << " ";
    }
    system("pause > NUL");
}