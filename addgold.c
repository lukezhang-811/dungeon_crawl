#include<stdlib.h>
#include<stdio.h>
#include<string.h>

int main() {
	// initialize all of the variables to process
	char *payload=getenv("QUERY_STRING");
    char *inputVar=strtok(payload, "=");
    char *answer=strtok(NULL,"&");
    char *temp=strtok(NULL,"=");
    char *gold=strtok(NULL,"");
	int goldpieces=0;
	// since gold can be displayed on the payload in two different ways, there are two different ways to process it
	if(strcmp(inputVar,"gold")==0) {
        goldpieces=atoi(answer);
	} else {
		goldpieces=atoi(gold);
	}
	// open up the index.html file to read line by line and print them out
	FILE *webpage=fopen("../index.html","rt");
	printf("Content-Type:text/html\n\n");
        printf("<html>");
	char array[200];
	while(fgets(array, 199, webpage)!=NULL) {
		if(strstr(array, "form name")) {
			printf("%s",array);
			// inserting the hidden field right under <form>
			printf("<input type=\"hidden\" name=\"gold\" value=\"%d\">", goldpieces);
			continue;
		// since addgold.cgi is in the cgi-bin folder, it must call the gif file in a different way
		} else if(strstr(array, "giphy.gif")) {
			printf("<center><img src=\"../giphy.gif\" alt=\"skull\" height=\"450\" width=\"450\"></center><br />");	
			continue;
		} else {
			printf("%s",array);
		}
	}
	// printf("<body>%s</body>",answer);
	
	printf("</html>");
	fclose(webpage);


	return 0;
}

// NAME: Luke Zhang
// ID: 260771133