// 	Software_License Graber
//
//	This program uses the .htm files created by NEWT Professional Network Inventory program, to create a text file
//	containing only the software license key. 
// 
//
//	ALGORITHM
//	========== 
//		Details about the software installed is found after html code : ">SOFTWARE</TD></TR><TD nowrap bgcolor=".
//		By finiding the code you, you could find the details of software in table format.
//		Every software table intializer has a repeating code, which you can find to identity and seperate the softwares.
//		Within this table, there is pattern for which license is found ( 13 lines after table initializer).
//		Within this license code line, there is pattern to obtain only the license and skip the html codes ( after:  "<TD nowrap>" and before "&nbsp;</TD></TR>").
//		Using these patterns, the username, computer name , software name and its license are found.  
//
//
//
// Parameters  - Main               
// ==========                
//    * fp     		opens the .htm files  
//	  * fdir		opens files containing all the names of the files within the directory 
//	  * fw			creates new text file to append required information
//	  active		variable used to find strings within htm files
//	  nxt-line		variable used to find strings within htm files
//    append		variable used to find strings within htm files
//    off			variable used to find strings within htm files
//	  line 			variable used to find strings within htm files
//	  htm_files[]	array to append names of the htm files within the directory
//    sentence[]	array to append sentences within htm files
//	  names_soft[] 	array to append the name of the software which has the license key
//	  lic_soft[]	array to append the license key of the software
//    comp_name[]	array to append the name of the computer which has the software
//    user_name[]	array to append the name of the user which uses this computer
//    a,b,c,d,e		Iterative values
//    f,g,h,i,j		Iterative values
//


#include <stdio.h>
#include <stdlib.h> 
#include <ctype.h>
#include <string.h>


