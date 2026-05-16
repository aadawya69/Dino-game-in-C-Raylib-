#include <raylib.h>

typedef struct 
{
  float x;
  float y;
  int width;
  int height;
  bool active;
}Obstacle;



int main(void)
{
  int height = 800;
  int width = 1600;
  int offset = 50;
  int offset_fordino = 90;
  int dino_vel= 2;
  int dino_pos_x = width/2;
  int dino_pos_y = height - offset_fordino;
  int dino_size_x = 50;
  int dino_size_y = 40;
  float gravity = 1.0;
  int player_left_right_vel = 4;
  float obs_x = width;
  float obs_speed = 7.0;
  int obs_size_x = 30;
  int obs_size_y = 60;
  float dino_spr_width = 0.0f;
  float dino_spr_height = 0.0f;  
  int frame_width =  44;     //Dino_sprite.width / 2;
  int frame_height =  44;       //Dino_sprite.height / 4;
  int current_frame =0;
  int frames_count = 0;
  int frame_speed = 10; 

  
  
  InitWindow(width ,height, "Dino Game");
  float ground_y = GetScreenHeight() - offset;
  float obs_y = ground_y - obs_size_y;


  Texture2D Dino_sprites[3];
  Dino_sprites[0]= LoadTexture("dino_idle1.png");
  Dino_sprites[1] = LoadTexture("dino_idle2.png");
  Dino_sprites[2] = LoadTexture("dino_idle3.png");  


  Obstacle obstacles[2];
  for (int i = 0; i <2 ; i++){
    obstacles[i].width = 30;
    obstacles[i].height = 60;
    obstacles[i].x =width + (i* 800);
    obstacles[i].y = ground_y - obstacles[i].height;
    obstacles[i].active = true;
    
    
    
  }

  SetTargetFPS(60);
 
  while(!WindowShouldClose()){
    BeginDrawing();
    dino_pos_y += dino_vel;
    dino_vel += gravity;
    frames_count ++;
    int dino_bottom = dino_pos_y + dino_size_y;

    if (dino_bottom >= ground_y){
      dino_vel = 0;

      dino_pos_y = ground_y - dino_size_y;
      if (IsKeyPressed(KEY_SPACE))
    {
      dino_vel =- 20;
      
    }
    }
    if (IsKeyDown(KEY_LEFT)){
      dino_pos_x -= player_left_right_vel;
    }
    if (IsKeyDown(KEY_RIGHT)){
      dino_pos_x += player_left_right_vel;
    }
    obs_x -= obs_speed;

    if (obs_x < - obs_size_x){
      obs_x = width;
    }

    if (frames_count >= (60/ frame_speed) ){
      frames_count =0;
      current_frame ++;

      if (current_frame > 2) current_frame =0;
    }

    for (int i = 0; i < 2; i++){
      obstacles[i].x -= obs_speed;
      if(obstacles[i].x < -obstacles[i].width)
      {
         obstacles[i].x = width + GetRandomValue(0,400);
      }
    }


    ClearBackground(RAYWHITE);
    dino_pos_y += dino_vel;
    dino_vel += gravity;

    Rectangle sourceRec ={
      0.0f,0.0f,44.0f,44.0f
    };

    Rectangle destRec = {
      (float)dino_pos_x,(float)dino_pos_y,(float)dino_size_x,(float)dino_size_y
    };
    Rectangle dinohit ={
      (float)dino_pos_x ,(float)dino_pos_y, (float)dino_size_x,(float)dino_size_y
    };

    for (int i = 0; i < 2; i++){
       Rectangle  obshitbox = {
        obstacles[i].x , obstacles[i].y , (float)obstacles[i].width ,(float)obstacles[i].height};

        if (CheckCollisionRecs(dinohit ,obshitbox)){
        dino_pos_x = 100;
        }
      
      }
       

    for (int i = 0; i < 2; i++){
      DrawRectangle(obstacles[i].x, obstacles[i].y, obstacles[i].width,obstacles[i].height,RED);
    }
    

    DrawTexturePro(Dino_sprites[current_frame],sourceRec ,destRec, (Vector2){0,0},0.0f,WHITE);
    //DrawTexture(Dino_sprite,dino_pos_x,dino_pos_y,WHITE);
    //DrawRectangle(dino_pos_x,dino_pos_y,dino_size_x,dino_size_y,GREEN);
    DrawLine(0,ground_y,width,ground_y,BLACK);
   // DrawRectangle(obs_x,obs_y,obs_size_x,obs_size_y,BROWN);
  
    EndDrawing();
  }

  
  for (int i = 0; i <3 ; i++){
    UnloadTexture(Dino_sprites[i]);
  }
 CloseWindow();
  
 

  return 0;
}