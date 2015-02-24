#include <iostream>
#include <cstring>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <algorithm>
using namespace std;

void Startup();
void GameSystem(char**, char**, int,int);
void shuffle(char**, char**, int, int);
void GametoPlay(char**,char**,char**,int,int,int);

int main(int argc, char* argv[]){
	Startup();
	return 0;
}

void Startup(){
	srand(time(0));
	int colA=0, colB=0;
	cout<<"Column A:";
	cin>>colA;
	cout<<"Column B:";
	cin>>colB;
	
	char** awords = new char*[colA];
	char** bwords = new char*[colB];

	char theword[20];
	for(int i=0;i<colA;i++){
		awords[i] = new char[20];
	}
	cout<<"Column A"<<endl;
	for(int i=0;i<colA;i++){
		cout<<i+1<<". ";
		cin>>theword;
		strcpy(awords[i],theword);
	}
	for(int i=0;i<colB;i++){
		bwords[i] = new char[20];
	}
	cout<<"Column B"<<endl;
	for(int i=0;i<colB;i++){
		cout<<i+1<<". ";
		cin>>theword;
		strcpy(bwords[i],theword);
	}

	GameSystem(awords,bwords,colA,colB);

	for(int i=0;i<colA;i++){
		delete awords[i];
	}
	delete[] awords;

	for(int i=0;i<colB;i++){
		delete bwords[i];
	}
	delete[] bwords;

}

void GameSystem(char** awords, char** bwords, int colA, int colB){

	cout<<"\nColumn A list:"<<endl;
	for(int i=0; i<colA;i++){
		cout<<awords[i]<<endl;
	}
	cout<<'\n';
	cout<<"Column B list:"<<endl;
	for(int i=0; i<colB;i++){
		cout<<bwords[i]<<endl;
	}
	cout<<'\n';
	cout<<"Match up each of the words for the answers!"<<endl;
	char ans;
	int pos, pos2, cont, size = 0;
	int cpos = 0;
	if(colA>colB){
		cont = colA;
		size = colA*2;

	}else{
		cont = colB;
		size = colB*2;
	}
	char** matchup = new char*[size];
	for(int i=0;i<size;i++){
		matchup[i] = new char[20];
	}
	do{
		cout<<"Choose a Column A word:";
		cin>>pos;
		cout<<"Choose a Column B word:";
		cin>>pos2;
		strcpy(matchup[cpos],awords[pos-1]);
		strcpy(matchup[cpos+1],bwords[pos2-1]);
		cpos+=2;
		if(cont==1){
			break;
		}
		cont--;
		cout<<"Another matchup? Y/N:";
		cin>>ans;
	}while(ans=='y'||ans=='Y');
	for(int i=0;i<size;i++){
		cout<<matchup[i]<<' ';
	}
	cout<<"\n\nSuccesfully created the answer sheet."<<endl;

	GametoPlay(awords,bwords,matchup,colA,colB,size);

}


void shuffle(char** awords, char** bwords, int sizea, int sizeb){

	char** tempa = new char*[sizea];
	for(int i=0;i<sizea;i++){
		tempa[i] = new char[20];
	}
	for(int i=0;i<sizea;i++){
		strcpy(tempa[i],awords[i]);
	}
	int randy;
	vector<int> nonrandy;
	bool flag = false;
	for(int i=0;i<sizea;i++){
		randy = rand()%sizea;
		do{
			if(find(nonrandy.begin(),nonrandy.end(),randy)!=nonrandy.end()){
				randy = rand()%sizea;
				flag = false;
			} else {
				vector<int>::iterator it;
				it = nonrandy.end();
				it = nonrandy.insert(it,randy);
				flag = true;
			}
		}while(!flag);
		strcpy(awords[i],tempa[randy]);
	}

	char** tempb = new char*[sizeb];
	for(int i=0;i<sizeb;i++){
		tempb[i] = new char[20];
	}
	for(int i=0;i<sizeb;i++){
		strcpy(tempb[i],bwords[i]);
	}
	randy = 0;
	vector<int> nonrandy2;
	flag = false;
	for(int i=0;i<sizeb;i++){
		randy = rand()%sizeb;
		do{
			if(find(nonrandy2.begin(),nonrandy2.end(),randy)!=nonrandy2.end()){
				randy = rand()%sizeb;
				flag = false;
			} else {
				vector<int>::iterator it;
				it = nonrandy2.end();
				it = nonrandy2.insert(it,randy);
				flag = true;
			}
		}while(!flag);
		strcpy(bwords[i],tempb[randy]);
	}
	
	for(int i=0;i<sizea;i++){
		delete tempa[i];
	}
	delete[] tempa;

	for(int i=0;i<sizeb;i++){
		delete tempb[i];
	}
	delete[] tempb;

}

void GametoPlay(char** awords,char** bwords, char** matchup,int colA,int colB, int size){
	
	shuffle(awords,bwords,colA,colB);
	cout<<"\nColumn A list:"<<endl;
	for(int i=0; i<colA;i++){
		cout<<awords[i]<<endl;
	}
	cout<<'\n';
	cout<<"Column B list:"<<endl;
	for(int i=0; i<colB;i++){
		cout<<bwords[i]<<endl;
	}
	cout<<'\n';
	cout<<"Let's start the matchup game!"<<endl;
	int pos, pos2, contwins = 0, contfails = 0, countplays = 0;
	char ans;
	do{
		cout<<"Choose a Column A word:";
		cin>>pos;
		cout<<"Choose a Column B word:";
		cin>>pos2;
		bool ifright = false;

		for(int i=0; i<size;i++){
			if(strlen(matchup[i])==strlen(awords[pos-1])){
				bool flag = false;
				for(int j=0;j<strlen(matchup[i]);j++){
					if(matchup[i][j] == awords[pos-1][j]){
						flag = true;
					}else{
						break;
					}
				}
				if(flag){
					if(strlen(matchup[i+1])==strlen(bwords[pos2-1])){
						for(int j=0;j<strlen(matchup[i+1]);j++){
							if(matchup[i+1][j] == bwords[pos2-1][j]){
								ifright = true;
							}else{
								ifright = false;
								break;
							}
						}
					}
				}
			}
		}

		cout<<'\n';
		if(ifright){
			contwins++;
			cout<<"You got it right :D"<<endl;
		}else{
			contfails++;
			cout<<"You got it wrong D:"<<endl;
		}
		pos = 0;
		pos2 = 0;
		cout<<"Another matchup? Y/N:";
		cin>>ans;
	}while(ans=='y'||ans=='Y');

	cout<<"Final Scores\nCorrect answers:"<<contwins<<"\nIncorrect answers:"<<contfails<<endl;
	double percentage = 0.0;
	if(contwins==0){
		percentage = 0.0;
	}else {
		countplays = contfails + contwins;
		percentage = contwins/countplays;
		percentage = percentage*100;
	}
	cout<<"Your score was of "<<percentage<<endl;


}
