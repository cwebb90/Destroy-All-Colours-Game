/*Christopher Webb
Project PRJ254
Final Project
main.cpp*/

#include "Entity.h"
#include "Player.h"
#include "Ball.h"
#include "Level.h"
#include <string>
#include <iostream>
#include <conio.h>
#include <vector>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h> 
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>


using namespace std;

// Function declarations
int initialise_allegro();
void process_events();
 
// Global variables
enum KEYS_PRESSED_LIST
{
   KEY_ESCAPE, KEY_A, KEY_S, KEY_D, KEY_SPACE, SIZE_OF_KEYS_PRESSED_ENUM
};

int movewait = 0;

bool keys_pressed[SIZE_OF_KEYS_PRESSED_ENUM];

bool gamestart = true;
bool gamelost = false;
bool gamewon = false;
bool gameover = false;

int gamestate = 0; 

int ballsremaining = 0;	//added after difficulty testing due to addition request

ALLEGRO_DISPLAY* display = NULL;
ALLEGRO_FONT* big_font = NULL;
ALLEGRO_EVENT_QUEUE* event_queue = NULL;

//sound and music
ALLEGRO_SAMPLE *maintheme=NULL;
ALLEGRO_SAMPLE_INSTANCE *mainthemeinstance=NULL;
ALLEGRO_SAMPLE *balldropsound=NULL;
ALLEGRO_SAMPLE *ballfallensound=NULL;
ALLEGRO_SAMPLE *ballcombinedsound=NULL;
ALLEGRO_SAMPLE *powerupsound=NULL;
ALLEGRO_SAMPLE *winsound=NULL;
ALLEGRO_SAMPLE *losesound=NULL;

ALLEGRO_SAMPLE_INSTANCE *sampleInstance = NULL;

//allegro timer
ALLEGRO_TIMER *timer = NULL;		//using an allegro timer allows us to make the game run smoothly
int frames_per_second = 60;			//it allows us to create a stable framerate by associating it with event queues

int balldropwait = 0;

bool update_logic = true;			//these variables allow us to update the game logic and the game rendering seperately 
bool render_frame = true;			
int consecutive_logic_updates = 0;
int max_consecutive_logic_updates = 10;


