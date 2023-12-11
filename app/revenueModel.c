#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

int main() {
    double quaterlyRevenue[20];
    // q = 0 is q2 2022
    double revenue = 0.0;
    int start = 1;
    double audience = 2000;
    for(int Q = 1; Q < 18; Q++) {
        
        for(double M = start; M < start +3; M++) {
            audience = audience * 4 * 0.3;
            double takehomePerc = 0.7;
            double studentMonthly = 0.07*(2.99*takehomePerc);
            double studentYearly = (0.05*22.99*takehomePerc)/12;
            double standardMonthly = 0.03*(7.99*takehomePerc);
            double standardYearly = (0.05*49.99*takehomePerc)/12;
            revenue += audience * (studentMonthly + studentYearly + standardMonthly + standardYearly);
            printf("%0.f\n", M);
            
            printf("aud: %f\n", audience);
            
            printf("rev: %f\n", revenue);
        
        }
        //double audience = 2000 * (pow(1.3, Q*3)) * 0.3;
        // printf("\naud: %f\n", audience);
        
        // printf("rev: %f\n\n", revenue);
        
        start = Q*3+1;
        quaterlyRevenue[Q-1] = revenue;
    }
    double total =0;
    double yearOneTotal=0;
    double yearTwoTotal=0;
    double yearThreeTotal=0;
    for(int k = 0; k < 16; k++) {
        int year = 0;
        int quater = 0;
        total += quaterlyRevenue[k];
        if(k < 4) { year = 2024; quater = k+1; yearOneTotal += quaterlyRevenue[k]; }
        else if(3<k && k< 8) { year = 2025; quater = k - 4; yearTwoTotal += quaterlyRevenue[k]; }
        else if(7<k) {year = 2026; quater = k-7; yearThreeTotal += (quaterlyRevenue[k]);}
        printf("Revenue for Q%d %d is: £%0.2f\n", quater, year, quaterlyRevenue[k]);
    }
    printf("\n\n\n2024 Total: £%f\n2025 Total: £%f\n2026 Total: £%f\n30 Month Total: £%f\n", yearOneTotal, yearTwoTotal-yearOneTotal, yearThreeTotal-yearTwoTotal-yearOneTotal, total);
    return 0;
}
