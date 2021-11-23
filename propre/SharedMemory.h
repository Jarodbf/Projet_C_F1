struct F1 {
	int id;
	int temp[4];
	int BStemp[4];
	char statut; //S=stand O=out E=enCourse
};

struct F1 * voitures;
int shmid;
struct F1 * voitures = malloc(sizeof(voitures)*20);
key_t key=22;

int conectShm(){
	
	int shmid = shmget(key,sizeof(struct F1)*20,IPC_CREAT|0666);
	voitures = (struct F1*) shmat(shmid,0,0);
}

int disconectShm(){
	shmdt(voitures);
	shmctl(shmid, IPC_RMID, NULL);
}