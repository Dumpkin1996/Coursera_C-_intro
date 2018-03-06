#include <iostream>
#include <iomanip>
#include <string>
#include <cmath>
using namespace std;

int lifetable[5];    // dragon ninja iceman lion wolf
int attacktable[5];  // dragon ninja iceman lion wolf
int r_loyalty;
int total_time;
int a_arrow;
int times;
int order[2][5]={{2,3,4,1,0},{3,0,1,2,4}};

string colortable[2]={"red", "blue"};
string typetable[5]={"dragon","ninja","iceman","lion","wolf"};

void print_time(){
	cout<<setfill('0')<<setw(3)<<times/60<<':';
	cout<<setfill('0')<<setw(2)<<times%60<<' ';
}

class Warrior;
class City;
class Headquarter;

class Warrior{
public:
	Warrior(int type, int c, int l, int a, int i, Headquarter * hp, int tl);
	int life;
	int attack;
	int id;
	int color;
	int type;               // 0:dragon  1:ninja  2:iceman  3:lion  4:wolf
	bool shotmark;
	bool quareward;
	double morale;  //dragon
	int loyalty;    //lion
	int step;       //iceman
	int weapon[3];          // sword bomb arrow
	int weapon_status[3];   // sword_attack  no_meaning  arrow_used_times 
	City * city_belong;
	Headquarter * quarter_belong; 
	void print_info();
	void move(City * cp);
	void move(Headquarter * hp);
	bool minute_5();
	void minute_10(bool end);
	void minute_30(int l_earned);
	void shoot(Warrior * target);
	void shot();
	void aftershot();
	int virtualfight(Warrior * opp);
	void bomb();
	int fight(Warrior * opp);
	void seize_weapon();   //wolf
	void yell();           //lion
	void getelements(); 
	void getreward();
	void reportweapon();
};

class City{
public:
	City(int p);
	City();
	int pos;
	int life;
	int flag;             //-1:none         0:red          1:blue    
	int n_win[2];
	int recentresult;     //-2:no battle    -1:draw        0:red win      1:blue win
	Warrior * redwarrior;
	Warrior * bluewarrior;
	void minute_5();
	void minute_10();
	void minute_30();
	void minute_38();
	void battle();
	void dragonyell();
	void getelements();
	void setflag();
};

class Headquarter{
public:
	Headquarter(int tl, int c);
	int total_life;
	int color;
	int n_warrior;
	int n_enemy;
	int won_life;
	bool new_entry;
	Warrior * newborn;
	Warrior * enemy1;
	Warrior * enemy2;
	void minute_0();
	void minute_5();
	void minute_10();
	void newbornout(City * cp);
	bool istaken();
	void getreward();
	void reportlife();
};


Warrior::Warrior(int type, int c, int l, int a, int i, Headquarter * hp, int tl): 
type(type), color(c), life(l), attack(a), id(i), quarter_belong(hp){
	city_belong = NULL;
	shotmark = 0;
	quareward = false;
	morale = -1;
	loyalty = 10000;
	step = 0;
	for (int i=0; i<3; i++){
		weapon[i] = 0;
		weapon_status[i] = 0;
	}
	print_time();
	cout<<colortable[color]<<' '<<typetable[type]<<' '<<id<<" born"<<endl;
	//deal with special warrior properties
	if (type==0){            //dragon special
		morale = (double) tl / (double) l;
		weapon[id%3] = 1;
		cout<<"Its morale is "<<fixed<<setprecision(2)<<morale<<endl;
	}
	if (type==1){           //ninja special
		weapon[id%3] = 1;
		weapon[(id+1)%3] = 1;
	}
	if (type==2){
		weapon[id%3] = 1;
	}
	if (type==3){           //lion special
		loyalty = tl;
		cout<<"Its loyalty is "<<loyalty<<endl;
	}
	//deal with sword attack value
	weapon_status[0] = (int) weapon[0] * 0.2 * attack;
	if (weapon_status[0]==0) weapon[0]=0;
}

void Warrior::print_info(){
	cout<<colortable[color]<<' '<<typetable[type]<<' '<<id;
}

