#define _DEFAULT_SOURCE
#include <stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>
#include<getopt.h>

#define RED "#FF7373"
#define ORANGE "#FFA500"

typedef unsigned long long int ulli;

enum{
    STATE_OK,
    STATE_WARNING,
    STATE_CRITICAL,
    STATE_UNKNOWN,
};

void useage(char *argv[])
{
    printf("Usage: %s [-b|B] [-t seconds] [-i interface] [-w Bytes:Bytes] [-c Bytes:Bytes] [-s] [-h]\n",argv[0]);
    printf("\n");
    printf("-b \t\t use bits/s\n");
    printf("-B \t\t use Bytes/s\n ");
    printf("-t seconds \t refresh time (default 1)\n");
    printf("-i interface \t network interfaces to monitor (comma separted).\n");
    printf("             \t If not specified, checks all interfaces\n");
    printf("-w Bytes:Bytes \t Set warning (color orange) for Rx:Tx bandwidth.(default: none)\n");
    printf("-c Bytes:Bytes \t Set critical (color red) for Rx:Tx bandwidth.(default: none)\n");
    printf("-s \t\t use SI units\n");
    printf("-h \t\t this help\n");
    printf("\n");
}

void get_values(char **const ifaces,int num_ifaces, time_t *const s, ulli * const received, ulli * const sent)
{
    FILE *f;
    f = fopen("/proc/net/dev","r");
    if(!f)
    {
        fprintf(stderr,"Can't open /proc/net/dev\n");
        exit(STATE_UNKNOWN);
    }

    ulli temp_r,temp_s;
    
    char line[BUFSIZ] = {0}; //{0} makes all the values in line to 0
    char ifname[BUFSIZ];

    *received = 0;
    *sent = 0;
    while(fgets(line,BUFSIZ-1,f)!=NULL)
    {
        if(sscanf(line,"%[^:]: %llu %*u %*u %*u %*u %*u %*u %*u %ullu",ifname,&temp_r,&temp_s)==3)
        {
            int i;
            int iface_found = num_ifaces == 0;

            for(i=0;i<num_ifaces;i++)
            {
                if(strcmp(ifaces[i],ifname)!=0)
                {
                    iface_found = 1;
                    break;
                }
            }
            
            if(!iface_found || strcmp(ifname,"lo")==0)
                continue;

            *received = *received+temp_r;
            *sent = *sent+temp_s;
        }
    }

    fclose(f);

    *s = time(NULL);
    if(!s)
    {
        fprintf(stderr,"Can't get Epoch time\n");
        exit(STATE_UNKNOWN);
    }
}

void display(int const unit, int const divisor, double b, int const warining, int const critical)
{
    char fmtstr[7];

    if(critical !=0 && b > critical)
    {
        printf("<span fallback='true color=%s'>",RED);
    }
    else if(warning !=0 && b > warning)
    {
        printf("<span fallback='true color=%s'>",ORANGE);
    }
    else
    {
        printf("<span fallback='true'>");
    }

    if(unit=='b')
        b=b*8;
    
    snprintf(fmtstr,sizeof(fmtstr),"%%%d.1lf",divisor>1000?6:5);

    if(b<divisor)
    {
        printf(fmtstr,b);
        printf(" %c/s",unit);
    }
    else if(b < divisor*divisor)
    {
        printf(fmtstr,b/divisor);
        printf("K%c/s",unit);
    }
    else if(b < divisor*divisor*divisor)
    {
        printf(fmtstr,b/(divisor*divisor));
        printf("M%c/s",unit);
    }
    else
    {
        printf(fmtstr,b/(divisor*divisor*divisor));
        printf("G%c/s",unit);
    }
    printf("</span>");
}

void parse_ifaces(char *str,char ***ifaces, int *num_ifaces)
{
    int max_ifaces = strlen(str)/2 +1;

    *ifaces = calloc(max_ifaces,sizeof(char*));
    *num_faces = 0;
    while(((*ifaces)[*num_ifaces]=strsep(&str,",")))
    {
        if((*ifaces)[*num_ifaces]!=NULL && (*ifaces)[*num_faces][0]!='\0')
        {
            (*num_ifaces)++;
        }
    }
}


int main(int argc, char *argv[])
{
    int c,unit = 'B',t = 1;
    char str_ifaces[BUFSIZ]={0};
    char **ifaces;
    int num_ifaces;
    int warningrx = 0, warningtx = 0, criticalrx=0,criticaltx=0;
    int divisor = 1024;
    char *envvar = NULL;
    char *label = "";

    envvar = getenv("USE_BITS");
    if(envvar && *envvar == '1')
        unit='b';

    envvar = getenv("USE_BYTES");
    if(envvar && *envvar =='1')
        unit='B';

    envvar = getenv("REFRESH_TIME");
    if(envvar)
        t = atoi(envvar);

    envvar
    if()
}
