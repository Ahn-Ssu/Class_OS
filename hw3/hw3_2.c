#include <stdio.h>
#include <unistd.h>
#include <sys/utsname.h>
#include <sys/sysinfo.h>
#include <sys/stat.h>
#include <time.h> 


void print_envInfo();
void print_fileInfo(char filename[]);

int main(int args, char *argv[]){

  argv[1] == NULL? print_envInfo() : print_fileInfo(argv[1]) ;
}

void print_fileInfo(char filename[]){

  if (access(filename, F_OK) == -1){
    perror(filename);
    exit(0);
  }

  printf("Permission of file %s\n", filename);
  printf("    permission to read: %d\n", access(filename, R_OK)? 0 : 1);
  printf("    permission to read: %d\n", access(filename, W_OK)? 0 : 1);
  printf("    permission to read: %d\n", access(filename, X_OK)? 0 : 1);

  printf("\n");
  struct stat st;
  stat(filename, &st);

  struct tm at, mt, ct;
  char buff[BUFSIZ];

  at = *localtime(&st.st_atime);
  mt = *localtime(&st.st_mtime);
  ct = *localtime(&st.st_ctime);
  

  printf("stat of file %s\n", filename);
  printf("    st_dev = %ld\n", st.st_dev);
  printf("    st_ino = %ld\n", st.st_ino);
  printf("    st_mode = %o (octal)\n", st.st_mode);
  printf("    st_uid = %d\n", st.st_uid);
  printf("    st_gid = %d\n", st.st_gid);
  printf("    st_size = %ld\n", st.st_size);
  printf("    st_atime = %d/%02d/%02d %02d:%02d:%02d\n", at.tm_year+1900, at.tm_mon+1, at.tm_mday, at.tm_hour, at.tm_min, at.tm_sec);
  printf("    st_mtime = %d/%02d/%02d %02d:%02d:%02d\n", mt.tm_year+1900, mt.tm_mon+1, mt.tm_mday, mt.tm_hour, mt.tm_min, mt.tm_sec);
  printf("    st_ctime = %d/%02d/%02d %02d:%02d:%02d\n", ct.tm_year+1900, ct.tm_mon+1, ct.tm_mday, ct.tm_hour, ct.tm_min, ct.tm_sec);
}

void print_envInfo(){

  printf("User and Process info:\n");
  printf("    getuid() = %d\n", getuid());
  printf("    getpid() = %d\n", getpid());
  printf("    getppid() = %d\n", getppid());

  
  printf("\n");
  struct utsname un;
  uname(&un);

  printf("Kernel info:\n");
  printf("    sysname  = %s\n",un.sysname);
  printf("    nodename = %s\n",un.nodename);
  printf("    release  = %s\n",un.release);
  printf("    version  = %s\n",un.version);
  printf("    machine  = %s\n",un.machine);


  printf("\n");
  struct sysinfo info;
  sysinfo(&info);

  printf("System info:\n");
  printf("    uptime  = %ld\n", info.uptime);
  printf("    totalram  = %ld\n", info.totalram);
  printf("    freeram  = %ld\n", info.freeram);
  printf("    procs  = %d\n", info.procs);

}

