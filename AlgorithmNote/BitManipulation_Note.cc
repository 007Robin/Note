Bit_manipulation
1）位运算
任何数&1都是其本身，
任何数 |1都变为1,
任何数^1变为相反数. 
---------------
任何数 &0 will return 0
&0 -> 0
&1 -> origin
---------------
a &= -a 可用来取出最右端为‘1’的位

x / 2  --> chops off rightmost bit
x % 2  --> returns the rightmost bit

(64=2^6 = 0100 0000)
i / 64 <==> i >> 5 (fast)
i % 64 <==> i & 0x3F (low 6 bits)

int a = 3 & 5; // bitwise AND      0000000011 & 00000000101
	/*
	   00000000011
	   00000000101
	  &=============
	   00000000001 = 1
	*/
int b = 3 | 5; // bitwise OR
	/*
	   00000000011
	   00000000101
	  |=============
	   00000000111 = 7
	 */
int c = 3 ^ 5; // bitwise XOR
	/*
	   00000000011
	   00000000101
	  ^=============
	   00000000110 = 6
	 */  
int d = ~3;    // NOT
	/*
	00000000000000000000000000000011
	11111111111111111111111111111100
	*/
int e = 1 << 5; // left shift equivalent to mult by 2 to the k
	/* 
	   00000000000000000000001
	   00000000000000000100000 // 32
	 */
int f = 1024 >> 3; // right shift  equivalent to / 2 to the k
	/*
	   0000000000010000000000 = 1024 = 2 to the 10
	   0000000000000010000000 = 128 = 2 to the 7
	*/   
int g = 5;
g <<= 2;
	// there are 12 op= types    += -= *= /= %= &= |= ^= <<= >>=
	// x = x OP y   ==>  x OP= y

bit 0 is the rightmost bit
000000000000000000000000000000000000000000000000000000000
000000000000000000000000000000000000000000000000000000001

if you want the bit k, use  1 << k
eg: 1 << 3
000000000000000000000000000000000000000000000000000001000
   
if you want to set X to 1, use OR (1 << k)
   1010101010111110000111110101010101X1010101010101001010101
   000000000000000000000000000000000010000000000000000000000
OR 101010101011111000011111010101010111010101010101001010101
//set k location to 1
   x  = x | (1 << k)     x |= 1 << k
      
HOW TO DO THIS with an array?
设我们有个BitArray，含uint64_t* bits; uint32_t size;
BitVec(uint32_t size) : bits(new uint64_t[(size+63)/64]){	}
eg : I want size = 65 bits, your bits is (65+63)/64 = 2 pointer. 
     I want 3 bits, yours is (3+63)/64 = 1 
65/64=1, 65%64=1, 所以取1个uint64_t bits, 再在第二个uint64_t bits里就多设1位，即可表示取到65位

size = 100000; // how to split this into which word, which bit within?
   i = bit / 64
   k = bit % 64
   x[ i ] |= 1 << k
   10000000000 = 1024  / 64 = 16   <==>  >> 6 
   10000 = 16      
   i = 16, 
   k = bit % 64 <==> & 0x3F <==> & 63
   64 = 1000000		63 = 0111111
   10000000000
AND00000111111
k= 00000000000

   10000000011 = 1027   
AND00000111111
k= 00000000011 = 3
   i = 16, k = 3
   
   x[index >> 6] |= 1 << (index & 63)     SET a bit
   &   ~(1 << k)  CLEAR a bit
   ^    (1 << k)  TOGGLE a bit
   Test a bit    return (bits[i] & (1 << k)) != 0   true or false


	
int x = 192;
const int m = 16*1024*1024/3;
x /= 3; // compiler might do: x * m >> 24

2）逻辑运算
&&
||
！

3）std function
accumulate(nums.begin(), nums.end(), 0, bit_xor<int>());
accumulate (InputIterator first, InputIterator last, init, a function pointer/a function object);
