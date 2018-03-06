#include <iostream>
#include <iomanip>
#include <string>
#include <cmath>
using namespace std;


class Iceman{
public:
	int _strength;
	int _color;
	int _id;
	Iceman(int strength, int color, int id){
		_strength = strength;
		_color = color;
		_id = id;
		if (_color == 0)
			cout<<"red iceman "<<_id<<" born with strength "<<strength<<",";
		else
			cout<<"blue iceman "<<_id<<" born with strength "<<strength<<",";
	}
};

class Lion{
public:
	int _strength;
	int _color;
	int _id;
	Lion(int strength, int color, int id){
		_strength = strength;
		_color = color;
		_id = id;
		if (_color == 0)
			cout<<"red lion "<<_id<<" born with strength "<<strength<<",";
		else
			cout<<"blue lion "<<_id<<" born with strength "<<strength<<",";
	}
};

class Wolf{
public:
	int _strength;
	int _color;
	int _id;
	Wolf(int strength, int color, int id){
		_strength = strength;
		_color = color;
		_id = id;
		if (_color == 0)
			cout<<"red wolf "<<_id<<" born with strength "<<strength<<",";
		else
			cout<<"blue wolf "<<_id<<" born with strength "<<strength<<",";
	}
};

class Ninja{
public:
	int _strength;
	int _color;
	int _id;
	Ninja(int strength, int color, int id){
		_strength = strength;
		_color = color;
		_id = id;
		if (_color == 0)
			cout<<"red ninja "<<_id<<" born with strength "<<strength<<",";
		else
			cout<<"blue ninja "<<_id<<" born with strength "<<strength<<",";
	}
};

class Dragon{
public:
	int _strength;
	int _color;
	int _id;
	Dragon(int strength, int color, int id){
		_strength = strength;
		_color = color;
		_id = id;
		if (_color == 0)
			cout<<"red dragon "<<_id<<" born with strength "<<strength<<",";
		else
			cout<<"blue dragon "<<_id<<" born with strength "<<strength<<",";
	}
};


//red: iceman lion wolf ninja dragon
//blue: lion dragon ninja iceman wolf

int main(){
	int c; cin>>c;
		
	for (int i=0; i<c; i++){
		int M; cin>>M; int R = M; int B = M;
		int l_dragon, l_ninja, l_iceman, l_lion, l_wolf;
		cin>>l_dragon>>l_ninja>>l_iceman>>l_lion>>l_wolf;
		cout<<"Case:"<<i+1<<endl;
		int time = 0;
		int rednum[5] = {0};
		int bluenum[5] = {0};
		int redlife[5] = {l_iceman, l_lion, l_wolf, l_ninja, l_dragon};
		int bluelife[5] = {l_lion, l_dragon, l_ninja, l_iceman, l_wolf};

		int redindex = 0; int redtotal = 0; bool redstopped = 0;
		int blueindex = 0; int bluetotal = 0; bool bluestopped = 0;
		
		while (true){
			if (redstopped && bluestopped) {
				break;
			}
			if (!redstopped){
				cout<<setfill('0')<<setw(3)<<time<<' ';
				if (R<l_wolf && R<l_iceman && R<l_ninja && R<l_dragon && R<l_lion){
					cout<<"red headquarter stops making warriors"<<endl;
					redstopped = 1;
				}
				else{
					if (redindex>4) redindex=0;
					while (R<redlife[redindex]){
						redindex++;
						if (redindex>4) redindex=0;
					}
					redtotal ++;
					R -= redlife[redindex];
					switch (redindex){
						case 0: Iceman(l_iceman, 0, redtotal); 
								rednum[0]++;
								cout<<rednum[0]<<" iceman in red headquarter"<<endl;
								break;
						case 1: Lion(l_lion, 0, redtotal); 
								rednum[1]++;
								cout<<rednum[1]<<" lion in red headquarter"<<endl;
								break;
						case 2: Wolf(l_wolf, 0, redtotal); 
								rednum[2]++;
								cout<<rednum[2]<<" wolf in red headquarter"<<endl;
								break;
						case 3: Ninja(l_ninja, 0, redtotal); 
								rednum[3]++;
								cout<<rednum[3]<<" ninja in red headquarter"<<endl;
								break;
						case 4: Dragon(l_dragon, 0, redtotal); 
								rednum[4]++;
								cout<<rednum[4]<<" dragon in red headquarter"<<endl;
								break;							
					}
					redindex ++;
				}
			}
			if (!bluestopped){
				cout<<setfill('0')<<setw(3)<<time<<' ';
				if (B<l_wolf && B<l_iceman && B<l_ninja && B<l_dragon && B<l_lion){
					cout<<"blue headquarter stops making warriors"<<endl;
					bluestopped = 1;
				}
				else{
					if (blueindex>4) blueindex=0;
					while (B<bluelife[blueindex]){
						blueindex++;
						if (blueindex>4) blueindex=0;
					}
					bluetotal ++;
					B -= bluelife[blueindex];
					switch (blueindex){
						case 3: Iceman(l_iceman, 1, bluetotal); 
								bluenum[3]++;
								cout<<bluenum[3]<<" iceman in blue headquarter"<<endl;
								break;
						case 0: Lion(l_lion, 1, bluetotal); 
								bluenum[0]++;
								cout<<bluenum[0]<<" lion in blue headquarter"<<endl;
								break;
						case 4: Wolf(l_wolf, 1, bluetotal); 
								bluenum[4]++;
								cout<<bluenum[4]<<" wolf in blue headquarter"<<endl;
								break;
						case 2: Ninja(l_ninja, 1, bluetotal); 
								bluenum[2]++;
								cout<<bluenum[2]<<" ninja in blue headquarter"<<endl;
								break;
						case 1: Dragon(l_dragon, 1, bluetotal); 
								bluenum[1]++;
								cout<<bluenum[1]<<" dragon in blue headquarter"<<endl;
								break;					
					}
					blueindex ++;
				}
			}
			time ++;
		}
	}
	return 0;
}