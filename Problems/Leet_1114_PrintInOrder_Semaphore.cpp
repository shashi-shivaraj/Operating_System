/*Suppose we have a class:
public class Foo {
  public void first() { print("first"); }
  public void second() { print("second"); }
  public void third() { print("third"); }
}
The same instance of Foo will be passed to three different threads.
Thread A will call first(), thread B will call second(), and thread C will call third().
Design a mechanism and modify the program to ensure that second() is executed after first(),
and third() is executed after second().

Example 1:
Input: [1,2,3]
Output: "firstsecondthird"
Explanation: There are three threads being fired asynchronously. The input [1,2,3] means thread A calls first(), thread B calls second(), and thread C calls third(). "firstsecondthird" is the correct output.

Example 2:
Input: [1,3,2]
Output: "firstsecondthird"
Explanation: The input [1,3,2] means thread A calls first(), thread B calls third(), and thread C calls second(). "firstsecondthird" is the correct output.
*/

#include <semaphore.h>
#include <fcntl.h>

class Foo 
{
    
public:
    Foo() 
    {    
    const char* SEM1_NAME = "firstComplete";
    const char* SEM2_NAME = "secondComplete";
    
    sem_unlink(SEM1_NAME);
	sem_unlink(SEM2_NAME);
        
    firstComplete = sem_open(SEM1_NAME, O_CREAT, 0660, 0); // init to 0 so it blocks
	secondComplete = sem_open(SEM2_NAME, O_CREAT, 0660, 0); // init to 0 so it doesnot block    
    }
    
    ~Foo()
    {
        sem_close(firstComplete);
	    sem_close(secondComplete);
    }

    void first(function<void()> printFirst) 
    {    
        // printFirst() outputs "first". Do not change or remove this line.
        printFirst();
        sem_post(firstComplete); //notify first complete
    }

    void second(function<void()> printSecond)
    {   
        sem_wait(firstComplete); //wait for first complete
        // printSecond() outputs "second". Do not change or remove this line.
        printSecond();
        sem_post(secondComplete); //notify second complete
    }

    void third(function<void()> printThird)
    {
         sem_wait(secondComplete); //wait for second complete
        // printThird() outputs "third". Do not change or remove this line.
        printThird();
    }
    
private :
    sem_t* firstComplete;
    sem_t* secondComplete;
};