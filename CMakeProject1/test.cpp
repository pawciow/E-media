#include <iostream>
#include <fstream>
#include <string.h>
using namespace std;
/*
int findSOS(const char * data, const int size)
{
	int i = 0;
	while(i<size)
	{
		if((int)(*(unsigned char*)&data[i]) == 0xff)
		{
			if((int)(*(unsigned char*)&data[i+1]) == 0xda)
			{
				return i;
			} 
		}
	i++;
	}
	return 0;
}

void xorEncrypt(char * toEncrypt, const char *key, const int size)
{

 

        int length = strlen(key);
        int znak, xorChar;
        int mod = 0;
 		int i = findSOS(toEncrypt, size);
 		i = i+2;

        do
        {
            if (mod >= length)
                mod=0;
            znak = toEncrypt[i];
            xorChar = znak^key[mod];
            mod++;
            toEncrypt[i] = xorChar;
            i++;

        }
        while (i < size - 2);
 		


}

int main () {
  streampos size;


  ifstream file ("robot_opiekunczy.jpg", ios::in|ios::binary|ios::ate);
  if (file.is_open())
  {
    size = file.tellg();
    cout << "Size:" << size << endl;
    char *memblock = new char[size];
    file.seekg (0, ios::beg);
    file.read (memblock, size);
    file.close();
    int a = (int)size;

    //cout << findSOS(memblock, size) << endl;

    cout << "the entire file content is in memory" << endl;
    
    for(int i = findSOS(memblock, size)+2; i<a-2 ; i++)
    {
      memblock[i] = 0x01;
    }
	

/////////////////////////
    //cout << hex <<  memblock[0] << endl;

    //xorEncrypt(memblock, "abcd", size);
    //xorEncrypt(memblock, "abcd", size);
    


    ofstream fileToSave;
    fileToSave.open("test.jpg");
      for(int i = 0; i<size; i++)
      {

             fileToSave <<  memblock[i];

      }
    fileToSave.close();

    delete[] memblock;
  }
  else cout << "Unable to open file";
  return 0;
}
*/
struct jpgImage
{
	char *image;
	int size;
	//jpg_headers::SOI_HEADER rawHeader;
	// jpgThumbnail thumbnail; // Temporaily cxommented as no miniature is attached to the first file
public:
	jpgImage(const char * fileName)
	{
		streampos sizes;
	  	ifstream file (fileName, ios::in|ios::binary|ios::ate);
		if (file.is_open())
		  {
		    sizes = file.tellg();
		    image = new char[size];

		    file.seekg (0, ios::beg);
		    file.read (image, size);
		    file.close();

		    size = (int) sizes;
		    cout << "Sizes:" << dec << sizes << endl;
		    cout << hex << (int)(*(unsigned char*) &image[1]) << endl;
		    cout << "the entire file content is in memory" << endl;
		   }
		else cout << "Unable to open file";
	}
	/*~jpgImage()
	{
		delete[] image;
	}*/
	int findSOS()
	{
		int i = 0;
		while(i<size)
		{
			if((int)(*(unsigned char*)&image[i]) == 0xff)
			{
				if((int)(*(unsigned char*)&image[i+1]) == 0xda)
				{
					return i;
				} 
			}
		i++;
		}
		return 0;
	}

	void xorEncrypt(const char *key)
	{
	        int length = strlen(key);
	        int znak, xorChar;
	        int mod = 0;
	 		int i = this->findSOS();
	 		i = i+2;
	        do
	        {
	            if (mod >= length) mod=0;
	            znak = image[i];
	            xorChar = znak^key[mod];
	            mod++;
	            image[i] = xorChar;
	            i++;

	        }
	        while (i < size - 2);
	}

	void saveToFile(const char* fileName)
	{
		ofstream fileToSave;
	    fileToSave.open(fileName);
		cout << "Size:" << dec << size << endl;
	      for(int i = 0; i<size; i++)
	      {
	      			
	      		cout << "i:" << dec << i << "Data: " << hex <<(int)(*(unsigned char*) &image[i]) << endl;
	             fileToSave <<  image[i];
	      }
	    fileToSave.close();
	}

	void damageImage()
	{
	for(int i = size/4; i<size/2 ; i++)
	    {
	      image[i] = 0x00;
	    }
	}


};

const char* fileName = "robot_opiekunczy.jpg";

int main()
{

	jpgImage img = jpgImage(fileName);
	img.saveToFile("test.jpg");
	return 0;
}