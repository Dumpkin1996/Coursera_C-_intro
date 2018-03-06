#include <iostream>
#include <iomanip>
#include <string>
#include <cmath>
using namespace std;

class Warrior{
public:
	int _strength;
	int _color;
	int _id;
	Warrior(int strength, int color, int & total):_strength(strength), _color(color){
		total++;
		_id = total;
	}
};

class Iceman: public Warrior{
public:
	int _arm;
	Iceman(int strength, int color, int & total, int & icemantotal):Warrior(strength, color, total){
		icemantotal++;
		_arm = _id%3;
		if (_color == 0){
			cout<<"red iceman "<<_id<<" born with strength "<<strength<<",";
			cout<<icemantotal<<" iceman in red headquarter"<<endl;
		}
		else{
			cout<<"blue iceman "<<_id<<" born with strength "<<strength<<",";
			cout<<icemantotal<<" iceman in blue headquarter"<<endl;
		}
		switch (_arm){
			case 0: cout<<"It has a sword"<<endl; break;
			case 1: cout<<"It has a bomb"<<endl; break;
			case 2: cout<<"It has a arrow"<<endl; break;
		}
	}
};

class Lion: public Warrior{
public:
	Lion(int strength, int color, int & total, int & liontotal, int X):Warrior(strength, color, total) {
		liontotal++;
		if (_color == 0){
			cout<<"red lion "<<_id<<" born with strength "<<strength<<",";
			cout<<liontotal<<" lion in red headquarter"<<endl;
		}
		else{
			cout<<"blue lion "<<_id<<" born with strength "<<strength<<",";
			cout<<liontotal<<" lion in blue headquarter"<<endl;
		}
		cout<<"It's loyalty is "<<X<<endl;
	}
};

class Wolf: public Warrior{
public:
	Wolf(int strength, int color, int & total, int & wolftotal):Warrior(strength, color, total) {
		wolftotal++;
		if (_color == 0){
			cout<<"red wolf "<<_id<<" born with strength "<<strength<<",";
			cout<<wolftotal<<" wolf in red headquarter"<<endl;
		}
		else{
			cout<<"blue wolf "<<_id<<" born with strength "<<strength<<",";
			cout<<wolftotal<<" wolf in blue headquarter"<<endl;
		}
	}
};

class Ninja: public Warrior{
public:
	int _arm1;
	int _arm2;
	Ninja(int strength, int color, int & total, int & ninjatotal):Warrior(strength, color, total) {
		ninjatotal++;
		_arm1 = _id%3;
		_arm2 = (_id+1)%3;
		if (_color == 0){
			cout<<"red ninja "<<_id<<" born with strength "<<strength<<",";
			cout<<ninjatotal<<" ninja in red headquarter"<<endl;
		}
		else{
			cout<<"blue ninja "<<_id<<" born with strength "<<strength<<",";
			cout<<ninjatotal<<" ninja in blue headquarter"<<endl;
		}
		switch (_arm1){
			case 0: cout<<"It has a sword and a bomb"<<endl; break;
			case 1: cout<<"It has a bomb and a arrow"<<endl; break;
			case 2: cout<<"It has a arrow and a sword"<<endl; break;
		}
	}
};

class Dragon: public Warrior{
public:
	double _morale;
	int _arm;
	Dragon(int strength, int color, int & total, int & dragontotal, int X, int l_dragon):Warrior(strength, color, total) {
		dragontotal++;
		_arm = _id%3;
		if (_color == 0){
			cout<<"red dragon "<<_id<<" born with strength "<<strength<<",";
			cout<<dragontotal<<" dragon in red headquarter"<<endl;
			_morale = (double) X/ (double)l_dragon;
		}
		else{
			cout<<"blue dragon "<<_id<<" born with strength "<<strength<<",";
			cout<<dragontotal<<" dragon in blue headquarter"<<endl;
			_morale = (double) X/ (double)l_dragon;
		}
		switch (_arm){
			case 0: cout<<"It has a sword,and it's morale is "<<fixed<<setprecision(2)<<_morale<<endl; break;
			case 1: cout<<"It has a bomb,and it's morale is "<<fixed<<setprecision(2)<<_morale<<endl; break;
			case 2: cout<<"It has a arrow,and it's morale is "<<fixed<<setprecision(2)<<_morale<<endl; break;
		}
	}
};


//red: iceman lion wolf ninja dragon
//blue: lion dragon ninja iceman wolf
//sword bomb arrow

int main(){
	int c; cin>>c;
		
	for (int i=0; i<c; i++){
		int M,R,B;
		int l_dragon, l_ninja, l_iceman, l_lion, l_wolf;
		cin>>M;
		R = M; B = M;
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
					R -= redlife[redindex];
					switch (redindex){
						case 0: Iceman(l_iceman, 0, redtotal, rednum[0]); break;
						case 1: Lion(l_lion, 0, redtotal, rednum[1], R); break;
						case 2: Wolf(l_wolf, 0, redtotal, rednum[2]); break;
						case 3: Ninja(l_ninja, 0, redtotal, rednum[3]); break;
						case 4: Dragon(l_dragon, 0, redtotal, rednum[4], R, l_dragon); break;							
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
					B -= bluelife[blueindex];
					switch (blueindex){
						case 3: Iceman(l_iceman, 1, bluetotal, bluenum[3]); break;
						case 0: Lion(l_lion, 1, bluetotal, bluenum[0], B); break;
						case 4: Wolf(l_wolf, 1, bluetotal, bluenum[4]); break;
						case 2: Ninja(l_ninja, 1, bluetotal, bluenum[2]); break;
						case 1: Dragon(l_dragon, 1, bluetotal, bluenum[1], B, l_dragon); break;					
					}
					blueindex ++;
				}
			}
			time ++;
		}
	}
	return 0;
}