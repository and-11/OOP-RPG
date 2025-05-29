#include "libraries.hpp"
#include "potion.hpp"
#include "functions.hpp"
#include "player.hpp"
#include "game.hpp"

#include "item.hpp"
#include "entity.hpp"
#include "user_interface.hpp"

#include "goblin.hpp"
#include "skeleton.hpp"
#include "wolf.hpp"
#include "orc.hpp"
#include "crow.hpp"

#include "exception.hpp"

void setup()
{
    UI joc;
    
    Game level;

    std::string name;
    std::shared_ptr<Entity> x;
    std::shared_ptr<Item> y;
   
    /// PLAYERS
    name = "Knight";
    x = std::make_shared<Player>( 4,10,name,2,2 ) ;
    level.add_creature( x );

    name = "Archer";
    x = std::make_shared<Player>( 10,6,name,2,2 ) ;
    level.add_creature( x );

    name = "Shield";
    x = std::make_shared<Player>( 1,23,name,2,2 ) ;
    level.add_creature( x );


    /// POTIONS
    name = "Healing";
    y = std::make_shared<Potion>( name,-1,25 );
    level.add_item( y );

    name = "Lightning";
    y = std::make_shared<Potion>( name,0,-30 );
    level.add_item( y );

    name = "Increase Stats";
    y = std::make_shared<Potion>( name,7,12 );
    level.add_item( y );


    /// ENEMIES

    /// lvl 1
    x= std::make_shared<Skeleton>( 2 );
    level.add_creature( x );
    x= std::make_shared<Crow>( 3 );
    level.add_creature( x );
    x= std::make_shared<Skeleton>( 1 );
    level.add_creature( x );
    x= std::make_shared<Wolf>( 2 );
    level.add_creature( x );

    joc.Add_level(level);
    level.reset();

    /// lvl 2
    x= std::make_shared<Orc>( 5 );
    level.add_creature( x );
    x= std::make_shared<Goblin>( 3 );
    level.add_creature( x );

    joc.Add_level(level);
    level.reset();

    /// lvl 3
    x= std::make_shared<Wolf>( 2 );
    level.add_creature( x );
    x= std::make_shared<Skeleton>( 1 );
    level.add_creature( x );
    x= std::make_shared<Wolf>( 1 );
    level.add_creature( x );
    x= std::make_shared<Skeleton>( 2 );
    level.add_creature( x );
    x= std::make_shared<Skeleton>( 2 );
    level.add_creature( x );
    x= std::make_shared<Orc>( 2 );
    level.add_creature( x );

    joc.Add_level(level);
    level.reset();

    /// lvl 4
    x= std::make_shared<Goblin>( 83 );
    level.add_creature( x );
    
    joc.Add_level(level);
    level.reset();
    
    /// lvl 5
    x= std::make_shared<Orc>( 1 );
    level.add_creature( x );
    x= std::make_shared<Orc>( 1 );
    level.add_creature( x );
    x= std::make_shared<Orc>( 1 );
    level.add_creature( x );
    
    joc.Add_level(level);
    level.reset();
    
    /// lvl 6
    x= std::make_shared<Orc>( 7 );
    level.add_creature( x );
    x= std::make_shared<Wolf>( 7 );
    level.add_creature( x );
    
    joc.Add_level(level);
    level.reset();
    

    ///     -   --- -   -   -   -   -   -   --  -   -   

    joc.start();
    x.reset();
    y.reset();
}


int main()
{
    std::string input_string;
    std::cout << "WELCOME!\npress: S -to start or Q - to quit\n";
    while( true )
    {
        std::cin >> input_string;           /// PLAY
        // input_string = 's';              /// PLAY
        
        char option = input_string[0];
        option = std::tolower( option );    

        try{
            if( option == 's' and input_string.size()==1  )
            {
                setup();
                break;
            } 
            else if( option == 'q' and input_string.size()==1 )
            {
                break;
            }
            else 
                throw Input_Invalid();
        }
        catch( MyException &e ){
            std::cout << e.what() << "\n";
        }
    }
}






