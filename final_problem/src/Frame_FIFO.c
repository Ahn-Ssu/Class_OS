/****

	This program shows the behavior of the plage replacement algorithms.
	Currently, it replaces pages using the FIFO algorithm.
	Following the instructions, modify this program to apply the LRU algorithm instead of FIFO.

	First, read Frame_FIFO.h and Frame_FIFO.c carefully.


	Copy:
		cp Frame_FIFO.h Frame_LRU_<student_id>_<Eng_name>.h
		cp Frame_FIFO.c Frame_LRU_<student_id>_<Eng_name>.c

	Compilation:
		gcc Frame_FIFO.c							// compile this program
		gcc Frame_LRU_<student_id>_<eng_name>.c		// compile your solution

	Run:
		./a.out <no_frames> [ref_string_file]

	FIFO Example)
		$ ./a.out 3
		Accessing page 7: (1, 0)        [  7 (  0)  -1 ( -1)  -1 ( -1) ]
		Accessing page 0: (1, 0)        [  7 (  0)   0 (  1)  -1 ( -1) ]
		Accessing page 1: (1, 0)        [  7 (  0)   0 (  1)   1 (  2) ]
		Accessing page 2: (1, 1)        [  2 (  3)   0 (  1)   1 (  2) ]
		Accessing page 0: (0, 0)        [  2 (  3)   0 (  1)   1 (  2) ]
		Accessing page 3: (1, 1)        [  2 (  3)   3 (  5)   1 (  2) ]
		Accessing page 0: (1, 1)        [  2 (  3)   3 (  5)   0 (  6) ]
		Accessing page 4: (1, 1)        [  4 (  7)   3 (  5)   0 (  6) ]
		Accessing page 2: (1, 1)        [  4 (  7)   2 (  8)   0 (  6) ]
		Accessing page 3: (1, 1)        [  4 (  7)   2 (  8)   3 (  9) ]
		Accessing page 0: (1, 1)        [  0 ( 10)   2 (  8)   3 (  9) ]
		Accessing page 3: (0, 0)        [  0 ( 10)   2 (  8)   3 (  9) ]
		Accessing page 2: (0, 0)        [  0 ( 10)   2 (  8)   3 (  9) ]
		Accessing page 1: (1, 1)        [  0 ( 10)   1 ( 13)   3 (  9) ]
		Accessing page 2: (1, 1)        [  0 ( 10)   1 ( 13)   2 ( 14) ]
		Accessing page 0: (0, 0)        [  0 ( 10)   1 ( 13)   2 ( 14) ]
		Accessing page 1: (0, 0)        [  0 ( 10)   1 ( 13)   2 ( 14) ]
		Accessing page 7: (1, 1)        [  7 ( 17)   1 ( 13)   2 ( 14) ]
		Accessing page 0: (1, 1)        [  7 ( 17)   0 ( 18)   2 ( 14) ]
		Accessing page 1: (1, 1)        [  7 ( 17)   0 ( 18)   1 ( 19) ]
		no_page_fault = 15
		no_page_replacement = 12

	LRU Example)
		$ ./Frame_LRU 3
		Accessing page 7: (1, 0)        [  7 (  0)  -1 ( -1)  -1 ( -1) ]
		Accessing page 0: (1, 0)        [  7 (  0)   0 (  2)  -1 ( -1) ]
		Accessing page 1: (1, 0)        [  7 (  0)   0 (  2)   1 (  4) ]
		Accessing page 2: (1, 1)        [  2 (  6)   0 (  2)   1 (  4) ]
		Accessing page 0: (0, 0)        [  2 (  6)   0 (  8)   1 (  4) ]
		Accessing page 3: (1, 1)        [  2 (  6)   0 (  8)   3 ( 10) ]
		Accessing page 0: (0, 0)        [  2 (  6)   0 ( 12)   3 ( 10) ]
		Accessing page 4: (1, 1)        [  4 ( 14)   0 ( 12)   3 ( 10) ]
		Accessing page 2: (1, 1)        [  4 ( 14)   0 ( 12)   2 ( 16) ]
		Accessing page 3: (1, 1)        [  4 ( 14)   3 ( 18)   2 ( 16) ]
		Accessing page 0: (1, 1)        [  0 ( 20)   3 ( 18)   2 ( 16) ]
		Accessing page 3: (0, 0)        [  0 ( 20)   3 ( 22)   2 ( 16) ]
		Accessing page 2: (0, 0)        [  0 ( 20)   3 ( 22)   2 ( 24) ]
		Accessing page 1: (1, 1)        [  1 ( 26)   3 ( 22)   2 ( 24) ]
		Accessing page 2: (0, 0)        [  1 ( 26)   3 ( 22)   2 ( 28) ]
		Accessing page 0: (1, 1)        [  1 ( 26)   0 ( 30)   2 ( 28) ]
		Accessing page 1: (0, 0)        [  1 ( 32)   0 ( 30)   2 ( 28) ]
		Accessing page 7: (1, 1)        [  1 ( 32)   0 ( 30)   7 ( 34) ]
		Accessing page 0: (0, 0)        [  1 ( 32)   0 ( 36)   7 ( 34) ]
		Accessing page 1: (0, 0)        [  1 ( 38)   0 ( 36)   7 ( 34) ]
		no_page_fault = 12
		no_page_replacement = 9

****/

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

