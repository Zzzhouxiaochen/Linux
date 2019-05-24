#include<iostream>
#include<vector>
#include<cmath>
#include<algorithm>

using namespace std;

int main() {
	int n1, n2, n3, n4;
	int A, B, C;
	cin >> n1 >> n2 >> n3 >> n4;
	A = (n1 + n3) / 2;
	B = A - n1;
	C = B - n2;
	if (A >= 0 && B >= 0 && C >= 0 && n4 == (B + C))
		cout << A << " " << B << " " << C;
	else
		cout << "No";
}
