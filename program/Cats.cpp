#include "Cats.h"
Cat::Cat(){
    for(int i=0;i<64;++i){
        name[i]='\0';
        }
    for(int i=0;i<64;++i){
        breed[i]='\0';
        }
    age[0]=age[1]='\0';
    gender='\0';
}
Cat::Cat(char* n,char* b,char* a,char g){
    strcpy(name,n);
    strcpy(breed,b);
    strcpy(age,a);
    gender=g;
}
Cat& Cat::operator = (const Cat& cat) {
        if (this == &cat) {
            return *this;
        }
    	strcpy(name,cat.name);
    	strcpy(breed,cat.breed);
    	strcpy(age,cat.age);
    	gender=cat.gender;
        return *this;
}
ostream & operator << (ostream & stream, const Cat & cat) {
    stream.write(cat.name , 64);
    stream.write(cat.breed , 64);
    stream.write(cat.age , 2);
    stream.put(cat.gender);
    return stream;
}
istream & operator >> (istream & stream, Cat & cat){
    stream.read(cat.name , 64);
    stream.read(cat.breed , 64);
    stream.read(cat.age , 2);
    stream.get(cat.gender);
    return stream;
}
void Cat::print(){
    cout<<"Имя: ";
    for(int i=0;i<64;++i){
        if(name[i]!='\0')cout<<name[i];
	else break;
	}
    cout<<endl<<"Порода: ";
    for(int i=0;i<64;++i){
        if(breed[i]!='\0')cout<<breed[i];
	else break;
	}
    cout<<endl<<"Возраст: ";
    for(int i=0;i<2;++i){
        if(age[i]!='\0')cout<<(int)age[i];
	else break;
	}
    cout<<endl<<"Пол: ";
    cout<<gender<<endl<<endl;
}
int compare_for_merge(Cat cat1,Cat cat2,int type){
if(type==1){
    for(int i=0;i<64;++i){
       	if(cat1.name[i]=='\0')return 0;
    	if(cat2.name[i]=='\0')return 1;
        if(cat1.name[i]<cat2.name[i])return 0;
	if(cat1.name[i]>cat2.name[i])return 1;
        }
    return 0;
    }
if(type==2){
    for(int i=0;i<64;++i){
   	if(cat1.breed[i]=='\0')return 0;
    	if(cat2.breed[i]=='\0')return 1;
        if(cat1.breed[i]<cat2.breed[i])return 0;
	if(cat1.breed[i]>cat2.breed[i])return 1;
        }
    return 0;
    }
if(type==3){
    int a=0,b=0;
    if(cat1.age[1]=='\0')a=(int)cat1.age[0];
    else a=((int)cat1.age[0])*10+(int)cat1.age[1];
    if(cat2.age[1]=='\0')b=(int)cat2.age[0];
    else b=((int)cat2.age[0])*10+(int)cat2.age[1];
    if(a<=b)return 0;
    else return 1;
    }
}
int compare_for_search(Cat cat,char * buf,int type){
if(type==1){
    for(int i=0;i<64;++i){
	if(buf[i]=='\0')return 2;
	if(cat.name[i]=='\0')return 0;
        if(cat.name[i]<buf[i])return 0;
	if(cat.name[i]>buf[i])return 1;
        }
    return 2;
    }
if(type==2){
    for(int i=0;i<64;++i){
	if(buf[i]=='\0')return 2;
	if(cat.breed[i]=='\0')return 0;
        if(cat.breed[i]<buf[i])return 0;
	if(cat.breed[i]>buf[i]) return 1;
        }
    return 2;
    }
if(type==3){
    int a=0,b=0;
    if(cat.age[1]=='\0')a=(int)cat.age[0];
    else a=((int)cat.age[0])*10+(int)cat.age[1];
    if(buf[1]!='-'||buf[1]!='\0')b=atoi(buf);
    else b=(int)buf[0];
    if(a<b)return 0;
    if(a>b)return 1;
    if(a==b)return 2;
    }
}
