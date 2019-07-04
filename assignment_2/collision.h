/*
*********************************************
*        Student Name: Ethan Houley         *
*      Student Number: n10353950            *
*           File Name: collision.h          *
*********************************************
*/
bool BoundingBox(double x0, double y0, int w0, int h0, double x1, double y1, int w1, int h1);
bool PixelCollision(int x0, int y0, int w0, int h0, uint8_t pixel0[], int x1, int y1, int w1, int h1, uint8_t pixel1[]);