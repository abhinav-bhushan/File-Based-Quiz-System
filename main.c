#define _CRT_SECURE_NO_WARNINGS
#include<time.h>
#include<stdio.h>
#define LEN_BUFF 256
#define TRUE 1
#define FALSE 0

const char* quizfilename[3] = {"quiz_easy.txt","quiz_medium.txt","quiz_hard.txt" };


struct question {
	char question[LEN_BUFF];
	int correct_answer;
	char option[4][LEN_BUFF];
	int user_answer;

};

/* Function Prorotypes*/
FILE* open_qfile(int );
int get_question(struct question*, FILE*);
int ask_question(struct question*);
int get_answer(struct question*);
int check_answer(struct question*);
int get_string(char*, int, FILE*);
int choose_difficulty(void);



int main()
{
	struct question q;
	int q_num=0;
	int user_answer;
	int q_answer;
	time_t start_time,end_time;
	double q_time;
	int score = 0;
	FILE* f;
	int difficulty;
	char name[LEN_BUFF];
	printf("Please enter your name\n");
	get_string(name, LEN_BUFF, stdin);
	difficulty = choose_difficulty();
	if (difficulty < 0 || difficulty>2)
		return 1;
	f = open_qfile(difficulty);
	if (!f)
	{
		printf("Thanks for taking the quiz\n");
		return 1;
	}
	while (get_question(&q, f)&&q_num<10)
	{
		printf("\nQuestion %d\n", ++q_num);
		ask_question(&q);
		start_time = time(NULL);
		user_answer=get_answer(&q);
		end_time=time(NULL);
		q_time = difftime(end_time, start_time);
		q_answer = check_answer(&q);
		if (user_answer < 1 || user_answer>4)
		{
			printf("Abandoning the quiz\n");
			break;
		}
		if (user_answer == q_answer)
		{
			printf("Congratulations.you have answered correctly.\n");
			printf("time taken to answer the question is %d seconds\n", (int)q_time);
			score++;
		}
		else
		{
			printf("Sorry.The correct answer is option (%d)\n", q_answer);
			printf("time taken to answer the question is %d seconds\n", (int)q_time);
		}

	}
	printf("your final score is %d\n", score);
	printf("Thank you %s for taking the quiz\n", name);
}

FILE* open_qfile(int difficulty)
{
	FILE* f;

	f = fopen(quizfilename[difficulty], "r");
	if (!f)
	{
		printf("There was an unexpected error opening the file %s\n",quizfilename[difficulty]);
		return NULL;
	}
	return f;
}

int get_question(struct question* a1, FILE* f)
{

	char s[LEN_BUFF];



	if (get_string(a1->question, LEN_BUFF, f) < 1)
	{
		return FALSE;
	}
	

	for (int i = 0; i < 4; i++)
	{
		if (get_string(a1->option[i], LEN_BUFF, f) < 1)


			return FALSE;
		
	}

	if (get_string(s, LEN_BUFF, f) < 1)
		return FALSE;

	sscanf(s, "%d", &a1->correct_answer);
	


	return TRUE;
}








int ask_question(struct question* a2)
{
	printf("%s\n", a2->question);
	
	for (int i = 0; i < 4; i++)
	{
		printf("(%d)%s\n",i+1, a2->option[i]);
	}


	return TRUE;
}
int get_answer(struct question* a3)
{
	int answer, got_answer = FALSE;
	char s[LEN_BUFF];
	while (!got_answer)
	{
		if (get_string(s, LEN_BUFF, stdin)< 1)
		{
			printf("Please enter 1,2,3 or 4\n");
			printf("Enter 0 to exit");
		}
		else if (sscanf(s, "%d", &answer) != 1)
		{
			printf("you have entered \"%s\" which is not a valid selection\n",s);
			printf("Please enter 1,2,3,4\n");
			printf("enter 0 to exit\n");
		}
		else if (answer < 0 || answer>4)
		{
			printf("the number %d is not a valid selection\n", answer);
			printf("please enter 1,2,3,4\n");
			printf("enter 0 to exit\n");

		}
		else if (answer == 0)
		{
			return 0;
		}
		else
			got_answer = TRUE;


	}
	
	return answer;
}
int check_answer(struct question* a4)
{
	int answer;
	answer=a4->correct_answer;

	return answer;
}

int get_string(char* buf, int bufsize, FILE* f)
{
	int i;
	char* s;
	s = fgets(buf, bufsize, f);
	if (!s)
	{
		return -1;

	}
	for (i = 0; i < bufsize - 1 && buf[i] != '\0'; i++)
	{
		if (buf[i] == '\n')
		{
			buf[i] = '\0';
			break;
		}
	}
	return i;
}

int choose_difficulty(void)
{
	int difficulty;
	char s[LEN_BUFF];
	printf("Select difficulty\n");
	printf("Press 1 for easy\n");
	printf("Press 2 for medium\n");
	printf("Press 3 for Hard\n");

	do
	{
		if (get_string(s, LEN_BUFF, stdin) < 1)
		{
			printf("Please enter 1,2,3\n");
			
			difficulty = 0;
		}
		else if (sscanf(s,"%d", &difficulty) != 1)
		{
			printf("Please enter 1,2,3 \n");
			
			difficulty = 0;
		}
		else if (difficulty < 0 || difficulty>3)
		{
			printf("Please enter 1,2,3\n");
			
			difficulty = 0;
		}
		
	} while (difficulty <1 || difficulty>3);
	
	




	return(difficulty - 1);
}


