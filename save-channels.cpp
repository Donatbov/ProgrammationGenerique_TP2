#include <cmath>
#include <iostream>
#include <fstream>
#include "Image2D.hpp"
#include "Image2DReader.hpp"
#include "Image2DWriter.hpp"
#include "Accessor.hpp"


int main( int argc, char** argv )
{
    typedef Image2D<Color> ColorImage2D;
    typedef Image2DReader<Color> ColorImage2DReader;
    typedef ColorImage2D::Iterator ColorIterator;
    if ( argc < 2 )
    {
        std::cerr << "Usage: save-channels <input.ppm>" << std::endl;
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
    typedef GrayLevelImage2D::Iterator GrayLevelIterator;
    GrayLevelImage2D imgR( img.w(), img.h() );
    GrayLevelImage2D imgG( img.w(), img.h() );
    GrayLevelImage2D imgB( img.w(), img.h() );

    //-----------------------------------------------------------------------------
    // rrrrrrrrrr Toute la transformation couleur -> canal rouge est ici rrrrrrrrrrr
    //
    // Servira à parcourir la composante rouge de l'image couleur.
    typedef ColorImage2D::GenericConstIterator< ColorRedAccessor > ColorRedConstIterator;
    // Notez comment on appelle la méthode \b générique `begin` de `Image2D`.
    ColorRedConstIterator itRed = img.begin< ColorRedAccessor >();
    // On écrit la composante rouge dans l'image en niveaux de gris.
    for ( GrayLevelIterator it = imgR.begin(), itE = imgR.end(); it != itE; ++it )
    {
        *it = *itRed;
        ++itRed;
        // NB: si on veut faire *itRed++, il faut redéfinir GenericConstIterator<T>::operator++(int).
    }
    //-----------------------------------------------------------------------------

    //-----------------------------------------------------------------------------
    // vvvvvvvvv Toute la transformation couleur -> canal vert est ici vvvvvvvvvvvv
    //
    // Servira à parcourir la composante verte de l'image couleur.
    typedef ColorImage2D::GenericConstIterator< ColorGreenAccessor > ColorGreenConstIterator;
    // Notez comment on appelle la méthode \b générique `begin` de `Image2D`.
    ColorGreenConstIterator itGreen = img.begin< ColorGreenAccessor >();
    // On écrit la composante verte dans l'image en niveaux de gris.
    for ( GrayLevelIterator it = imgG.begin(), itE = imgG.end(); it != itE; ++it )
    {
        *it = *itGreen;
        ++itGreen;
        // NB: si on veut faire *itGreen++, il faut redéfinir GenericConstIterator<T>::operator++(int).
    }
    //-----------------------------------------------------------------------------

    //-----------------------------------------------------------------------------
    // bbbbbbbbb Toute la transformation couleur -> canal rouge est ici bbbbbbbbbbb
    //
    // Servira à parcourir la composante bleue de l'image couleur.
    typedef ColorImage2D::GenericConstIterator< ColorBlueAccessor > ColorBlueConstIterator;
    // Notez comment on appelle la méthode \b générique `begin` de `Image2D`.
    ColorBlueConstIterator itBlue = img.begin< ColorBlueAccessor >();
    // On écrit la composante rouge dans l'image en niveaux de gris.
    for ( GrayLevelIterator it = imgB.begin(), itE = imgB.end(); it != itE; ++it )
    {
        *it = *itBlue;
        ++itBlue;
        // NB: si on veut faire *itBlue++, il faut redéfinir GenericConstIterator<T>::operator++(int).
    }
    //-----------------------------------------------------------------------------

    std::ofstream outputR( "papillon_red.pgm" );
    bool okR = GrayLevelImage2DWriter::write( imgR, outputR, false );
    if ( !okR )
    {
        std::cerr << "Error writing output file." << std::endl;
        return 1;
    }
    outputR.close();

    std::ofstream outputG( "papillon_green.pgm" );
    bool okG = GrayLevelImage2DWriter::write( imgG, outputG, false );
    if ( !okG )
    {
        std::cerr << "Error writing output file." << std::endl;
        return 1;
    }
    outputG.close();

    std::ofstream outputB( "papillon_blue.pgm" );
    bool okB = GrayLevelImage2DWriter::write( imgB, outputB, false );
    if ( !okB )
    {
        std::cerr << "Error writing output file." << std::endl;
        return 1;
    }
    outputB.close();
    return 0;
}


