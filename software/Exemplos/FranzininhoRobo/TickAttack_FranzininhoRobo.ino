/*
* TickAttack for Arduino
* Author: Pedro Bertoleti
* Date: Jul/2017
*/

/*
*  IMPORTANT: 
*  1) This code was writen to be compiled for ATTINY85, using Timer1 interrupt as Tick generator. 
*     For porting it to another platforms, the major effort is replacing interrupt timer routines for 
*     those allowed in desired platform.
*  2) NEVER use delays into Tasks! A task manager tries to execute all the tasks
*     in real-time and in the "time to execute" it´s needed. A delay will certanly 
*     spoil it all. 
*     NEVER use blocking functions inside tasks.
*     AVOID USING very time expensive loops inside tasks.  
*/

/*
* Using this Task Manager
* 
* Write inside Task1, Task2, Task3 and Task4 functions what must be done
* in these tasks (first of all, read IMPORTANT item #2. Do not ignore what
* is written there).
*
* If you need more tasks, simply write more functions according to Tasks´ 
* function modules (in other words, copy, paste, change the name, declare
* prototypes and that´s it!). Please, do not forget to refresh NUMBER_OF_TASKS define
* and create a define for your tasks´ index too.
*/
#include <SoftwareSerial.h>
#include "avr/wdt.h"

/*
*  Defines
*/
#define INDEX_TASK_1                 0
#define INDEX_TASK_2                 1
#define INDEX_TASK_3                 2
#define INDEX_TASK_4                 3
#define NUMBER_OF_TASKS                4
#define TIME_TO_EXECUTE_TASK1          100   //time unit: ms
#define TIME_TO_EXECUTE_TASK2          500  //time unit: ms
#define TIME_TO_EXECUTE_TASK3          1000  //time unit: ms
#define TIME_TO_EXECUTE_TASK4          1000  //time unit: ms
#define TASK_TIMEOUT                   1000  //time unit: ms

#define YES                        1
#define NO                         0

/*
*  Global variables
*/
void (*ScheduledTasks[NUMBER_OF_TASKS])(void);  //It stores the function pointers of Task.
int TimeScheduledTasks[NUMBER_OF_TASKS];        //It stores the task´s times (time period to execute)
int RecentTasksTimeToExecute[NUMBER_OF_TASKS];  //It stores the recent task´s times ("time to execute" each task)
char TimerIntGeneraed;                          //It indicates if  timer interrupt has been generated
char TaskIsExecuting;                           //It indicates if a task in executing (important information for consider task timeout validation)
int TaskTimeout;                                //used for timeout counting
SoftwareSerial mySerial(2, 6);                  //pin 2(RX) and pin 6 (TX) - software serial
char IsThereCommandToBeCleared;                 //It indicates if there's a command to be cleared (so the robot won't repeat "forever" the lst command sent)

/*
*  Constants
*/
const byte PIN_A = 0;
const byte PIN_B = 1;
const byte PIN_C = 3;
const byte PIN_D = 4;


/*
*  Prototypes
*/
void InitTasks(void);
void ExecuteTask(void);
void Task1(void);       //task number one - write into this function what this taks will make
void Task2(void);       //task number two - write into this function what this task will make
void Task3(void);       //task number three - write into this function what this task will make
void Task4(void);       //task number four - write into this function what this task will make

/*
* Application function prototypes
*/
void SetupApplication(void);
void GoForward(void);
void GoBackwards(void);
void GoLeft(void);
void GoRight(void);
void StopRobot(void);

/*
*   Functions
*/

/*
*   Applications Functions
*/

void SetupApplication(void)
{
  pinMode(PIN_A, OUTPUT);
  pinMode(PIN_B, OUTPUT);
  pinMode(PIN_C, OUTPUT);
  pinMode(PIN_D, OUTPUT);
  mySerial.begin(9600);
}

void GoForward(void)
{
  digitalWrite(PIN_A, HIGH);
  digitalWrite(PIN_B, LOW);
  digitalWrite(PIN_C, HIGH);
  digitalWrite(PIN_D, LOW);
}

void GoBackwards(void)
{
  digitalWrite(PIN_A, LOW);
  digitalWrite(PIN_B, HIGH);
  digitalWrite(PIN_C, LOW);
  digitalWrite(PIN_D, HIGH);
}

void StopRobot(void)
{
  digitalWrite(PIN_A, LOW);
  digitalWrite(PIN_B, LOW);
  digitalWrite(PIN_C, LOW);
  digitalWrite(PIN_D, LOW);
}

void GoRight(void)
{
  digitalWrite(PIN_A, LOW);
  digitalWrite(PIN_B, HIGH);
  digitalWrite(PIN_C, HIGH);
  digitalWrite(PIN_D, LOW);
}

void GoLeft(void)
{
  digitalWrite(PIN_A, HIGH);
  digitalWrite(PIN_B, LOW);
  digitalWrite(PIN_C, LOW);
  digitalWrite(PIN_D, HIGH);
}

