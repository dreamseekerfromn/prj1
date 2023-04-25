#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <getopt.h>
#include "log.h"

int 
main(int argc, char *argv[]){
	//init var
	int c, hflag, nflag, lflag;
	char *fname = "logfile.txt";	//for -l switch, default is logfile.txt
	char *e;			//for strtol
	int option_index = 0;		//for getopt_long
	int err_flag = 0;		//for getopt_long
	char *strbuff = "42";		//handling default value for -n

	char *endptr;			//for strtol
	long value;			//for strtol


	opterr = 0;

	//initialize flags
	hflag = 0;
	nflag = 0;
	lflag = 0;

	//declare long options
	struct option options[] = {
		{"help", 0, 0, 'h'},
		{0,0,0,0}
	};

	//getopt_long will be used to accept long switch
	//short ones will be h,n,l
	if (argc >1){
		while(( c = getopt_long(argc,argv, ":hn:l:", options,&option_index)) != -1)
			switch (c)
				{
					//-h, --help for information about switch
					case 'h':
						hflag = 1;
						break;
					//-n to print different integer on the logfile
					case 'n':
						nflag = 1;
						printf("%s\n",optarg);

						//strtol to check int or not
						value = strtol(optarg,&endptr, 10);
						if(*endptr !='\0')
							{
								printf("test : you must type digits after -n, not %s",stderr);
								return 1;
							}
						strbuff = (char *)malloc(strlen(optarg)+1);
						strcpy(strbuff,optarg);
						break;
					//-l to change logfile name
					case 'l':
						lflag = 1;
						if(strncmp(optarg,"-",1) == 0)
							{
								perror("test : you must type file name after -l switch.");
								return 1;
							}
						fname = (char*) malloc(strlen(optarg)+1);
						strcpy(fname,optarg);
						break;
					//errors in getopt
					case '?':
						err_flag = 1;
						printf("Unknown option : -%c is found\n", optopt);
						break;
				}
	}
	//if errflag is on, just exit
	if (err_flag ==1)
		{
			return 1;
		}
	//if iflag is on
	//print simple definition and then term
	if (hflag == 1)
		{
			printf("this program is designed for testing log library function\n");
			printf("-h --help\n print options\n");
			printf("-n [value]\n to print [value] on the logfile\n");
			printf("-l [filename]\n change logfile name to [filename]\n");
		}
	else
		{
			create_log(strbuff);
			//if no switch
			//just test the loglib
			//next 3 lines will test addmsg func
			create_log("TEST : this is test msg");
			create_log("TEST : this is test msg for queue");
			create_log("TEST : this is test msg for clearfunc");
	
			savelog(fname);
	
			//next 2 lines will test getlog func
			char *strings = getlog();
			printf("%s", strings);


			//next 3 will test clearlog func
			clearlog();
			strings = getlog();
			printf("%s", strings);
		}

	return 0;
}
