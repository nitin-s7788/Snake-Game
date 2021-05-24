#include<iostream>
#include<windows.h>
#include<conio.h>     // for _kbhit()
#include<cstdlib>    // for random number
#include<ctime>      // for random number
#include<process.h>

using namespace std;

int score = 0;
bool not_game_over = true;

class coordinate
{
    public :
    int x, y;
    coordinate(int y, int x)
    {
        this->y = y;
        this->x = x;
    }
    coordinate()
    {

    }
};

class snake_node
{
    public :
    coordinate c;
    char ch;
    snake_node *next;
    snake_node (int y, int x)
    {
        this->c.y = y;
        this->c.x = x;
        ch = 'o';
        next = NULL;
    }
    snake_node ()
    {
        next = NULL;
    }
} ;

class head_tail_pair
{
    public :
    snake_node * H;
    snake_node * T;

    head_tail_pair( snake_node *H, snake_node *T)
    {
        this->H = H;
        this->T = T;
    }
};

void gotoxy(short int x, short int y)
{
    COORD c = { x, y};
    SetConsoleCursorPosition( GetStdHandle( STD_OUTPUT_HANDLE), c);
}

// this function should writen before move_snake() function, as this is called inside it.
void generate_food (char stage_snake[17][75])
{
    int y,x;
    srand(time(NULL));    // used in place of randomize function,  the use of this function is that we get different random numbers in each run.
    while (true)
    {
        y = ( rand() % 15 ) + 1;   // rand() % 15  is doing work of random(15) , generate random number between 0 to 14.
        x = ( rand() % 73 ) + 1;

        if(stage_snake[y][x] == ' ')
        {
            stage_snake[y][x] = 'X';
            break;
        }    
    }
  
}

void put_snake_in_stage(char stage_snake[17][75], snake_node * tail)
{
    snake_node* temp = tail;

    for(int i=1; i<16; i++)
    {
        for(int j=1; j<74; j++)
        {
            if(stage_snake[i][j] != 'X')
                stage_snake[i][j] = ' ';
        }
    }
    while (temp != NULL)
    {
        stage_snake[temp->c.y][temp->c.x] = temp->ch;
        temp = temp->next;
    }
}

void print_snake(char stage_snake[17][75])
{
    char snake[1500];
    int k=0;
    for(int i=1; i<16; i++)
    {
        for(int j=0; j<75; j++)
            snake[k++] = stage_snake[i][j];
        snake[k++] = '\n';
    }

    snake[k] = '\0';
    cout<<snake;
    gotoxy(32, 20);
    cout<<"SCORE : "<<score<<endl;
    for(long int i=0; i<25000000; i++);
}

bool is_not_game_over(snake_node * head)
{
    if(head->c.y == 0 || head->c.y == 16 || head->c.x == 0 || head->c.x == 74)
        return false;
    else
        return true;
}

void game_over()
{
    for(int i=0; i<31; i++)
        cout<<" ";
    cout<<"GAME   OVER"<<endl;
    getch();

}

head_tail_pair  move_snake(char stage_snake [17][75], int new_direction, snake_node * tail, snake_node * head)
{
    
    snake_node * temp_tail = tail;
    snake_node * temp_head = head;

    snake_node * new_head = NULL;
    
    bool is_food_eaten = false;

    head_tail_pair P(temp_head, temp_tail);


    tail = tail->next;
    head->ch = 'o';

    if(new_direction == 1)
    {
        if ( stage_snake[head->c.y][head->c.x+1] != 'X' && stage_snake[head->c.y][head->c.x+1] != ' ' )
        {
            game_over();
            not_game_over = false;
            return P;
        }
        
        if ( stage_snake[head->c.y][head->c.x+1] == 'X' )
            is_food_eaten = true;

        new_head = new snake_node( head->c.y, head->c.x+1);
        new_head->ch = '>';
       
    }
    else if(new_direction == 2)
    {
         if ( stage_snake[head->c.y+1][head->c.x] != 'X' && stage_snake[head->c.y+1][head->c.x] != ' ' )
        {
            game_over();
            not_game_over = false;
            return P;
        }

        if ( stage_snake[head->c.y+1][head->c.x] == 'X' )
            is_food_eaten = true;

        new_head = new snake_node( head->c.y+1, head->c.x);
        new_head->ch = 'v';
        
        for(long int i=0; i<13000000; i++);
    }
    else if(new_direction == 3)
    {
         if ( stage_snake[head->c.y][head->c.x-1] != 'X' && stage_snake[head->c.y][head->c.x-1] != ' ' )
        {
            game_over();
            not_game_over = false;
            return P;
        }

        if ( stage_snake[head->c.y][head->c.x-1] == 'X' )
            is_food_eaten = true;

        new_head = new snake_node( head->c.y, head->c.x-1);
        new_head->ch = '<';
        
    }
    else if(new_direction == 4)
    {
        if ( stage_snake[head->c.y-1][head->c.x] != 'X' && stage_snake[head->c.y-1][head->c.x] != ' ' )
        {
            game_over();
            not_game_over = false;
            return P;
        }
        if ( stage_snake[head->c.y-1][head->c.x] == 'X' )
            is_food_eaten = true;

        new_head = new snake_node( head->c.y-1, head->c.x);
        new_head->ch = '^';
        
        for(long int i=0; i<13000000; i++);
    }
    else
    {
        cout<<"UNWANTED ACTION";
        for(long int i=0; i<100000000; i++);
        not_game_over = false;
    }

    head->next = new_head;
    head = head->next;
    
    if( is_food_eaten )
    {
        tail = temp_tail;
        score++;
        generate_food (stage_snake);
    }
    else
    {
        delete temp_tail;
    }

    put_snake_in_stage( stage_snake, tail);

    P.H = head;
    P.T = tail;

    return P;
}



