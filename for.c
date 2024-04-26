// #include <stdio.h>

// int main() {
//     int days, rooms;
    
//     // prompt the user to input the number of days and rooms
//     printf("Enter the number of days: ");
//     scanf("%d", &days);
//     printf("Enter the number of rooms: ");
//     scanf("%d", &rooms);
    
//     // create a 2-dimensional array to store the availability of rooms
//     int availability[days][rooms];
    
//     // prompt the user to input the availability of rooms for each day
//     for (int i = 0; i < days; i++) {
//         printf("Day %d:\n", i+1);
//         for (int j = 0; j < rooms; j++) {
//             printf("Room %d: ", j+1);
//             scanf("%d", &availability[i][j]);
//         }
//     }
    
//     // print out the availability of rooms for each day
//     printf("Availability of rooms:\n");
//     for (int i = 0; i < days; i++) {
//         printf("Day %d: ", i+1);
//         for (int j = 0; j < rooms; j++) {
//             printf("%d ", availability[i][j]);
//         }
//         printf("\n");
//     }
    
//     return 0;
// }
#include <stdio.h>

int main()
{
    int A[7] = {0,0,0,0,0,0,0};
    int n ;
    scanf("%d", &n);
    int r;
    scanf("%d",&r);
    int tot_rooms = 10;
    int i;
    for(i = 0;i<n;i++){
        A[i] = r;
    }

    for(i=0; i<7; i++){
        printf("%d \t %d \n ",i+1, (10-A[i]));
    }

    return 0;
}