//main starts here
int main()
{

	al_init();				//i need to call these first as my entire game relies upon the allegro library
	initialise_allegro();	//initialise allegro


	//font stuff
	al_init_font_addon();	//these allow me to use text and fonts in the game
    al_init_ttf_addon();	

	big_font = al_load_ttf_font("assets/8BIT WONDER.TTF", 25 ,0); //this checks that the fonts have been loaded and displays an error message if they have not been loaded correctly
	if (!big_font) 
	{
		cout << "Big Font creation failed" << endl;
		cout << "Press any key to exit" << endl;
		_getch();
		al_destroy_font(big_font);
		al_destroy_display(display);
		return -1;
	 }

	//level1 background
	ALLEGRO_BITMAP* background = al_load_bitmap("assets/allegro_background1.bmp");// bitmap to display behind the level
	ALLEGRO_BITMAP* background2 = al_load_bitmap("assets/allegro_background2.bmp");// bitmap to display behind the level
	ALLEGRO_BITMAP* background3 = al_load_bitmap("assets/allegro_background3.bmp");// bitmap to display behind the level

	//win/lose/start messages to display
	ALLEGRO_BITMAP* startgame = al_load_bitmap("assets/start.bmp");
	ALLEGRO_BITMAP* nextlevel = al_load_bitmap("assets/win.bmp");
	ALLEGRO_BITMAP* losegame = al_load_bitmap("assets/losegame.bmp");
	ALLEGRO_BITMAP* wongame = al_load_bitmap("assets/wingame.bmp");

	//Object creations start here

	Level* level = new Level("assets/wall.bmp", "assets/ballused.bmp", "assets/combo.bmp", "assets/redused.bmp", "assets/blueused.bmp", "assets/yellowused.bmp", 24, 1, 240);

	Player player1(60, 60, "player1", "assets/player_arrow.bmp", level, 0);

	//UI ball generation, for showing the player what ball is coming next
	Ball* ui_redball = new Ball(660, 460, "ui_redball", "assets/red_ball.bmp", level, 1, 1, 'R', &player1);
	Ball* ui_blueball = new Ball(660, 460, "ui_blueball", "assets/blue_ball.bmp", level, 1, 1, 'B', &player1);
	Ball* ui_yellowball = new Ball(660, 460, "ui_yellowball", "assets/yellow_ball.bmp", level, 1, 1, 'Y', &player1);

	//UI ball vector
	vector<Ball*>uiBalls;
	uiBalls.push_back(ui_redball);
	uiBalls.push_back(ui_blueball);
	uiBalls.push_back(ui_yellowball);

	int ballcount = 0;
	int ballwait = 59;
	
	Ball* redball1 = new Ball(player1.getX(), player1.getY()+120, "redball1", "assets/red_ball.bmp", level, 1, 1, 'R', &player1);
	Ball* redball2 = new Ball(player1.getX(), player1.getY()+120, "redball2", "assets/red_ball.bmp", level, 1, 2, 'R', &player1);
	Ball* redball3 = new Ball(player1.getX(), player1.getY()+120, "redball3", "assets/red_ball.bmp", level, 1, 3, 'R', &player1);
	Ball* redball4 = new Ball(player1.getX(), player1.getY()+120, "redball4", "assets/red_ball.bmp", level, 1, 4, 'R', &player1);
	Ball* redball5 = new Ball(player1.getX(), player1.getY()+120, "redball5", "assets/red_ball.bmp", level, 1, 5, 'R', &player1);
	Ball* redball6 = new Ball(player1.getX(), player1.getY()+120, "redball6", "assets/red_ball.bmp", level, 1, 6, 'R', &player1);
	Ball* redball7 = new Ball(player1.getX(), player1.getY()+120, "redball7", "assets/red_ball.bmp", level, 1, 7, 'R', &player1);
	Ball* redball8 = new Ball(player1.getX(), player1.getY()+120, "redball8", "assets/red_ball.bmp", level, 1, 8, 'R', &player1);
	Ball* redball9 = new Ball(player1.getX(), player1.getY()+120, "redball9", "assets/red_ball.bmp", level, 1, 9, 'R', &player1);
	Ball* redball10 = new Ball(player1.getX(), player1.getY()+120, "redball10", "assets/red_ball.bmp", level, 1, 10, 'R', &player1);
	Ball* redball11 = new Ball(player1.getX(), player1.getY()+120, "redball11", "assets/red_ball.bmp", level, 1, 11, 'R', &player1);
	Ball* redball12 = new Ball(player1.getX(), player1.getY()+120, "redball12", "assets/red_ball.bmp", level, 1, 12, 'R', &player1);
	Ball* redball13 = new Ball(player1.getX(), player1.getY()+120, "redball13", "assets/red_ball.bmp", level, 1, 13, 'R', &player1);
	Ball* redball14 = new Ball(player1.getX(), player1.getY()+120, "redball14", "assets/red_ball.bmp", level, 1, 14, 'R', &player1);
	Ball* redball15 = new Ball(player1.getX(), player1.getY()+120, "redball15", "assets/red_ball.bmp", level, 1, 15, 'R', &player1);
	Ball* redball16 = new Ball(player1.getX(), player1.getY()+120, "redball16", "assets/red_ball.bmp", level, 1, 16, 'R', &player1);
	Ball* redball17 = new Ball(player1.getX(), player1.getY()+120, "redball17", "assets/red_ball.bmp", level, 1, 17, 'R', &player1);
	Ball* redball18 = new Ball(player1.getX(), player1.getY()+120, "redball18", "assets/red_ball.bmp", level, 1, 18, 'R', &player1);
	Ball* redball19 = new Ball(player1.getX(), player1.getY()+120, "redball19", "assets/red_ball.bmp", level, 1, 19, 'R', &player1);
	Ball* redball20 = new Ball(player1.getX(), player1.getY()+120, "redball20", "assets/red_ball.bmp", level, 1, 20, 'R', &player1);
	Ball* redball21 = new Ball(player1.getX(), player1.getY()+120, "redball21", "assets/red_ball.bmp", level, 1, 21, 'R', &player1);
	Ball* redball22 = new Ball(player1.getX(), player1.getY()+120, "redball22", "assets/red_ball.bmp", level, 1, 22, 'R', &player1);
	Ball* redball23 = new Ball(player1.getX(), player1.getY()+120, "redball23", "assets/red_ball.bmp", level, 1, 23, 'R', &player1);
	Ball* redball24 = new Ball(player1.getX(), player1.getY()+120, "redball24", "assets/red_ball.bmp", level, 1, 24, 'R', &player1);
	Ball* redball25 = new Ball(player1.getX(), player1.getY()+120, "redball25", "assets/red_ball.bmp", level, 1, 25, 'R', &player1);
	Ball* redball26 = new Ball(player1.getX(), player1.getY()+120, "redball26", "assets/red_ball.bmp", level, 1, 26, 'R', &player1);
	Ball* redball27 = new Ball(player1.getX(), player1.getY()+120, "redball27", "assets/red_ball.bmp", level, 1, 27, 'R', &player1);
	Ball* redball28 = new Ball(player1.getX(), player1.getY()+120, "redball28", "assets/red_ball.bmp", level, 1, 28, 'R', &player1);
	Ball* redball29 = new Ball(player1.getX(), player1.getY()+120, "redball29", "assets/red_ball.bmp", level, 1, 29, 'R', &player1);
	Ball* redball30 = new Ball(player1.getX(), player1.getY()+120, "redball30", "assets/red_ball.bmp", level, 1, 30, 'R', &player1);

	Ball* yellowball1 = new Ball(player1.getX(), player1.getY()+120, "yellowball1", "assets/yellow_ball.bmp", level, 1, 1, 'Y', &player1);
	Ball* yellowball2 = new Ball(player1.getX(), player1.getY()+120, "yellowball2", "assets/yellow_ball.bmp", level, 1, 2, 'Y', &player1);
	Ball* yellowball3 = new Ball(player1.getX(), player1.getY()+120, "yellowball3", "assets/yellow_ball.bmp", level, 1, 3, 'Y', &player1);
	Ball* yellowball4 = new Ball(player1.getX(), player1.getY()+120, "yellowball4", "assets/yellow_ball.bmp", level, 1, 4, 'Y', &player1);
	Ball* yellowball5 = new Ball(player1.getX(), player1.getY()+120, "yellowball5", "assets/yellow_ball.bmp", level, 1, 5, 'Y', &player1);
	Ball* yellowball6 = new Ball(player1.getX(), player1.getY()+120, "yellowball6", "assets/yellow_ball.bmp", level, 1, 6, 'Y', &player1);
	Ball* yellowball7 = new Ball(player1.getX(), player1.getY()+120, "yellowball7", "assets/yellow_ball.bmp", level, 1, 7, 'Y', &player1);
	Ball* yellowball8 = new Ball(player1.getX(), player1.getY()+120, "yellowball8", "assets/yellow_ball.bmp", level, 1, 8, 'Y', &player1);
	Ball* yellowball9 = new Ball(player1.getX(), player1.getY()+120, "yellowball9", "assets/yellow_ball.bmp", level, 1, 9, 'Y', &player1);
	Ball* yellowball10 = new Ball(player1.getX(), player1.getY()+120, "yellowball10", "assets/yellow_ball.bmp", level, 1, 10, 'Y', &player1);
	Ball* yellowball11 = new Ball(player1.getX(), player1.getY()+120, "yellowball11", "assets/yellow_ball.bmp", level, 1, 11, 'Y', &player1);
	Ball* yellowball12 = new Ball(player1.getX(), player1.getY()+120, "yellowball12", "assets/yellow_ball.bmp", level, 1, 12, 'Y', &player1);
	Ball* yellowball13 = new Ball(player1.getX(), player1.getY()+120, "yellowball13", "assets/yellow_ball.bmp", level, 1, 13, 'Y', &player1);
	Ball* yellowball14 = new Ball(player1.getX(), player1.getY()+120, "yellowball14", "assets/yellow_ball.bmp", level, 1, 14, 'Y', &player1);
	Ball* yellowball15 = new Ball(player1.getX(), player1.getY()+120, "yellowball15", "assets/yellow_ball.bmp", level, 1, 15, 'Y', &player1);
	Ball* yellowball16 = new Ball(player1.getX(), player1.getY()+120, "yellowball16", "assets/yellow_ball.bmp", level, 1, 16, 'Y', &player1);
	Ball* yellowball17 = new Ball(player1.getX(), player1.getY()+120, "yellowball17", "assets/yellow_ball.bmp", level, 1, 17, 'Y', &player1);
	Ball* yellowball18 = new Ball(player1.getX(), player1.getY()+120, "yellowball18", "assets/yellow_ball.bmp", level, 1, 18, 'Y', &player1);
	Ball* yellowball19 = new Ball(player1.getX(), player1.getY()+120, "yellowball19", "assets/yellow_ball.bmp", level, 1, 19, 'Y', &player1);
	Ball* yellowball20 = new Ball(player1.getX(), player1.getY()+120, "yellowball20", "assets/yellow_ball.bmp", level, 1, 20, 'Y', &player1);
	Ball* yellowball21 = new Ball(player1.getX(), player1.getY()+120, "yellowball21", "assets/yellow_ball.bmp", level, 1, 21, 'Y', &player1);
	Ball* yellowball22 = new Ball(player1.getX(), player1.getY()+120, "yellowball22", "assets/yellow_ball.bmp", level, 1, 22, 'Y', &player1);
	Ball* yellowball23 = new Ball(player1.getX(), player1.getY()+120, "yellowball23", "assets/yellow_ball.bmp", level, 1, 23, 'Y', &player1);
	Ball* yellowball24 = new Ball(player1.getX(), player1.getY()+120, "yellowball24", "assets/yellow_ball.bmp", level, 1, 24, 'Y', &player1);
	Ball* yellowball25 = new Ball(player1.getX(), player1.getY()+120, "yellowball25", "assets/yellow_ball.bmp", level, 1, 25, 'Y', &player1);
	Ball* yellowball26 = new Ball(player1.getX(), player1.getY()+120, "yellowball26", "assets/yellow_ball.bmp", level, 1, 26, 'Y', &player1);
	Ball* yellowball27 = new Ball(player1.getX(), player1.getY()+120, "yellowball27", "assets/yellow_ball.bmp", level, 1, 27, 'Y', &player1);
	Ball* yellowball28 = new Ball(player1.getX(), player1.getY()+120, "yellowball28", "assets/yellow_ball.bmp", level, 1, 28, 'Y', &player1);
	Ball* yellowball29 = new Ball(player1.getX(), player1.getY()+120, "yellowball29", "assets/yellow_ball.bmp", level, 1, 29, 'Y', &player1);
	Ball* yellowball30 = new Ball(player1.getX(), player1.getY()+120, "yellowball30", "assets/yellow_ball.bmp", level, 1, 30, 'Y', &player1);

	Ball* blueball1 = new Ball(player1.getX(), player1.getY()+120, "blueball1", "assets/blue_ball.bmp", level, 1, 1, 'B', &player1);
	Ball* blueball2 = new Ball(player1.getX(), player1.getY()+120, "blueball2", "assets/blue_ball.bmp", level, 1, 2, 'B', &player1);
	Ball* blueball3 = new Ball(player1.getX(), player1.getY()+120, "blueball3", "assets/blue_ball.bmp", level, 1, 3, 'B', &player1);
	Ball* blueball4 = new Ball(player1.getX(), player1.getY()+120, "blueball4", "assets/blue_ball.bmp", level, 1, 4, 'B', &player1);
	Ball* blueball5 = new Ball(player1.getX(), player1.getY()+120, "blueball5", "assets/blue_ball.bmp", level, 1, 5, 'B', &player1);
	Ball* blueball6 = new Ball(player1.getX(), player1.getY()+120, "blueball6", "assets/blue_ball.bmp", level, 1, 6, 'B', &player1);
	Ball* blueball7 = new Ball(player1.getX(), player1.getY()+120, "blueball7", "assets/blue_ball.bmp", level, 1, 7, 'B', &player1);
	Ball* blueball8 = new Ball(player1.getX(), player1.getY()+120, "blueball8", "assets/blue_ball.bmp", level, 1, 8, 'B', &player1);
	Ball* blueball9 = new Ball(player1.getX(), player1.getY()+120, "blueball9", "assets/blue_ball.bmp", level, 1, 9, 'B', &player1);
	Ball* blueball10 = new Ball(player1.getX(), player1.getY()+120, "blueball10", "assets/blue_ball.bmp", level, 1, 10, 'B', &player1);
	Ball* blueball11 = new Ball(player1.getX(), player1.getY()+120, "blueball11", "assets/blue_ball.bmp", level, 1, 11, 'B', &player1);
	Ball* blueball12 = new Ball(player1.getX(), player1.getY()+120, "blueball12", "assets/blue_ball.bmp", level, 1, 12, 'B', &player1);
	Ball* blueball13 = new Ball(player1.getX(), player1.getY()+120, "blueball13", "assets/blue_ball.bmp", level, 1, 13, 'B', &player1);
	Ball* blueball14 = new Ball(player1.getX(), player1.getY()+120, "blueball14", "assets/blue_ball.bmp", level, 1, 14, 'B', &player1);
	Ball* blueball15 = new Ball(player1.getX(), player1.getY()+120, "blueball15", "assets/blue_ball.bmp", level, 1, 15, 'B', &player1);
	Ball* blueball16 = new Ball(player1.getX(), player1.getY()+120, "blueball16", "assets/blue_ball.bmp", level, 1, 16, 'B', &player1);
	Ball* blueball17 = new Ball(player1.getX(), player1.getY()+120, "blueball17", "assets/blue_ball.bmp", level, 1, 17, 'B', &player1);
	Ball* blueball18 = new Ball(player1.getX(), player1.getY()+120, "blueball18", "assets/blue_ball.bmp", level, 1, 18, 'B', &player1);
	Ball* blueball19 = new Ball(player1.getX(), player1.getY()+120, "blueball19", "assets/blue_ball.bmp", level, 1, 19, 'B', &player1);
	Ball* blueball20 = new Ball(player1.getX(), player1.getY()+120, "blueball20", "assets/blue_ball.bmp", level, 1, 20, 'B', &player1);
	Ball* blueball21 = new Ball(player1.getX(), player1.getY()+120, "blueball21", "assets/blue_ball.bmp", level, 1, 21, 'B', &player1);
	Ball* blueball22 = new Ball(player1.getX(), player1.getY()+120, "blueball22", "assets/blue_ball.bmp", level, 1, 22, 'B', &player1);
	Ball* blueball23 = new Ball(player1.getX(), player1.getY()+120, "blueball23", "assets/blue_ball.bmp", level, 1, 23, 'B', &player1);
	Ball* blueball24 = new Ball(player1.getX(), player1.getY()+120, "blueball24", "assets/blue_ball.bmp", level, 1, 24, 'B', &player1);
	Ball* blueball25 = new Ball(player1.getX(), player1.getY()+120, "blueball25", "assets/blue_ball.bmp", level, 1, 25, 'B', &player1);
	Ball* blueball26 = new Ball(player1.getX(), player1.getY()+120, "blueball26", "assets/blue_ball.bmp", level, 1, 26, 'B', &player1);
	Ball* blueball27 = new Ball(player1.getX(), player1.getY()+120, "blueball27", "assets/blue_ball.bmp", level, 1, 27, 'B', &player1);
	Ball* blueball28 = new Ball(player1.getX(), player1.getY()+120, "blueball28", "assets/blue_ball.bmp", level, 1, 28, 'B', &player1);
	Ball* blueball29 = new Ball(player1.getX(), player1.getY()+120, "blueball29", "assets/blue_ball.bmp", level, 1, 29, 'B', &player1);
	Ball* blueball30 = new Ball(player1.getX(), player1.getY()+120, "blueball30", "assets/blue_ball.bmp", level, 1, 30, 'B', &player1);


	//testing vector, easier to check combinations/shapes
	/*vector<Ball*>allballs;
	allballs.push_back(redball1);
	allballs.push_back(redball2);
	allballs.push_back(redball3);
	allballs.push_back(redball4);
	allballs.push_back(blueball1);
	allballs.push_back(blueball2);
	allballs.push_back(blueball3);
	allballs.push_back(blueball4);
	allballs.push_back(redball5);
	allballs.push_back(redball6);
	allballs.push_back(redball7);
	allballs.push_back(redball8);
	allballs.push_back(yellowball1);
	allballs.push_back(yellowball2);
	allballs.push_back(yellowball3);
	allballs.push_back(yellowball4);
	allballs.push_back(blueball5);
	allballs.push_back(blueball6);
	allballs.push_back(blueball7);
	allballs.push_back(blueball8);
	allballs.push_back(yellowball5);
	allballs.push_back(yellowball6);
	allballs.push_back(yellowball7);
	allballs.push_back(yellowball8);*/
	
	//gigantic vector allocation, goodness.
	vector<Ball*>allballs;
	allballs.reserve(51);
	allballs.push_back(blueball1);
	allballs.push_back(redball1);
	allballs.push_back(yellowball1);
	allballs.push_back(yellowball2);
	allballs.push_back(blueball2);
	allballs.push_back(redball2);
	allballs.push_back(redball3);
	allballs.push_back(blueball3);
	allballs.push_back(yellowball3);
	allballs.push_back(redball4);
	allballs.push_back(blueball4);
	allballs.push_back(yellowball4);
	allballs.push_back(yellowball5);
	allballs.push_back(redball5);
	allballs.push_back(blueball5);
	allballs.push_back(blueball6);
	allballs.push_back(redball6);
	allballs.push_back(redball7);
	allballs.push_back(yellowball6);
	allballs.push_back(yellowball7);
	allballs.push_back(blueball7);
	allballs.push_back(redball8);
	allballs.push_back(redball9);
	allballs.push_back(yellowball8);
	allballs.push_back(blueball8);
	allballs.push_back(yellowball9);
	allballs.push_back(redball10);
	allballs.push_back(blueball9);
	allballs.push_back(blueball10);
	allballs.push_back(yellowball10);
	allballs.push_back(redball11);
	allballs.push_back(redball12);
	allballs.push_back(yellowball11);
	allballs.push_back(blueball11);
	allballs.push_back(yellowball12);
	allballs.push_back(yellowball13);
	allballs.push_back(redball13);
	allballs.push_back(blueball12);
	allballs.push_back(redball14);
	allballs.push_back(yellowball14);
	allballs.push_back(blueball13);
	allballs.push_back(blueball14);
	allballs.push_back(redball15);
	allballs.push_back(yellowball15);
	allballs.push_back(yellowball16);
	allballs.push_back(redball16);
	allballs.push_back(blueball15);
	allballs.push_back(redball17);
	allballs.push_back(yellowball17);
	allballs.push_back(yellowball18);
	allballs.push_back(blueball16);
	
	//cout << "size: " << (int) allballs.size() << '\n';
	//cout << "capacity: " << (int) allballs.capacity() << '\n';
	//cout << "max_size: " << (int) allballs.max_size() << '\n';

	//counter and old global time
	int counter = 60;		
	int time = 240;
	

	int resetcounter = 60;//unused, testing purposes

	al_start_timer(timer);

	while(!keys_pressed[KEY_ESCAPE]/*&&gamelost==false*/)//game loop
	{
		process_events(); // deals with events, such as mouse and keyboard input

		
////////////RENDERING/////////////////////////////////////////////////////////////////////////

		if(render_frame)
		{
			render_frame = false;

			level->render();	//draws level

			player1.draw();		//draws Player character

			for (int count= 0; count<allballs.size(); count++)
			{
				if(allballs[count]->isUsed()==true && allballs[count]->isAlive()==true)
				{
				allballs[count]->draw();
				}

			}

			//UI Text
			al_draw_textf(big_font , al_map_rgb(0, 0, 0), 600, 0, 0, "Level ");
			al_draw_textf(big_font , al_map_rgb(0, 0, 0), 730, 0, 0, "%d", level->getLevelNumber());
			al_draw_textf(big_font , al_map_rgb(0, 0, 0), 600, 40, 0,"Points");
			al_draw_textf(big_font , al_map_rgb(0, 0, 0), 600, 90, 0,"%d", level->getPointsEarned());
			al_draw_textf(big_font , al_map_rgb(0, 0, 0), 600, 150, 0,"Needed");
			al_draw_textf(big_font , al_map_rgb(0, 0, 0), 600, 180, 0,"%d", level->getPointsNeeded());
			al_draw_textf(big_font , al_map_rgb(0, 0, 0), 600, 240, 0, "Time");
			al_draw_textf(big_font , al_map_rgb(0, 0, 0), 600, 270, 0, "%d", level->getTime());
			al_draw_textf(big_font , al_map_rgb(0, 0, 0), 600, 340, 0, "Balls left ");
			al_draw_textf(big_font , al_map_rgb(0, 0, 0), 600, 370, 0, "%d", ballsremaining);
			al_draw_textf(big_font , al_map_rgb(0, 0, 0), 600, 420, 0, "Next up");
			

			////////drawing the next ball in UI/////////
			if(allballs[ballcount]->getColour()=='R')
			{
			uiBalls[0]->draw();		
			}
			else if(allballs[ballcount]->getColour()=='B')
			{
			uiBalls[1]->draw();		
			}
			else if(allballs[ballcount]->getColour()=='Y')
			{
			uiBalls[2]->draw();		
			}
			//////////////////////////////////////
		
			//plays main theme
			al_play_sample_instance(mainthemeinstance);



			al_flip_display();	//draws to screen		

			//al_draw_bitmap(background,0,0,0);

			if(gamestart==true)
			{
				al_draw_bitmap(startgame, 60,180,0);
				al_flip_display();
				al_rest(5);
				gamestart=false;
			}
			
			if(level->getLevelNumber()==1||
				level->getLevelNumber()==4||
				level->getLevelNumber()==7||
				level->getLevelNumber()==10)
			{
			al_draw_bitmap(background,0,0,0);//draws background bitmap
			}
			else if(level->getLevelNumber()==2||
				level->getLevelNumber()==5||
				level->getLevelNumber()==8)
			{
			al_draw_bitmap(background2,0,0,0);//draws background bitmap
			}
			else if(level->getLevelNumber()==3||
				level->getLevelNumber()==6||
				level->getLevelNumber()==9)
			{
			al_draw_bitmap(background3,0,0,0);//draws background bitmap
			}


		}

////////////LOGIC/////////////////////////////////////////////////////////////////////////

		if(update_logic)
		{
			update_logic = false;
						
			///timer related code///
			counter--;								 ///counter is decremented every frame, as they are 60 per second
			if (counter==0)							 ///once this reaches 0 one second has passed
			{										 ///then we can decrement the time counter by one
				level->timeminus();								 ///then  reset the frames per second so this can happen again and again every second
				counter=60;
			}
			///////////////////////////////////////////



//////////keyboard methods/////////////

			if(keys_pressed[KEY_SPACE]) 
			{
				
				balldropwait++;
				if(balldropwait==65)	//makes sure balls dont fall on each other
				{
				allballs[ballcount]->Use();	//uses ball on current ball count
				ballcount++;				//increments the ball count
				balldropwait = 0;			//resets the waiting variable
				al_play_sample(balldropsound, 3.0, 0.0,1.0,ALLEGRO_PLAYMODE_ONCE,NULL);//plays the sound effect
				}
			}

			//could have if counter =<50, do method

			if(keys_pressed[KEY_A])	//moves left
			{
				movewait++;
				if(movewait==10)
				{
				player1.playerLeft();
				movewait=0;
				}
			}

			if(keys_pressed[KEY_S])
			{
				//was to be used for moving balls down faster
			}

			if(keys_pressed[KEY_D])	//moves right
			{
				movewait++;
				if(movewait==10)
				{
				player1.playerRight();
				movewait=0;
				}
			}


			
		//////////ball checks/////////////////////
		for (int count= 0; count<allballs.size(); count++)
		{
			if(allballs[count]->isWallBelow()||allballs[count]->isBallBelow())	//if there's a ball or a wall below the current ball in loop,
			{
				allballs[count]->fallen();										//set its status to fallen			
				//al_play_sample(ballfallensound, 1.0, 0.0,1.0,ALLEGRO_PLAYMODE_ONCE,NULL); logic errors cause to play infinitely, cannot find fix
			}
			if(allballs[count]->isFalling()==false)								//if the current ball has fallen
			{
				if(allballs[count]->getColour()=='R')
				{
				allballs[count]->isnowRedBall();								//set up the level vector as neccessary
				}
				if(allballs[count]->getColour()=='B')
				{
				allballs[count]->isnowBlueBall();		
				}
				if(allballs[count]->getColour()=='Y')
				{
				allballs[count]->isnowYellowBall();		
				}
				if(allballs[count]->isFalling()==false
					&& (allballs[count]->getY()<=180))							//if ypos of balls reaches too high, needs to be slightly more accurate
				{
					gamelost=true;
				}
			}
		
			//check if ball is used, if it is then call down on it
			if(allballs[count]->isUsed()==true)
			{
				allballs[count]->down();		
			}

			//check for wins and calculate points earned
			level->checkForWins();
			level->checkForCombo();
			level->calculatepoints();
			//level->calculatecombo(); unused pointless method

		}

///////endgame checks//////////

		if(time==0||ballcount==allballs.size()-2)	//if the player reaches the end of the vector of balls, or close enough to not crash game
		{
			gamelost=true;
		}

		if(gamelost==true)
		{
			al_play_sample(losesound, 3.0, 0.0,1.0,ALLEGRO_PLAYMODE_ONCE,NULL);
			al_draw_bitmap(losegame, 100,200,0);	//display lose message for three seconds then break out of code
			al_flip_display();
			al_rest(3);
			break;
		}

		if(level->getPointsEarned()>=level->getPointsNeeded())
		{
			gamewon=true;
		}

		//gamewon checks
		if(gamewon==true)
		{
			for(int count= 0; count<allballs.size(); count++)
			{
				allballs[count]->resetballpositions();
			}
			level->setLevelNumber(level->getLevelNumber()+1);	//increase level number
			level->levelreset();								//reset level array information
			ballcount=0;										//reset ballcount to 0
			gamewon=false;										//gamewon is no longer true

			al_play_sample(winsound, 3.0, 0.0,1.0,ALLEGRO_PLAYMODE_ONCE,NULL);
			al_draw_bitmap(nextlevel, 100,200,0);				//display message for 3 seconds
			al_flip_display();
			al_rest(3);
		}

		//level if statements
		//sets up neccessary required points, need to still add changes to time and balls
		if(level->getLevelNumber()==2)
		{
			level->setPointsNeeded(32);
		}
		if(level->getLevelNumber()==3)
		{
			level->setPointsNeeded(46);
		}
		if(level->getLevelNumber()==4)
		{
			level->setPointsNeeded(52);
		}
		if(level->getLevelNumber()==5)
		{
			level->setPointsNeeded(60);
		}
		if(level->getLevelNumber()==6)
		{
			level->setPointsNeeded(64);
		}
		if(level->getLevelNumber()==7)
		{
			level->setPointsNeeded(68);
		}
		if(level->getLevelNumber()==8)
		{
			level->setPointsNeeded(72);
		}
		if(level->getLevelNumber()==9)
		{
			level->setPointsNeeded(76);
		}
		if(level->getLevelNumber()==10)
		{
			level->setPointsNeeded(80);
		}
		if(level->getLevelNumber()==11)
		{
			gameover==true;
		}

		if(gameover==true)
		{
			al_play_sample(winsound, 3.0, 0.0,1.0,ALLEGRO_PLAYMODE_ONCE,NULL);
			al_draw_bitmap(wongame, 100,200,0);//display message then break and end game
			al_flip_display();
			al_rest(3);
			break;
		}

		ballsremaining = allballs.size()-ballcount;

		//end of logic loop
		}
		
	}

	delete level;
	al_destroy_display(display);
	al_destroy_font(big_font);
	al_destroy_event_queue(event_queue);
	al_destroy_timer(timer);


	return 0;
}


