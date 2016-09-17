/*
	Comp 2511 - Assignment 2
	This program is modelled after the Unix Cat program, except with fewer switches.
	The program should perform various functions on the file specified on command line
	according to the switches applied. If no file is read, read from stdin.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
void concat();
void display_help();

/*Main Method*/
int main(int argc, char *argv[]){
	FILE *fp;
	int i;
	int bflag = 0;
	int eflag = 0;
	int hflag = 0;
	int nflag = 0;
	int sflag = 0;
	int tflag = 0;
	int dashflag = 0;

	for (i = 1; i < argc; i++){
		if(argv[i][0] != '-')
			break;
		if(strlen(argv[i]) != 2){
			fprintf(stderr,"%s%s\n%s\n","./concat: invalid option ", argv[i],"Try './concat -h' for more information.");
			exit(0);
		}
		if(dashflag == 1)
			break;
		switch(argv[i][1]){
			case 'b':
				bflag++;
				break;
			case 'e':
				eflag++;
				break;
			case 'h':
				hflag++;
				display_help();
				break;
			case 'n':
				nflag++;
				break;
			case 's':
				sflag++;
				break;
			case 't':
				tflag++;
				break;
			case '-':
				dashflag++;
				break;
			default:
				fprintf(stderr,"%s%c\n%s\n","./concat: invalid option -- ", argv[i][1], "Try './concat -h' for more information.");
				exit(1);
		}
	}
	
	if(i == argc){
		concat(stdin,bflag,eflag, nflag, sflag, tflag);
	}
	
	for(; i < argc; i++){
		if((fp = fopen(argv[i], "rb")) == 0){
			fprintf(stderr,"%s", "FILE CAN'T BE OPENED");
			return 2;
		}
		concat(fp,bflag,eflag,nflag,sflag,tflag);
		if(fclose(fp) != 0){
			perror("fclose");
			return 3;
		}
	}
	
	
	return 0;
		
}

/*
/*According to each switch, goes through the operations and display them to standard output.*/
void concat(FILE *fp, int bflag, int eflag, int nflag, int sflag, int tflag){

	static int linenumber = 1;
	int c;
    static int linecount = 1;
	
	

	while ((c = fgetc(fp)) != EOF){
	
		if(c == '\n'){
			linecount++;
			if(sflag == 1 && linecount > 2)
				continue;
			if(nflag == 1){
				if(linecount >= 2){
					printf("%6d  ", linenumber);
					linenumber++;
				}
			}
			if(eflag == 1){
				putchar('$');
			}
			putchar(c);
		} else {
			if(linecount >= 1){
				if(nflag == 1 || bflag == 1){
					printf("%6d  ", linenumber);
					linenumber++;
				}
			}
			if(tflag == 1){
				if(c == '\t'){
					putchar('^'); 
					c = 'I';
				}
			}
			putchar(c);
			linecount = 0;
		}
	}
}

/*Display help and exit*/
void display_help(void){
	printf("Usage: concat [OPTION] ... [FILE]...\n"
		   "Concatenate FILE(s), or standard input, to standard output.\n"
			"  -b number non-empty output lines\n"
			"  -e display $ at end of each lines\n"
			"  -n number all output lines\n"
			"  -s suppress repeated empty output lines\n"
			"  -t display TAB characters as ^I\n"
			"  -h display this help and exit\n"
			"  -- mark end of options\n"
	);
	
	exit(0);
}






