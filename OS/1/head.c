#include "types.h"
#include "stat.h"
#include "user.h"

char buf[10000];

void head(int fd, char *name, int line){
	int i, n;

	printf(1,"\n\n");
	i=0;

	while((n = read(fd, buf, sizeof(buf))) > 0){
		for(i=0; i<n; i++){
			printf(1, "%c", buf[i]);
			if(buf[i] == '\n')
				--line;
			if(line==0)
				break;
			// ++i;
		}
	}
	
	// while(buf[i]!=0){			

	// }
	printf(1,"\n");
	if(n < 0){
		printf(1, "head: read error\n");
		exit();
	}
}

int main(int argc, char *argv[]){
	int fd, i, line;//, c, length;
	i = 1;
	line = 10;
	if(argc <= 1){
		head(0, "", 10);
		exit();
	}
	if (argv[1][0] == '-') {
		i = 2;
		line = atoi(&argv[1][1]);
	}

	for(; i < argc; i++){
		if((fd = open(argv[i], 0)) < 0){
			printf(1, "head: cannot open %s\n", argv[i]);
			exit();
		}
		head(fd, argv[i], line);
		close(fd);
	}
	exit();
}