void Warrior::move(City *cp){
	city_belong = cp;
	if (type==2){        //iceman special
		step++;
		if (step%2==0){
			if (life<10) life = 1;
			else life -= 9;
			attack += 20;
		}
	}
}

void Warrior::move(Headquarter * hp){
	hp->n_enemy++;
	hp->new_entry = 1;
	if (hp->enemy1) hp->enemy2 = this;
	else hp->enemy1 = this;
	city_belong = NULL;
	//iceman special
	if (type==2){        //iceman special
		step++;
		if (step%2==0){
			if (life<10) life = 1;
			else life -= 9;
			attack += 20;
		}
	}
}

bool Warrior::minute_5(){
	//lion special
	if(type==3) return (loyalty<=0);
	return false;
}

void Warrior::minute_10(bool end){
	print_time();
	print_info();
	if (end) cout<<" reached "<<colortable[(color+1)%2]<<" headquarter";
	else cout<<" marched to city "<<city_belong->pos+1;
	cout<<" with "<<life<<" elements and force "<<attack<<endl;
}

void Warrior::minute_30(int l_earned){
	print_time();
	print_info();  cout<<" earned "<<l_earned<<" elements for his headquarter"<<endl;
	quarter_belong->total_life += l_earned;
}

void Warrior::shoot(Warrior * target){
	weapon_status[2]++;
	if (weapon_status[2]==3){
		weapon_status[2]=0;
		weapon[2]=0;
	}
	target->shotmark = 1;
	print_time();
	print_info();  cout<<" shot";
	if (target->life <= a_arrow){
		cout<<" and killed ";
		target->print_info();
	}
	cout<<endl;
}

void Warrior::shot(){
	if (shotmark)  life -= a_arrow;
	shotmark = 0;
}

void Warrior::aftershot(){
	if (life <= 0){
		if (color==0){
			if (city_belong->bluewarrior){
				if (city_belong->bluewarrior->life > 0){
					city_belong->n_win[0]=0;
					city_belong->n_win[1]++;
					city_belong->recentresult = 1;
					city_belong->bluewarrior->quareward = true;
					//wolf special
					if (city_belong->bluewarrior->type==4){
						city_belong->bluewarrior->seize_weapon();
					}
					//dragon special
					if (city_belong->bluewarrior->type==0){
						city_belong->bluewarrior->morale += 0.2;
					}
				}
			}
			delete city_belong->redwarrior;
			city_belong->redwarrior = NULL;
		}
		else if (color==1){
			if (city_belong->redwarrior){
				if (city_belong->redwarrior->life > 0){
					city_belong->n_win[1]=0;
					city_belong->n_win[0]++;
					city_belong->recentresult = 0;
					city_belong->redwarrior->quareward = true;
					if (city_belong->redwarrior->type==4){
						city_belong->redwarrior->seize_weapon();
					}
					if (city_belong->redwarrior->type==0){
						city_belong->redwarrior->morale += 0.2;
					}
				}
			}
			delete city_belong->bluewarrior;
			city_belong->bluewarrior = NULL;
		}
	}
}



int Warrior::virtualfight(Warrior * opp){
    if (city_belong->flag == color || 
    	(city_belong->flag == -1 && city_belong->pos%2 == color) ){    
    	if (opp->life - attack - weapon[0]*weapon_status[0] > 0){
    		if (opp->type == 1) return 0;
    		else{
    			if (life - (int)opp->attack/2 - opp->weapon[0]*opp->weapon_status[0] > 0) return 0;
    			else return -1;
    		}
    	}
    	else  return 1; 
	}
	else{
		if (life - opp->attack - opp->weapon[0]*opp->weapon_status[0] > 0){
    		if (type == 1) return 0;
    		else{
    			if (opp->life - (int)attack/2 - weapon[0]*weapon_status[0] > 0) return 0;
    			else return 1;
    		}
    	}
    	else  return -1; 
	}
}