////////////////////////////////////////////////////////////////////////

void process_events()
{
	ALLEGRO_EVENT allegro_event;

	// get the next event from the event queue
	bool got_event = al_get_next_event(event_queue, &allegro_event);

	if(got_event == false) return; // no event waiting

	// test if a key is pressed down, update global keypress array
	if(allegro_event.type == ALLEGRO_EVENT_KEY_DOWN) 
	{
		switch(allegro_event.keyboard.keycode) 
		{
		case ALLEGRO_KEY_ESCAPE:
			keys_pressed[KEY_ESCAPE] = true;
			break;
		case ALLEGRO_KEY_A:
			keys_pressed[KEY_A] = true;
			break;
		case ALLEGRO_KEY_S:
			keys_pressed[KEY_S] = true;
			break;
		case ALLEGRO_KEY_D:
			keys_pressed[KEY_D] = true;
			break;
		case ALLEGRO_KEY_SPACE:
			keys_pressed[KEY_SPACE] = true;
			break;
		}
	}	
	// Test if a key is let go, update global keypress array
	else if(allegro_event.type == ALLEGRO_EVENT_KEY_UP) 
	{
		switch(allegro_event.keyboard.keycode) 
		{
		case ALLEGRO_KEY_ESCAPE:
			keys_pressed[KEY_ESCAPE] = false;
			break;
		case ALLEGRO_KEY_A:
			keys_pressed[KEY_A] = false;
			break;
		case ALLEGRO_KEY_S:
			keys_pressed[KEY_S] = false;
			break;
		case ALLEGRO_KEY_D:
			keys_pressed[KEY_D] = false;
			break;
		case ALLEGRO_KEY_SPACE:
			keys_pressed[KEY_SPACE] = false;
			break;
		}
	}

		else if(got_event && allegro_event.type == ALLEGRO_EVENT_TIMER)
	{

	// if logic taking too long ensures frame is rendered occasionally and input is responsive
	// this essentially ignores logic updates if there are a lot of consecutive ones

		if(++consecutive_logic_updates < max_consecutive_logic_updates)
		{
			update_logic = true;
		}

	// only render frame if no events left to process
		if(al_is_event_queue_empty(event_queue))
		{
			render_frame = true;
			consecutive_logic_updates=0;
		}
	}

}

