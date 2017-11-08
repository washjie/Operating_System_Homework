#include<stdlib.h>
#include<stdio.h>
#include<dirent.h>
#include <string>
#include<sys/stat.h> 
#include<iostream>
#include<fstream>
#include<string.h>
#include<unistd.h>
#include<vector>
#include<sys/resource.h>
 
using namespace std;

int myFind(char*, vector<string>);

int main(int argc, char* argv[]){   
	
	vector<string> options;
	
	int argv_count=2;
	
	while(argv[argv_count]){
		options.push_back(argv[argv_count]);
		argv_count++;
	}
	myFind(argv[1],options);
	
	return 0;
} 
 
 int myFind(char* path_name, vector<string> op){
	DIR *dir;
	if( (dir=opendir(path_name))==NULL ){
		exit(EXIT_FAILURE);
	}
	else
	{
		struct dirent *dir_name;
		while((dir_name = readdir(dir)) != NULL)
		{
			if(!strcmp(dir_name->d_name,".")||!strcmp(dir_name->d_name,".."))
				continue;
			
			char* temp=new char;	
			stpcpy(temp,path_name);
			strcat(temp,"/");
			strcat(temp,dir_name->d_name);
				
			DIR *dir_temp;
			if( (dir_temp=opendir(temp))==NULL ){
					
				struct stat stat_buffer; 
				if(stat(temp, &stat_buffer) )
					return 0;
					
				int pass=1;
				//scan all the option
				for(int i=0; i < op.size()/2;i++){
					int temp_num;
					int index = i*2;
					if(op[index]=="-name"){
						if(dir_name->d_name!=(string)
							op[index+1])pass=0;
					}
					else if(op[index]=="-inode"){	
						temp_num = atoi(op[index+1].c_str());
						if(stat_buffer.st_ino!=temp_num)
							pass=0;
					}
					else if(op[index]=="-size_max"){	
						temp_num = atoi(op[index+1].c_str());
						double min_size = temp_num;
						for(int i = 0; i < 20; i++){
							min_size *= 2;
						}
						
						if(stat_buffer.st_size > min_size)
							pass=0;
					}
					else if(op[index]=="-size_min"){
						temp_num = atoi(op[i*2+1].c_str());
						double max_size = temp_num;
						for(int i = 0; i < 20; i++){
							max_size *= 2;
						}
						
						if(stat_buffer.st_size < max_size)
							pass=0;
					}
				}
				
				double temp_size=stat_buffer.st_size;
				for(int i = 0; i < 20; i++){
					temp_size /= 2;
				}
				
				if(pass==1)
					cout<<temp<<" "<<stat_buffer.st_ino<<" "<<temp_size<<"MB"<<endl;
				
				if(op.size()==0)
					cout<<temp<<endl;
			
			}
			else{			
				int m=myFind(temp,op);
			}
		}
	}
	
	return 0;
}