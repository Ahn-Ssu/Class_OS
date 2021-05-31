/*
	hw7_1.c and hw7_1_main.c are the solution of the Dining Philosophers Problem using Moniter.
	This program implements the concept of Monitor using functions, pthread_mutex_t and pthread_cond_t.

	Following the instructions, complete this program

	Compilation:
		gcc hw7_1.c hw7_1_main.c Console.c -pthread -lm

*/

#ifndef	__PHILOSOPHERS__
#define	__PHILOSOPHERS__

#define MIN(x, y) ((x) < (y) ? (x) : (y))
#define PI 3.141592

#ifndef	TRUE
	#define TRUE 1
	#define FALSE 0
#endif	//	TRUE

#define MAX_PHIL 30

enum PhilosopherState { THINKING, EATING, HUNGRY };

typedef struct {
	int no_phil;
	int state[MAX_PHIL];

	pthread_mutex_t mutex;			// mutex to ensure mutual exclusion of Philosopher functions
	pthread_cond_t self[MAX_PHIL];
} Philosophers;

void Philosophers_Init(Philosophers *dp, int no_phil);
void Philosophers_Destroy(Philosophers *dp);
void Philosophers_PickUp(Philosophers *dp, int i);
void Philosophers_PutDown(Philosophers *dp, int i);
void Philosophers_Test(Philosophers *dp, int i);

void Philosophers_Display(Philosophers *dp, int screen_width, int screen_height);
int Philosophers_Check(Philosophers *dp);

#endif	//	__PHILOSOPHERS__