#define TRUE 1
#define FALSE 0


typedef struct {
	int *page;
	int no_frame;
	int cur_time;

	int *load_time;				// only for FIFO. DO NOT use this field for LRU.

	// TO DO: add fields necessary to implement the LRU replacement algorithm
} Frame;

void Frame_Init(Frame *frame, int no_frame);	// constructor
void Frame_Destroy(Frame *frame);				// destructor
int Frame_FindPage(Frame *frame, int page_no);	// returns the index of the page, or -1 if the page does not exist in the frame
int Frame_FindEmpty(Frame *frame);	// returns the index of an empty frame, or -1 if there is no empty frame
void Frame_Set(Frame *frame, int idx, int page_no);	// put page_no into page[idx]
int Frame_Get(Frame *frame, int idx);	// returns page[idx]
void Frame_AccessPage(Frame *frame, int idx, int *page_fault, int *page_replacement);	// updates the frame status when a page is accessed
void Frame_UpdateTime(Frame *frame);	// increases cur_time

void Frame_MarkLoadTime(Frame *frame, int idx);	// copy cur_time to load_time[idx]
int Frame_FIFO(Frame *frame);		// returns the index of the frame to be replaced which was selected by the FIFO replacement algorithm

void Frame_Display(Frame *frame);		// display the contents of frame (see the source code)

int Frame_LRU(Frame *frame);		// returns the index of the frame to be replaced which was selected by the LRU replacement algorithm

// TO DO: declare functions necessary to implement LRU


// Note! The solution should work for any arbitrary reference string.
#define MAX_STRING 512
int ref_string[MAX_STRING] = {
	7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3, 2, 1, 2, 0, 1, 7, 0, 1, -1	// -1 indicates the end of the reference string
};
int ReadReferenceString(const char *filename, int *string);	// reads a reference string from a text file


int main(int argc, char *argv[])
// DO NOT modify this function.
{
	if(argc == 1){
		printf("Usage: %s <no_frames> [ref_string_file]\n", argv[0]);
		return 0;
	}

	int no_frame = 0;
	no_frame = atoi(argv[1]);
	if(no_frame == 0)
		no_frame = 3;

	if(argc >= 3)
		ReadReferenceString(argv[2], ref_string);

	Frame frame;
	Frame_Init(&frame, no_frame);

	int no_page_fault = 0;
	int no_page_replacement = 0;

	for(int i = 0; ref_string[i] >= 0; i++){
		int cur_page = ref_string[i];
		printf("Accessing page %d: ", cur_page);

		int page_fault = 0, page_replacement = 0;
		Frame_AccessPage(&frame, cur_page, &page_fault, &page_replacement);
		no_page_fault += page_fault;
		no_page_replacement += page_replacement;

		printf("(%d, %d) ", page_fault, page_replacement);

		Frame_Display(&frame);
	}

	printf("no_page_fault = %d\n", no_page_fault);
	printf("no_page_replacement = %d\n", no_page_replacement);

	Frame_Destroy(&frame);

	return 0;
}

