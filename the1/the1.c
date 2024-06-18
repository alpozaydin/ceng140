#include<stdio.h>

int addresses[4];
int is_inside_intron = 0;

int matching(char* chain, char* sequence){
    int cursor = 0;
    int intron_index = 0;
    int aa_index = 0;
    int match_found = 0; // setting the initial condition the 0=false

    while (sequence[cursor] != '\0')
    {
        int arg = chain[aa_index];
        printf("initials are (%c -> cursor = %d%c%c%c, aa_index = %d, aa = %c ) ", arg, cursor, sequence[cursor], sequence[cursor + 1], sequence[cursor + 2], aa_index, chain[aa_index]);
        match_found = 0;
        switch (arg) {
        case 'g': 
            if ((sequence[cursor] == 'C') && (sequence[cursor + 1] == 'C')){
                match_found = 1;
            }
            break;
        case 'a': 
            if ((sequence[cursor] == 'C') && (sequence[cursor + 1] == 'G')){
                match_found = 1;
            }
            break;
        case 'v': 
            if ((sequence[cursor] == 'C') && (sequence[cursor + 1] == 'A')){
                match_found = 1;
            }
            break;
        case 'i': 
            if ((sequence[cursor] == 'T') && (sequence[cursor + 1] == 'A') && (sequence[cursor + 2] != 'C')){
                match_found = 1;      
            }
            break;
        case 'l': 
            if ((sequence[cursor] == 'A') && (sequence[cursor + 1] == 'A') && (sequence[cursor + 2] == 'T' || sequence[cursor + 2] == 'C')){
                match_found = 1;      
            }
            else if ((sequence[cursor] == 'G') && (sequence[cursor + 1] == 'A'))
            {
                match_found = 1;
            }
            break;
        case 's': 
            if ((sequence[cursor] == 'A') && (sequence[cursor + 1] == 'G')){
                match_found = 1;      
            }
            else if ((sequence[cursor] == 'T') && (sequence[cursor + 1] == 'C') && ((sequence[cursor + 2] == 'A') || (sequence[cursor + 2] == 'G')))
            {
                match_found = 1;
            }         
            break;
        case 't': 
            if ((sequence[cursor] == 'T') && (sequence[cursor + 1] == 'G')){
                match_found = 1;      
            }
            break;
        case 'p': 
            if ((sequence[cursor] == 'G') && (sequence[cursor + 1] == 'G')){
                match_found = 1;      
            }
            break;
        case 'd':
            if ((sequence[cursor] == 'C') && (sequence[cursor + 1] == 'T') && (sequence[cursor + 2] == 'A' || sequence[cursor + 2] == 'G')){
                match_found = 1;      
            }
            break;
        case 'e':
             if ((sequence[cursor] == 'C') && (sequence[cursor + 1] == 'T') && (sequence[cursor + 2] == 'T' || sequence[cursor + 2] == 'C')){
                match_found = 1;      
            }
            break;
        case 'k': 
            if ((sequence[cursor] == 'T') && (sequence[cursor + 1] == 'T') && (sequence[cursor + 2] == 'T' || sequence[cursor + 2] == 'C')){
                match_found = 1;      
            }
            break;
        case 'r':
            if ((sequence[cursor] == 'G') && (sequence[cursor + 1] == 'C')){
                match_found = 1;      
            }
            else if ((sequence[cursor] == 'T') && (sequence[cursor + 1] == 'C') && (sequence[cursor + 2] == 'T' || sequence[cursor + 2] == 'C'))
            {
                match_found = 1;
            }
            break;
        case 'n': 
            if ((sequence[cursor] == 'T') && (sequence[cursor + 1] == 'T') && (sequence[cursor + 2] == 'A' || sequence[cursor + 2] == 'G')){
                match_found = 1;      
            }
            break;
        case 'q':
            if ((sequence[cursor] == 'G') && (sequence[cursor + 1] == 'T') && (sequence[cursor + 2] == 'T' || sequence[cursor + 2] == 'C')){
                match_found = 1;      
            }
            break;
        case 'c': 
            if ((sequence[cursor] == 'A') && (sequence[cursor + 1] == 'C') && (sequence[cursor + 2] == 'A' || sequence[cursor + 2] == 'G')){
                match_found = 1;      
            }
            break;
        case 'm': 
            if ((sequence[cursor] == 'T') && (sequence[cursor + 1] == 'A') && (sequence[cursor + 2] == 'C')){
                match_found = 1;      
            }
            break;
        case 'w': 
            if ((sequence[cursor] == 'A') && (sequence[cursor + 1] == 'C') && (sequence[cursor + 2] == 'C')){
                match_found = 1;      
            }
            break;
        case 'f': 
            if ((sequence[cursor] == 'A') && (sequence[cursor + 1] == 'A') && (sequence[cursor + 2] == 'A' || sequence[cursor + 2] == 'G')){
                match_found = 1;      
            }
            break;
        case 'y': 
            if ((sequence[cursor] == 'A') && (sequence[cursor + 1] == 'T') && (sequence[cursor + 2] == 'A' || sequence[cursor + 2] == 'G')){
                match_found = 1;      
            }
            break;
        case 'h': 
            if ((sequence[cursor] == 'G') && (sequence[cursor + 1] == 'T') && (sequence[cursor + 2] == 'A' || sequence[cursor + 2] == 'G')){
                match_found = 1;      
            }
            break;
        case '.':
            if ((sequence[cursor] == 'A') && (sequence[cursor + 1] == 'T') && (sequence[cursor + 2] == 'T' || sequence[cursor + 2] == 'C')){
                match_found = 1;      
            }
            else if ((sequence[cursor] == 'A') && (sequence[cursor + 1] == 'C') && (sequence[cursor + 2] == 'T'))
            {
                match_found = 1;
            }
            break;
        default: 
            break;
    } // end of the switch-case statement

    if (match_found)
    {
        printf("match_found ");
        cursor += 3;
        aa_index += 1;
        if (is_inside_intron == 1)
        {
            addresses[intron_index] = cursor - 4;
            is_inside_intron = 0;
            intron_index += 1;
        }
        
    } else { // no match found -> intron area
        printf("no_match ");
        cursor += 1;
        if (is_inside_intron == 0)
        {
            addresses[intron_index] = cursor - 1;
            is_inside_intron = 1;
            intron_index += 1;
        }
    }
    printf("last -> cursor=%d, aa_index=%d, aa = %c\n", cursor, aa_index, chain[aa_index]);
    } // end of the while loop
    return 0;
}


