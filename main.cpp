
#include "functions.h"



#include "potion.h"

#include "player.h" 
#include "game.h" 
#include "goblin.h" 
#include "item.h" 
#include "entity.h" 
#include "exception.h" 
#include "functions.h" 
#include "user_interface.h"

void Play_the_game()
{
    Game level,lvl2;
    UI jocc;
    
    std::shared_ptr<Entity> x = std::make_shared<Player>( 1,10,"KING",2,2 ) ;
    
    level.add_creature( x );
    x = std::make_shared<Player>( 1,10,"olo",2,2 ) ;
    
    level.add_creature( x );
    
    

    
    std::shared_ptr<Item> y = std::make_shared<Potion>( "Healing",-1,25 );
    level.add_item( y );

    y = std::make_shared<Potion>( "Lightning",0,-100 );
    level.add_item( y );


    y = std::make_shared<Potion>( "Increase_stats",4,4 );
    level.add_item( y );

    // x= std::make_shared<Player>( 1,1000,"Flavius",1,1 );
    // level.add_creature( x );
    // x= std::make_shared<Player>( 2,500,"Maria_t",1,1 );
    // level.add_creature( x );
    
    x= std::make_shared<Goblin>( 2 );
    level.add_creature( x );
    x= std::make_shared<Goblin>( 1 );
    level.add_creature( x );
    x= std::make_shared<Goblin>( 3 );
    level.add_creature( x );

    jocc.Add_level(level);
    
    // x= std::make_shared<Goblin>( 4 );
    // level.add_creature( x );
    // jocc.Add_level(level);
    
    // x= std::make_shared<Goblin>( 2 );
    // level.add_creature( x );
    
    jocc.start();
}


int main()
{
    
    // std::cout << "WELCOME!\npress: S -to start or Q - to quit\n";
    // while( 1 )
    // {
    //     std::string input_string;
    //     std::cin >> input_string;
    //     char option = input_string[0];
    //     option = std::tolower( option );    

    //     try{
    //         if( option == 's' and input_string.size()==1  )
    //         {
                Play_the_game();
    //             break;
    //         } 
    //         else if( option == 'q' and input_string.size()==1 )
    //         {
    //             break;
    //         }
    //         else 
    //             throw Input_Invalid();
    //     }
    //     catch( MyException &e ){
    //         std::cout << e.what();
    //     }
    // }
}






