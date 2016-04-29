// init: The initial user-level program

#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"
#include "bcrypt.h"
char *argv[] = { "sh", 0 };

char* itoa(int i, char b[]){
    char const digit[] = "0123456789";
    char* p = b;
    if(i<0){
        *p++ = '-';
        i *= -1;
    }
    int shifter = i;
    do{ //Move to where representation ends
        ++p;
        shifter = shifter/10;
    }while(shifter);
    *p = '\0';
    do{ //Move back, inserting digits as u go
        *--p = digit[i%10];
        i = i/10;
    }while(i);
    return b;
}

int
main(void)
{
  int pid, wpid;
  if(open("console", O_RDWR) < 0){
    mknod("console", 1, 1);
    open("console", O_RDWR);
  }
  dup(0);  // stdout
  dup(0);  // stderr
  for(;;){
    printf(1, "init: starting sh\n");
    int fd = open("password.txt", O_RDWR);
    if (fd < 0) {
      printf(1,"No password set. Please choose one.\n");
      char buf[100];
      char buf2[100];
      newpass:
        printf(1,"Enter password: ");
        gets(buf,sizeof(buf));
        printf(1,buf);
        printf(1,"Re-enter to confirm: ");
        gets(buf2,sizeof(buf2));
        printf(1,buf2);
        if (strcmp(buf,buf2)) {
          printf(1,"Passwords do not match. Try again.\n");
          goto newpass;
        }
        fd = open("password.txt", O_CREATE|O_RDWR);



        // int salty;
        // salty = random() + random() + random() + random();
        // printf(1,"I'm so salty: %d\n",salty);
        int i;
        uchar rando[17];
        // char digit[100];

        // for (i = 0; i < 4; i++) {
        //   strncat(buf, itoa(random(), random), 1);
        // }

        for (i = 0; i < 16; i++) {
          rando[i] = (char) random()%57 + 65;//itoa(random()%10, digit);
        }
        
        write(fd, bcrypt(buf, rando), sizeof(bcrypt(buf, rando)));
        // write(fd, buf, sizeof(buf));
        write(fd, rando, sizeof(rando));



        printf(1,"Password successfully set. You may now use it to log in.");
    }
      enterpass:
        printf(1,"Enter password: ");
        if (1) {
          printf(1,"Password correct, logging you in.\n");
        }
        else {
          printf(1,"Password incorrect\n");
          goto enterpass;
        }
    pid = fork();
    if(pid < 0){
      printf(1, "init: fork failed\n");
      exit();
    }
    if(pid == 0){
      exec("sh", argv);
      printf(1, "init: exec sh failed\n");
      exit();
    }
    while((wpid=wait()) >= 0 && wpid != pid)
      printf(1, "zombie!\n");
  }
}