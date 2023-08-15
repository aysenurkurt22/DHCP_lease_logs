#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX_LEASES 2000
struct DhcpLease {
    char IPAddress[50];
    char MACAddress[50];
    char StartEpoch[50];
    char EndEpoch[50];
};

char *explode(char *delim, char *str, int limit) {
    char *copy = strdup(str);

    char *token = strtok(copy, delim);
    char *istenen[20] ;
    
    int i = 0;
    while (token != NULL) {
        istenen[i++] = token;
        if (i == limit)
            break;
        token = strtok(NULL, " ");
    }
    
    free(copy);
    return istenen[i-1];
     
}



int main() {
    char dosyayol[] = "file.txt";

    struct DhcpLease leases[MAX_LEASES];
    int leaseCount = 0;

    FILE *file = fopen(dosyayol, "r");
    if (file == NULL) {
        printf("Dosya yok");
        return 1;
    }

    char satir[500];
    struct DhcpLease *item = NULL;

    while (fgets(satir, sizeof(satir), file) != NULL) {

        char *orj_satir  =strdup(satir);
        char *token = strtok(orj_satir, " \n");


        while (token != NULL) {
           
            if (strcmp(token, "lease") == 0) {
                item = &leases[leaseCount];
                token=explode(" ",satir,2);
                strcpy(item->IPAddress, token);
            }
            else if (strcmp(token, "starts") == 0) {
                token=explode(" ",satir,8);
                strcpy(item->StartEpoch, token);
            } 
            else if (strcmp(token, "ends") == 0) {
                token=explode(" ",satir,8);
                strcpy(item->EndEpoch, token);
                
            }
            else if (strcmp(token, "hardware") == 0) {
                token=explode(" ",satir,3);
                
                strcpy(item->MACAddress, token);
            }
            else if (strcmp(token, "}") == 0) {
                leaseCount++;
            }

            token = strtok(NULL, " \n");
        }
    }

    fclose(file);
 
	int i;
    for ( i = 0; i < leaseCount; i++) {
        printf("IP: %s\n", leases[i].IPAddress);
        printf("Baslangic Zaman: %s\n", leases[i].StartEpoch);
        printf("Bitis Zaman: %s\n", leases[i].EndEpoch);
        printf("MAC: %s\n", leases[i].MACAddress);
        printf("********************\n");
    }


    return 0;
}


