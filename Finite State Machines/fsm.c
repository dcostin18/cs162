#include <string.h>
#include <stdio.h>

typedef struct Transition
{
    char* init_state;
    char* combo_state;
    char* final_state;
} *transition;


transition new_transition(char* is,char* cs, char* fs)
{
    transition tor = (transition) malloc(sizeof(struct Transition));
    tor->init_state = is;
    tor->combo_state = cs;
    tor->final_state = fs;

    return tor;
}

void extract_fill_trans(char* string, int fields, transition* arr)
{
    char* start = string;
    char* end;
    int index = 0;

    //store initial state
    end = strchr(start, ':');
    char* init_state = (char*) malloc(256*sizeof(char));
    strncpy(init_state, start, end-start);
    start = end+1;

    //chop off initial state
    char* newstr = (char*) malloc(256*sizeof(char));
    strncpy(newstr, start, strlen(string)-strlen(newstr));

    for(int i=0; i<fields; i++)
    {
        end = strchr(newstr, ':');
        char* combo_state[256];
        strncpy(newstr, start, end-start);
        start = end+1;

        end = strchr(newstr, ' ');
        char* final_state[256];
        strncpy(newstr, start, end-start);
        start = end+1;
        end = strchr(newstr, ' ');

        arr[i] = new_transition(init_state, combo_state, final_state);

    }

    return;

}

int countFields(char* string)
{
    char * start = string;
    char * end;
    int count=1;
    while ( ( end = strchr( start, ',' ) ) != NULL )
    {
        start = end + 1;
        count++;
    }
    printf("Fields = %d\n", count);
    return count;
}


void fill_states(char* filename, char** arr)
{
    char* line = NULL;
    size_t len = 0;
    ssize_t read;
    FILE* fp;

    fp = fopen(filename, "r");
    int begin_read = 0;
    while((read = getline(&line, &len, fp))!=-1)
    {
        if(strstr(line, "[states]")!=NULL)
        {
            begin_read=1;
            continue;
        }
        else if(strstr(line, "[transitions]")!=NULL) begin_read = 0;
        else if(begin_read==0) continue;
        else if(strstr(line, "names:")!=NULL)
        {
            extract_fill_trans(line, countFields(line), arr);
            
        }

    }
}

void fill_transitions(char* filename, transition* arr)
{
    char* line = NULL;
    size_t len = 0;
    ssize_t read;
    FILE* fp;

    fp = fopen(filename, "r");
    int begin_read = 0;
    while((read = getline(&line, &len, fp))!=-1)
    {
        if(strstr(line, "[transitions]")!=NULL)
        {
            begin_read=1;
            continue;
        }
        else if(strstr(line, "[states]")!=NULL) begin_read = 0;
        else if(begin_read==0) continue;
        else if(strstr(line, ":")!=NULL)
        {
            extract_fill_trans(line, countFields(line), arr);
            
        }

    }
}

int main(int argc, char** argv)
{
    char* filename = argv[1];
    FILE* fp;
    char* line = NULL;
    size_t len = 0;
    ssize_t read;
    char c;


    transition* arr[256];
    char** states[256];
    fill_transitions(filename, arr);
    fill_states(filename, states);


    fp = fopen(filename, "r");
    char* state = states[0];
    while(c = fgetc(fp)!=EOF)
    {
        int match = 0;
        for(int i=0; i<256; i++)
        {
            if(states[0] == c)
            {
                int index = strchr(arr[i], ':');
                char* substr[256];
                strncpy(substr, arr[i], 1);
                state = substr;

            }
        }
    }

    if(state == states[0]) printf("Accept");
    else printf("Reject.");

    fclose(fp);
    if(line)
        free(line);

}