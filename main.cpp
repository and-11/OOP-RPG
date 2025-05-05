
#include "libraryes.h"

void setup()
{
    Game level;
    // Game lvl2;
    UI jocc;

    std::string name = "KING";
    std::shared_ptr<Entity> x = std::make_shared<Player>( 1,10,name,2,2 ) ;
    level.add_creature( x );

    // name = "olo";
    // x = std::make_shared<Player>( 1,10,name,2,2 ) ;
    // level.add_creature( x );
    
    

    name = "Healing";
    std::shared_ptr<Item> y = std::make_shared<Potion>( name,-1,25 );
    level.add_item( y );

    // name = "Lightning";
    // y = std::make_shared<Potion>( name,0,-100 );
    // level.add_item( y );

    // name = "Increase_stats";
    // y = std::make_shared<Potion>( name,4,4 );
    // level.add_item( y );


    x= std::make_shared<Goblin>( 2 );
    level.add_creature( x );
    // x= std::make_shared<Goblin>( 1 );
    // level.add_creature( x );
    // x= std::make_shared<Goblin>( 3 );
    // level.add_creature( x );

    jocc.Add_level(level);
    
    // x= std::make_shared<Goblin>( 4 );
    // level.add_creature( x );
    // jocc.Add_level(level);
    
    // x= std::make_shared<Goblin>( 2 );
    // level.add_creature( x );
    
    jocc.start();

    
    
    ///     -   --- -   -   -   -   -   -   --  -   -   
    x.reset();
    y.reset();
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
                setup();
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






