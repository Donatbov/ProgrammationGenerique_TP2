#ifndef TP2_IMAGE2DREADER_HPP
#define TP2_IMAGE2DREADER_HPP

#include <iostream>
#include <string> // chaînes de caractères
#include <fstream> // flux sur les fichiers
#include <sstream> // flux sur les chaînes de caractères
#include "Color.hpp"
#include "Image2D.hpp"

using std::ifstream;
using std::stringstream;
using std::string;

template <typename TValue>
class Image2DReader {
public:
    typedef TValue Value;
    typedef Image2D<Value> Image;
    static bool read(Image& img, ifstream &input)
    {
        std::cerr << "[Image2DWriter<TValue>::read] NOT IMPLEMENTED." << std::endl;
        return false;
    }
};

/// Specialization for gray-level images.
template <>
class Image2DReader<unsigned char> {
public:
    typedef unsigned char Value;
    typedef Image2D<Value> Image;
    static bool read(Image& img, ifstream &input) {
        int row = 0, col = 0, numrows = 0, numcols = 0, graylevel = 0;
        stringstream ss;
        string inputLine;
        string version;
        string comment;

        // entete du fichier
        // First line : version
        getline(input,inputLine);
        version = inputLine;

        // Second line : comment
        getline(input,inputLine);
        comment = inputLine;

        // Third line : size
        getline(input,inputLine);
        // on passe par un ss temporaire pour séparer num_col et num_row (c'est pas ouf mais ça marche)
        stringstream sstemp;
        sstemp << inputLine;
        sstemp >> numcols >> numrows;
        img = Image(numcols, numrows);

        // fourth line : graylevel
        getline(input,inputLine);
        graylevel = (unsigned int)std::stoi(inputLine);


        // Following lines : data
        // Continue with a stringstream
        ss << input.rdbuf();

        if (version == "P5"){
            unsigned char value;
            for (auto it = img.begin(); it != img.end(); ++it) {
                ss >> std::noskipws >> value;
                *it = value;
            }
        }
        else if (version == "P2"){
            unsigned int value; //on utilise un ui pour que la lecture dans le flux de '11' ne soit pas '1' '1'
            for (auto it = img.begin(); it != img.end(); ++it) {
                ss >> std::skipws >> value;
                *it = (unsigned char)value;
            }
        }else{
            std::cerr << "[Image2DWriter<TValue>::read] NOT IMPLEMENTED for " << version << " VERSION" << std::endl;
        }

        return true;
    }
};


/// Specialization for color images.
template <>
class Image2DReader<Color> {
public:
    typedef Color Value;
    typedef Image2D<Value> Image;
    static bool read(Image& img, ifstream &input) {
        int row = 0, col = 0, numrows = 0, numcols = 0, colorLevel = 0;
        stringstream ss;
        string inputLine;
        string version;
        string comment;

        // entete du fichier
        // First line : version
        getline(input,inputLine);
        version = inputLine;
        std::cout << "version: " << version << std::endl;

        /*
        // Second line : comment
        getline(input,inputLine);
        comment = inputLine;
        std::cout << "comment: " << comment << std::endl;
         */

        // Third line : size
        getline(input,inputLine);
        // on passe par un ss temporaire pour séparer num_col et num_row (c'est pas ouf mais ça marche)
        stringstream sstemp;
        sstemp << inputLine;
        sstemp >> numcols >> numrows;
        img = Image(numcols, numrows);
        std::cout << "numcols: " << numcols << " numrows: " << numrows <<std::endl;

        // fourth line : colorLevel
        getline(input,inputLine);
        colorLevel = std::stoi(inputLine);    // 255 en général
        std::cout << "colorLevel: " << colorLevel << std::endl;



        // Following lines : data
        // Continue with a stringstream
        ss << input.rdbuf();

        if (version == "P6"){
            unsigned char valueR; //on utilise un ui pour que la lecture dans le flux de '11' ne soit pas '1' '1'
            unsigned char valueG;
            unsigned char valueB;
            for (auto it = img.begin(); it != img.end(); ++it) {
                ss >> std::noskipws >> valueR;
                ss >> std::noskipws >> valueG;
                ss >> std::noskipws >> valueB;
                Color c  = Color(valueR, valueG, valueB);
                *it = c;
            }
        }else{
            std::cerr << "[Image2DWriter<TValue>::read] NOT IMPLEMENTED for " << version << " VERSION" << std::endl;
        }

        return true;
    }


};


#endif //TP2_IMAGE2DREADER_HPP
