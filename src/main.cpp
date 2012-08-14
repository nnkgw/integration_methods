#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum eMethod{
  eIdeal,
  eEuler,
  eVerlet,

  eNum,
};

struct sVector2{
  double x;
  double y;
};

int main (int argc, const char * argv[]) {
  eMethod method   = eIdeal;
  int     step_num = 60;
  if (argc < 2){ // parse args
    printf("usage:integration verlet 60\n");
    exit(-1);
  }else{
    if (strncmp(argv[1], "euler" , 6) == 0) { method = eEuler;  }
    if (strncmp(argv[1], "verlet", 6) == 0) { method = eVerlet; }
    sscanf(argv[2], "%d", &step_num);
  }
  double dt = 1.0 / (double(step_num) / 10.0);

  sVector2 position = {  0.0,  0.0 };
  sVector2 velocity = { 10.0, 49.0 };

  sVector2 prev_position;
  sVector2 prev_velocity;
  sVector2 next_position;
  sVector2 next_velocity;

  double t =  0.0;
  double g = -9.8;

  printf("# time position.y\n");
  printf("%f %f\n", t, position.y);

  switch(method) {
  case eIdeal:
       for(int i = 0; i < step_num; i++) {
         t += dt;
         position.x = velocity.x * t;
         position.y = velocity.y * t + 0.5 * g * (t*t);
         printf("%f %f\n", t, position.y);
       }
       break;
  case eEuler:
       for(int i = 0; i < step_num; i++) {
         t += dt;
         velocity.x  = velocity.x;
         velocity.y += g * dt;
         position.x += velocity.x * dt;
         position.y += velocity.y * dt;
         printf("%f %f\n", t, position.y);
       }       
       break;
  case eVerlet:
       for(int i = 0; i < step_num; i++) {
         t += dt;
         if (i ==0) {
           velocity.y += g * dt;
           next_position.x = position.x + velocity.x * dt; // first step
           next_position.y = position.y + velocity.y * dt;
         }
         prev_position = position;
         position = next_position;
         next_position.x = 2.0 * position.x - prev_position.x;
         next_position.y = 2.0 * position.y - prev_position.y + g * (dt * dt);
         printf("%f %f\n", t, position.y);
       }
       break;
  }
  return 0;
}

