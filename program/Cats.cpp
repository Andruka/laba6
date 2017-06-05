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
    ifstream fin("../generator/result.txt");
    if(!fin)return 1;
    ofstream fout1(F1);
    ofstream fout2(F2);
    Cat temp;
    Cat cat;
    for(int i=0;;++i){
	fin>>temp;
        if(fin.eof())return 0;
	cat=temp;
	if(i%2)fout1<<cat;
	else fout2<<cat;
	}
    fin.close();
}
int Program::compare(Cat cat1,Cat cat2,int type){
if(type==1){
    string buf1=cat1.name,buf2=cat2.name;
    for(int i=0;;++i){
        if(buf1[i]<buf2[i])return 0;
	else{
	    if(buf1[i]!=buf2[i])return 1;
	    }
	if(buf1.size()==i+1)return 0;
	if(buf2.size()==i+1)return 1;
        }
    }
if(type==2){
    string buf1=cat1.breed,buf2=cat2.breed;
    for(int i=0;;++i){
        if(buf1[i]<buf2[i])return 0;
	else{
	    if(buf1[i]!=buf2[i])return 1;
	    }
	if(buf1.size()==i+1)return 0;
	if(buf2.size()==i+1)return 1;
        }
    }
if(type==3){
    if(cat1.age<=cat2.age)return 0;
    else return 1;
    }
}
void Program::sort(int type){
    int block[2];
    int x=1;
    int a;
    int checkCat,actualFin;
    Cat cat[2];
    ifstream fin[2];
    ofstream fout[2];
    while(true){
	block[0]=block[1]=x;
	fin[0].open("1.txt");
	fin[1].open("2.txt");
	fout[0].open("3.txt");
	fout[1].open("4.txt");
   	for(int i=1;;++i){
	    a=(i%2);
	    if(fin[0].eof() && fin[1].eof())break;
	    for(int j=(x*2);j>0;--j){
		if(!fin[0].eof() || !fin[1].eof()){
	            if(j==(x*2) && !fin[0].eof()){
		        fin[0]>>cat[0];
			if(fin[0].eof()){
			    if(i==1 && j==x*2){
	    			rename("2.txt","result.txt");
	    			return;
				}
			    ++j;
			    block[1]+=block[0];
			    block[0]=0;
			    continue;
			    }
			--block[0];
			continue;
			}
		    if(j==(x*2)){
			fin[1]>>cat[0];
			if(fin[1].eof()){
			    ++j;
			    block[0]+=block[1];
			    block[1]=0;
			    continue;
			    }
			--block[1];
			continue;
			}
		    if(j==(x*2-1)){
			fin[1]>>cat[1];
			if(fin[1].eof()){
			    ++j;
			    block[0]+=block[1];
			    block[1]=0;
			    fout[a]<<cat[0];			    
			    continue;
			    }
			--block[1];
		        checkCat=compare(cat[0],cat[1],type);
		        fout[a]<<cat[checkCat];
		        if(j==1){
			    if(checkCat==0)fout[a]<<cat[1];
			    else fout[a]<<cat[0];
			    }
			continue;						
			}
		    if(block[0]!=0 && block[1]!=0){
		    	fin[checkCat]>>cat[checkCat];
			if(fin[checkCat].eof()){
			    if(fin[0].eof()){
			        block[1]+=block[0];
			        block[0]=0;				
				}
			    else{
			        block[0]+=block[1];
			        block[1]=0;				
				}
			    ++j;
			    continue;
			    }
			--block[checkCat];
		    	checkCat=compare(cat[0],cat[1],type);
		    	fout[a]<<cat[checkCat];
			}
		    else{
			if(block[0]==0)actualFin=1;
			else actualFin=0;
		        fin[actualFin]>>cat[checkCat];
			if(fin[actualFin].eof()){
			    if(fin[0].eof()){
			        block[1]+=block[0];
			        block[0]=0;				
				}
			    else{
			        block[0]+=block[1];
			        block[1]=0;				
				}
			    if(fin[0].eof() && fin[1].eof()){
				if(checkCat==0)fout[a]<<cat[1];
				else fout[a]<<cat[0];				
				}
			    ++j;
			    continue;
			    }
			--block[actualFin];
		        checkCat=compare(cat[0],cat[1],type);
		        fout[a]<<cat[checkCat];			
			}
		    if(j==1){
			if(checkCat==0)fout[a]<<cat[1];
			else fout[a]<<cat[0];
			}
		    }
		else break;
	    	}
	    block[0]=block[1]=x;
	    }
	fin[0].close();
	fin[1].close();
	fout[0].close();
	fout[1].close();
	rename("1.txt","temp.txt");
	rename("3.txt","1.txt");
	rename("temp.txt","3.txt");
	rename("2.txt","temp.txt");
	rename("4.txt","2.txt");
	rename("temp.txt","4.txt");
	x=x*2;		
	}
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