int main(int argc, char const *argv[])
{
    char sequence[3000];
    char chain[3000];
    int i = 0;
    int n = 0;
    char ch;

    // sequnce 
    while ((ch = getchar()) != '.'){
        if (ch != ' ' && ch != '\n' && ch != '\t'){ // creating the sequence array without any blanks
            sequence[i] = ch;
            i++;
        }
    }
    sequence[i] = '\0'; // adding the null character to the end of the string


    // aminoacid chain
    while ((ch = getchar()) != '.'){
        if (ch != ' ' && ch != '\n' && ch != '\t'){ // creating the aminoacid array without any blanks
            chain[n] = ch;
            n++;
        }
    }
    chain[n] = '.'; // to correctly detect the stop codons
    chain[n + 1] = '\0'; // adding the null character to the end of the string

    matching(chain, sequence);

    if (addresses[3] == 0)
    {
        printf("NONE\n");
    } else
    {
        for (i = 0; i < 4; i++)
    {
        printf("%d ", addresses[i]);
    }
    printf("\n");
    }
    
    return 0;
}

/*  cotrol statements
    int y=0,p=0;
    while (sequence[y])
    {
        printf("%c", sequence[y]);
        y++;
    }
    while (chain[p])
    {
        printf("%c", chain[p]);
        p++;
    }
*/