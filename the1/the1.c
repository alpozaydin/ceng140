#include<stdio.h>

int is_matching(int cursor, char* sequence,char letter) {
    switch (letter) {
        case 'g': 
            if ((sequence[cursor] == 'C') && (sequence[cursor + 1] == 'C')){
                return 1;
            }
            break;
        case 'a': 
            if ((sequence[cursor] == 'C') && (sequence[cursor + 1] == 'G')){
                return 1;
            }
            break;
        case 'v': 
            if ((sequence[cursor] == 'C') && (sequence[cursor + 1] == 'A')){
                return 1;
            }
            break;
        case 'i': 
            if ((sequence[cursor] == 'T') && (sequence[cursor + 1] == 'A') && (sequence[cursor + 2] != 'C')){
                return 1;      
            }
            break;
        case 'l': 
            if ((sequence[cursor] == 'A') && (sequence[cursor + 1] == 'A') && (sequence[cursor + 2] == 'T' || sequence[cursor + 2] == 'C')){
                return 1;      
            }
            else if ((sequence[cursor] == 'G') && (sequence[cursor + 1] == 'A'))
            {
                return 1;
            }
            break;
        case 's': 
            if ((sequence[cursor] == 'A') && (sequence[cursor + 1] == 'G')){
                return 1;      
            }
            else if ((sequence[cursor] == 'T') && (sequence[cursor + 1] == 'C') && ((sequence[cursor + 2] == 'A') || (sequence[cursor + 2] == 'G')))
            {
                return 1;
            }         
            break;
        case 't': 
            if ((sequence[cursor] == 'T') && (sequence[cursor + 1] == 'G')){
                return 1;      
            }
            break;
        case 'p': 
            if ((sequence[cursor] == 'G') && (sequence[cursor + 1] == 'G')){
                return 1;      
            }
            break;
        case 'd':
            if ((sequence[cursor] == 'C') && (sequence[cursor + 1] == 'T') && (sequence[cursor + 2] == 'A' || sequence[cursor + 2] == 'G')){
                return 1;      
            }
            break;
        case 'e':
             if ((sequence[cursor] == 'C') && (sequence[cursor + 1] == 'T') && (sequence[cursor + 2] == 'T' || sequence[cursor + 2] == 'C')){
                return 1;      
            }
            break;
        case 'k': 
            if ((sequence[cursor] == 'T') && (sequence[cursor + 1] == 'T') && (sequence[cursor + 2] == 'T' || sequence[cursor + 2] == 'C')){
                return 1;      
            }
            break;
        case 'r':
            if ((sequence[cursor] == 'G') && (sequence[cursor + 1] == 'C')){
                return 1;      
            }
            else if ((sequence[cursor] == 'T') && (sequence[cursor + 1] == 'C') && (sequence[cursor + 2] == 'T' || sequence[cursor + 2] == 'C'))
            {
                return 1;
            }
            break;
        case 'n': 
            if ((sequence[cursor] == 'T') && (sequence[cursor + 1] == 'T') && (sequence[cursor + 2] == 'A' || sequence[cursor + 2] == 'G')){
                return 1;      
            }
            break;
        case 'q':
            if ((sequence[cursor] == 'G') && (sequence[cursor + 1] == 'T') && (sequence[cursor + 2] == 'T' || sequence[cursor + 2] == 'C')){
                return 1;      
            }
            break;
        case 'c': 
            if ((sequence[cursor] == 'A') && (sequence[cursor + 1] == 'C') && (sequence[cursor + 2] == 'A' || sequence[cursor + 2] == 'G')){
                return 1;      
            }
            break;
        case 'm': 
            if ((sequence[cursor] == 'T') && (sequence[cursor + 1] == 'A') && (sequence[cursor + 2] == 'C')){
                return 1;      
            }
            break;
        case 'w': 
            if ((sequence[cursor] == 'A') && (sequence[cursor + 1] == 'C') && (sequence[cursor + 2] == 'C')){
                return 1;      
            }
            break;
        case 'f': 
            if ((sequence[cursor] == 'A') && (sequence[cursor + 1] == 'A') && (sequence[cursor + 2] == 'A' || sequence[cursor + 2] == 'G')){
                return 1;      
            }
            break;
        case 'y': 
            if ((sequence[cursor] == 'A') && (sequence[cursor + 1] == 'T') && (sequence[cursor + 2] == 'A' || sequence[cursor + 2] == 'G')){
                return 1;      
            }
            break;
        case 'h': 
            if ((sequence[cursor] == 'G') && (sequence[cursor + 1] == 'T') && (sequence[cursor + 2] == 'A' || sequence[cursor + 2] == 'G')){
                return 1;      
            }
            break;
        case '.':
            if ((sequence[cursor] == 'A') && (sequence[cursor + 1] == 'T') && (sequence[cursor + 2] == 'T' || sequence[cursor + 2] == 'C')){
                return 1;      
            }
            else if ((sequence[cursor] == 'A') && (sequence[cursor + 1] == 'C') && (sequence[cursor + 2] == 'T'))
            {
                return 1;
            }
            break;
        default: 
            break;
    } 
    return 0;
}