////////////////////////////////////////////////////////////////////////

int initialise_allegro()
{
	if(!al_init()) 
	{
		cout << "Allegro initialisation failed" << endl;
		cout << "Press any key to exit" << endl;
		_getch();
		return -1;
	}

	// tell allegro program needs keyboard input
	if(!al_install_keyboard()) 
	{
		cout << "Keyboard initialisation failed" << endl;
		cout << "Press any key to exit" << endl;
		_getch();
		return -1;
	}
		
	if(!al_install_audio())
	{
    	cout << "Audio initialisation failed" << endl;
		cout << "Press any key to exit" << endl;
		_getch();
		return -1;
    return -1;
	}

	if(!al_init_acodec_addon())
	{	
		cout << "failed to initialize audio codecs!" << endl;
		cout << "Press any key to exit" << endl;
		_getch();
		return -1;
	}

	if (!al_reserve_samples(10))
	{
		cout << "failed to reserve samples!" << endl;
		cout << "Press any key to exit" << endl;
		_getch();
		return -1;
	}

	maintheme = al_load_sample( "assets/maintheme.ogg" );
	//source of music: http://www.tannerhelland.com/dmusic/FamiliarRoads.ogg

	mainthemeinstance = al_create_sample_instance(maintheme);
	al_set_sample_instance_playmode(mainthemeinstance, ALLEGRO_PLAYMODE_LOOP);

	al_attach_sample_instance_to_mixer(mainthemeinstance, al_get_default_mixer());

	balldropsound = al_load_sample( "assets/dropballsound.ogg" );
	ballfallensound = al_load_sample( "assets/ballfallensound.ogg" );
	ballcombinedsound = al_load_sample( "assets/combinesound.ogg" );
	powerupsound = al_load_sample( "assets/powerupsound.ogg" );
	winsound = al_load_sample( "assets/winlevelsound.ogg" );
	losesound = al_load_sample( "assets/diesound.ogg" );
	//source of sound effects: http://rpg.hamsterrepublic.com/ohrrpgce/Free_Sound_Effects


	// initialise keypress array
	for(int i=0; i < SIZE_OF_KEYS_PRESSED_ENUM; i++) 
	{
		keys_pressed[i] = false;
	}

	display = al_create_display(840, 900); // create a display window of size 960 by 960



	if(!display) 
	{
		cout << "Display initialisation failed" << endl;
		cout << "Press any key to exit" << endl;
		_getch();
		return -1;
	}

 	al_set_window_position(display, 0, 0); // position display window on screen

	if(!al_init_image_addon())//checks for allegro bitmap stuff
	{
		cout << "Bitmap initialisation failed" << endl;
		cout << "Press any key to exit" << endl;
		_getch();
		return -1;
	}



	// need to create an event queue so allegro can respond to events, such as keypresses
	event_queue = al_create_event_queue();

	if(!event_queue) 
	{
		cout << "Event queue creation failed" << endl;
		cout << "Press any key to exit" << endl;
		_getch();
		al_destroy_display(display);
		return -1;
	}

	al_init_primitives_addon(); 
	
	timer = al_create_timer(1.0 / frames_per_second);
 
	// register  display with the event queue, so display change events can be processed
	al_register_event_source(event_queue, al_get_display_event_source(display));

	// register keyboard with the event queue, so keypress events can be processed
	al_register_event_source(event_queue, al_get_keyboard_event_source());

	al_register_event_source(event_queue, al_get_timer_event_source(timer));

	return 0;
}
