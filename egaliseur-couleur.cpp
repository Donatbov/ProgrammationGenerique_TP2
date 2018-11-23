#include <cmath>
#include <iostream>
#include <fstream>
#include "Image2D.hpp"
#include "Image2DReader.hpp"
#include "Image2DWriter.hpp"
#include "Accessor.hpp"
#include "Histogramme.hpp"


int main( int argc, char** argv )
{
    typedef Image2D<Color> ColorImage2D;
    typedef Image2DReader<Color> ColorImage2DReader;
    typedef ColorImage2D::Iterator ColorIterator;
    if ( argc < 3 )
    {
        std::cerr << "Usage: histogramme <input.ppm> <output.pgm>" << std::endl;
        return 0;
    }
    ColorImage2D img;
    std::ifstream input( argv[1] ); // récupère le 1er argument.
    bool ok = ColorImage2DReader::read( img, input );
    if ( !ok )
    {
        std::cerr << "Error reading input file." << std::endl;
        return 1;
    }
    input.close();

    // création de l'histogramme
    Histogramme histo = Histogramme();
    histo.init(img.begin< ColorValueAccessor >(), img.end< ColorValueAccessor >());

    //on égalise
    for ( auto it = img.begin< ColorValueAccessor >(), itE = img.end< ColorValueAccessor >(); it != itE; ++it )
    {
        *it  = (unsigned char) histo.egalisation(*it);
    }

    typedef Image2DWriter<Color> ColorImage2DWriter;
    std::ofstream output( argv[2] ); // récupère le 2eme argument.
    bool ok2 = ColorImage2DWriter::write( img, output, false );
    if ( !ok2 )
    {
        std::cerr << "Error writing output file." << std::endl;
        return 1;
    }
    output.close();
    return 0;
}


