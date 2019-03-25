#include "CMakeProject1.h"
#include <fstream>
#include <string>
#include <iostream>

using namespace std;

namespace jpg_headers
{
	struct SOI_HEADER
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

	std::ostream & operator << (std::ostream& os, const SOI_HEADER& soi)
	{
		os << "SOI_HEADER:" << std::endl;

		os << "SOI: 0x";
		for (int i = 0; i < 2; i++)
		{
			os << std::hex << (int) soi.SOI[i];
		}

		os << "APP0_HEADER:" << std::endl;
		os << std::endl << "APP0: 0x";
		for (int i = 0; i < 2; i++)
		{
			os << std::hex << (int) soi.APP0[i];
		}

		os << std::endl << "Length of segment excluding APP0 marker: ";
		for(auto i: soi.Length)
		    os << (int) i;

		os << std::endl << "Identifier: 0x";
		for (auto i: soi.Identifier)
		    os << hex << (int) i;

		os << std::endl << "Version of JFIF: ";
		for(auto i: soi.Version)
		    os << (int) i;

		os << std::endl << "Units used for Resolution: " << (int) soi.Units;

		os << std::endl << "Horizontal Resolution X: ";
		for(auto i: soi.Xdensity)
		    os  << (int) i;
        os << std::endl << "Horizontal Resolution Y: ";
        for(auto i: soi.Ydensity)
            os  << (int) i;


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
*/