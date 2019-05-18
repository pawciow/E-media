#include "main.h"

#include "RSA.hpp"
int main()
{
    std::vector<char > d {'d','u','p','a'};
    RSA<long int> a(450, d);

    auto b = a.Encrypt();
    a.Decrypt(b);

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