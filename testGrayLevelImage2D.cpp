#include <iostream>
#include <fstream>
#include "Image2DReader.hpp"
#include "Image2DWriter.hpp"

using namespace std;

int main( int argc, char** argv )
{
    typedef unsigned char GrayLevel;
    typedef Image2D<GrayLevel> GrayLevelImage2D;
    /* //test
    GrayLevelImage2D img( 8, 8, 5 ); // imagette 8x8 remplie de 5
    for ( int y = 0; y < img.h(); ++y )
    {
        for ( int x = 0; x < img.w(); ++x )
            cout << " " << (int) img.at( x, y ); // la conversion permet de voir les caractères sous forme d'entiers.
        cout << std::endl;
    }*/

    //test lire une image PGM et l'écrire
    if(argv[1] && argv[2]) {
        GrayLevelImage2D img;
        ifstream input(argv[1]);
        try {
            Image2DReader<unsigned char>::read(img, input);
        }
        catch (char const *msg) {
            std::cerr << "Exception: " << msg << std::endl;
        }
        catch (...) {
            std::cerr << "Exception inconnue." << std::endl;
        }
        input.close();

        //  export
        ofstream output(argv[2]);
        Image2DWriter<GrayLevel>::write(img, output, false);
        output.close();
        std::cout << std::endl;

    }
    else{
        std::cerr << "Pas de argv[1] et/ou argv[2], attendus : fichier_d_entree "
                  << "fichier_de_sortie \"double-brighness\" ou \"filtrage-median {k}\" ou \"egalisation\" ";
    }

    return 0;
}
