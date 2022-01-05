#include <semaphore.h>

struct F1 {
	int id;
	int idBst[4];
	int temp[6];
	int BStemp[4];
	char statut; //S=stand O=out E=enCourse
	int lost;
};

struct F1 * voitures;
sem_t *sm;
int shmid;
int key=22;

void connectShm(){
	
	shmid = shmget(key,sizeof(struct F1)*21,IPC_CREAT|0666);
	voitures = (struct F1*) shmat(shmid,0,0);
	int shmid_sem = shmget(IPC_PRIVATE, sizeof(sem_t), 0666 | IPC_CREAT);
    sm = shmat(shmid_sem, NULL, 0);
}

void disconectShm(){
	shmdt(voitures);
	shmctl(shmid, IPC_RMID, NULL);
}