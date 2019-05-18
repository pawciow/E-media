//
// Created by pawci on 18.05.2019.
//

#include "jpg.h"
namespace jpg_headers
{
std::ostream & operator << (std::ostream& os, const SOI_HEADER& soi)
{
    os << "SOI_HEADER:" << std::endl;

    os << "SOI: 0x";
    for (int i = 0; i < 2; i++)
    {
        os << std::hex << (int) soi.jfif0_header.SOI[i];
    }

    os << std::endl << "APP0_HEADER:" << std::endl;
    os << std::endl << "APP0: 0x";
    for (int i = 0; i < 2; i++)

    {
        os << std::hex << (int) soi.jfif0_header.APP0[i];
    }

    os << std::endl << "Length of segment excluding APP0 marker: ";
    for(auto i: soi.jfif0_header.Length)
        os << (int) i;

    os << std::endl << "Identifier: 0x";
    for (auto i: soi.jfif0_header.Identifier)
        os << hex << (int) i;

    os << std::endl << "Version of JFIF: ";
    for(auto i: soi.jfif0_header.Version)
        os << (int) i;

    os << std::endl << "Units used for Resolution: " << (int) soi.jfif0_header.Units;

    os << std::endl << "Horizontal Resolution X: ";
    for(auto i: soi.jfif0_header.Xdensity)
        os  << (int) i;
    os << std::endl << "Horizontal Resolution Y: ";
    for(auto i: soi.jfif0_header.Ydensity)
        os  << (int) i;

    os << std::endl << "Thumbnail:" << std::endl;

    os << (int) soi.jfif0_header.XThumbnail << " X, " << (int) soi.jfif0_header.YThumbnail << " Y" << std::endl;

    os << std::endl << "Start of APP1 header info:" << std::endl;
    os << "0x";
    for(int i =0;i< 2;i++)
        os << std::hex << (int)soi.jfif1_header.APP1_Marker[i] ;

    os <<"\n" << "APP1 Data Size: ";
    for(int i= 0;i < 2; i++)
        os << (int)soi.jfif1_header.Length[i];

    os <<"\n" << "EXIF Header: 0x";
    for(int i = 0;i < 6; i++)
        os << std::hex << (int) soi.jfif1_header.EXIF_Header[i];

    os << "\n" << "Endian: ";
    if(soi.jfif1_header.Tiff.Endian[0] == 'M' && soi.jfif1_header.Tiff.Endian[1] == 'M')
        os<< "Big(Motorola): ";
    for(int i = 0; i < 2; i++)
        os << soi.jfif1_header.Tiff.Endian[i];

    os << "\n" << "TIFF version: 0x";
    for(int i = 0; i < 2;i++)
        os << std::hex << (int)soi.jfif1_header.Tiff.TIFF_version[i];




    os << "\n\n";

    return os;
}

SOI_HEADER readJpgHeader(std::fstream& fs)
{
    SOI_HEADER header;
    fs.read((char*)&header, sizeof(SOI_HEADER));

    for (int i = 0; i < sizeof(SOI_HEADER); i++)
    {
        std::cout << std::hex << (int)((unsigned char*)&header)[i] << std::endl;
    }

    return header;
}
} // namespace jpg_headers
