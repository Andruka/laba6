#include "Cats.h"
Cat::Cat(){
    name="";
    breed="";
    gender=0;
    age=0;
}
Cat::Cat(string n,string b,char g,int a){
    name=n;
    breed=b;
    gender=g;
    age=a;
}
Cat& Cat::operator = (const Cat& cat) {
        if (this == &cat) {
            return *this;
        }
        name = cat.name;
        breed = cat.breed;
        gender = cat.gender;
        age = cat.age;
        return *this;
}
ostream & operator << (ostream & stream, const Cat & cat) {
    stream<<cat.name<<endl;
    stream<<cat.breed<<endl;
    stream<<cat.gender<<endl;
    stream<<cat.age<<endl;
    return stream;
}
istream & operator >> (istream & stream, Cat & cat) {
    string buf;
    getline (stream, cat.name);
    getline (stream, cat.breed);
    getline (stream,buf);    
    cat.gender=buf[0];
    getline (stream, buf);
    cat.age=atoi(buf.c_str());
    return stream;
}
int Program::start(){
    string buf;
    const char * F1="1.txt";
    const char * F2="2.txt";
    ifstream fin("../laba6/generator/result.txt");
    if(!fin)return 1;
    ofstream fout1(F1);
    ofstream fout2(F2);
    Cat temp;
    Cat cat;
    for(int i=0;;++i){
	fin>>temp;
        if(fin.eof())return 0;
	cat=temp;
	if(i%2)fout2<<cat;
	else fout1<<cat;
	}
    fin.close();
}
int Program::compare(Cat cat1,Cat cat2,int type){
if(type==1){
    string buf1=cat1.name,buf2=cat2.name;
    for(int i=0;;++i){
        if(buf1[i]<buf2[i])return 1;
	else{
	    if(buf1[i]!=buf2[i])return 2;
	    }
	if(buf1.size()==i+1)return 1;
	if(buf2.size()==i+1)return 2;
        }
    }
if(type==2){
    string buf1=cat1.breed,buf2=cat2.breed;
    for(int i=0;;++i){
        if(buf1[i]<buf2[i])return 1;
	else{
	    if(buf1[i]!=buf2[i])return 2;
	    }
	if(buf1.size()==i+1)return 1;
	if(buf2.size()==i+1)return 2;
        }
    }
if(type==3){
    if(cat1.age<=cat2.age)return 1;
    else return 2;
    }
}
void Program::sort(int type){
    const char * F1="1.txt";
    const char * F2="2.txt";
    const char * F3="3.txt";
    const char * F4="4.txt";
    int x=1;
    int blockFin1=0,blockFin2=1;//осталось считать котов из этого файла до конца блока
    int checkFin=1;//из какого файла будет считан кот
    bool checkFout=true;//проверка файла,в который запишется кот
    bool check1=true;
    int checkCat=1;//этот этот кот оказался меньшим
    Cat cat1;
    Cat cat2;
    Cat temp;
    //while(true){
	ifstream fin1(F1),fin2(F2);
	ofstream fout1(F3),fout2(F4);
	fin1>>cat1;
	    while(blockFin1 || blockFin2){
		if(!blockFin1 || !blockFin2){
		    if(blockFin1=0){
			while(blockFin2!=0){
			    fin2>>temp;
			    if(fin2.eof()){blockFin2=0;break;}
			    --blockFin2;
			    if(checkCat==1)cat1=temp;
			    else cat2=temp;
			    if(compare(cat1,cat2,type)==1){
			    if(checkFout){fout1<<cat1;checkFout=false;}
				else {fout2<<cat1;checkFout=true;}
				checkCat=1;
			 	}
			    else{
				if(checkFout){fout1<<cat2;checkFout=false;}
				else {fout2<<cat2;checkFout=true;}
				checkCat=2;				    
				}
			    }
		 	if(fin1.eof() ||fin2.eof()){blockFin1=blockFin2=0;break;}
			blockFin1=blockFin2=x;
			continue;
			}
		    else{
			while(blockFin1!=0){
			    fin1>>temp;
			    if(fin1.eof()){blockFin1=0;break;}
			    --blockFin1;
			    if(checkCat==1)cat1=temp;
			    else cat2=temp;
			    if(compare(cat1,cat2,type)==1){
				if(checkFout){fout1<<cat1;checkFout=false;}
				else {fout2<<cat1;checkFout=true;}
				checkCat=1;
				}
			    else{
				if(checkFout){fout1<<cat2;checkFout=false;}
				else {fout2<<cat2;checkFout=true;}	
				checkCat=2;			    
				}
			    }
		 	if(fin1.eof()==1 ||fin2.eof()==1){blockFin1=blockFin2=0;break;}
			blockFin1=blockFin2=x;
			continue;			    
			}
		    }
		if(checkFin==1)fin1>>temp;
	 	if(fin1.eof()){blockFin1=0;break;}
		--blockFin1;
		if(checkFin==2)fin2>>temp;
	 	if(fin2.eof()){blockFin2=0;break;}
		--blockFin2;
		if(checkCat==1)cat1=temp;
		else cat2=temp;
		if(compare(cat1,cat2,type)==1){
		    if(checkFout){fout1<<cat1;checkFout=false;}
		    else {fout2<<cat1;checkFout=true;}
		    if(checkCat==2){
			if(checkFin==1)checkFin=2;
			else checkFin=1;
			}
		    checkCat=1;	
		    }
		else{
		    if(checkFout){fout1<<cat2;checkFout=false;}
		    else {fout2<<cat2;checkFout=true;}
		    if(checkCat==1){
			if(checkFin==1)checkFin=2;
			else checkFin=1;
			}
		    checkCat=2;			
		    }
		}
cout<<1<<endl;
	    if(!fin1.eof()){
		while(!fin1.eof()){
		    fin1>>temp;
		    if(fin1.eof()){blockFin1=0;break;}
		    if(checkCat==1)cat1=temp;
		    else cat2=temp;
		    if(compare(cat1,cat2,type)==1){
			checkCat=1;
		        if(checkFout){fout1<<cat1;checkFout=false;}
			else {fout2<<cat1;checkFout=true;}
			}
		    else{
			checkCat=2;
			if(checkFout){fout1<<cat2;checkFout=false;}
			else {fout2<<cat2;checkFout=true;}				    
			}
		    }
		}
cout<<2<<endl;
	    if(!fin2.eof()){
		while(!fin2.eof()){
		    fin2>>temp;
		    if(fin2.eof()){blockFin2=0;break;}
		    if(checkCat==1)cat1=temp;
		    else cat2=temp;
		    if(compare(cat1,cat2,type)==1){
		        checkCat=1;
		        if(checkFout){fout1<<cat1;checkFout=false;}
			else {fout2<<cat1;checkFout=true;}
			}
		    else{
			checkCat=2;
			if(checkFout){fout1<<cat2;checkFout=false;}
			else {fout2<<cat2;checkFout=true;}				    
			}
		    }		    
		}
	blockFin1=blockFin2=x=x*2;
	fin1.close();
	fin2.close();
	fout1.close();
	fout2.close();
	/*rename("1.txt","temp.txt");
	rename("3.txt","1.txt");
	rename("temp.txt","3.txt");
	rename("2.txt","temp.txt");
	rename("4.txt","2.txt");
	rename("temp.txt","4.txt");*/
	//}
}
void Program::work(){
    int type;
    start();
    cout<<"Тип сортировки:"<<endl;
    cin>>type;
    sort(type);
    cout<<"Отсортировано!"<<endl;
}
int main(){
    Program program;
    program.work();
}
