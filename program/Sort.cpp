#include "Sort.h"
int Program::start(){
    const char * F1="1.txt";
    const char * F2="2.txt";
    ifstream in("../generator/result.txt");
    in.unsetf (std::ios::skipws);
    if(!in)return 1;
    ofstream out1(F1);
    ofstream out2(F2);
    Cat cat;
    for(int i=0;;++i){
	in>>cat;
        if(in.eof())break;
	if(i%2)out1<<cat;
	else out2<<cat;
	}
    in.close();
    out1.close();
    out2.close();
}
void Program::merge(int type,const char * fn){
    ifstream fin[2];
    ofstream fout[2]; 
    int block[2];
    int x=1;
    int a;
    int checkCat,actualFin;
    Cat cat[2];
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
	    			rename("2.txt",fn);
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
		        checkCat=compare_for_merge(cat[0],cat[1],type);
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
		    	checkCat=compare_for_merge(cat[0],cat[1],type);
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
		        checkCat=compare_for_merge(cat[0],cat[1],type);
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
void Program::search(int type){
    if(type==0)return;
    ifstream in;
    if(type==1)in.open("name.txt");
    if(type==2)in.open("breed.txt");
    if(type==3)in.open("age.txt");    
    if(!in)return;
    string trash;
    switch(type){
	case 1:cout<<"Введите имя или его часть"<<endl;break;
	case 2:cout<<"Введите название породы или его часть"<<endl;break;
	case 3:cout<<"Введите диапазон возраста через дефис"<<endl;break;
	}
    int temp=0;
    char maxAge[2];
    char buf[64];
    Cat cat;
    for(int i=0;i<64;++i){
	buf[i]='\0';
	}
    getline(cin,trash,'\n');
    cin.get(buf,65);
    if(type==3){
	if(buf[1]=='-' || buf[1]=='\0'){
	    maxAge[0]=buf[2];
	    maxAge[1]=buf[3];	    
	    }
	else{
	    maxAge[0]=buf[3];
	    maxAge[1]=buf[4];	    
	    }
	}
    streampos middle,end,beg=0;
    in.seekg(0,in.end);
    end=in.tellg();
    while(true){
	if((end-beg)==131)break;
	middle=(((end+beg)/131)/2)*131;
        in.seekg(middle);
        in>>cat;
	if(compare_for_search(cat,buf,type)==0)beg=middle;
	else end=middle;
	}
    in.seekg(beg);
    in>>cat;
    if(compare_for_search(cat,buf,type)==0)in>>cat;
    while(true){
	if(in.eof()){
	    if(temp==0)cout<<"Коты не найдены!"<<endl;
	    return;
	    }
	if(compare_for_search(cat,buf,type)==1)break;
	cout<<"-----Кот №"<<temp+1<<"-----"<<endl;
	cat.print();
        ++temp;
	in>>cat;
	}
    if(type==3 && maxAge[0]!='\0'){
        while(true){
	    if(in.eof())return;
	    if(compare_for_search(cat,maxAge,type)==1)break;
	    cout<<"-----Кот №"<<temp+1<<"-----"<<endl;
	    cat.print();
	    ++temp;
	    in>>cat;
	    }
	}
    in.close();
}
void Program::show(int type){
    ifstream in;
    Cat cat;
    if(type==0)return;
    if(type==1)in.open("name.txt");
    if(type==2)in.open("breed.txt");
    if(type==3)in.open("age1.txt");
    for(int i=0;;++i){ 
	in>>cat;
	if(in.eof())break;
        cout<<"-----Кот №"<<i+1<<"-----"<<endl;
	cat.print();
	}
    in.close(); 
}
void Program::work(){
    int type;
    start();
    merge(1,"name.txt");
    start();
    merge(2,"breed.txt");
    start();
    merge(3,"age1.txt");
    system("clear");
    cout<<"Коты отсортированы,программа готова к работе!"<<endl;
    while(true){
    	cout<<"1-показать список отсортированных котов\n2-осуществить поиск определённых котов по атрибутам\n0-закрыть программу"<<endl;
        cin>>type;
	system("clear");
    	switch(type){
	    case 1:cout<<"Выберите критерий сортировки:\n1-сортировка по имени\n2-сортировка по породе\n3-сортировка по возрасту\n0-назад\n";
	           cin>>type;
		   system("clear");
	           show(type);
	           break;
	    case 2:cout<<"Выберите критерий поиска:\n1-поиск по имени\n2-поиск по породе\n3-поиск по возрасту\n0-назад\n";
	           cin>>type;
		   system("clear");
	           search(type);
		   break;
	    case 0:return;
	    }
	}
}

