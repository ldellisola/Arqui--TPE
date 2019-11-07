#include "./include/Game.h"
int X = 0;
int Y = 1;
int XMIDDLE = SCREEN_WIDTH/2;                       //la mitad en x de la panalla
int YMIDDLE = SCREEN_HEIGHT/2;                      //la mitad  en y de la pantalla
int R_BLOCKS = 4;                                   //Cantidad de filas de bloques
int C_BLOCKS = 5;                                   //Cantidad de columnas de bloques
int bar_vel= 1;                                     //velocidad de la barra 
int LIVESi = 3;                                     //cantidad de vidas al iniciar el juego    
int lives;                                          //cantidad de vidas que tiene
int blocks[R_BLOCKS][C_BLOCKS];                     //matriz de los bloques
int ball_pos[2];                                    //pelota en el medio de ls pantalla
int ball_vel;                                       //la velocidad cuenta de a cuantos cuadraditos se mueve
int pos_bar;


int runGame(void){
    
    lives = LIVESi;                     
    blocks[R_BLOCKS][C_BLOCKS];         
    ball_pos[]={XMIDDLE, YMIDDLE};      
    ball_vel=1;                         
    pos_bar = XMIDDLE;
    ball_direc = D;

    //pongo la matriz de bloques todos en uno, (osea que estan)
    for(int i = 0; i < C_BLOCKS ; i++){
        for(int j = 0; j < R_BLOCKS; j++){
            blocks[i][j]= 1;
        }
    }

    /*Inicializo el juego con el estado inicial: 
        status= .pos_barra(x)
                .matrizDeBloques(si esta en 1, sino en 0)
                .pos de pelota(x,y)
                .velocidad de la pelota
                .direccion de pelota (6 posibilidades)
                .cantidad de vidas
    */
    
    
    startGame(pos_bar, blocks, ball_pos, ball_vel, ball_direc, lives);      //inicializa el juego(empieza a pintar la pantalla)
    
    return 0;
}

 //juega recursivamente

int startGame(int bar_pos,int[R_BLOCKS][C_BLOCKS] blocks, int [2] ball_pos, int ball_vel, ballDirec ball_direc, int lives){
    if(stopKeyPressed()){ //cambiar al menu principal
        mainMenu();
    }

    int block[3];                       // block[0]=posX de bloque que choco, block[1]=posY, block[2]=lado que choco del bloque;
    print_ball(ball_pos);
    print_blocks(blocks);
    print_bar(bar_pos);


    /*MOVIMIENTO DE LA BARRA*/
        //barHitWall devuelve un int que representa que pared esta chocando (enum walls)
    if(left_arrow_pressed()){
       if(!barHitWall() || barHitWall() == RIGHT){      
             bar_pos  -= bar_vel;                     //muevo la barra para la izquierda
       }
    }
    if(right_arrow_pressed()){
        if(!barHitWall() || barHitWall() == LEFT){
            bar_pos += bar_vel;                     //muevo la barra para la derecha
        }
    }

    /*MOVIMIENTO DE LA PELOTA*/
        //si pega contra una pared
    switch(wall = ballHitWall()){
        case NONE:
            ball_move();
        case FLOOR:
            lives -=1; 
            ball_pos[]={XMIDDLE, YMIDDLE};
            ball_direc= D;
            pos_bar = XMIDDLE;
            break;
        case LEFT:    
        case RIGHT:
        case UPPER:
            invertDirection(wall);
            ball_move();
            break;
    }
    //si pega contra un bloque
    block=ballHitBlock();
    if(block != NO_BLOCK){      //NO_BLOCK[]={-1,-1,-1}?
        blocks[block[0]][block[1]]=0;
        invertDirection(block[2]); //acordarse que si pega en la derecha tiene que devolver wall = LEFT
        ball_move();
    }else{
        ball_move();
    }
    //Si pega en la barra
    if(bar_side = ballHitBar()){
        ballHitBarChangeDireccion(bar_side);
        ball_move();
    }else{
        ball_move();
    }
    startGame(pos_bar, blocks, ball_pos, ball_vel, ball_direc, lives);
}

