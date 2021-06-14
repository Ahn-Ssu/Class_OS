#include <sys/sysinfo.h>
#include <stdio.h>

int main()
{
    struct sysinfo info;
    sysinfo(&info); 

    printf("load: %ld %ld %ld\n", info.loads[0],
                                info.loads[1],
                                info.loads[2]);

    printf("mem : %ld %ld %ld\n", info.totalram, 
                                info.totalram-info.freeram,
                                info.freeram);
    printf("total ram size %ld\n", info.totalram);
    printf("shared ram isze %ld\n", info.sharedram);
    printf("buffer ram size %ld\n", info.bufferram);
    printf("total swap space size %ld\n", info.totalswap);
    printf("Swap space still available size %ld\n", info.freeswap);
    printf("# current processes : %d", info.procs);

}  