int main ()
{
    char ans = 'n';

    do
    {
    
    not_game_over = true;
    score = 0;

    system("CLS");

    cout<<"                            SNAKE - GAME\n";
    cout<<"                       MADE  BY  -  NITIN  SOLANKI\n";
    
    char stage_snake[17][75];
    
    for(int i=0; i<75; i++)
        cout<<"#";
    for(int i=0; i<16; i++)
        cout<<"\n";
    for(int i=0; i<75; i++)
        cout<<"#";


    int new_direction = 1; 

    for(int i=0; i<17; i++)
        for(int j=0; j<75; j++)
        {
            if( j==0 || j==74 || i==0 || i==16)
                stage_snake[i][j] = '#';
            else
                stage_snake[i][j] = ' ';
        } 

    snake_node * tail, *temp, *head; 
    temp = new snake_node(4,10);
    tail = temp;
    temp->next = new snake_node(4,11);
    temp = temp->next;
    temp->next = new snake_node(4,12);
    temp = temp->next;
    temp->next = new snake_node(4,13);
    temp = temp->next;
    temp->next = new snake_node(4,14);
    temp = temp->next;
    temp->next = new snake_node(4,15);
    temp = temp->next;
    temp->next = new snake_node(4,16);
    temp = temp->next;
    temp->ch = '>';
    head = temp;

    put_snake_in_stage (stage_snake, tail);

    gotoxy(0,3);

    generate_food(stage_snake);

    print_snake(stage_snake);

    while( is_not_game_over( head ) && not_game_over )
    {
        if(_kbhit())
        {
            
            int ch1, ch2;  // as arrow key not have a ascii values,  when pressed they returns 2 values 1.> 0 (i.e.) if ch1 == 0 [in some compilers return 224 in place of 0]
                            // arrow key pressed, and 2.> 72,75,77,80 for different arrow keys.
            ch1 = _getch();

            int temp_direction;

            if( ch1 == 0xE0)
            {
                ch2 = _getch();
                
                if(ch2 == 77)   // i.e. right
                    temp_direction = 1;
                else if(ch2 == 80)   // i.e. down
                    temp_direction = 2;
                else if(ch2 == 75)   // i.e. left
                    temp_direction = 3;
                else if(ch2 == 72)   // i.e. up
                    temp_direction = 4;
                else
                {
                    gotoxy(28, 21);
                    getch();
                    cout<<" WRONG INPUT KEY ";
                    getch();
                    break;
                }
            }
            else
            {
                gotoxy(28, 21);
                getch();
                cout<<" WRONG INPUT KEY ";
                getch();
                break;
            }
        
            
            if(temp_direction - new_direction != 2 && temp_direction - new_direction != -2)
                new_direction = temp_direction;

            head_tail_pair P = move_snake(stage_snake, new_direction, tail, head);
            head = P.H;
            tail = P.T;
            gotoxy(0,3);
            print_snake(stage_snake);

        }
        else
        {
            head_tail_pair P = move_snake(stage_snake, new_direction, tail, head);
            head = P.H;
            tail = P.T;
            gotoxy(0,3);
            print_snake(stage_snake);
        }
   
    }
    delete tail;
    delete head;
    delete temp;
    cout<<"\n WANT TO PLAY AGAIN : (y/n) : ";
    cin>>ans;
    } while (ans == 'y' || ans == 'Y');
    
    return 0;
}