void print_blocks(int[R_BLOCKS][C_BLOCKS] blocks){
    for(int i = 0; i < C_BLOCKS ; i++){
        for(int j = 0; j < R_BLOCKS; j++){
            if( blocks[i][j] == 1){
                print_block(i*BLOCK_WIDTH + BLOCK_XSEPARATION, j*BLOCK_HEIGHT + BLOCK_YSEPARATION);
            }
        }
    }
}

void ballHitBarChangeDireccion(barSides side){
    //enum ballDirec{LU, U, RU, RD,D, LD}ball_direc
    switch(side){
        case L:
            ball_direc = LD;
            break;
        case R:
            ball_direc = RD;
            break;
        case UL:
            ball_direc = LU;
            break;
        case UM:
            ball_direc = U;
            break;
        case UR:
            ball_direc = RU;
            break;
    }
}

void ballMove(){
    switch(ball_direc){
        case LU:
            ball_pos[X] -= ( ball_vel * 0,7071); 
            ball_pos[Y] += ( ball_vel * 0,7071);
            break;
        case U:
            ball_pos[Y] += ball_vel;  
            break;
        case RU:
            ball_pos[X] += ( ball_vel * 0,7071); 
            ball_pos[Y] += ( ball_vel * 0,7071);
            break;
        case RD:
            ball_pos[X] += ( ball_vel * 0,7071); 
            ball_pos[Y] -= ( ball_vel * 0,7071);
            break;
        case D: 
            ball_pos[Y] += ball_vel * 0,7071;
            break;
        case LD:
            ball_pos[X] -= ( ball_vel * 0,7071); 
            ball_pos[Y] -= ( ball_vel * 0,7071);
            break;
    } 
}
//{LU, U, RU, RD, D, LD}ball_direc;


//walls{NONE = 0, LEFT, RIGHT, UPPER, FLOOR}wall; 

void invertDirection(walls wall){
    switch(wall){
        case LCORNER:
            ball_direc = RD;
        break;
        case RCORNER = LD;
        case LEFT:
            switch(ball_direc){
                case LU:
                    ball_direc = RU;
                break;
                case LD:
                    ball_direc = RD;
                break;
            }
        break;
        case RIGHT:
            switch(ball_direc){
                case RU:
                    ball_direc = LU;
                break;
                case RD:
                    ball_direc = LD;
                break;
            }
        break;
        case UPPER:
            switch(ball_direc){
                case LU:
                    ball_direc = LD;
                break;
                case RU:
                    ball_direc = RD;
                break;
                case U:
                    ball_direc = D;
                break;
            }
        break;
        //FLOOR SOLO PASA CON LOS BLOQUES(la parte de arriba)
        case FLOOR:
            switch(ball_direc){
                case LD:
                    ball_direc = LU;
                break;
                case RD:
                    ball_direc = RU;
                break;
                case D:
                    ball_direc = U;
                break;
            }
        break;

    }
}

walls ballHitWall(){
    if((ball_pos[x] + BALL_RADIO) == SCREEN_WIDTH && (ball_pos[Y] - BALL_RADIO)== 0){
        return RCORNER;
    }
    if((ball_pos[x] - BALL_RADIO) == 0 && (ball_pos[Y] - BALL_RADIO)== 0){
        return LCORNER;
    }
    if(ball_pos[X] + BALL_RADIO == SCREEN_WIDTH ){
        return RIGHT;
    }
    if(ball_pos[X] - BALL_RADIO == 0){
        return LEFT;
    }
    if(ball_pos[Y] + BALL_RADIO == SCREEN_HEIGHT){
        return FLOOR;
    }
    if(ball_pos[Y] - BALL_RADIO == 0 ){
        return UPPER;
    }
}

/* funciones a hacer=
    .bool stopKeyPressed()
    .bool left_arrow_pressed()
    .bool right_arrow_pressed()
    .walls barHitWall()                     devuelve el wall, (enum walls)
    .walls ballHitWall()                              ""
    .int[3] ballHitBlock()                  devuelve la pos del block o {-1,-1,-1} si no le pego a nada, resta  blocks_left -=1;
    .print_ball(ball_pos)
    .print_bar(bar_pos) 
    .mainMenu()                             seria la funcion que se corre para mostrar si elegir la terminal o el juego
en el if 0=false; 1=true  SORRY TAMI SOY UN DESASTRE

