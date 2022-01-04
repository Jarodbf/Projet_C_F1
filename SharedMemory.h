struct F1 {
	int id;
	int idBst[4];
	int temp[5];
	int BStemp[4];
	char statut; //S=stand O=out E=enCourse
	int lost;
};

struct F1 * voitures;
int shmid;
int key=22;

void connectShm(){
	
	shmid = shmget(key,sizeof(struct F1)*21,IPC_CREAT|0666);
	voitures = (struct F1*) shmat(shmid,0,0);
}

void disconectShm(){
	shmdt(voitures);
	shmctl(shmid, IPC_RMID, NULL);
}