void Warrior::bomb(){
	print_time();
	print_info();  cout<<" used a bomb and killed "<<colortable[(color+1)%2]<<' ';
	if (color==0) cout<<typetable[city_belong->bluewarrior->type]<<' '<<city_belong->bluewarrior->id;
	else cout<<typetable[city_belong->redwarrior->type]<<' '<<city_belong->redwarrior->id;
	cout<<endl;
	delete city_belong->redwarrior;   city_belong->redwarrior=NULL;
	delete city_belong->bluewarrior; city_belong->bluewarrior=NULL;
}

int Warrior::fight(Warrior * opp){
	int mark = 0; int oppmark = 0;
	if (type==3) mark = life;                   //lion special
	if (opp->type==3) oppmark = opp->life;
	print_time();
	print_info();  cout<<" attacked ";  opp->print_info();
	cout<<" in city "<<city_belong->pos+1<<" with "<<life<<" elements and force "<<attack<<endl;
	opp->life -= (attack + weapon[0]* weapon_status[0]);
	if(weapon[0]==1){
		weapon_status[0] *= 0.8;
		if (weapon_status[0] == 0) weapon[0]=0;
	}
	if (opp->life > 0){
		if(opp->type != 1){
			print_time();
			opp->print_info();  cout<<" fought back against "; print_info();
			cout<<" in city "<<city_belong->pos+1<<endl;
			life -= ((int)opp->attack/2 + opp->weapon[0]*opp->weapon_status[0]);
			if(opp->weapon[0]==1){
				opp->weapon_status[0] *= 0.8;
				if (opp->weapon_status[0] == 0) opp->weapon[0]=0;
			}
		}
		if(life>0){
			city_belong->recentresult = -1;
			if (opp->type==0)  opp->morale -= 0.2;           //dragon special
			if (type==0) morale -= 0.2;                      
			if (opp->type==3) opp->loyalty -= r_loyalty;     //lion special
			if (type==3) loyalty -= r_loyalty;
			return 0;
		}
		else{
			print_time();
			print_info(); cout<<" was killed in city "<<city_belong->pos+1<<endl;
			opp->quareward = true;
			city_belong->recentresult = opp->color;
			opp->life += mark;                               //lion special
			if (opp->type==4)  opp->seize_weapon();          //wolf special
			if (opp->type==0)  opp->morale += 0.2;           //dragon special
			if (color==0){
				delete city_belong->redwarrior;
				city_belong->redwarrior=NULL;
			}
			else{
				delete city_belong->bluewarrior;
				city_belong->bluewarrior=NULL;
			}
			return  -1;
		}	
	}
	else{
		print_time();
		opp->print_info();  cout<<" was killed in city "<<city_belong->pos+1<<endl;
		quareward = true;
		city_belong->recentresult = color;
		life += oppmark;                 //lion special
		if (type==4)  seize_weapon();    //wolf special
		if (type==0)  morale += 0.2;     //dragon special
		if (opp->color==0){
			delete city_belong->redwarrior;
			city_belong->redwarrior=NULL;
		}
		else{
			delete city_belong->bluewarrior;
			city_belong->bluewarrior=NULL;
		}
		return 1;
	}
	return 0;
}

void Warrior::seize_weapon(){
	if(type==4){//wolf special
		if (color==0){
			for (int i = 0; i<3; i++){
				if (weapon[i]==0){
					weapon[i] = city_belong->bluewarrior->weapon[i];
					weapon_status[i] = city_belong->bluewarrior->weapon_status[i];
				}
			}
		}
		if (color==1){
			for (int i = 0; i<3; i++){
				if (weapon[i]==0){
					weapon[i] = city_belong->redwarrior->weapon[i];
					weapon_status[i] = city_belong->redwarrior->weapon_status[i];
				}
			}
		}
	}
}

void Warrior::yell(){
	if (type==0){//dragon special
		if (city_belong->flag == color || 
	    	(city_belong->flag == -1 && city_belong->pos%2 == color) ){
			if (morale > 0.8){
				print_time();
				print_info();   cout<<" yelled in city "<<city_belong->pos+1<<endl;
			}
		}
	}
}

