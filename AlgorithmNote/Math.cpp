//******* countPrime ********* O(nlog(logn))
int countPrime(int n) {
	if(n < 2) return false;
	vector<int> table(n, true);
	table[0] = false;	//1 is not prime
	for(int i  = 3; i < n; i+=2) 	//pass all even
		table[i] == false;
	for(inti  = 3; i <= sqrt(n); i++) {		//begin from prime 3
		if(table[i - 1]) {
			for(int j = i*i; j < n; j += 2*i) 
				table[j - 1] = false;
		}
	}

	int count = 0;
	for(inti  = 0; i < n; i++)
		if(table[i]) count++;
}

//******* gcd lcm ******** O(logn)
int gcd(int a, int b) 	
	return b == 0 ? a : gcd(b, a % b);
int lcm(int a, int b) 
	return  a* b/ gcd(a, b)

/******** sqrt ***********
x = sqrt(n), 即求 f(x) = x^2 - n 与 x轴的交点横坐标。
函数上一点（x, f(x)) 的切线tangent斜率slope为2x，该点切线与x轴的交点横坐标x - f(x)/2x，比(x，f(x))更接近所求值，极限下 x = x - f(x)/2x ==> （带入f(x) = x^2 - n  ）
x - x^2 /2x + n/2x = (2x -x + n/x)/2 = (x + n/x)/2 
==> 在x*x>n下，不断循环x = (x + n/x) / 2则可以求出x 即 sqrt(n)。（或者精度<1e-6循环中止）
*************************/
int mySqrt(int n) {
  long x = n;
  while(x*x > n) 
      x = (x + n/x) / 2;
  return x;
}

//******* power, powermod ******** O(logn)
double myPow(double x, int n) {
    if(n == 0) return 1;
    double half = myPow(x, n/2);
    if(n % 2 == 0)
        return half * half;
    if(n > 0)
        return half * half * x;
    else
        return half * half / x;
}
int power(double x, int n) {
	double ans = 1;
	while( n > 0) {
		if( n % 2 != 0) 
			ans = ans * x;
		x = x * x;	
		n = n / 2;
	}
	return ans;
}
int powermod(double x, int n, double m) {
	double ans = 1;
	while( n > 0) {
		if( n % 2 != 0) 
			ans = ans * x mod m;
		x = x * x mod m ;	
		n = n / 2;
	}
	return ans;
}

//******* Fermat ********* O(nlogn)
bool Fermat(int p, int k) {
	for(int i  = 0; i < k; i++) {
		int  a = rand() % (p-1) + 2;
		if( powermod(2, p-1, p) != 1)
			return false;
	}
	return true; (probably )
}

//****** Miller-Rabin ****** O(nlogn)
bool Miller-Rabin(int n, int k) {
	int s = 0;
	while( ( (n-1) & (1<<s) ) != 1)  {s++;}
	double d = (n-1)/power(2,s);
	for(inti  = 0; i < k; i++) {
		int a = rand() % (n -1) + 2;	
		double x = powermod( 2, d, n);
		if( x ==1 || x == n-1) 
			continue;
		for(int j = 1; j < s -1; j++) {
			x = powermod( x, 2, n);
			if( x == 1) return false;
			if( x == n -1) continue;
			return false;
		}
	}
	return true; (probably)
}
