#include "CMakeProject1.h"
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
}

struct jpgImage
{
	jpg_headers::SOI_HEADER rawHeader;
	// jpgThumbnail thumbnail; // Temporaily cxommented as no miniature is attached to the first file
};

const char* fileName = R"(C:/Users/Pawel/source/repos/CMakeProject1/robot_opiekunczy.jpg)";

int main()
{
	fstream imageFile;
	imageFile.open(fileName, std::ios_base::binary | std::ios_base::in);
	if (!imageFile)
	{
		return 0;
	}
	auto header = jpg_headers::readJpgHeader(imageFile);

	cout << header << endl;
	int a; cin >> a;
	return 0;
}

/*
DOKUMENTACJA/Ważne linki:
https://en.wikipedia.org/wiki/JPEG
https://www.media.mit.edu/pia/Research/deepview/exif.html
https://www.get-metadata.com/result/0c42f250-c9e9-47f3-a3d8-d6511773b622
 https://superuser.com/questions/256582/how-to-get-the-file-header-size-of-tiff-image
 https://www.fileformat.info/format/tiff/egff.htm
*/