void Warrior::getelements(){
	print_time();
	print_info(); cout<<" earned "<<city_belong->life<<" elements for his headquarter"<<endl;
	quarter_belong->won_life += city_belong->life;
	city_belong->life = 0;
}

void Warrior::getreward(){
	if (quareward){
		if (quarter_belong->total_life >= 8){
			quarter_belong->total_life -= 8;
			life += 8;
		}
	}
	quareward = false;
}

void Warrior::reportweapon(){
	print_time();
	print_info(); cout<<" has ";
	if (weapon[2]==1){
		cout<<"arrow("<<3-weapon_status[2]<<')';
		if (weapon[1]==1){
			cout<<",bomb";
			if(weapon[0]==1)   cout<<",sword("<<weapon_status[0]<<')'<<endl;
			else cout<<endl;
		}
		else{
			if (weapon[0]==1)  cout<<",sword("<<weapon_status[0]<<')'<<endl;
			else cout<<endl;
		}
	}
	else{
		if (weapon[1]==1){
			cout<<"bomb";
			if(weapon[0]==1)   cout<<",sword("<<weapon_status[0]<<')'<<endl;
			else cout<<endl;
		}
		else{
			if (weapon[0]==1)  cout<<"sword("<<weapon_status[0]<<')'<<endl;
			else cout<<"no weapon"<<endl;
		}
	}
}

Headquarter::Headquarter(int tl, int c):total_life(tl), color(c){
	n_warrior = 0;
	n_enemy = 0;
	won_life = 0;
	new_entry = false;
	newborn = NULL;
	enemy1 = NULL;
	enemy2 = NULL;
}

void Headquarter::minute_0(){
	int index = order[color][n_warrior%5];
    if (total_life >= lifetable[index]){
        total_life -= lifetable[index];
        n_warrior++;
        newborn = new Warrior(index, color, lifetable[index], attacktable[index], n_warrior, this, total_life);
    }
}

void Headquarter::minute_5(){
	if(newborn){
		if (newborn->minute_5()){
			print_time();
			newborn->print_info(); cout<<" ran away"<<endl;
			delete newborn;
			newborn = NULL;
		}
	}
}

void Headquarter::minute_10(){
	if (new_entry){
		if (enemy2) enemy2->minute_10(true);
		else enemy1->minute_10(true);
	}
	new_entry = 0;
}

void Headquarter::newbornout(City * cp){
	if (color==0) cp->redwarrior = newborn;
	else if (color==1) cp->bluewarrior = newborn;
	if (newborn) newborn->move(cp);
	newborn = NULL;
}

bool Headquarter::istaken(){
	if (n_enemy==2){
		return true;
	}
	return false;
}

void Headquarter::getreward(){
	total_life += won_life;
	won_life = 0;
}

void Headquarter::reportlife(){
	print_time();
	cout<<total_life<<" elements in "<<colortable[color]<<" headquarter"<<endl;
}

City::City(int p):pos(p){
	life = 0;
	redwarrior = NULL;
	bluewarrior = NULL;
	flag = -1;
	recentresult = -2;
	n_win[0] = 0; n_win[1] = 0;
}

City::City(){
	life = 0;
	pos = -1;
	redwarrior = NULL;
	bluewarrior = NULL;
	flag = -1;
	recentresult = -2;
	n_win[0] = 0; n_win[1] = 0;
}

void City::minute_5(){
	if (redwarrior){
		if (redwarrior->minute_5()){
			print_time();
			cout<<"red lion "<<redwarrior->id<<" ran away"<<endl;
			delete redwarrior;
			redwarrior = NULL;
		}
	}
	if (bluewarrior){
		if(bluewarrior->minute_5()){
			print_time();
			cout<<"blue lion "<<bluewarrior->id<<" ran away"<<endl;
			delete bluewarrior;
			bluewarrior = NULL;
		}
	}
}

void City::minute_10(){
	if (redwarrior) redwarrior->minute_10(false);
	if (bluewarrior) bluewarrior->minute_10(false);
}

void City::minute_30(){
	if (redwarrior && !bluewarrior){
		redwarrior->minute_30(life);
		life = 0;
	}
	if (bluewarrior && !redwarrior){
		bluewarrior->minute_30(life);
		life = 0;
	}
}
 
