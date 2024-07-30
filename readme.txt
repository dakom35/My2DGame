This is a project to learn how to make 'simple' games in C++ with the SFML library
The goal is to "shoot" the monsters popping on the screen : a good aim warm-up.


This is the command to compile and generate the executable game file : 
    Linux : 
        g++ -o Aim_Training main.cpp Game.cpp -lsfml-audio -lsfml-graphics -lsfml-window -lsfml-system
    Windows :
        g++ -o Aim_Training main.cpp Game.cpp -IC:\SFML\include\ -LC:\SFML\lib\ -lsfml-audio -lsfml-graphics -lsfml-window -lsfml-system
 
Credits : 
    SFML tutorial in C++ : https://www.youtube.com/playlist?list=PL6xSOsbVA1eb_QqMTTcql_3PdOiE928up (author : SurajSharmaFourKnob )
    Monster sprite : Stephen "Redshrike" Challener (Sprites) 5hiroi (concepts) Heather Lee Harvey (concept) (EmeraldActivities.com) www.OpenGameArt.org
    Sounds (freesound.org) : 
        -> Monster1's death sound :  by Michel88 (Licence : CC SAMPLING+ 1.0 DEED) 
        -> Monster1 bis death sound : by bananplyte (Licence : Creative Commons 0) 
        -> Monster2's death sound : by SoundFlakes (Licence : CC BY 4.0 DEED)
    Music :
        -> Phobos by Lone Peak Music 
            -> Youtube : https://www.youtube.com/watch?v=1HV3PN3g7fQ&list=PLsVfn9YIFmNA5BbgWyjLZ4MlDEemQqa7C
            -> hosting site : https://lonepeakmusic.bandcamp.com/
            -> Licence : Attribution 3.0 Unported (CC BY 3.0)


Developer's journal : 

TODO : 
    1) get a faster pseudo random number generator such as Xoshiro256+ (done with hash())
    2) check if game could benefit from std::thread (game is not laggy anymore so later maybe)
    3) make different screams for the monsters when they are shot 