int main()
{
	//initalizing the file pointers
	FILE *fdir;
	FILE *fp;
	FILE *fw;
	
	//initalizing iterative variables
	int a = 0;
	int b = 0;
	int c = 0;
	int d = 0;
	int e = 0;
	int f = 0;
	int g = 0;
	int h = 0;
	int i = 0;
	int j = 0;
	int active = 0;
	int nxt_line = 0;
	int append = 0;
	int off = 0;
	int line = 0;
	
	//initalizing appendable arrays 
	char htm_files[70];
	char sentence[700];
	char names_soft[70] = {'\0'};
	char lic_soft[100] = {'\0'};
	char comp_name[50];
	char user_name[90];
	
	//pattern within htm used to find the lisence key / username / computer name
	char s_comp[] = "Machine Name:</TD><TD>";
	char u_name[] = "Username:</TD><TD>";
	char s_soft[] = ">SOFTWARE</TD></TR><TD nowrap bgcolor=";
	char e_soft[] = "object(s) listed</TD></TR></TABLE><P>";
	
	//opening directory names 
	fdir = fopen("filenames.txt","r");
	fw = fopen("Excel_Text.txt","w");
	
	//storing .htm file names within htm_files array
	while(fgets(htm_files,40,fdir)!=NULL){
		a=0;
		
		//removing /n within the htm_files to NULL 
		while(a!=30){
			if(htm_files[a] == '\n'){
				htm_files[a] = '\0';
			}
			a++;
		}
		
		//checking if the files 
		if(strncmp(htm_files,"soft_lic.exe",strlen("soft_lic.exe")) == 0){
			continue;
		}
		if(strncmp(htm_files,"htm files",strlen("htm files")) == 0){
			continue;
		}
		if(strncmp(htm_files,".gitignore",strlen(".gitignore")) == 0){
			continue;
		}
		if(strncmp(htm_files,".gitattributes",strlen(".gitattributes")) == 0){
			continue;
		}
		if(strncmp(htm_files,"README.md",strlen("README.md")) == 0){
			continue;
		}
		if(strncmp(htm_files,"filenames.txt", strlen("filenames.txt")) == 0){
			continue;
		}
		if(strncmp(htm_files,"soft_lic.cpp",strlen("soft_lic.cpp")) == 0){
			continue;
		}
		if(strncmp(htm_files,"start.bat",strlen("start.bat")) == 0){
			continue;
		}
		if(strncmp(htm_files,"filenames_batch.bat",strlen("filenames_batch.bat")) == 0){
			continue;
		}
		if(strncmp(htm_files,"gmon.out",strlen("gmon.out")) == 0){
			continue;
		}
		if(strncmp(htm_files,"Excel_Refreshed.xlsm",strlen("gmon.out")) == 0){
			continue;
		}
		if(strncmp(htm_files,"Excel_Text.txt",strlen("gmon.out")) == 0){
			continue;
		}
		if(strncmp(htm_files,"excelrefresh.vbs",strlen("gmon.out")) == 0){
			continue;
		}
		
		a=0;
		
		fp = fopen(htm_files,"r");
		if (fp == NULL) {
    		perror("Error");
    		printf("%s", htm_files);
    	}
    	
    	//reinitializing variables for new .htm files
		a = 0;
		b = 0;
		c = 0;
		d = 0;
		e = 0;
		f = 0;
		g = 0;
		h = 0;
		i = 0;
		j=0;
    	
    	//stores every sentence in .htm file in sentence variable
		while(fgets(sentence, 700, fp)!= NULL){
			a=0;
			// runs through the sentence array until new sentence character is found 
			while(sentence[a]!= '\n'){
				
				// Algorithum is implemented 
				if(active == 1){
					if(nxt_line == 1 || nxt_line == 13){
						if(sentence[a-1]=='>' && a < 14){
							append = 1;
							d=0;
						}
						if(sentence[a] == '&'){
							if(sentence[a+1] == 'n'){
								append = 0;
								names_soft[d] = '\0';
								lic_soft[d] = '\0';
								d=0;
							}
						}
					}
				}
				
				if(append == 1 && nxt_line == 1){
					names_soft[d] = sentence[a];
					d++;
				}
				if(append == 1 && nxt_line == 13){
					lic_soft[d] = sentence[a];
					d++;
				}
				
				while(sentence[a+e] == s_comp[e] && f == 0){
					e++;
				}
				if(e == strlen(s_comp)){
					if (g == 0){
						g = a+e;
						f = 1;
					}
					if(a>=g){
						if(sentence[a] == '&'){
							e=0;
							comp_name[d] = '\0';
							d=0;
						}else{
							comp_name[d] = sentence[a];
							d++;
						}
					}
				}else{
					e = 0;
				}
				
				while(sentence[a+h] == u_name[h] && i == 0){
					h++;
				}
				if(h == strlen(u_name)){
					if (j == 0){
						j = a+h;
						i = 1;
					}
					if(a>=j){
						if(sentence[a] == '&' || sentence[a] == '@' || sentence[a] == '('){
							h=0;
							user_name[d] = '\0';
							d=0;
						}else{
							user_name[d] = sentence[a];
							d++;
						}
					}
				}else{
					h = 0;
				}
							
				while(sentence[a+b] == s_soft[b] && active == 0){
					b++;
				}
				if(b == strlen(s_soft) && active == 0){
					active = 1;
					b=0;
				}else{
					b=0;
				}	
				
				while(sentence[a+c] == e_soft[c] && active == 1){
					c++;
				}
				if(c == strlen(e_soft) && active == 1){
					active = 0;
					c=0;
				}else{
					c=0;
				}
				a++;
			}
			if(active == 1 && nxt_line == 14){ 
				if(strcmp(lic_soft,"\0")!=0){
					//writes to the text file named : Excel_Text.txt
					fprintf(fw,"%s\t%s\t%s\t%s\n",comp_name,user_name,names_soft,lic_soft);
				}
			}
			if(active == 1){
				if (strcmp(sentence,"<TR>\n")==0){
					nxt_line = 0;
				}
				nxt_line++;
			}
			line++;
		}
	fclose(fp);
	}
	
	fclose(fdir);
	fclose(fw);
	
	return 0;
}