void City::minute_38(){
	if (redwarrior && bluewarrior){
		if (redwarrior->weapon[1]==1 && redwarrior->virtualfight(bluewarrior)==-1 ){
			redwarrior->bomb(); 
		}
		else if (bluewarrior->weapon[1]==1 && bluewarrior->virtualfight(redwarrior)==-1){
			bluewarrior->bomb();
		}
	}
}

void City::battle(){
	int temp;
	if (redwarrior&&bluewarrior){
		if (flag==0 || (flag==-1&&pos%2==0)){
			temp = redwarrior->fight(bluewarrior);
			if (temp==0) {n_win[0]=0; n_win[1]=0;}
			if (temp==1) {n_win[0]++; n_win[1]=0;}
			if (temp==-1) {n_win[1]++; n_win[0]=0;}
		}
		else{
			temp = bluewarrior->fight(redwarrior);
			if (temp==0) {n_win[0]=0; n_win[1]=0;}
			if (temp==1) {n_win[1]++; n_win[0]=0; }
			if (temp==-1) {n_win[0]++; n_win[1]=0;}
		}
	}
}

void City::dragonyell(){
	if (redwarrior){
		if (recentresult==0 || recentresult==-1){
			if (redwarrior->type==0){
				redwarrior->yell();
			}
		}
	}
	if (bluewarrior){
		if (recentresult==1 || recentresult==-1){
			if (bluewarrior->type==0){
				bluewarrior->yell();
			}
		}
	}
}

void City::getelements(){
	if (recentresult==0) redwarrior->getelements();
	else if (recentresult==1) bluewarrior->getelements();
	recentresult = -2;
}

void City::setflag(){
	if (flag!=0 && n_win[0]==2){
		print_time();
		cout<<"red flag raised in city "<<pos+1<<endl;
		flag = 0;
		n_win[0] = 0; n_win[1]=0;
	}
	if (flag!=1 && n_win[1]==2){
		print_time();
		cout<<"blue flag raised in city "<<pos+1<<endl;
		flag = 1;
		n_win[0]=0; n_win[1]=0;
	}
}

