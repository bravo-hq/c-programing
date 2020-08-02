#include<stdlib.h>
#include<stdio.h>

struct _retire_info{
  int months;
  double contribution;
  double rate_of_return;
};

typedef struct _retire_info retire_info;

double calculation (int startAge,double initial,retire_info data){
   for (int i=1;i<=data.months;i++){
    printf("Age %3d month %2d you have $%.2lf\n",startAge/12,startAge%12,initial);
    initial=initial+data.rate_of_return*initial+data.contribution;
    startAge++;
  }
  return initial;
}
void retirement (int startAge,double initial,retire_info working,retire_info retired){
  initial=calculation (startAge,initial,working);
  initial=calculation (startAge+working.months,initial,retired);
}
int main(void){
  retire_info working={489,1000,.045/12};
  retire_info retired={384,-4000,.01/12};
  double initial=21345;
  int Age=327;
  retirement(Age,initial,working,retired);

  return EXIT_SUCCESS;
}