/*
*   TickAttack Functions
*/

//Function: initialize and schedule tasks
//Params: nothing
//Return: nothing
void InitTasks(void)
{
    //init function pointers of tasks
    ScheduledTasks[INDEX_TASK_1] = Task1;
    ScheduledTasks[INDEX_TASK_2] = Task2;
    ScheduledTasks[INDEX_TASK_3] = Task3;
    ScheduledTasks[INDEX_TASK_4] = Task4;
	
    //init temporization values of each task. These values do no change during execution
    TimeScheduledTasks[INDEX_TASK_1] = TIME_TO_EXECUTE_TASK1;
    TimeScheduledTasks[INDEX_TASK_2] = TIME_TO_EXECUTE_TASK2;
    TimeScheduledTasks[INDEX_TASK_3] = TIME_TO_EXECUTE_TASK3;
    TimeScheduledTasks[INDEX_TASK_4] = TIME_TO_EXECUTE_TASK4;
	
    //init recent temporization values of each task. These values will change during execution (they´re used to decide which task must be executed)
    RecentTasksTimeToExecute[INDEX_TASK_1] = TIME_TO_EXECUTE_TASK1;
    RecentTasksTimeToExecute[INDEX_TASK_2] = TIME_TO_EXECUTE_TASK2;
    RecentTasksTimeToExecute[INDEX_TASK_3] = TIME_TO_EXECUTE_TASK3;	
    RecentTasksTimeToExecute[INDEX_TASK_4] = TIME_TO_EXECUTE_TASK4;	
    
    //It indicates that there´s no task executing
    TaskIsExecuting = NO;
}

//Function: Task 1 function (reads serial incoming data and control robot)
//Params: nothing
//Return: nothing
void Task1(void)
{
  if (mySerial.available())
  {
    //reads serial data
    int cmd = mySerial.read();
    IsThereCommandToBeCleared = YES;
    
    //controlling robot
    switch(cmd)
    {
      case 'a':
	    GoForward();
            break;
      case 'b':
	    GoLeft();
            break;
      case 'd':
	    GoRight();
            break;
      case 'e':
	    GoBackwards();
            break;
      case 'c':
	    StopRobot();
            break;
      default:
            IsThereCommandToBeCleared = NO;
            break;
    }
  }
}

//Function: Task 2 function (clear a command sent previously to robot)
//Params: nothing
//Return: nothing
void Task2(void)
{
    if (IsThereCommandToBeCleared == YES)
       StopRobot(); 
}

//Function: Task 3 function
//Params: nothing
//Return: nothing
void Task3(void)
{
    
}

//Function: Task 4 function
//Params: nothing
//Return: nothing
void Task4(void)
{
    
}

void setup()
{   
  //Init/configures all tasks
  InitTasks(); 

  //Init/configures application variables and functions
  IsThereCommandToBeCleared = NO;
  SetupApplication();


  //setup TIMER 1 = Toverflow = (Timer Max Value(255) x prescaler(32))/fosc(8 MHz) = 1,02 ms
  TCCR1 = (1<<CS12)|(1<<CS11);    //Prescale = 32
  TIMSK = 1<<TOIE1;               //Timer 1 Overflow Interrupt Enable
  sei();                          //Globla interrupt Enable
  
  TimerIntGeneraed = NO;
}

//Function: timer 1 isr
//Params: nothing 
//Return: nothing
ISR(TIMER1_OVF_vect)  
{
    char i;
    
    TimerIntGeneraed = YES;

    //Here, the "time to execute" of each task is refreshed

    for (i=0; i<NUMBER_OF_TASKS; i++)
    {
	if (RecentTasksTimeToExecute[i] > 0)
  	  RecentTasksTimeToExecute[i]--;			
    }
			
    if (TaskIsExecuting == YES)
    {
        TaskTimeout--;
            
         if (!TaskTimeout)
         {
             //Timeout has reached (possibly a task has crashed. Microcontroller must be reset)
             wdt_enable(WDTO_15MS); 
             while(1);   
         }
    }
}


//Function: Execute tasks
//Params: nothing
//Return: nothing
void ExecuteTask(void)
{
    char i;
    
    for (i=0; i<NUMBER_OF_TASKS; i++)
    {
	//Check if it´s time to execute a task
	if ((ScheduledTasks[i] != 0) && (RecentTasksTimeToExecute[i] == 0))
        {
  	    TaskIsExecuting = YES;
            TaskTimeout = TASK_TIMEOUT;
            ScheduledTasks[i]();  //executes the task
            TaskIsExecuting = NO;
	    RecentTasksTimeToExecute[i] = TimeScheduledTasks[i];  //reagendamento da tarefa		
        }
    }
}

void loop()
{
    if ((TimerIntGeneraed == YES)  && (NUMBER_OF_TASKS)) 
    {
        TimerIntGeneraed = NO;  
        ExecuteTask();			
    }
}