int main(){
	int n_case; cin>>n_case;
		
	for (int j=0; j<n_case; j++){
		
		int M,N;  cin>>M>>N>>a_arrow>>r_loyalty>>total_time;  //read information
		for (int i=0; i<5; i++)  cin>>lifetable[i];
		for (int i=0; i<5; i++)  cin>>attacktable[i];

		cout<<"Case "<<j+1<<':'<<endl;   //initilization
		times = 0;
		Headquarter redquarter = Headquarter(M, 0);
		Headquarter bluequarter = Headquarter(M, 1);
		City Map[30];
		for (int i=0; i<N; i++)  Map[i] = City(i);
		
		
		while (times <= total_time){
			redquarter.minute_0();      //mintue 0
			bluequarter.minute_0();
			times += 5;

			if (times>total_time) break;   //minute 5
			else{
				redquarter.minute_5();
				bluequarter.minute_5();
				for (int i=0; i<N; i++){
					Map[i].minute_5();
				}
			}
			times +=5;

			if(times>total_time) break;   //minute 10
			else{
				if (Map[0].bluewarrior){                               //blue: from city to headquarter
					Map[0].bluewarrior->move(&redquarter); 
					Map[0].bluewarrior = NULL;
				}
				for (int i=0; i<N-1; i++){                              //blue: from city to city
					Map[i].bluewarrior = Map[i+1].bluewarrior;
					if (Map[i].bluewarrior)  Map[i+1].bluewarrior->move(&Map[i]);
				}
				bluequarter.newbornout(&Map[N-1]);                      //blue: from headquarter to city
				if (Map[N-1].redwarrior){                               //red: from city to headquarter
					Map[N-1].redwarrior->move(&bluequarter); 
					Map[N-1].redwarrior = NULL;
				}
				for (int i=N-1; i>0; i--){                              //red: from city to city
					Map[i].redwarrior = Map[i-1].redwarrior;
					if (Map[i].redwarrior)  Map[i-1].redwarrior->move(&Map[i]);
				}
				redquarter.newbornout(&Map[0]);                        //red: from headquarter to city
				//complete all movements first and then output these movements from west to east
				redquarter.minute_10();
				if (redquarter.istaken()) {print_time();  cout<<"red headquarter was taken"<<endl;}
				for (int i=0; i<N; i++){
					Map[i].minute_10();
				}
				bluequarter.minute_10();
				if (bluequarter.istaken())  {print_time(); cout<<"blue headquarter was taken"<<endl;}
				if (redquarter.istaken() || bluequarter.istaken())   break;
			}
			times += 10;

			if(times>total_time) break;   //minute 20
			else{
				for (int i=0; i<N; i++) Map[i].life += 10;
			}
			times += 10;

			if(times>total_time) break;   //minute 30
			else{
				for (int i=0; i<N; i++)   Map[i].minute_30();
			}
			times += 5;

			if(times>total_time) break;    //minute 35
			else if (N>1){
				//shoot and output, pretend that the warrior shot is not affected
				if (Map[0].redwarrior)
					if (Map[0].redwarrior->weapon[2]==1)
						if (Map[1].bluewarrior)
							Map[0].redwarrior->shoot(Map[1].bluewarrior);
				for (int i=1; i<N-1; i++){
					if (Map[i].redwarrior){
						if (Map[i].redwarrior->weapon[2]==1){
							if (Map[i+1].bluewarrior){
								Map[i].redwarrior->shoot(Map[i+1].bluewarrior);
							}
						}
					}
					if (Map[i].bluewarrior){
						if (Map[i].bluewarrior->weapon[2]==1){
							if (Map[i-1].redwarrior){
								Map[i].bluewarrior->shoot(Map[i-1].redwarrior);
							}
						}
					}
				}
				if (Map[N-1].bluewarrior)
					if (Map[N-1].bluewarrior->weapon[2]==1)
						if (Map[N-2].redwarrior)
							Map[N-1].bluewarrior->shoot(Map[N-2].redwarrior);
				//make the warrior shot affected
				for (int i=0; i<N; i++){
					if (Map[i].redwarrior) Map[i].redwarrior->shot();
					if (Map[i].bluewarrior) Map[i].bluewarrior->shot();
				}
				for (int i=0; i<N; i++){
					if (Map[i].redwarrior) Map[i].redwarrior->aftershot();
					if (Map[i].bluewarrior) Map[i].bluewarrior->aftershot();
				}
			}
			times += 3;

			if(times>total_time) break;   //minute 38
			else{
				for (int i=0; i<N; i++){
					Map[i].minute_38();
				}
			}
			times += 2;

			if(times>total_time) break;   //minute 40
			else{
				for (int i=0; i<N; i++){
					Map[i].battle();
					Map[i].dragonyell();
					Map[i].getelements();
					Map[i].setflag();
				}
				for (int i=0; i<N; i++){
					if (Map[i].bluewarrior)
						Map[i].bluewarrior->getreward();
				}
				for (int i=N-1; i>=0; i--){
					if (Map[i].redwarrior)
						Map[i].redwarrior->getreward();
				}
				redquarter.getreward();
				bluequarter.getreward();
			}
			times+=10;

			if(times>total_time) break;   //minute 50
			else{
				redquarter.reportlife();
				bluequarter.reportlife();		
			}
			times+=5;

			if(times>total_time) break;   //minute 55
			else{
				for (int i=0; i<N; i++){
					if (Map[i].redwarrior) Map[i].redwarrior->reportweapon();
				}
				if (bluequarter.enemy1) bluequarter.enemy1->reportweapon();
				if (bluequarter.enemy2) bluequarter.enemy2->reportweapon();
				if (redquarter.enemy1) redquarter.enemy1->reportweapon();
				if (redquarter.enemy2) redquarter.enemy2->reportweapon();
				for (int i=0; i<N; i++){
					if (Map[i].bluewarrior) Map[i].bluewarrior->reportweapon();
				}

			}
			times += 5;
		}
	}
}