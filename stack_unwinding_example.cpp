#include <iostream>
 
void last() // called by third()
{
    std::cout << "Start last\n";
    std::cout << "last throwing int exception\n";
    throw -1;
    std::cout << "End last\n";
 
}
 
void third() // called by second()
{
    std::cout << "Start third\n";
    last();
    std::cout << "End third\n";
}
 
void second() // called by first()
{
    std::cout << "Start second\n";
    try
    {
        third();
    }
    catch(double)
    {
         std::cerr << "second caught double exception\n";
    }
    std::cout << "End second\n";
}
 
void first() // called by main()
{
    std::cout << "Start first\n";
    try
    {
        second();
    }
    catch (int)
    {
         std::cerr << "first caught int exception\n";
    }
    catch (double)
    {
         std::cerr << "first caught double exception\n";
    }
    std::cout << "End first\n";
}
 
int main()
{
    std::cout << "Start main\n";
    try
    {
        first();
    }
    catch (int)
    {
         std::cerr << "main caught int exception\n";
    }
    std::cout << "End main\n";
 
    return 0;
}

／*
The answer follows:

Start main
Start first
Start second
Start third
Start last
last throwing int exception
first caught int exception
End first
End main
*／
／*
Let’s examine what happens in this case. The printing of all the start statements is straightforward and doesn’t warrant further explanation. Function last() prints “last throwing int exception” and then throws an int exception. This is where things start to get interesting.

Because last() doesn’t handle the exception itself, the stack begins to unwind. Function last() terminates immediately and control returns to the caller, which is third().

Function third() doesn’t handle any exceptions, so it terminates immediately and control returns to second().

Function second() has a try block, and the call to third() is within it, so the program attempts to match the exception with an appropriate catch block. However, there are no handlers for exceptions of type int here, so second() terminates immediately and control returns to first().

Function first() also has a try block, and the call to second() is within it, so the program looks to see if there is a catch handler for int exceptions. There is! Consequently, first() handles the exception, and prints “first caught int exception”.

Because the exception has now been handled, control continues normally at the end of the catch block within first(). This means first() prints “End first” and then terminates normally.

Control returns to main(). Although main() has an exception handler for int, our exception has already been handled by first(), so the catch block within main() does not get executed. main() simply prints “End main” and then terminates normally.
*／