int ReadReferenceString(const char *filename, int *string)
// DO NOT modify this function.
{
	FILE *fp = fopen(filename, "r");
	if(fp == NULL){
		printf("Failed to open file %s in %s.\n", filename, __FUNCTION__);
		return FALSE;
	}

	for(int i = 0; i < MAX_STRING; i++){
		fscanf(fp, "%d", &string[i]);
		if(string[i] < 0)
			break;
	}

	fclose(fp);

	return TRUE;
}

void Frame_Init(Frame *frame, int no_frame)
// TO DO: modify this function to implement LRU
{
	frame->page = (int *)malloc(no_frame * sizeof(int));
	frame->load_time = (int *)malloc(no_frame * sizeof(int));

	if(frame->page == NULL || frame->load_time == NULL){
		printf("Failed to allocate memory in %s (%s %d)\n", __FUNCTION__, __FILE__, __LINE__);
		return;
	}

	for(int i = 0; i < no_frame; i++){
		frame->page[i] = -1;				// -1 indicates empty
		frame->load_time[i] = -1;			// -1 indicates not loaded yet
	}

	frame->no_frame = no_frame;
	frame->cur_time = 0;
}

void Frame_Destroy(Frame *frame)
// TO DO: modify this function to implement LRU
{
	frame->no_frame = 0;

	free(frame->page);
	free(frame->load_time);
}

int Frame_FindPage(Frame *frame, int page_no)
// DO NOT modify this function
{
	for(int i = 0; i < frame->no_frame; i++){
		if(frame->page[i] == page_no)
			return i;
	}

	return -1;
}

int Frame_FindEmpty(Frame *frame)
// DO NOT modify this function
{
	return Frame_FindPage(frame, -1);
}

void Frame_Set(Frame *frame, int idx, int page_no)
// DO NOT modify this function
{
	frame->page[idx] = page_no;
}

int Frame_Get(Frame *frame, int idx)
// DO NOT modify this function
{
	return frame->page[idx];
}

void Frame_AccessPage(Frame *frame, int page_no, int *page_fault, int *page_replacement)
// This function updates the frame status when a page is accessed (read or written).
// (Read the code to understand the purpose of the page_fault and page_replacement parameters.)
// Currently, this function replaces the page according to the FIFO algorithm.
// TO DO: Modify this function apply LRU.
//		  Comment out all function calls that are not necessary for LRU.
{
	*page_fault = *page_replacement = FALSE;

	int idx = Frame_FindPage(frame, page_no);	// try to find the target page
	if(idx == -1){		// page fault
		*page_fault = TRUE;

		idx = Frame_FindEmpty(frame);	// try to find an empty frame

		if(idx == -1){	// page replacement
			*page_replacement = TRUE;

			idx = Frame_FIFO(frame);
		}

		Frame_Set(frame, idx, page_no);	// load the page into frame[idx]

		Frame_MarkLoadTime(frame, idx); 
	} 

	Frame_UpdateTime(frame);			// increase frame->cur_time
}

void Frame_UpdateTime(Frame *frame)
// DO NOT modfiy this function
{
	frame->cur_time++;
}

void Frame_MarkLoadTime(Frame *frame, int idx)
// DO NOT modify this function.
{
	frame->load_time[idx] = frame->cur_time;
}

int Frame_FIFO(Frame *frame)
// DO NOT modify this function.
{
	int min_idx = 0;
	for(int i = 1; i < frame->no_frame; i++){
		if(frame->load_time[i] < frame->load_time[min_idx])
			min_idx = i;
	}

	return min_idx;
}

void Frame_Display(Frame *frame)
// TO DO: modify this function to display the last access time instead of the load time.
{
	printf("\t[");
	for(int i = 0; i < frame->no_frame; i++)
		printf("%3d (%3d) ", frame->page[i], frame->load_time[i]);

	printf("]\n");

	fflush(stdout);
}

int Frame_LRU(Frame *frame)
// returns the index of the frame to be replaced which was selected by the LRU replacement algorithm
// TO DO: implement this function
{



}


// TO DO: define functions necessary to implement LRU

