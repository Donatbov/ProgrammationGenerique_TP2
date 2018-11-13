#include <iostream>
#include <fstream>
#include "Color.hpp"
#include "Image2DReader.hpp"
#include "Image2DWriter.hpp"

using namespace std;

int main( int argc, char** argv )
{
    typedef Image2D<Color> ColorImage2D;
    typedef ColorImage2D::Iterator Iterator;
    typedef ColorImage2D::ConstIterator ConstIterator;

    if(argv[1] && argv[2]) {
        ColorImage2D img;

        // import
        ifstream input(argv[1]);
        try {
            Image2DReader<Color>::read(img, input);
        }
        catch (char const *msg) {
            std::cerr << "Exception: " << msg << std::endl;
        }
        catch (...) {
            std::cerr << "Exception inconnue." << std::endl;
        }
        input.close();

        // traitement
        for (Iterator it = img.begin(); it != img.end(); ++it) {
            Color c = *it;
            *it = Color(c.blue, c.green, c.red);    // on inverse les canaux rouges et bleus
        }


        // export
        ofstream output(argv[2]);
        Image2DWriter<Color>::write(img, output, false);
        output.close();
        std::cout << std::endl;

    }
    else{
        std::cerr << "Pas de argv[1] et/ou argv[2], attendus : fichier_d_entree ";
    }


    return 0;
}

