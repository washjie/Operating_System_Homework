#include <stdio.h>
#include <stdlib.h>

#define RECORD_SIZE 4096
#define NUM_HEX 16
int main(){
	char str[RECORD_SIZE];
	int i;
	FILE *fp, *fp_new;
	fp = fopen("data.txt", "r");
	fp_new = fopen("new_data.txt", "w");
	while(fscanf(fp, "%s", str) != EOF){
            fprintf(fp_new, "%c%c%c%c", str[0], str[1], str[2], str[3]);
	}
	fprintf(fp_new, "\n");
	fclose(fp);

	fp = fopen("data.txt", "r");
	while(fscanf(fp, "%s", str) != EOF){
            fprintf(fp_new, "%s", str);
            fprintf(fp_new, "\n");
	}

	fclose(fp);
	fclose(fp_new);

	return 0;
}
