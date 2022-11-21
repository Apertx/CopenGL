#include "texture.h"
#include <fcntl.h>
#include <stdlib.h>
#include <windows.h>
#include "GL.h"
#include "GLU.h"


#pragma pack(push, 1)
typedef struct {
	unsigned short    bfType;
	unsigned int    bfSize;         // размер файла
	unsigned int    bfReserved;     // 0       
	unsigned int    bfOffBits;      // смещение до поля данных
	unsigned int    biSize;         // размер струкуры в байтах
	unsigned int    biWidth;        // ширина в точках
	unsigned int    biHeight;       // высота в точках
	unsigned short    biPlanes;     // всегда должно быть 1
	unsigned short    biBitCount;   // 0 | 1 | 4 | 8 | 16 | 24 | 32
	unsigned int    biCompression;  // BI_RGB | BI_RLE8 | BI_RLE4 | BI_BITFIELDS | BI_JPEG | BI_PNG
	unsigned int    biSizeImage;       // количество байт в поле данных
	unsigned int    biXPelsPerMeter;   // горизонтальное разрешение, точек на дюйм
	unsigned int    biYPelsPerMeter;   // вертикальное разрешение, точек на дюйм
	unsigned int    biClrUsed;         // количество используемых цветов
	unsigned int    biClrImportant;    // количество существенных цветов
} BMPheader;

unsigned int loadTexture(const char *filename) {
	unsigned char *data;
	int file, i, j, data_size;
	BMPheader bh;
	unsigned int textureID;

	file = open(filename, O_RDONLY);
	if (file == 0)
		return 0;

	i = read(file, &bh, sizeof(BMPheader));
	if (i != sizeof(BMPheader))
		return 0;
	if (bh.bfType != 0x4D42)
		return 0;
	if (bh.biSize == 0)
		return 0;
	if (bh.biWidth == 0)
		return 0;
	if (bh.biHeight == 0)
		return 0;
	if (bh.biPlanes != 1)
		return 0;
	if (bh.biBitCount != 24 && bh.biBitCount != 32)
		return 0;
	data_size = bh.biWidth * bh.biHeight * bh.biBitCount / 8;
	if (bh.biCompression != 0)
		return 0;
	if (bh.biSizeImage != data_size)
		return 0;

	data = (unsigned char *) malloc(data_size);
	if (data == NULL)
		return 0;
	lseek(file, bh.bfOffBits, 0);
	i = read(file, data, data_size);
	/*if (i == data_size) {
		free(data);
		return 0;
	}*/
	close(file);

	switch (bh.biBitCount) {
	case 24:
		for (i = 0; i < data_size; i += 3) {
			data[i] ^= data[i + 2];
			data[i + 2] ^= data[i];
			data[i] ^= data[i + 2];
		}
		break;
	case 32:
		file = 0;
		for (i = 0; i < data_size; i += 4) {
			file = data[i];
			data[j] = data[i + 2];
			data[j + 1] = data[i + 1];
			data[j + 2] = file;
			j += 3;
		}
		break;
	}

	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);
	//glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, bh.biWidth, bh.biHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
	gluBuild2DMipmaps(GL_TEXTURE_2D, 3, bh.biWidth, bh.biHeight, GL_RGB, GL_UNSIGNED_BYTE, data);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
	free(data);
	return textureID;
}
