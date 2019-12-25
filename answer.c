#include<stdlib.h>
#include<stdio.h>
#include<string.h>

int main(int argc, char *argv[]) {
	// get the payload from the site
	char *payload=getenv("QUERY_STRING");
	// make a copy of the payload so that it can be split up
	char copyPayload[strlen(payload)];
	strcpy(copyPayload,payload);
	// splitting up the payload copy into individual tokens
	char *inputVar=strtok(copyPayload, "=");
	char *gold=NULL;
	char *temp=NULL;
	char *answer=NULL;
	// check if there is '&' in the payload, different ways of processing
	if(strstr(payload,"&")) {
		gold=strtok(NULL,"&");
		temp=strtok(NULL,"=");
		answer=strtok(NULL,"\n");
	} else {
		answer=strtok(NULL,"\n");
	}
	// an int variable to store the amount of gold	
	int goldpieces=0;
	if(gold==NULL){
			goldpieces=10;
	} else {
			goldpieces=atoi(gold);
	}
	printf("Content-Type:text/html\n\n");
    printf("<html>");
	// clear up the '+' in the input so that it can become spaces
	for(int i=0; i<strlen(answer); i++) {
		if(answer[i]=='+') {
			answer[i]=' ';
		}
	}
	// printf("%s plus %s",inputVar,answer);
	// a solution to be compared with the answer
	char *solution="Hylian Shield";
	// open up the index.html file so that we can print them line by line
	FILE *webpage=fopen("../index.html","rt");
	char array[200];
	while(fgets(array, 199, webpage)!=NULL) {
		// since index.html is in public_html but answer.cgi is in cgi-bin, different path to call for the gif
		if(strstr(array, "giphy.gif")) {
			printf("<center><img src=\"../giphy.gif\" alt=\"skull\" height=\"450\" width=\"450\"></center><br />");	
			continue;
		// skip over the rest of the webpage
		} else if(strstr(array, "dare")||strstr(array,"submit")||strstr(array,"NORTH")) {
			continue;
		} else {
			printf("%s",array);
		}
	}
	// all of the links to other pages include the addgold program so that gold can be sent to other sites
	// if the player has over 100 goldpieces, it will automatically display a YOU WIN page
	if(goldpieces>=100){
		printf("<center><font size=\"4\" color=\"white\"><body><p><b>YOU HAVE COLLECTED MORE THAN 100 GOLDPIECES, YOU WIN!</b></p></body></font></center> <br />");
	// if the player has less than 0 goldpieces, it will automatically display a YOU DIE page
	} else if(goldpieces<=0) {
		printf("<center><font size=\"4\" color=\"white\"><body><p><b>YOU DON'T HAVE ENOUGH MONEY TO PAY FOR YOU LIFE, YOU HAVE BEEN SLAIN BY THE SKELETON KING!</b></p></body></font></center> <br />");
	// different paths to different people's websites
	} else if(strcmp(answer, "NORTH")==0) {
		printf("<center><font size=\"4\" color=\"white\"><body><p><a href=\"http://www.cs.mcgill.ca/~mstron1/cgi-bin/addgold.cgi?gold=%d\">click here to go NORTH!</a></p></body></center></font>",goldpieces);
		printf("<center><font size=\"4\" color=\"white\"><body><p><a href=\"http://www.cs.mcgill.ca/~lzhang166/cgi-bin/addgold.cgi?gold=%d\">click here to go BACK!</a></p></body></font></center>",goldpieces);
	} else if(strcmp(answer, "SOUTH")==0) {
		printf("<center><font size=\"4\" color=\"white\"><body><p><a href=\"http://www.cs.mcgill.ca/~kkhour4/cgi-bin/addgold.cgi?gold=%d\">click here to go SOUTH!</a></p></body></center></font>",goldpieces);
		printf("<center><font size=\"4\" color=\"white\"><body><p><a href=\"http://www.cs.mcgill.ca/~lzhang166/cgi-bin/addgold.cgi?gold=%d\">click here to go BACK!</a></p></body></font></center>",goldpieces);
    } else if(strcmp(answer, "EAST")==0) {
		printf("<center><font size=\"4\" color=\"white\"><body><p><a href=\"http://www.cs.mcgill.ca/~mtotar/cgi-bin/addgold.cgi?gold=%d\">click here to go EAST!</a></p></body></center></font>",goldpieces);
		printf("<center><font size=\"4\" color=\"white\"><body><p><a href=\"http://www.cs.mcgill.ca/~lzhang166/cgi-bin/addgold.cgi?gold=%d\">click here to go BACK!</a></p></body></font></center>",goldpieces);
    } else if(strcmp(answer, "WEST")==0) {
		printf("<center><font size=\"4\" color=\"white\"><body><p><a href=\"http://www.cs.mcgill.ca/~akermo/cgi-bin/addgold.cgi?gold=%d\">click here to go WEST!</a></p></body></center></font>",goldpieces);
		printf("<center><font size=\"4\" color=\"white\"><body><p><a href=\"http://www.cs.mcgill.ca/~lzhang166/cgi-bin/addgold.cgi?gold=%d\">click here to go BACK!</a></p></body></font></center>",goldpieces);
    // display the current amount of gold a player has
	} else if(strcmp(answer, "GOLD")==0) {
		printf("<center><font size=\"4\" color=\"white\"><body><p>You currently have %d gold</p></body></font></center> <br />",goldpieces);
		printf("<center><font size=\"4\" color=\"white\"><body><p><a href=\"http://www.cs.mcgill.ca/~lzhang166/cgi-bin/addgold.cgi?gold=%d\">click here to go BACK!</a></p></body></font></center>",goldpieces);
	// processing the answers, if the answer is correct goldpieces get added by 10, else it gets subtracted by 5
	} else {
			if(strcmp(answer, solution)==0) {
					printf("<center><font size=\"4\" color=\"white\"><body><p>Answer is correct! You received 10 gold pieces</p></body></font></center> <br />");
					goldpieces+=10;
					printf("<center><font size=\"4\" color=\"white\"><body><p><a href=\"http://www.cs.mcgill.ca/~lzhang166/cgi-bin/addgold.cgi?gold=%d\">click here to go BACK!</a></p></body></font></center>",goldpieces);
			} else {
					printf("<center><font size=\"4\" color=\"white\"><body><p>Answer is wrong! The almighty skeleton king takes 5 gold pieces from you</p></body></font></center> <br />");
					goldpieces-=5;
					printf("<center><font size=\"4\" color=\"white\"><body><p><a href=\"http://www.cs.mcgill.ca/~lzhang166/cgi-bin/addgold.cgi?gold=%d\">click here to go BACK!</a></p></body></font></center>",goldpieces);
			}
	}
			
	
	printf("</html>");

	return 0;	
}

// NAME: Luke Zhang
// ID: 260771133