#include <stdio.h> 
#include <unistd.h> 
#include <sys/types.h> 
#include <sys/wait.h> 
#include <time.h> 
#include <stdlib.h> 
int main() 
{
 
	FILE *lab_1;/* объявляем указатель на структуру File*/ 
	(lab_1 = fopen("fl.txt", "wt"));/*открываем файл "lab.txt" для записи*/ 
	pid_t pid; /* объявляем переменнтую типа pid_t, которая показывает идентификатор процесса*/ 
	int *status=NULL;/*задаем статус равным NULL, т.к. информация о статусе завершения дочернего процесса для нас не имеет значения*/ 
	switch(pid=fork()) {/* порождаем дочерний процесс с помощью функции fork */ 

		case 0: { /*для дочернего процесса*/ 
			fprintf(lab_1, " Pid of child: %d\nPid of  parent: %d\n\n", getpid(), getppid());/*зааписываем в файл идентификатор дочернего и родительского процессов*/ 
			int TenMbyte = 1024*1024*10; 
			int i=0; 
			for( i; i < TenMbyte; i++){ 
				fprintf(lab_1, "A"); /*цикл будет записывать в файл букву 'A' пока их не наберется на 10 мегабайт*/ 
			} 

			return 0; 

		} 

		case -1: { 
			perror("Fork failed"); 
			return -1; 
		} 

	
		default:{/*для родительского процесса*/ 
    			time_t start = time(NULL);//записываем в start  текущее  время в секундах(до начала дочернего процесса)
 			waitpid(pid, status, 0);/*родительский процесс запишет в файл сколько он ждал завершения дочернего*/
			time_t end = time(NULL);//записываем в ens текузее время в секундах(после завершения дочернего процесса)
			printf("Time: %ld\n",end-start);// считаем разницу между end и start как длительность ожидания рожительским процессом дочернего 
 			return 0; 
		}
		fclose(lab_1);/*закрываем файл*/ 
		} 

} 