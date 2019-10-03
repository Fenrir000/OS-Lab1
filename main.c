/* Из родительского процесса создается  дочерний. Дочерний пишет свой pid  и  pid  родителя в txt файл  и  генерирует 10 Мб чего-нибудь.
  Родительский ожидает окончания дочернего  и выводит сколько он ждал
  */
#include <stdio.h> 
#include <unistd.h> 
#include <sys/types.h> 
#include <sys/wait.h> 
#include <time.h> 
#include <stdlib.h> 
int main() 
{
 
	FILE *lab_1;/* объявляем указатель на структуру File*/ 
	(lab_1 = fopen("fl.txt", "wt"));/*открываем файл "fl.txt" для записи*/ 
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
    	      		struct timespec start, end;//объявляем структуры для хранения определенного времени
			clock_gettime (CLOCK_REALTIME, &start);//записываем в start  текущее  время в секундах(до начала дочернего процесса)
 			waitpid(pid, status, 0);/*родительский процесс начнет ожидание завершения дочернего*/
			clock_gettime (CLOCK_REALTIME, &end);//записываем в end текущее время в секундах(после завершения дочернего процесса)
			long double WaitingTime=0.0;//объявляем переменную в которую запишем время ожидания			 
			 WaitingTime=(1000000000*(end.tv_sec - start.tv_sec)+(end.tv_nsec - start.tv_nsec));// считаем разницу в наносекундах как длительность ожидания родительским процессом дочернего
			printf("I was waiting for %Lf nanoseconds\n",WaitingTime);// выводим время ожидания
 			return 0; 
		
		}
		fclose(lab_1);/*закрываем файл*/ 
		} 

} 
