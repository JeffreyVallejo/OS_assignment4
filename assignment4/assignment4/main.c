//
//  main.c
//  assignment4
//
//  Created by jeffrey v on 8/7/18.
//  Copyright © 2018 jeffrey v. All rights reserved.
//

#include<stdio.h>
#include<time.h>
void firstInFirstOut(void);
void leastRecentlyUsed(void);
void optimal(void);

int main()
{
    printf("\n***** Running FIFO Algorithm *****\n");
    firstInFirstOut();
    printf("\n\n***** Running LRU Algorithm *****\n");
    leastRecentlyUsed();
    printf("\n\n***** Running Optimal Algorithm *****\n");
    optimal();
    return 0;
}
void firstInFirstOut() {
    int reference_string[30];
    int page_faults = 0;
    int m, n, s;
    int pages = 5;
    int frames;


    printf("\nEnter values of Reference String:\n");
    for(m = 0; m < pages; m++)
    {
        printf("Value %d:\t", m + 1);
        scanf("%d", &reference_string[m]);
    }
    printf("\nEnter Total Number of Frames:\t");
    {
        scanf("%d", &frames);
    }
    int temp[frames];
    for(m = 0; m < frames; m++)
    {
        temp[m] = -1;
    }
    for(m = 0; m < pages; m++)
    {
        s = 0;
        for(n = 0; n < frames; n++)
        {
            if(reference_string[m] == temp[n])
            {
                s++;
                page_faults--;
            }
        }
        printf("FAULT\t");
        page_faults++;
        if((page_faults <= frames) && (s == 0))
        {
            temp[m] = reference_string[m];
        }
        else if(s == 0)
        {
            temp[(page_faults - 1) % frames] = reference_string[m];
        }
        printf("\n");
        for(n = 0; n < frames; n++)
        {
            printf("%d\t", temp[n]);
        }
    }
    printf("\nTotal Page Faults:\t%d\n", page_faults);
}

void leastRecentlyUsed () {
    int frames[30], temp[30], pages[5];
    int total_pages = 5, m, n, position = 0, k, l, total_frames;
    int a = 0, b = 0, page_fault = 0;
    printf("\nEnter Total Number of Frames:\t");
    scanf("%d", &total_frames);
    
    for(m = 0; m < total_frames; m++)
    {
        frames[m] = -1;
    }

    printf("Enter Values for Reference String:\n");
    for(m = 0; m < total_pages; m++)
    {
        printf("Value %d:\t", m + 1);
        scanf("%d", &pages[m]);
    }
    for(n = 0; n < total_pages; n++)
    {
        a = 0;
        b = 0;
        for(m = 0; m < total_frames; m++)
        {
            if(frames[m] == pages[n])
            {
                a = 1;
                b = 1;
                break;
            }
        }
        if(a == 0)
        {
            for(m = 0; m < total_frames; m++)
            {
                if(frames[m] == -1)
                {
                    frames[m] = pages[n];
                    b = 1;
                    printf("FAULT\t");
                    page_fault++;
                    break;
                }
            }
        }
        if(b == 0)
        {
            for(m = 0; m < total_frames; m++)
            {
                temp[m] = 0;
            }
            for(k = n - 1, l = 1; l <= total_frames - 1; l++, k--)
            {
                for(m = 0; m < total_frames; m++)
                {
                    if(frames[m] == pages[k])
                    {
                        temp[m] = 1;
                    }
                }
            }
            for(m = 0; m < total_frames; m++)
            {
                if(temp[m] == 0)
                    position = m;
            }
            frames[position] = pages[n];
            printf("FAULT\t");
            page_fault++;
        }
        printf("\n");
        for(m = 0; m < total_frames; m++)
        {
            printf("%d\t", frames[m]);
        }
    }
    printf("\nTotal Number of Page Faults:\t%d\n", page_fault);
}


void optimal() {
    
    int reference_string[30], frames[25], interval[25];
    int pages, total_frames, page_faults = 0;
    int m, n, temp, flag, found;
    int position = 0, maximum_interval, previous_frame = -1;
    printf("\nEnter Total Number of Pages:\t");
    scanf("%d", &pages);
    printf("\nEnter Values of Reference String\n");
    for(m = 0; m < pages; m++)
    {
        printf("Value %d:\t", m + 1);
        scanf("%d", &reference_string[m]);
    }
    printf("\nEnter Total Number of Frames:\t");
    scanf("%d", &total_frames);
    for(m = 0; m < total_frames; m++)
    {
        frames[m] = -1;
    }
    for(m = 0; m < pages; m++)
    {
        flag = 0;
        for(n = 0; n < total_frames; n++)
        {
            if(frames[n] == reference_string[m])
            {
                flag = 1;
                printf("\t");
                break;
            }
        }
        if(flag == 0)
        {
            if (previous_frame == total_frames - 1)
            {
                for(n = 0; n < total_frames; n++)
                {
                    for(temp = m + 1; temp < pages; temp++)
                    {
                        interval[n] = 0;
                        if (frames[n] == reference_string[temp])
                        {
                            interval[n] = temp - m;
                            break;
                        }
                    }
                }
                found = 0;
                for(n = 0; n < total_frames; n++)
                {
                    if(interval[n] == 0)
                    {
                        position = n;
                        found = 1;
                        break;
                    }
                }
            }
            else
            {
                position = ++previous_frame;
                found = 1;
            }
            if(found == 0)
            {
                maximum_interval = interval[0];
                position = 0;
                for(n = 1; n < total_frames; n++)
                {
                    if(maximum_interval < interval[n])
                    {
                        maximum_interval = interval[n];
                        position = n;
                    }
                }
            }
            frames[position] = reference_string[m];
            printf("FAULT\t");
            page_faults++;
        }
        for(n = 0; n < total_frames; n++)
        {
            if(frames[n] != -1)
            {
                printf("%d\t", frames[n]);
            }
        }
        printf("\n");
    }
    printf("\nTotal Number of Page Faults:\t%d\n", page_faults);
}
