//
// Created by pawci on 18.05.2019.
//

#ifndef EMEDIA_JPG_H
#define EMEDIA_JPG_H
#include <fstream>
#include <string>
#include <iostream>

using namespace std;

namespace jpg_headers
{
    struct SOI_HEADER
    {
        struct JFIF_APP0
        {
            unsigned char SOI[2];          /* 00h  Start of Image Marker     */
            unsigned char APP0[2];         /* 02h  Application Use Marker    */
            unsigned char Length[2];       /* 04h  Length of APP0 Field      */
            unsigned char Identifier[5];   /* 06h  "JFIF" (zero terminated) Id String */
            unsigned char Version[2];      /* 07h  JFIF Format Revision      */
            unsigned char Units;           /* 09h  Units used for Resolution */ //  01 : Pixels per inch (2.54 cm
            unsigned char Xdensity[2];     /* 0Ah  Horizontal Resolution     */ //	0x78
            unsigned char Ydensity[2];     /* 0Ch  Vertical Resolution       */ //  0x78
            unsigned char XThumbnail;      /* 0Eh  Horizontal Pixel Count    */ //  0
            unsigned char YThumbnail;      /* 0Fh  Vertical Pixel Count      */ //  0

        };
        struct JFIF_APP1
        {
            unsigned char APP1_Marker[2];
            unsigned char Length[2];
            unsigned char EXIF_Header[6];
            struct TIFF_header
            {
                unsigned char Endian[2];
                unsigned char TIFF_version[2];
                unsigned char OFFSET_IFD[4];
            };
            TIFF_header Tiff;
            struct TIFF_Tags
            {
                // TODO: this
            };



        };

        JFIF_APP0 jfif0_header;
        JFIF_APP1 jfif1_header;

    };


}

struct jpgImage
{
    jpg_headers::SOI_HEADER rawHeader;
    // jpgThumbnail thumbnail; // Temporaily cxommented as no miniature is attached to the first file
};

const char* fileName = R"(C:/Users/Pawel/source/repos/CMakeProject1/robot_opiekunczy.jpg)";



#endif //EMEDIA_JPG_H
