
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

unsigned char* ppmRead(const char* filename, int* width, int* height ) {

   FILE* fp;
   int i, w, h, d;
   unsigned char* image;
   char head[70];		// max line <= 70 in PPM (per spec).

   fp = fopen( filename, "rb" );
   if ( !fp ) {
      perror(filename);
      return NULL;
   }

   // Grab first two chars of the file and make sure that it has the
   // correct magic cookie for a raw PPM file.
   fgets(head, 70, fp);
   if (strncmp(head, "P6", 2)) {
      printf("%s: Not a raw PPM file\n", filename);
      return NULL;
   }

   // Grab the three elements in the header (width, height, maxval).
   i = 0;
   while( i < 3 ) {
      fgets( head, 70, fp );
      if ( head[0] == '#' )		// skip comments.
         continue;
      if ( i == 0 )
         i += sscanf( head, "%d %d %d", &w, &h, &d );
      else if ( i == 1 )
         i += sscanf( head, "%d %d", &h, &d );
      else if ( i == 2 )
         i += sscanf( head, "%d", &d );
   }

   // Grab all the image data in one fell swoop.
   image = (unsigned char*) malloc( sizeof( unsigned char ) * w * h * 3 );
   fread( image, sizeof( unsigned char ), w * h * 3, fp );
   fclose( fp );

   *width = w;
   *height = h;
   return image;

}

GLuint createTexture(GLenum target, GLint internalformat, GLenum format, int w, int h, void *data)
{
    GLuint tex;
    glGenTextures(1, &tex);
    glBindTexture(target, tex);
    glTexParameteri(target, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(target, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(target, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(target, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(target, GL_GENERATE_MIPMAP_SGIS, GL_TRUE);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    printf("hello : %s", data);
    gluBuild2DMipmaps( GL_TEXTURE_2D, 3, w, h, GL_RGB, GL_UNSIGNED_BYTE, data);
    /* glTexImage2D(target, 0, internalformat, w, h, 0, format, GL_UNSIGNED_BYTE, data); */
    return tex;
}


GLuint loadTexture(const char *filename)
{
    unsigned char *data = 0;
    int width, height;
    data =  (GLubyte*) ppmRead(filename, &width, &height);
    if (!data)
    {
        printf("Error opening file '%s'\n", filename);
        return 0;
    }

    printf("Loaded '%s', %d x %d pixels\n", filename, width, height);

    return createTexture(GL_TEXTURE_2D, GL_RGBA8, GL_RGBA, width, height, data);
}