char sequence[3000];
char chain[3000];
int length_sequence, length_chain;


int main()
{
    
    int i = 0;
    int n = 0;
    char ch;

    int start_cursor;
    int end_cursor;
    int aa_index;
    int aa_index_end;
    int exon1_index[2] = {0, 0};
    int exon2_index[2] = {0, 0};
    int exon3_index[2] = {0, 0};
    int intron1[2] = {0, 0};
    int intron2[2] = {0, 0};
    start_cursor = 0;
    aa_index = 0;
    
       
    while ((ch = getchar()) != '.'){
        if (ch != ' ' && ch != '\n' && ch != '\t'){ 
            sequence[i] = ch;
            i++;
        }
    }
    sequence[i] = '\0'; 
    length_sequence = i - 1;


    while ((ch = getchar()) != '.'){
        if (ch != ' ' && ch != '\n' && ch != '\t'){ 
            chain[n] = ch;
            n++;
        }
    }
    chain[n] = '.'; 
    chain[n + 1] = '\0'; 
    length_chain = n;
    
    exon3_index[1] = length_sequence;
    
    while (is_matching(start_cursor, sequence, chain[aa_index]))
    {
        start_cursor += 3;
        aa_index += 1;
    }
    exon1_index[1] = start_cursor - 1; 

    end_cursor = length_sequence - 2;
    aa_index_end = length_chain;
    while (is_matching(end_cursor, sequence, chain[aa_index_end]))
    {
        end_cursor -= 3;
        aa_index_end -= 1;
    }
    exon3_index[0] = end_cursor + 3;

    if (exon3_index[0] > exon3_index[1] || exon1_index[1] < 0) 
    {
        printf("NONE\n");
        return 0;
    }


    if (aa_index - 1 >= aa_index_end)
    {
        int temp_start = exon1_index[1] + 1; 
        int temp_end = exon3_index[0] - 3;
        int temp_aa_index = aa_index - 1;
        
        if (aa_index - 1 - aa_index_end >= 1) /* if they overlap ---> lenght - aa_end + aa_start = total aminoacid found || lenght + 1 = total aminoacid number -> aa_start - aa_end - 1 = redundant*/
        {   
            int redundant;
            redundant = aa_index - aa_index_end - 1;
            if (redundant % 2 == 1)
            {
                exon1_index[1] -= 3 * ((redundant + 1) / 2);
                exon3_index[0] += 3 * ((redundant + 1) / 2);
                temp_start = exon1_index[1] + 2;
                temp_end = exon3_index[0] - 2;
                while (temp_end >= temp_start)
                {
                    if (is_matching(temp_start, sequence, chain[aa_index - ((redundant + 1) / 2)]))
                    {
                        exon2_index[0] = temp_start;
                        exon2_index[1] = temp_start + 2;
                        intron1[0] = exon1_index[1] + 1;
                        intron1[1] = exon2_index[0] - 1;
                        intron2[0] = exon2_index[1] + 1;
                        intron2[1] = exon3_index[0] - 1;
                        printf("%d %d %d %d\n", intron1[0], intron1[1], intron2[0], intron2[1]);
                        return 0;
                    }
                    temp_start += 1;
                } printf("NONE"); return 0;
            } else
            {
                exon1_index[1] -= 3 * ((redundant + 2) / 2);
                exon3_index[0] += 3 * ((redundant) / 2);
                temp_start = exon1_index[1] + 2;
                temp_end = exon3_index[0] - 2;
                while (temp_end >= temp_start)
                {
                    if (is_matching(temp_start, sequence, chain[aa_index - ((redundant + 1) / 2)]))
                    {
                        exon2_index[0] = temp_start;
                        exon2_index[1] = temp_start + 2;
                        intron1[0] = exon1_index[1] + 1;
                        intron1[1] = exon2_index[0] - 1;
                        intron2[0] = exon2_index[1] + 1;
                        intron2[1] = exon3_index[0] - 1;
                        printf("%d %d %d %d\n", intron1[0], intron1[1], intron2[0], intron2[1]);
                        return 0;
                    }
                    temp_start += 1;
                }
            }
        }
        
        while (temp_start < temp_end)
        {
            if (is_matching(temp_start, sequence, chain[temp_aa_index]))
            {
                break;
            } else
            {
                temp_start += 1;
            }
        }
        if (temp_end > temp_start)
        {
            exon2_index[0] = temp_start;
            exon2_index[1] = temp_start + 2;
            exon1_index[1] -= 3;
        } else 
        {   
            int temp_start = exon1_index[1] + 1;
            int temp_end = exon3_index[0] - 3;
            int temp_aa_index = aa_index_end + 1;
            while (temp_start < temp_end)
            {
                if (is_matching(temp_end, sequence, chain[temp_aa_index]))
                {
                    break;
                } else
                {
                    temp_end -=1;
                }
            }
            if (temp_end > temp_start)
            {
            exon2_index[0] = temp_end;
            exon2_index[1] = temp_end + 2;
            exon3_index[0] += 3;
            
            } else
            {
                printf("NONE\n");
                return 0;
            }
            
        }
        intron1[0] = exon1_index[1] + 1;
        intron1[1] = exon2_index[0] - 1;
        intron2[0] = exon2_index[1] + 1;
        intron2[1] = exon3_index[0] - 1;
        printf("%d %d %d %d\n", intron1[0], intron1[1], intron2[0], intron2[1]);
    }
    
    else 
    {
        while (start_cursor <= end_cursor)
        {
            int temp_start = start_cursor;
            int temp_aa_index = aa_index;
            int temp_aa_index_end = aa_index_end;
            while (is_matching(temp_start, sequence, chain[temp_aa_index]) && temp_start < start_cursor + 3 * (aa_index_end - aa_index + 1))
            {
                temp_start += 3;
                temp_aa_index += 1;
            }
            if (temp_aa_index > temp_aa_index_end)
            {
                exon2_index[0] = start_cursor;
                exon2_index[1] = start_cursor + (3 * (aa_index_end - aa_index + 1)) - 1;
                intron1[0] = exon1_index[1] + 1;
                intron1[1] = exon2_index[0] - 1;
                intron2[0] = exon2_index[1] + 1;
                intron2[1] = exon3_index[0] - 1;
                printf("%d %d %d %d\n", intron1[0], intron1[1], intron2[0], intron2[1]);
                return 0;
            }
            start_cursor += 1;
        }
        printf("NONE\n");
        return 0;
    }
    
}