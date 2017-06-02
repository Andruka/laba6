#include"Generator.h"
Generator::Cat::Cat(string n,string b,char s,int a){
    c_name=n;
    c_breed=b;
    c_gender=s;
    c_age=a;
}
void Generator::Cat::print(ofstream & fout){
    fout<<c_name<<endl;
    fout<<c_breed<<endl;
    fout<<c_gender<<endl;
    fout<<c_age<<endl;
}
bool Generator::check(ifstream & fin,vector<string> & v){
    string buf;
    if(fin.eof())return 1;
    while(true){
        getline(fin,buf);
	if(fin.eof())return 0;
	v.push_back(buf);
        }
}
bool Generator::work(int quantity,int max_age){
    ifstream fm("male.txt");
    ifstream ff("female.txt");
    ifstream fb("breed.txt");
    ofstream fr("result.txt");
    srand(time(0));
    cout<<"Идёт чтение файлов,ожидайте..."<<endl;
    if(check(fm,vM)){cout<<"Файл male.txt пуст! "<<endl;return 1;}
    if(check(ff,vF)){cout<<"Файл female.txt пуст! "<<endl;return 1;}
    if(check(fb,vB)){cout<<"Файл breed.txt пуст! "<<endl;return 1;}
    cout<<endl<<"Файлы считаны,идёт генерация базы котов,подождите ещё чуть чуть..."<<endl;
    for(int i=0;i<quantity;++i){
	if(rand() % 2)gender='m';
	else gender='f';
  	if(gender == 'm'){
	    Cat cat(vM[rand() % vM.size()],vB[rand() % vB.size()],gender,rand() % max_age + 1);
	    cat.print(fr);
	    }
	else {
	    Cat cat(vF[rand() % vF.size()],vB[rand() % vB.size()],gender,rand() % max_age + 1);
	    cat.print(fr);
	    }
        }
    return 0;
}
int main(int argc , char ** argv ){
    int quantity;
    int max_age;
    if(argc!=3)cout<<"Ошибка!"<<endl;
    quantity=atoi(argv[1]);
    max_age=atoi(argv[2]);
    Generator gen;
    if(gen.work(quantity,max_age)){cout<<"Какой-то входной файл оказался пустым"<<endl;return 1;}
    cout<<"База котов сгенерирована!"<<endl;
}
