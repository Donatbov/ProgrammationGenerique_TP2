#ifndef TP2_HISTOGRAMME_HPP
#define TP2_HISTOGRAMME_HPP

#include <array>
#include <algorithm>
#include "Image2D.hpp"

class Histogramme {
public:
    typedef std::array<double, 256> tabValue;
    typedef Image2D<unsigned char> GrayLevelImage2D;
    //constructor
    Histogramme(){
        m_histogramme.fill(0);
        m_histogramme_cummule.fill(0);
    }

    template <typename InputIterator>
    void init( InputIterator it, InputIterator itE ) {
        unsigned int nbPixel = itE-it;

        for ( ; it != itE; ++it) {   //on parcourt tous les pixels de l'image
            m_histogramme[*it] += 1.0/nbPixel;   //on incrémente la proportion au bon indice
        }
        // on crée ensuite l'histogramme cummulé
        m_histogramme_cummule = m_histogramme;
        for (int j = 1; j <= m_histogramme.size()-1; ++j) {
            m_histogramme_cummule[j] += m_histogramme_cummule[j-1];
        }

    }

    /**
    @return retourne une image en niveau de gris (2*256 x 200) qui représente l'histogramme de l'image
    */
    GrayLevelImage2D toImage(){
        int tailleY = 200;
        GrayLevelImage2D imgHisto = GrayLevelImage2D(2*256, tailleY, 255);
        double max = *std::max_element(m_histogramme.begin(), m_histogramme.end()); // max = le plus grand element dans m_histogramme

        for(int x = 0 ; x < m_histogramme.size() ; x++){
            for(int y = tailleY-1; y > (tailleY - (m_histogramme[x]*tailleY) / max) ; y-- ){
                imgHisto.at(x,y) = 0; //on met en noir la colonne x de hauteur 100 - (m_histogramme[x]*tailleY)/max
            }
        }

        //pareil pour l'histo cumulé
        for(int x = 0 ; x < m_histogramme_cummule.size() ; x++){
            for(int y = tailleY-1; y > (tailleY-(m_histogramme_cummule[x]*tailleY)) ; y-- ){
                imgHisto.at(x+255,y) = 0; //on met en noir la colonne x+255 de hauteur tailleY-(m_histogramme_cummule[x]*tailleY)
            }
        }
        return imgHisto;
    }

    /**
    @param j prend une valeur en entrée
    @return et retourne une autre valeur basée sur l'histogramme cummulé croissant
    */
    int egalisation( int j ) const {
        return (int)(255*m_histogramme_cummule[j]);
    }

private:
    tabValue m_histogramme;
    tabValue m_histogramme_cummule;
};

#endif //TP2_HISTOGRAMME_HPP
