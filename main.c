#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>

int main( int argc, char *argv[] )
{
	if( argc < 6 )
	{
		printf( "Give image as a first paramter!\n" );
		exit(1);
	}

	// Width 1 and 2 and Height 1 and 2
	int w1, w2, h1, h2;
	int width, height;

	// Set requested sizes to integers.
	w1 = atoi( argv[2] );
	h1 = atoi( argv[3] );
	w2 = atoi( argv[4] );
	h2 = atoi( argv[5] );

	// New pixbuf height
	height = h1+h2;

	// New pixbuf width
	if( w1 > w2 )
		width = w1;
	else
		width = w2;

	FILE *fp;
	fp = fopen( argv[1], "r" );

	if( fp == NULL )
	{
		printf( "File %s not found!\n", argv[1] );
		exit(1);
	}

	gtk_init( &argc, &argv );

	// Two pixbufs because two different images 
	GdkPixbuf *pb;
	GdkPixbuf *pb2;

	// Here we store final pixbuf what will be saved to file.
	GdkPixbuf *new_pb;

	GError *error = NULL;

	// New pixbuf is just empty
	new_pb = gdk_pixbuf_new( GDK_COLORSPACE_RGB, TRUE, 8,
		width, height );

	pb = gdk_pixbuf_new_from_file_at_scale( argv[1], w1, h1, 
		FALSE, &error );

	pb2 = gdk_pixbuf_new_from_file_at_scale( argv[1], w2, h2, 
		FALSE, &error );

	gdk_pixbuf_copy_area( pb, 0, 0, w1, h1, new_pb, 0, h2 );
	gdk_pixbuf_copy_area( pb2, 0, 0, w2, h2, new_pb, 0, 0 );
	gdk_pixbuf_save( new_pb, argv[6], "jpeg", &error, "quality", 
		"85", NULL );
	return 0;
}
