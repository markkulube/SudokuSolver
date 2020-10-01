#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv) {
		//standard input variable
        char message[2048];

        // sscanf variables
        char uid[35], stime[180], tty[180], time[180], cmd[180], copy[2048];
        int pid, ppid, c_col;

        // Counting pattern variables
        int cur_uid_counter = 0;
        char cur_process_uid[35];
        int most_uid_counter = 0;
        char most_process_uid[35];
        

    // One argument in commandline.
    if (argc == 1) {

        // Read standard input.
        while(fgets(message, 2048, stdin) != NULL) {

                // Assign ps -ef row values to variables
                // corresponding to column headers.
			   strcpy(copy, message);
			   sscanf(copy, "%s %d %d %d %s %s %s %s", uid, &pid, &ppid, &c_col, stime, tty, time, cmd);
			   //printf("%s %d %d %d %s %s %s %s\n", uid, pid, ppid, c_col, stime, tty, time, cmd);
			   
			   // Copy first uid to holder.
			   if((strcmp(cur_process_uid, "") == 0)) {
			   	strcpy(cur_process_uid, uid);
			   	cur_uid_counter += 1;
			   } else if (strcmp(cur_process_uid, uid) == 0) {
			   	cur_uid_counter += 1;

			   } else {
			   		if (cur_uid_counter > most_uid_counter) {
				   		most_uid_counter = cur_uid_counter;
				   		strcpy(most_process_uid, cur_process_uid);
			   		}
			   		cur_uid_counter = 1;
			   		strcpy(cur_process_uid, uid);
			   }    
        }

        // After while-loop exists check if 
        // the last uid has most processes.
        if(cur_uid_counter > most_uid_counter) {
			   		most_uid_counter = cur_uid_counter;
				   	strcpy(most_process_uid, cur_process_uid);
			   } 
        
    } else if ( argc == 2) {

    	int argv1 = strtol(argv[1], NULL, 10);
    	// Read standard input.
        while(fgets(message, 2048, stdin) != NULL) {

                // Assign ps -ef row values to variables
                // corresponding to column headers.
			   strcpy(copy, message);
			   sscanf(copy, "%s %d %d %d %s %s %s %s", uid, &pid, &ppid, &c_col, stime, tty, time, cmd);
			if(argv1 == ppid) {
			   // Copy first uid to local variable.
			   if((strcmp(cur_process_uid, "") == 0)) {
			   	strcpy(cur_process_uid, uid);
			   	cur_uid_counter += 1;
			   } else if (strcmp(cur_process_uid, uid) == 0) {
			   	cur_uid_counter += 1;

			   } else {
			   		if (cur_uid_counter > most_uid_counter) {
				   		most_uid_counter = cur_uid_counter;
				   		strcpy(most_process_uid, cur_process_uid);
			   		}
			   		cur_uid_counter = 1;
			   		strcpy(cur_process_uid, uid);
			   }    
        	

	        // After while-loop exists check if 
	        // the last uid has most processes.
	        if(cur_uid_counter > most_uid_counter) {
				   		most_uid_counter = cur_uid_counter;
					   	strcpy(most_process_uid, cur_process_uid);
				   }
     		}
		}
    } else {
        // This code is from lecture 18 September simple_string.c
        // We print the error message to stderr rather than the default
        // stdout (used by printf) because we want to see the error message
        // on a terminal even when we have redirected stdout.
        fprintf(stderr, "USAGE: most_processes [ppid]\n");
        return 1;   
    }
    
    printf("%s %d\n", most_process_uid, most_uid_counter);
    
    return 0;
}