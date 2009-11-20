#include <stdio.h>
#include <stdlib.h>
#include <Imlib2.h>

/*
Dual wallpaper generator
Copyright (C) 2009 Aleksi Räsänen <aleksi.rasanen@runosydan.net>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU Affero General Public License as
published by the Free Software Foundation, either version 3 of the
License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Affero General Public License for more details.

You should have received a copy of the GNU Affero General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
int 
main( int argc, char *argv[] )
{
  Imlib_Image input_image;
  Imlib_Image output_image;

  int image1_width, image1_height, image2_width, image2_height;
  int input_width, input_height, output_width;
  
  if( argc < 7 )  
    {
      printf( "Usage: %s inputfile img1_width img1_height ", argv[0] );
      printf( "img2_width img2_height output.jpg\n" ); 
      exit(1);
    }

  FILE *fp;
  fp = fopen( argv[1], "r" );

  if( fp == NULL ) 
    {
      printf( "File %s not found!\n", argv[1] );
      exit(1);
    }

  image1_width = atoi( argv[2] );
  image1_height = atoi( argv[3] );
  image2_width = atoi( argv[4] );
  image2_height = atoi( argv[5] );

  input_image = imlib_load_image( argv[1] );

  // Output image width must be selected by wider image
  if( image1_width > image2_width )
    output_width = image1_width;
  else
    output_width = image2_width;

  output_image = imlib_create_image( output_width,
				     image1_height + image2_height );

  if(! input_image )
    {
      printf( "Failed to load image %s\n", argv[1] );
      exit(1);
    }

  // Read original image size
  imlib_context_set_image( input_image );
  input_width = imlib_image_get_width();
  input_height = imlib_image_get_height();

  imlib_context_set_image( output_image );

  // Copy whole input image to output image
  imlib_blend_image_onto_image( input_image, 0, 0, 0, 
				input_width, input_height, 
				0, 0,
				image1_width, image1_height );

  imlib_blend_image_onto_image( input_image, 0, 0, 0,
				input_width, input_height,
				0, image1_height,
				image2_width, image2_height );

  imlib_save_image( argv[6] );
 

  return 0;
}
