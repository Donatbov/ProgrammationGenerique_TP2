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

    typedef Image2D<unsigned char> GrayLevelImage2D;
    typedef Image2DWriter<unsigned char> GrayLevelImage2DWriter;

    // création de l'image de l'histogramme
    Histogramme histo = Histogramme();
    histo.init(img.begin< ColorValueAccessor >(), img.end< ColorValueAccessor >());
    GrayLevelImage2D imgHisto = histo.toImage();

    std::ofstream output( argv[2] ); // récupère le 2eme argument.
    bool ok2 = GrayLevelImage2DWriter::write( imgHisto, output, false );
    if ( !ok2 )
    {
        std::cerr << "Error writing output file." << std::endl;
        return 1;
    }
    output.close();
    return 0;
}


