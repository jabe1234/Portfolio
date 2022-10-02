/*
 *  Key bindings:
 *  l          Toggles lighting
 *  F1         Toggle smooth/flat shading
 *  F2         Toggle local viewer mode
 *  F3         Toggle light distance (1/5)
 *  F4         Move to pond view
 *  F5         Move to Cabin and wind turbine view
 *  F6         Move to Forest View
 *  F7         Move to Powerline View
 *  F8         Move to Sandbox View
 *  F9         Invert bottom normal
 *  m          Toggles light movement
 *  []         Lower/rise light
 *  p          Toggles ortogonal/perspective projection
 *  o          Cycles through objects
 *  r/R        Randomizes the tree placement
 *  f          Turns fog on/off
 *  +/-        Change field of view of perspective
 *  x          Toggle axes
 *  arrows     Change view angle
 *  w/a/s/d    Move camera around area
 *  PgDn/PgUp  Zoom in and out
 *  0          Reset view angle
 *  ESC        Exit
 */
#include "CSCIx229.h"

int axes=1;       //  Display axes
int mode=1;       //  Projection mode
int projection = 0;
int view = 0;     //  Chnages scene rendered
int move=1;       //  Move light
int th=0;         //  Azimuth of view angle
int ph=0;         //  Elevation of view angle
int fov=55;       //  Field of view (for perspective)
int obj=0;        //  Scene/opbject selection
double asp=1;     //  Aspect ratio
double dim=15;     //  Size of world
int alpha=100;    //  Transparency
double Kth = 0; // Kelp displacement
int Fth = 0; // Fish displacment
double treelocation[5][5][4];
unsigned int texture[11];  //  Texture names
unsigned int treeTex[1]; // Stores tree texture
unsigned int skyTex[3]; // Stores sky texture
unsigned int cactusTex[1]; // stores cactus texture
unsigned int waterTex[3]; // stores water texture
unsigned int palmTex[3]; // stores palm tree textures
unsigned int pyramidTex[3]; // stores pyramid textures
unsigned int mountains[1]; // stores mountain texture
unsigned int doorTex[1]; // stores door texture
double rep=1;  //  Repetition
double height = 0;
double spark = 0; // determines if sparks displayed
int Wth = 0;
int FogCheck = 0;

int degree = 0; // angle in first person
int phi = 0; // angle of elevation in first person

double x = 0; // x location in first person
double y = 2; // y location in first person
double z = 0; // z location in first person

double gx = 1; // change of x step in first person
double gz = 1; // chnage of y step in first person

// Light values
int light     =   1;  // Lighting
int one       =   1;  // Unit value
int distance  =   5;  // Light distance
int inc       =  10;  // Ball increment
int smooth    =   1;  // Smooth/Flat shading
int local     =   0;  // Local Viewer Model
int emission  =   0;  // Emission intensity (%)
int ambient   =  10;  // Ambient intensity (%)
int diffuse   =  50;  // Diffuse intensity (%)
int specular  =   0;  // Specular intensity (%)
int shininess =   0;  // Shininess (power of two)
float shiny   =   1;  // Shininess (value)
int zh        =  90;  // Light azimuth
float ylight  =   0;  // Elevation of light
typedef struct {float x,y,z;} vtx;
typedef struct {int A,B,C;} tri;
#define n 500
vtx is[n];

/*
 *  Draw vertex in polar coordinates with normal
 *  Taken from class example 13
 */
static void Vertex(double th,double ph)
{
   double x = Sin(th)*Cos(ph);
   double y = Cos(th)*Cos(ph);
   double z =         Sin(ph);
   //  For a sphere at the origin, the position
   //  and normal vectors are the same
   glNormal3d(x,y,z);
   glVertex3d(x,y,z);
}

/*
 *  Draw a ball
 *     at (x,y,z)
 *     radius (r)
 *  Taken from class example 13
 */
static void ball(double x,double y,double z,double r)
{ 
   //  Save transformation
   glPushMatrix();
   //  Offset, scale and rotate
   glTranslated(x,y,z);
   glScaled(r,r,r);
   //  White ball with yellow specular
   float yellow[]   = {1.0,1.0,0.0,1.0};
   float Emission[] = {0.0,0.0,0.01*emission,1.0};
   glMaterialf(GL_FRONT,GL_SHININESS,shiny);
   glMaterialfv(GL_FRONT,GL_SPECULAR,yellow);
   glMaterialfv(GL_FRONT,GL_EMISSION,Emission);
   //  Bands of latitude
   for (int ph=-90;ph<90;ph+=inc)
   {
      glBegin(GL_QUAD_STRIP);
      for (int th=0;th<=360;th+=2*inc)
      {
         Vertex(th,ph);
         Vertex(th,ph+inc);
      }
      glEnd();
   }
   //  Undo transofrmations
   glPopMatrix();
}

// Taken from class example 18
// Creates a vertex with normal and texture coordinate for a point on a sphere
static void BallVertex(int th,int ph)
{
   double x = Cos(th)*Cos(ph);
   double y = Sin(th)*Cos(ph);
   double z =         Sin(ph);
   glNormal3d(x,y,z);
   glTexCoord2d(th/120.0,ph/60.0+0.5);
   glVertex3d(x,y,z);
}

/*
 *  Draw a ball
 *     at (x,y,z)
 *     radius (r)
 *  Taken from class example 13
 */
static void Texball(double x,double y,double z,double dx, double dy, double dz, int tex)
{
   //  Save transformation
   glPushMatrix();
   //  Offset, scale and rotate
   glTranslated(x,y,z);
   glScaled(dx,dy,dz);
   //  White ball with yellow specular
   float yellow[]   = {1.0,1.0,0.0,1.0};
   float Emission[] = {0.0,0.0,0.01*emission,1.0};
   glMaterialf(GL_FRONT,GL_SHININESS,shiny);
   glMaterialfv(GL_FRONT,GL_SPECULAR,yellow);
   glMaterialfv(GL_FRONT,GL_EMISSION,Emission);

   glEnable(GL_TEXTURE_2D);
      glTexEnvi(GL_TEXTURE_ENV , GL_TEXTURE_ENV_MODE , GL_MODULATE);
      glBindTexture(GL_TEXTURE_2D,texture[tex]);
   //  Bands of latitude
   for (int ph=-90;ph<90;ph+=inc)
   {
      glBegin(GL_QUAD_STRIP);
      for (int th=0;th<=360;th+=2*inc)
      {
         BallVertex(th,ph);
         BallVertex(th,ph+inc);
      }
      glEnd();
   }
   glDisable(GL_TEXTURE_2D);
   //  Undo transofrmations
   glPopMatrix();
}




/* 
 *  Draw sky box
 * Scaled by value D
 * adapted from class example 24
 */
static void Sky(double D)
{
   //  Textured white box dimension (-D,+D)
   glPushMatrix();
   glScaled(D,D,D);
   glEnable(GL_TEXTURE_2D);
   glTexEnvi(GL_TEXTURE_ENV , GL_TEXTURE_ENV_MODE , GL_MODULATE);
   glColor3f(1,1,1);


   glBindTexture(GL_TEXTURE_2D,skyTex[0]);


   // Sides of sky box
   glBegin(GL_QUADS);
   glTexCoord2f(0.00,0); glVertex3f(-1,-1,-1);
   glTexCoord2f(0.25,0); glVertex3f(+1,-1,-1);
   glTexCoord2f(0.25,1); glVertex3f(+1,+1,-1);
   glTexCoord2f(0.00,1); glVertex3f(-1,+1,-1);

   glTexCoord2f(0.25,0); glVertex3f(+1,-1,-1);
   glTexCoord2f(0.50,0); glVertex3f(+1,-1,+1);
   glTexCoord2f(0.50,1); glVertex3f(+1,+1,+1);
   glTexCoord2f(0.25,1); glVertex3f(+1,+1,-1);

   glTexCoord2f(0.50,0); glVertex3f(+1,-1,+1);
   glTexCoord2f(0.75,0); glVertex3f(-1,-1,+1);
   glTexCoord2f(0.75,1); glVertex3f(-1,+1,+1);
   glTexCoord2f(0.50,1); glVertex3f(+1,+1,+1);

   glTexCoord2f(0.75,0); glVertex3f(-1,-1,+1);
   glTexCoord2f(1.00,0); glVertex3f(-1,-1,-1);
   glTexCoord2f(1.00,1); glVertex3f(-1,+1,-1);
   glTexCoord2f(0.75,1); glVertex3f(-1,+1,+1);
   glEnd();


   glBindTexture(GL_TEXTURE_2D,skyTex[1]);

   glBegin(GL_QUADS); // Top of sky box
   glTexCoord2f(0.0,0); glVertex3f(+1,+1,-1);
   glTexCoord2f(0.5,0); glVertex3f(+1,+1,+1);
   glTexCoord2f(0.5,1); glVertex3f(-1,+1,+1);
   glTexCoord2f(0.0,1); glVertex3f(-1,+1,-1);
   glEnd();


   glBindTexture(GL_TEXTURE_2D,skyTex[1]);


   glBegin(GL_QUADS); // Bottom of skybox
   glTexCoord2f(1.0,1); glVertex3f(-1,-1,+1);
   glTexCoord2f(0.5,1); glVertex3f(+1,-1,+1);
   glTexCoord2f(0.5,0); glVertex3f(+1,-1,-1);
   glTexCoord2f(1.0,0); glVertex3f(-1,-1,-1);
   glEnd();

   //  Undo
   glDisable(GL_TEXTURE_2D);
   glPopMatrix();
}

/*
 * Draw little cactus
 * at (x,y,z)
 * scaled by (dx,dy,dz)
 */
static void littleCactus (double x, double y, double z, double dx, double dy, double dz)
{
   //  Save transformation
   glPushMatrix();
   //  Offset, scale and rotate
   glTranslated(x,y,z);
   glScaled(dx,dy,dz);

   // Enable textures
   glEnable(GL_TEXTURE_2D);
   glTexEnvi(GL_TEXTURE_ENV , GL_TEXTURE_ENV_MODE , GL_MODULATE);
   glBindTexture(GL_TEXTURE_2D,cactusTex[0]);//Binds cactus texture
   //  Bands of latitude
   for (int ph=-90;ph<90;ph+=inc)
   {
      glBegin(GL_QUAD_STRIP);
      for (int th=0;th<=360;th+=2*inc)
      {
         BallVertex(th,ph);
         BallVertex(th,ph+inc);
      }
      glEnd();
   }
   glDisable(GL_TEXTURE_2D);
   //  Undo transofrmations
   glPopMatrix();
}

/*
 * Draws larger cactus
 * at (x,y,z)
 * scaled by (dx,dy,dz)
 * rotated around the y axis by th
 */
static void largeCactus(double x, double y, double z, double dx, double dy, double dz, double th)
{
   //  Save transformation
   glPushMatrix();
   //  Offset, scale and rotate
   glTranslated(x,y,z);
   glScaled(dx,dy,dz);

   // Enables Textures
   glEnable(GL_TEXTURE_2D);
      glTexEnvi(GL_TEXTURE_ENV , GL_TEXTURE_ENV_MODE , GL_MODULATE);
      glBindTexture(GL_TEXTURE_2D,cactusTex[0]); // Binds cactus texture
   //  Bands of latitude
  

   // First - Main stem (cylinder) and cap to main stem (sphere)

   glColor3f(1,1,1);
      double index = 0;
      double cone = 1;
      double tail = 0;
      double wid = 1;
      glBegin(GL_QUADS); // Creates cyclinder for cactus body
         for (int th=0;th<=360;th+=10)
         {
            
            glNormal3f(wid*Cos(th),0,wid*Sin(th));
            glTexCoord2f(index/36,1); glVertex3d(wid*Cos(th),cone,wid*Sin(th));
            glTexCoord2f(index/36,0); glVertex3d(wid*Cos(th),tail,wid*Sin(th));
            index++;
            glNormal3f(wid*Cos(th+10),0,wid*Sin(th+10));
            glTexCoord2f(index/36,0); glVertex3d(wid*Cos(th+10),tail,wid*Sin(th+10));
            glTexCoord2f(index/36,1); glVertex3d(wid*Cos(th+10),cone,wid*Sin(th+10));
         }
         glEnd();

         littleCactus(0,cone,0,1,1,1); // Creates round top to the cactus




   
   glDisable(GL_TEXTURE_2D);
   //  Undo transofrmations
   glPopMatrix();
}

/*
 * Draw Ghost
 * at (x,y,z)
 * with (dx,dy,dz) scaler
 * Based on code from class example 13
 */
static void ghost(double x, double y, double z, double r, double th)
   {
      //  Save transformation
      glPushMatrix();
      //  Offset, scale and rotate
      glTranslated(x,y,z);
      glRotated(th,0,1,0);
      glScaled(r,r,r);

        // enable blending to allow tranlucent water
    glEnable(GL_BLEND);



      glDepthMask(GL_FALSE); // does not write over the z buffer
      glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

      const double cone = 3;
      const double tail = 1;
      const  double wid = 1;


      // Cone

      // Bottom
      glColor4f(1,1,1,.6);
      glEnable(GL_TEXTURE_2D);
      glTexEnvi(GL_TEXTURE_ENV , GL_TEXTURE_ENV_MODE , GL_MODULATE);
      glBindTexture(GL_TEXTURE_2D,texture[1]); // textured the ghost with a sheet to be like a bed sheet
      glBegin(GL_TRIANGLE_FAN);
         glNormal3f(0,-1,0);
         glTexCoord2f(.5,.5); glVertex3f(0,tail,0);
         for (int th=0;th<=360;th+=10)
         {
            glTexCoord2f(wid*Cos(th),wid*Sin(th)); glVertex3d(wid*Cos(th),tail,wid*Sin(th));
         }
         glEnd();


      // Side
      // Based on function from class example 8
      glBindTexture(GL_TEXTURE_2D,texture[1]); // textured the body with a cloth texture to be like a bedsheet
      glBegin(GL_TRIANGLES);
         for (int th=0;th<=360;th+=10)
         {
            glNormal3f(wid*Cos(th),cone,wid*Sin(th));
            glTexCoord2f(Cos(th),Sin(th)); glVertex3f(wid*Cos(th),tail,wid*Sin(th));
            glNormal3f(wid*Cos(th),cone,wid*Sin(th));
            glTexCoord2f(.5,.5); glVertex3d(0,cone,0);
            glNormal3f(wid*Cos(th + 10),cone,wid*Sin(th + 10));
            glTexCoord2f(Cos(th + 10),Sin(th + 10)); glVertex3d(wid*Cos(th + 10),tail,wid*Sin(th +10));
         }
         glEnd();
      //  Switch off textures so it doesn't apply to the rest
      
      // Head
      //  Bands of latitude
      glColor4f(1,1,1,.6);
      Texball(0,3,0,.5,.5,.5,1); // textured with cloth to show the ghost is wearing the traditional bedsheet

      // Eyes
      glColor4f(0,0,0,.6);
      ball(.5,3.1,.1, .1); // did not texture the black eyeballs as the eyes are meant to be comical and simplistic
      ball(.5,3.1,-.1,.1); // Also difficult to texture the black eyes and make it look good

      const double hat = 1;

      // Hat 
      glColor4f(1,1,1,.6);
      glBindTexture(GL_TEXTURE_2D,texture[8]); // creates stripes in the argyle colors with the texture
      glBegin(GL_POLYGON); // textured in argyle
         glNormal3f(0,1,0);
         for (int th=0;th<=360;th+=10)
         {
            glTexCoord2f(.5 + .5* Cos(th),.5 + .5* Sin(th)); glVertex3d(hat*Cos(th),tail + 2.4,hat*Sin(th));
         }
         glEnd();

      // Hat 
      glBindTexture(GL_TEXTURE_2D,texture[8]); // creates stripes in the argyle colors with the texture
      glBegin(GL_POLYGON); // textured in argyle
         glNormal3f(0,-1,0);
         for (int th=0;th<=360;th+=10)
         {
            glTexCoord2f(.5 + .5* Cos(th),.5 + .5* Sin(th)); glVertex3d(hat*Cos(th),tail + 2.2,hat*Sin(th));
         }
         glEnd();

      // Hat sides
      const double t = 3.4;
      const double b = 3.2;
      const double w = 1;
      glBindTexture(GL_TEXTURE_2D,texture[8]); // creates stripes in the argyle colors with the texture
      glBegin(GL_QUADS);
         for (int th=0;th<=360;th+=10)
         {
            glNormal3f(w*Cos(th),0,w*Sin(th));
            glTexCoord2f(0,1); glVertex3d(w*Cos(th),t,w*Sin(th));
            glTexCoord2f(0,0); glVertex3d(w*Cos(th),b,w*Sin(th));
            glNormal3f(w*Cos(th + 10),0,w*Sin(th + 10));
            glTexCoord2f(0,0); glVertex3d(w*Cos(th + 10),b,w*Sin(th + 10));
            glTexCoord2f(0,1); glVertex3d(w*Cos(th + 10),t,w*Sin(th + 10));
         }
         glEnd();

      // Hat sides
      const double top = 4.4;
      const double bottom = 3.4;
      const double width = .5;
      glBindTexture(GL_TEXTURE_2D,texture[8]); // creates stripes in the argyle colors with the texture
      double index = 0;
      glBegin(GL_QUADS);
         for (int th=0;th<=360;th+=10)
         {
            glNormal3f(width*Cos(th),0,width*Sin(th));
            glTexCoord2f(index/36,1); glVertex3d(width*Cos(th),top,width*Sin(th));
            glTexCoord2f(index/36,0); glVertex3d(width*Cos(th),bottom,width*Sin(th));
            index++;
            glNormal3f(width*Cos(th + 10),0,width*Sin(th + 10));
            glTexCoord2f(index/36,0); glVertex3d(width*Cos(th + 10),bottom,width*Sin(th + 10));
            glTexCoord2f(index/36,1); glVertex3d(width*Cos(th + 10),top,width*Sin(th + 10));
         }
         glEnd();

      // Hat top
      glBindTexture(GL_TEXTURE_2D,texture[8]);
      glBegin(GL_POLYGON); // textured with argile 
         glNormal3f(0,1,0);
         for (int th=0;th<=360;th+=10)
         {
            glTexCoord2f(.5 + .5*Cos(th),.5 + .5*Sin(th)); glVertex3d(width*Cos(th),top,width*Sin(th));
         }
         glEnd();
      glDisable(GL_TEXTURE_2D);

            glDepthMask(GL_TRUE); // pixels will be written to z buffer

      glDisable(GL_BLEND); // turns off blending
   
      //  Undo transofrmations
      glPopMatrix();
   }

/*
 * Draw a Headstone
 *  at (x,y,z)
 *  with (dx,dy,dz) scaler
 *  with (th) rotation in degrees
 */

static void gravestone(double x,double y,double z,double dx,double dy,double dz,double th)
{
   //  Save transformation
   glPushMatrix();
   //  Offset, scale and rotate
   glTranslated(x,y,z);
   glRotated(th,0,1,0);
   glScaled(dx,dy,dz);

   glEnable(GL_TEXTURE_2D);
   glTexEnvi(GL_TEXTURE_ENV , GL_TEXTURE_ENV_MODE , GL_MODULATE);
   glBindTexture(GL_TEXTURE_2D,texture[7]); // texture meant to look like a marble headstone

   glBegin(GL_QUADS);
   // Front
   glColor3f(1,1,1);
   glNormal3f(0,0,1);
   glTexCoord2f(0,0); glVertex3f(-.25,0,1);
   glTexCoord2f(0,1); glVertex3f(-.25,1,1);
   glTexCoord2f(1,1);glVertex3f(.25,1,1);
   glTexCoord2f(1,0); glVertex3f(.25,0,1);

   // Back
   glNormal3f(0,0,-1);
   glTexCoord2f(0,0); glVertex3f(-.25,0,-1);
   glTexCoord2f(0,1); glVertex3f(-.25,1,-1);
   glTexCoord2f(1,1); glVertex3f(.25,1,-1);
   glTexCoord2f(1,0); glVertex3f(.25,0,-1);

   // Sides
   glNormal3f(1,0,0);
   glTexCoord2f(0,0); glVertex3f(.25,0,-1);
   glTexCoord2f(0,.5);glVertex3f(.25,0,1);
   glTexCoord2f(.5,.5);glVertex3f(.25,1,1);
   glTexCoord2f(.5,0); glVertex3f(.25,1,-1);

   glNormal3f(-1,0,0);
   glTexCoord2f(0,0); glVertex3f(-.25,0,-1);
   glTexCoord2f(0,.5); glVertex3f(-.25,0,1);
   glTexCoord2f(.5,.5); glVertex3f(-.25,1,1);
   glTexCoord2f(.5,0); glVertex3f(-.25,1,-1);

   // Top (TEMP)

   glNormal3f(0,1,0);
   glTexCoord2f(0,0); glVertex3f(-.25,1,-1);
   glTexCoord2f(0,.5);glVertex3f(-.25,1,1);
   glTexCoord2f(.5,.5); glVertex3f(.25,1,1);
   glTexCoord2f(.5,0); glVertex3f(.25,1,-1);

   glEnd();

    //  Switch off textures so it doesn't apply to the rest
      glDisable(GL_TEXTURE_2D);

   //  Undo transofrmations
   glPopMatrix();

}

/* 
 * Draw a Tree
 * as (x,y,z)
 * scaled by (dx,dy,dz)
 * Based on code from class example 8
 */

static void tree(double x, double y, double z, double dx, double dy, double dz)
   {
      //  Save transformation
      glPushMatrix();
      //  Offset, scale and rotate
      glTranslated(x,y,z);
      glScaled(dx,dy,dz);

      //  gray box with gray specular
      float gray[]   = {0.1,0.1,0.1,1.0};
      float Emission[] = {0.0,0.0,0.01*emission,1.0};
      glColor3f(1,1,1);
      glMaterialf(GL_FRONT,GL_SHININESS,shiny);
      glMaterialfv(GL_FRONT,GL_SPECULAR,gray);
      glMaterialfv(GL_FRONT,GL_EMISSION,Emission);

      const double cone = 2;
      const double tail = 0;
      const  double wid = 1;
      const double leave = 2;

      // Trunk 
      // Based on code from class example 8
      glEnable(GL_TEXTURE_2D);
      glTexEnvi(GL_TEXTURE_ENV , GL_TEXTURE_ENV_MODE , GL_MODULATE);
      glBindTexture(GL_TEXTURE_2D,texture[0]); // bark of the tree
      glColor3f(1,1,1);
      double index = 0;
      glBegin(GL_QUADS);
         for (int th=0;th<=360;th+=10)
         {
            
            glNormal3f(wid*Cos(th),0,wid*Sin(th));
            glTexCoord2f(index/36,1); glVertex3d(wid*Cos(th),cone,wid*Sin(th));
            glTexCoord2f(index/36,0); glVertex3d(wid*Cos(th),tail,wid*Sin(th));
            index++;
            glNormal3f(wid*Cos(th+10),0,wid*Sin(th+10));
            glTexCoord2f(index/36,0); glVertex3d(wid*Cos(th+10),tail,wid*Sin(th+10));
            glTexCoord2f(index/36,1); glVertex3d(wid*Cos(th+10),cone,wid*Sin(th+10));
         }
         glEnd();
      //  Switch off textures so it doesn't apply to the rest

      // Leaves
      glColor3f(0,.8,0);
      glBindTexture(GL_TEXTURE_2D,texture[3]); // needles of the tree

      glBegin(GL_TRIANGLES);
         for (int th=0;th<=360;th+=10)
         {
            glNormal3f(leave*Cos(th),cone + 2,leave*Sin(th));
            glTexCoord2f(.5*Cos(th),.5*Sin(th)); glVertex3f(leave*Cos(th),tail + 2,leave*Sin(th));
            glNormal3f(leave*Cos(th),cone + 2,leave*Sin(th));
            glTexCoord2f(0,0); glVertex3d(0,cone + 2,0);
            glNormal3f(leave*Cos(th+ 10),cone + 2,leave*Sin(th+ 10));
            glTexCoord2f(.5*Cos(th +10),.5*Sin(th + 10)); glVertex3d(leave*Cos(th + 10),tail + 2,leave*Sin(th +10));
         }
         glEnd();
      

      
      glBegin(GL_TRIANGLE_FAN); //  Bottom of the leaves
         glNormal3f(0,-1,0);
         glVertex3f(0,tail + 2,0);
         for (int th=0;th<=360;th+=10)
         {
            glTexCoord2f(Cos(th),Sin(th)); glVertex3d(leave*Cos(th),tail + 2,leave*Sin(th));
         }
         glEnd();
   
    glDisable(GL_TEXTURE_2D);

      //  Undo transofrmations
      glPopMatrix();
      
   }
/*
 * draws coconut
 * at (x,y,z)
 * scaled by (r,r,r)
 */
static void coconut(double x, double y, double z, double r)
{
   //  Save transformation
   glPushMatrix();
   //  Offset, scale and rotate
   glTranslated(x,y,z);
   glScaled(r,r,r);

   // Enables textures
   glEnable(GL_TEXTURE_2D);
      glTexEnvi(GL_TEXTURE_ENV , GL_TEXTURE_ENV_MODE , GL_MODULATE);
      glBindTexture(GL_TEXTURE_2D,palmTex[1]); // Binds coconut texture
   //  Bands of latitude
   for (int ph=-90;ph<90;ph+=inc)
   {
      glBegin(GL_QUAD_STRIP);
      for (int th=0;th<=360;th+=2*inc)
      {
         BallVertex(th,ph);
         BallVertex(th,ph+inc);
      }
      glEnd();
   }
   glDisable(GL_TEXTURE_2D);
   //  Undo transofrmations
   glPopMatrix();
}

/*
 * draws a log
 * at (x,y,z)
 * scaled by (dx,dy,dz)
 * rotated by th around the x axis, ph around the z axis, and yh around the y axis
 */
static void wood(double x, double y, double z, double dx, double dy, double dz, double th, double ph, double yh)
{
   //  Save transformation
   glPushMatrix();
   //  Offset, scale and rotate
   glTranslated(x,y,z);
   glRotated(th,1,0,0);
   glRotated(ph,0,0,1);
   glRotated(yh,0,1,0);
   glScaled(dx,dy,dz);

   // Trunk 
      // Based on code from class example 8
      glEnable(GL_TEXTURE_2D);
      glTexEnvi(GL_TEXTURE_ENV , GL_TEXTURE_ENV_MODE , GL_MODULATE);
      glBindTexture(GL_TEXTURE_2D,texture[0]); // bark of the tree
      glColor3f(1,1,1);

      const double cone = 1;
      const double tail = -1;
      const  double wid = .5;
      double index = 0;
      glBegin(GL_QUADS); // Trunk of log
         for (int th=0;th<=360;th+=10)
         {
            
            glNormal3f(wid*Cos(th),0,wid*Sin(th));
            glTexCoord2f(index/36,1); glVertex3d(wid*Cos(th),cone,wid*Sin(th));
            glTexCoord2f(index/36,0); glVertex3d(wid*Cos(th),tail,wid*Sin(th));
            index++;
            glNormal3f(wid*Cos(th+10),0,wid*Sin(th+10));
            glTexCoord2f(index/36,0); glVertex3d(wid*Cos(th+10),tail,wid*Sin(th+10));
            glTexCoord2f(index/36,1); glVertex3d(wid*Cos(th+10),cone,wid*Sin(th+10));
         }
         glEnd();

         glBindTexture(GL_TEXTURE_2D,treeTex[0]); // end of the log

         //Top
         glBegin(GL_POLYGON); // end of log
         glNormal3f(0,1,0);
         for (int th=0;th<=360;th+=10)
         {
            glTexCoord2f(.5 + .5* Cos(th),.5 + .5* Sin(th)); glVertex3d(wid*Cos(th),cone,wid*Sin(th));
         }
         glEnd();

         //Bottom
         glBegin(GL_POLYGON); // other end of log
         glNormal3f(0,-1,0);
         for (int th=0;th<=360;th+=10)
         {
            glTexCoord2f(.5 + .5* Cos(th),.5 + .5* Sin(th)); glVertex3d(wid*Cos(th),tail,wid*Sin(th));
         }
         glEnd();


      //  Switch off textures so it doesn't apply to the rest
      glDisable(GL_TEXTURE_2D);

      glPopMatrix();
}

/*
 * draws dead tree
 * at (x,y,z)
 * scaled by (dx,dy,dz)
 * rotated by th around the y axis
 */
static void deadTree(double x, double y, double z, double dx, double dy, double dz, double th)
{
   //  Save transformation
   glPushMatrix();
   //  Offset, scale and rotate
   glTranslated(x,y,z);
   glRotated(th,1,0,0);
   glScaled(dx,dy,dz);

   // Draws logs to form dead tree
   wood(0,2,0,1,2,1,0,0,0);
   wood(1,4.5,0,1,1.5,1,0,135,0);
   wood(-1,4.5,0,1,1.5,1,0,225,0);
   wood(0,4.5,-1,1,1.5,1,135,0,0);
   wood(0,4.5,1,1,1.5,1,225,0,0);

   glPopMatrix();
}


/*
 * draws a fish
 * at (x,y,z)
 * scaled by (dx,dy,dz)
 * rotated by th around the y axis
 */
static void fish(double x, double y, double z, double dx, double dy, double dz, double th, int color)
{
    //  Save transformation
      glPushMatrix();
      //  Offset, scale and rotate
      glTranslated(x,y,z);
      glRotated(th,0,1,0);
      glScaled(dx,dy,dz);
      // glRotated(th,0,1,0); // Going to rotate fish to swim in a circle

      //  gray box with gray specular
      float gray[]   = {0.1,0.1,0.1,1.0};
      float Emission[] = {0.0,0.0,0.01*emission,1.0};
      glColor3f(1,1,1);
      glMaterialf(GL_FRONT,GL_SHININESS,shiny);
      glMaterialfv(GL_FRONT,GL_SPECULAR,gray);
      glMaterialfv(GL_FRONT,GL_EMISSION,Emission);

      //Post
      const double cone = 1;
      const double tail = 0;
      const  double wid = .2;
      if (color == 0)
      {
         glColor4f(1,0,0,alpha); // red fish
      }
      else if (color == 1)
      {
         glColor4f(.5,0,.5,alpha); // purple fish
      }
      else if (color == 2)
      {
         glColor4f(0,.5,.5,alpha); // blue fish
      }

      // Enables textures
      glEnable(GL_TEXTURE_2D);
      glTexEnvi(GL_TEXTURE_ENV , GL_TEXTURE_ENV_MODE , GL_MODULATE);
      glBindTexture(GL_TEXTURE_2D,waterTex[1]); // binds scale texture
      double index = 0;

          glBegin(GL_QUADS); // Body of fish
         for (int th=0;th<=360;th+=10)
         {
            glNormal3f(0,wid*Cos(th),wid*Sin(th));
            glTexCoord2f(index/36,1); glVertex3d(cone,wid*Cos(th),wid*Sin(th));
            glTexCoord2f(index/36,0); glVertex3d(tail,wid*Cos(th),wid*Sin(th));
            index++;
            glNormal3f(0,wid*Cos(th+10),wid*Sin(th+10));
            glTexCoord2f(index/36,0); glVertex3d(tail,wid*Cos(th+10),wid*Sin(th+10));
            glTexCoord2f(index/36,1); glVertex3d(cone,wid*Cos(th+10),wid*Sin(th+10));
         }
         glEnd();

            // Top
               glBegin(GL_POLYGON); // Front of the fish body
               glNormal3f(1,0,0);
                     for (int th=0;th<=360;th+=10)
                     {
                        glTexCoord2f(.5 + .5*Cos(th),.5 + .5*Sin(th)); glVertex3d(cone,wid*Cos(th),wid*Sin(th));
                     }
               glEnd();

               // bottom 
               glBegin(GL_POLYGON); // back of the fish body
               glNormal3f(-1,0,0);
                     for (int th=0;th<=360;th+=10)
                     {
                        glTexCoord2f(.5 + .5*Cos(th),.5 + .5*Sin(th)); glVertex3d(tail,wid*Cos(th),wid*Sin(th));
                     }
               glEnd();

            // Head
               double head = 1.2;
               double headWid = 0.1;
             glBegin(GL_QUADS); // cone of the fish head
               for (int th=0;th<=360;th+=10)
               {
                  glNormal3f(head-cone,wid*Cos(th),wid*Sin(th));
                  glTexCoord2f(index/72,1); glVertex3d(head,headWid*Cos(th),headWid*Sin(th));
                  glTexCoord2f(index/72,0); glVertex3d(cone,wid*Cos(th),wid*Sin(th));
                  index++;
                  glNormal3f(cone,wid*Cos(th + 10),wid*Sin(th + 10));
                  glTexCoord2f(index/72,0); glVertex3d(cone,wid*Cos(th+10),wid*Sin(th+10));
                  glTexCoord2f(index/72,1); glVertex3d(head,headWid*Cos(th+10),headWid*Sin(th+10));
               }
               glEnd();

            // Nose
            // Top
               glBegin(GL_POLYGON); // fish nose
               glNormal3f(1,0,0);
                     for (int th=0;th<=360;th+=10)
                     {
                        glTexCoord2f(.5 + .5*Cos(th),.5 + .5*Sin(th)); glVertex3d(head,headWid*Cos(th),headWid*Sin(th));
                     }
               glEnd();

            //fins
            glBegin(GL_TRIANGLES);
            glNormal3f(0,0,1);
            glTexCoord2f(0,1); glVertex3d(cone-.3,wid+.1,0);
            glTexCoord2f(1,1); glVertex3d(tail+.3,wid+.1,0);
            glTexCoord2f(0,.5); glVertex3d(cone/2,wid-.2,0);
            glEnd();


      glDisable(GL_TEXTURE_2D);

      glColor3f(0,0,0); // Fish eyes
      ball(1.1,.11,.11,.03);
      ball(1.1,.11,-.11,.03);

      // Undo transformations
      glPopMatrix();
}


/* 
 * draws water that is translucent to see fish below
 */
static void water()
{
   //  Save transformation
      glPushMatrix();
      

      fish(5*Sin(Fth),-2,5*Cos(Fth),2,2,2,Fth, 0); // draws a fish under the water

      fish(7*Sin(Fth + 90),-3,7*Cos(Fth + 90),2,2,2,Fth + 90, 1); // draws a fish under the water

      fish(-3*Sin(Fth + 90),-3,-3*Cos(Fth + 90),2,2,2,Fth - 90, 2); // draws a fish under the water


      // enable blending to allow tranlucent water
    glEnable(GL_BLEND);



      glDepthMask(GL_FALSE); // does not write over the z buffer
      glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

              glEnable(GL_TEXTURE_2D);
      glTexEnvi(GL_TEXTURE_ENV , GL_TEXTURE_ENV_MODE , GL_MODULATE);
      glBindTexture(GL_TEXTURE_2D,waterTex[0]); 
      
      glColor4f(1,1,1, .7);
      glNormal3f(0,1,0);
      glBegin(GL_QUADS); // draws translucent water layer
      glTexCoord2f(0,0); glVertex3f(-12,-.05,-12);
      glTexCoord2f(0,12); glVertex3f(-12,-.05,12);
      glTexCoord2f(12,12); glVertex3f(12,-.05,12);
      glTexCoord2f(12,0); glVertex3f(12,-.05,-12);
      glEnd();

      glDepthMask(GL_TRUE); // pixels will be written to z buffer

      glDisable(GL_BLEND); // turns off blending



      glPopMatrix();
}

/*
 * draws pyramid
 * at (x,y,z)
 * scaled by (dx,dy,dz)
 */
static void pyramid(double x, double y, double z, double dx, double dy, double dz, double height)
{
   //  Save transformation
      glPushMatrix();
      //  Offset, scale and rotate
      glTranslated(x,y,z);
      glScaled(dx,dy,dz);

      glColor3f(1,1,0);

      //Enables textures
      glEnable(GL_TEXTURE_2D);
      glTexEnvi(GL_TEXTURE_ENV , GL_TEXTURE_ENV_MODE , GL_MODULATE);
      glBindTexture(GL_TEXTURE_2D,pyramidTex[0]); // binds limestone texture

      glBegin(GL_TRIANGLES); // each face of the pyramid
      glNormal3f(0,1,-.5);
      glTexCoord2f(0,0); glVertex3d(-.5,0,-.5);
      glTexCoord2f(.5,1); glVertex3f(0,1,0);
      glTexCoord2f(1,0); glVertex3f(.5,0,-.5);

      glNormal3f(.5,1,0);
      glTexCoord2f(0,0); glVertex3d(.5,0,-.5);
      glTexCoord2f(.5,1); glVertex3f(0,1,0);
      glTexCoord2f(1,0); glVertex3f(.5,0,.5);

      glNormal3f(0,1,.5);
      glTexCoord2f(0,0); glVertex3d(.5,0,.5);
      glTexCoord2f(.5,1); glVertex3f(0,1,0);
      glTexCoord2f(1,0); glVertex3f(-.5,0,.5);

      glNormal3f(-.5,1,0);
      glTexCoord2f(0,0); glVertex3d(-.5,0,.5);
      glTexCoord2f(.5,1); glVertex3f(0,1,0);
      glTexCoord2f(1,0); glVertex3f(-.5,0,-.5);
      glEnd();

        //  Switch off textures so it doesn't apply to the rest
      glDisable(GL_TEXTURE_2D);


      glPopMatrix();



}

/*
 * draws a fencepost
 * at (x,y,z)
 * scaled by (dx,dy,dz)
 * rotated by th around the y axis
 */
static void Fencepost(double x,double y,double z,
                 double dx,double dy,double dz,
                 double th)
{
     //  Save transformation
   glPushMatrix();
   //  Offset
   glTranslated(x,y,z);
   glRotated(th,0,1,0);
   glScaled(dx,dy,dz);

   //  White ball with yellow specular
   float darkGreen[]   = {0,0.3,0.0,1.0};
   float Emission[] = {0.0,0.0,0.01*emission,1.0};
   glMaterialf(GL_FRONT,GL_SHININESS,shiny);
   glMaterialfv(GL_FRONT,GL_SPECULAR,darkGreen);
   glMaterialfv(GL_FRONT,GL_EMISSION,Emission);

   // Fencepost
   glColor3f(1,1,1);
   glEnable(GL_TEXTURE_2D);
      glTexEnvi(GL_TEXTURE_ENV , GL_TEXTURE_ENV_MODE , GL_MODULATE);
      glBindTexture(GL_TEXTURE_2D,5); // wooden fence posts
    glBegin(GL_QUADS);
   
   // Front
   glNormal3f(0,0,-1);
   glTexCoord2f(0,0); glVertex3d(-.1,0,-.1);
   glTexCoord2f(0,1); glVertex3d(-.1,1,-.1);
   glTexCoord2f(1,1); glVertex3d(.1,1,-.1);
   glTexCoord2f(1,0); glVertex3d(.1,0,-.1);

   // Side
   glNormal3f(1,0,0);
   glTexCoord2f(0,0); glVertex3d(.1,0,-.1);
   glTexCoord2f(0,1); glVertex3d(.1,1,-.1);
   glTexCoord2f(1,1); glVertex3d(.1,1,.1);
   glTexCoord2f(1,0); glVertex3d(.1,0,.1);

   // Back
   glNormal3f(0,0,1);
   glTexCoord2f(0,0); glVertex3d(.1,0,.1);
   glTexCoord2f(0,1); glVertex3d(.1,1,.1);
   glTexCoord2f(1,1); glVertex3d(-.1,1,.1);
   glTexCoord2f(1,0); glVertex3d(-.1,0,.1);

   // Side
   glNormal3f(-1,0,0);
   glTexCoord2f(0,0); glVertex3d(-.1,0,.1);
   glTexCoord2f(0,1); glVertex3d(-.1,1,.1);
   glTexCoord2f(1,1); glVertex3d(-.1,1,-.1);
   glTexCoord2f(1,0); glVertex3d(-.1,0,-.1);

   // Top
   glNormal3f(0,1,0);
   glTexCoord2f(0,0); glVertex3d(-.1,1,-.1);
   glTexCoord2f(0,1); glVertex3d(-.1,1,.1);
   glTexCoord2f(1,1); glVertex3d(.1,1,.1);
   glTexCoord2f(1,0); glVertex3d(.1,1,-.1);
   glEnd();
   glDisable(GL_TEXTURE_2D);



   glPopMatrix();
}

// Taken from class example 18
// Generates points on a sphere with normals pointed towards center of sphere
static void InverseBallVertex(int th,int ph)
{
   double x = Cos(th)*Cos(ph);
   double y = Sin(th)*Cos(ph);
   double z =         Sin(ph);
   glNormal3d(-x,-y,-z);
   glTexCoord2d(th/120.0,ph/60.0+0.5);
   glVertex3d(x,y,z);
}

/*
 * draws grass to outline the pond
 */
static void quarterFillIN(int th)
{
   glPushMatrix();

   glRotated(th,0,1,0);
   
      glEnable(GL_TEXTURE_2D);
      glTexEnvi(GL_TEXTURE_ENV , GL_TEXTURE_ENV_MODE , GL_MODULATE);
      glBindTexture(GL_TEXTURE_2D,texture[2]);
   glNormal3f(0,1,0);
   glBegin(GL_POLYGON);
   glTexCoord2f(1,1); glVertex3d(1,0,1);
   glTexCoord2f(0,1); glVertex3d(0,0,1);
   for (int th = 90; th >= 0; th -= inc)
   {
      glTexCoord2f(Cos(th),Sin(th)); glVertex3d(Cos(th),0,Sin(th));
   }
   glTexCoord2f(1,1); glVertex3d(1,0,1);
   glEnd();
    //glDisable(GL_TEXTURE_2D);

   glPopMatrix();
}

static void pond(double x, double y, double z, double dx, double dy, double dz)
{
    //  Save transformation
   glPushMatrix();
   //  Offset, scale and rotate
   glTranslated(x,y,z);
   glScaled(dx,dy,dz);
   //  White ball with yellow specular
   float yellow[]   = {1.0,1.0,0.0,1.0};
   float Emission[] = {0.0,0.0,0.01*emission,1.0};
   glMaterialf(GL_FRONT,GL_SHININESS,shiny);
   glMaterialfv(GL_FRONT,GL_SPECULAR,yellow);
   glMaterialfv(GL_FRONT,GL_EMISSION,Emission);

   glEnable(GL_TEXTURE_2D);
      glTexEnvi(GL_TEXTURE_ENV , GL_TEXTURE_ENV_MODE , GL_MODULATE);
      glBindTexture(GL_TEXTURE_2D,waterTex[2]);
   //  Bands of latitude
   for (int ph=-90;ph<90;ph+=inc)
   {
      glBegin(GL_QUAD_STRIP);
      for (int th=180;th<=360;th+=2*inc) // generates pong bottom 
      {
         InverseBallVertex(th,ph);
         InverseBallVertex(th,ph+inc);
      }
      glEnd();
   }

   for (int i = 0; i < 360; i += 90)
   {
      quarterFillIN(i); // draws grass around pond
   }

   glBegin(GL_QUADS); // draws grass for ground away from pond
   glNormal3f(0,1,0);
   glTexCoord2f(5,5); glVertex3f(5,0,5);
   glTexCoord2f(-5,5); glVertex3f(-5,0,5);
   glTexCoord2f(-5,0); glVertex3f(-5,0,1);
   glTexCoord2f(5,0); glVertex3f(5,0,1);

   glTexCoord2f(5,5); glVertex3f(5,0,-5);
   glTexCoord2f(-5,5); glVertex3f(-5,0,-5);
   glTexCoord2f(-5,0); glVertex3f(-5,0,-1);
   glTexCoord2f(5,0); glVertex3f(5,0,-1);

   glTexCoord2f(5,5); glVertex3f(5,0,1);
   glTexCoord2f(-5,5); glVertex3f(1,0,1);
   glTexCoord2f(-5,0); glVertex3f(1,0,-1);
   glTexCoord2f(5,0); glVertex3f(5,0,-1);

   glTexCoord2f(5,5); glVertex3f(-5,0,1);
   glTexCoord2f(-5,5); glVertex3f(-1,0,1);
   glTexCoord2f(-5,0); glVertex3f(-1,0,-1);
   glTexCoord2f(5,0); glVertex3f(-5,0,-1);

   glEnd();

   

   //  Undo transofrmations
   glPopMatrix();
}

/* draws connection between fencepost
 * at (x,y,z)
 * scaled by (dx,dy,dz)
 * rotated by th around the y axis
 */
static void fence(double x,double y,double z,
                 double dx,double dy,double dz,
                 double th)
{
      //  Save transformation
   glPushMatrix();
   //  Offset
   glTranslated(x,y,z);
   glRotated(th,0,1,0);
   glScaled(dx,dy,dz);

   //  White ball with yellow specular
   float darkGreen[]   = {0,0.3,0.0,1.0};
   float Emission[] = {0.0,0.0,0.01*emission,1.0};
   glMaterialf(GL_FRONT,GL_SHININESS,shiny);
   glMaterialfv(GL_FRONT,GL_SPECULAR,darkGreen);
   glMaterialfv(GL_FRONT,GL_EMISSION,Emission);

   // Fence connections
   glColor3f(1,1,1);

   glEnable(GL_TEXTURE_2D);
      glTexEnvi(GL_TEXTURE_ENV , GL_TEXTURE_ENV_MODE , GL_MODULATE);
      glBindTexture(GL_TEXTURE_2D,5); // wooden fence posts

   glBegin(GL_QUADS);

   // Sides
   glNormal3f(0,-1,0);
   glTexCoord2f(0,0); glVertex3d(-.1,-.1,-.5);
   glTexCoord2f(0,1); glVertex3d(-.1,-.1,.5);
   glTexCoord2f(1,1); glVertex3d(.1,-.1,.5);
   glTexCoord2f(1,0); glVertex3d(.1,-.1,-.5);

   glNormal3f(1,0,0);
   glTexCoord2f(0,0); glVertex3d(.1,-.1,-.5);
   glTexCoord2f(0,1); glVertex3d(.1,-.1,.5);
   glTexCoord2f(1,1); glVertex3d(.1,.1,.5);
   glTexCoord2f(1,0); glVertex3d(.1,.1,-.5);

   glNormal3f(0,1,0);
   glTexCoord2f(0,0); glVertex3d(.1,.1,-.5);
   glTexCoord2f(0,1); glVertex3d(.1,.1,.5);
   glTexCoord2f(1,1); glVertex3d(-.1,.1,.5);
   glTexCoord2f(1,0); glVertex3d(-.1,.1,-.5);

   glNormal3f(-1,0,0);
   glTexCoord2f(0,0); glVertex3d(-.1,.1,-.5);
   glTexCoord2f(0,1); glVertex3d(-.1,.1,.5);
   glTexCoord2f(1,1); glVertex3d(-.1,-.1,.5);
   glTexCoord2f(1,0); glVertex3d(-.1,-.1,-.5);

   glNormal3f(0,0,1);
   glTexCoord2f(0,0); glVertex3f(-.1,-.1,.5);
   glTexCoord2f(1,0); glVertex3f(.1,-.1,.5);
   glTexCoord2f(1,1); glVertex3f(.1,.1,.5);
   glTexCoord2f(0,1); glVertex3f(-.1,.1,.5);

   glNormal3f(0,0,-1);
   glTexCoord2f(0,0); glVertex3f(-.1,-.1,-.5);
   glTexCoord2f(1,0); glVertex3f(.1,-.1,-.5);
   glTexCoord2f(1,1); glVertex3f(.1,.1,-.5);
   glTexCoord2f(0,1); glVertex3f(-.1,.1,-.5);
   glEnd();
     glDisable(GL_TEXTURE_2D);

   glPopMatrix();


}

/*
 * draws whole fence
 * at (x,y,z)
 * scaled by (dx,dy,dz)
 * rotated by th around the y axis
 */
static void Fence(double x,double y,double z,
                 double dx,double dy,double dz,
                 double th)
{
       //  Save transformation
   glPushMatrix();
   //  Offset
   glTranslated(x,y,z);
   glRotated(th,0,1,0);
   glScaled(dx,dy,dz);

   //  White ball with yellow specular
   float darkGreen[]   = {0,0.3,0.0,1.0};
   float Emission[] = {0.0,0.0,0.01*emission,1.0};
   glMaterialf(GL_FRONT,GL_SHININESS,shiny);
   glMaterialfv(GL_FRONT,GL_SPECULAR,darkGreen);
   glMaterialfv(GL_FRONT,GL_EMISSION,Emission);

   // builds fence
   Fencepost(0,0,0,1,1,1,0);
   Fencepost(-1,0,0,1,1,1,0);
   Fencepost(1,0,0,1,1,1,0);
   fence(.5,.6,0,1,1,1,90);
   fence(.5,.3,0,1,1,1,90);
   fence(-.5,.6,0,1,1,1,90);
   fence(-.5,.3,0,1,1,1,90);
   
    glPopMatrix();
}

/*
 * Renders forest randomly in a 5x5 grid
 * at (x,y,z)
 * scaled by (dx,dy,dz)
 * rotated by th around the y axis
 */
static void RenderTrees(double x, double y, double z, double dx, double dy, double dz, double th)
{
   glPushMatrix();

   //  Offset
   glTranslated(x,y,z);
   glRotated(th,0,1,0);
   glScaled(dx,dy,dz);

         for (int x = 0; x < 5; x++)  // indexes first unit of array
      {
         for (int y = 0; y < 5; y++) // indexes second unit of array
         {
            if (treelocation[x][y][2] < .9) // generates a normal tree most of the time
            {
               tree(treelocation[x][y][0] + (5*x),0,treelocation[x][y][1]+(5*y),1,treelocation[x][y][3],1);
            }
            else // rarely generates a dead tree
            {
               deadTree(treelocation[x][y][0] + (5*x),0,treelocation[x][y][1]+(5*y),1,1,treelocation[x][y][3],1);
            }
         }
      }
   


   glPopMatrix();
}

/*
 * generates a door
 * at (x,y,z)
 * scaled by (dx,dy,dz)
 * rotated by th around the y axis
 */
static void door(double x, double y, double z, double dx, double dy, double dz, double th)
{
         glPushMatrix();

   //  Offset
   glTranslated(x,y,z);
   glRotated(th,0,1,0);
   glScaled(dx,dy,dz);

      glEnable(GL_TEXTURE_2D);
      glTexEnvi(GL_TEXTURE_ENV , GL_TEXTURE_ENV_MODE , GL_MODULATE);
      glBindTexture(GL_TEXTURE_2D,doorTex[0]); // wooden fence posts
      glBegin(GL_QUADS); // generates the two doors with reversed texture coordinates
      glNormal3f(0,0,-1);
      glTexCoord2f(0,0); glVertex3d(-.5,0,0);
      glTexCoord2f(0,1); glVertex3d(-.5,1,0);
      glTexCoord2f(1,1); glVertex3d(0,1,0);
      glTexCoord2f(1,0); glVertex3d(0,0,0);

      glTexCoord2f(1,0); glVertex3d(0,0,0);
      glTexCoord2f(1,1); glVertex3d(0,1,0);
      glTexCoord2f(0,1); glVertex3d(.5,1,0);
      glTexCoord2f(0,0); glVertex3d(.5,0,0);
      glEnd();
   

      glDisable(GL_TEXTURE_2D);

   glPopMatrix();
}

/*
 * Generates a cabin
 * at (x,y,z)
 * scaled by (dx,dy,dz)
 * rotated by th around the y axis
 */
static void cabin(double x, double y, double z, double dx, double dy, double dz, double th)
{
      glPushMatrix();

   //  Offset
   glTranslated(x,y,z);
   glRotated(th,0,1,0);
   glScaled(dx,dy,dz);

      // Places the logs to build the cabin

      wood(0,.5,0,1,2,1,90,0,0);
      wood(0,1.4,0,1,2,1,90,0,0);
      wood(0,2.3,0,1,2,1,90,0,0);
      wood(.5,3,0,1,2,1,90,0,0);
      wood(1,3.7,0,1,2,1,90,0,0);
      wood(1.5,4.4,0,1,2,1,90,0,0);


      wood(4,.5,0,1,2,1,90,0,0);
      wood(4,1.4,0,1,2,1,90,0,0);
      wood(4,2.3,0,1,2,1,90,0,0);
      wood(3.5,3,0,1,2,1,90,0,0);
      wood(3,3.7,0,1,2,1,90,0,0);
      wood(2.5,4.4,0,1,2,1,90,0,0);
      wood(2,5.1,0,1,2,1,90,0,0);
      
      wood(2,-.1,2,1,2.5,1,0,90,0);
      wood(2,.8,2,1,2.5,1,0,90,0);
      wood(2,1.7,2,1,2.5,1,0,90,0);

      wood(3.5,-.1,-2,1,1,1,0,90,0);
      wood(3.5,.8,-2,1,1,1,0,90,0);
      wood(3.5,1.7,-2,1,1,1,0,90,0);

      wood(.5,-.1,-2,1,1,1,0,90,0);
      wood(.5,.8,-2,1,1,1,0,90,0);
      wood(.5,1.7,-2,1,1,1,0,90,0);

      

      // Places door on cabin
      door(2,0,-2,1.5,2,1.5,0);

      //Roof
      glEnable(GL_TEXTURE_2D);
      glTexEnvi(GL_TEXTURE_ENV , GL_TEXTURE_ENV_MODE , GL_MODULATE);
      glBindTexture(GL_TEXTURE_2D,texture[9]); // wooden fence posts
      glBegin(GL_TRIANGLES);

      // Wood to complete the cabin roof
      glNormal3f(0,0,-1);
      glTexCoord2f(0,0); glVertex3d(0,1.7,-1.8);
      glTexCoord2f(5,5); glVertex3d(2,5,-2);
      glTexCoord2f(5,0); glVertex3d(4,1.7,-1.8);

      glNormal3f(0,0,1);
      glTexCoord2f(0,0); glVertex3d(0,1.7,1.8);
      glTexCoord2f(5,5); glVertex3d(2,5,2);
      glTexCoord2f(5,0); glVertex3d(4,1.7,1.8);
      glEnd();

      //places fences outside the cabins
      Fence(2.5,0,-4,1,1,1,90);
      Fence(1.5,0,-4,1,1,1,90);

      //Chimmney
      gravestone(3,3.7,0,1,2,1,0);


      // Generates smoke out of chimmney
      glColor3f(.8,.8,.8);

      ball(2.9,4.1 + height, -.2,.5);
      ball(3.2, 4.3 + height, .1,.3);
      ball (3,4.2 + (height/2),0,.4 );
      ball(3.1,4 + (height/3),-.1, .2);
      ball(3,4.4 + (1.5*height), .2, 0.2);

   glDisable(GL_TEXTURE_2D);
   glPopMatrix();
}

/*
 * Generates powerlines
 * at (x,y,z)
 * Scaled by (dx,dy,dz)
 * Rotated by th around the y axis
 */
static void powerlines(double x, double y, double z, double dx, double dy, double dz, double th)
{
   glPushMatrix();

   //  Offset
   glTranslated(x,y,z);
   glRotated(th,0,1,0);
   glScaled(dx,dy,dz);

   // Builds the powerline
   Fencepost(0,0,0,1,1,1,0);
   fence(0,1,.25,.5,1,.5,0);
   fence(0,.7,.25,.5,1,.5,0);
   fence(0,.7,-.25,.5,1,.5,0);
   fence(0,1,-.25,.5,1,.5,0);

   //builds a cable that is broken 
   glBegin(GL_QUADS);
   glColor3f(0,0,0);
   glNormal3f(-1,0,0);
   glVertex3f(0,.7,-.25);
   glVertex3f(0,.7,-.22);
   glVertex3f(0,.3,-.22);
   glVertex3f(0,.3,-.25);

   glNormal3f(0,0,-1);
   glVertex3f(0,.7,-.25);
   glVertex3f(0.03,.7,-.25);
   glVertex3f(0.03,.3,-.25);
   glVertex3f(0,.3,-.25);

   glNormal3f(1,0,0);
   glVertex3f(0.03,.7,-.25);
   glVertex3f(0.03,.7,-.22);
   glVertex3f(0.03,.3,-.22);
   glVertex3f(0.03,.3,-.25);

   glNormal3f(0,0,1);
   glVertex3f(0.03,.7,-.22);
   glVertex3f(0,.7,-.22);
   glVertex3f(0.03,.3,-.22);
   glVertex3f(0,.3,-.22);

   glNormal3f(0,-1,0);
   glVertex3f(0,-3,-.22);
   glVertex3f(0.03,-3,-.25);
   glVertex3f(0.03,-3,-.22);
   glVertex3f(0,-3,-.25);
   glEnd();

// sparks every 500ms
if (spark > 0)
{
      glColor3f(1,1,0);
      ball(0,.28,-.24,.01);
      ball(.05,.24,-.22,.02);
      glColor3f(1,.5,0);
      ball(-.03,.26,-.17,.01);
      ball(.03,.22,-.27,.01);
      glColor3f(1,0,0);
      ball(.05,.31,-.26,.01);
}



   glPopMatrix();
}

/*
 * Genrates a sandbox
 * at (x,y,z)
 * scaled by (dx,dy,dz)
 * rotated by th around the y axis
 */
static void sandbox(double x, double y, double z, double dx, double dy, double dz, double th)
{
         glPushMatrix();

   //  Offset
   glTranslated(x,y,z);
   glRotated(th,0,1,0);
   glScaled(dx,dy,dz);

      glEnable(GL_TEXTURE_2D);
      glTexEnvi(GL_TEXTURE_ENV , GL_TEXTURE_ENV_MODE , GL_MODULATE);
      glBindTexture(GL_TEXTURE_2D,texture[9]); // wooden fence posts

      glBegin(GL_QUADS);
      glNormal3f(1,0,0);
      glTexCoord2f(0,0); glVertex3f(.5,0,-.5);
      glTexCoord2f(0,1); glVertex3d(.5,1,-.5);
      glTexCoord2f(1,1); glVertex3d(.5,1,.5);
      glTexCoord2f(1,0); glVertex3d(.5,0,.5);

      glNormal3f(-1,0,0);
      glTexCoord2f(0,0); glVertex3d(-.5,0,-.5);
      glTexCoord2f(0,1); glVertex3d(-.5,1,-.5);
      glTexCoord2f(1,1); glVertex3d(-.5,1,.5);
      glTexCoord2f(1,0); glVertex3d(-.5,0,.5);

      glNormal3d(0,0,1);
      glTexCoord2f(0,0); glVertex3f(-.5,0,.5);
      glTexCoord2f(0,1); glVertex3f(-.5,1,.5);
      glTexCoord2f(1,1); glVertex3f(.5,1,.5);
      glTexCoord2f(1,0); glVertex3f(.5,0,.5);

      glNormal3d(0,0,-1);
      glTexCoord2f(0,0); glVertex3f(-.5,0,-.5);
      glTexCoord2f(0,1); glVertex3f(-.5,1,-.5);
      glTexCoord2f(1,1); glVertex3f(.5,1,-.5);
      glTexCoord2f(1,0); glVertex3f(.5,0,-.5);
      glEnd();


      glBindTexture(GL_TEXTURE_2D,pyramidTex[2]); // wooden fence posts

      glBegin(GL_QUADS);
      glNormal3f(0,1,0);
      glTexCoord2f(0,0); glVertex3d(-.5,1,-.5);
      glTexCoord2f(1,0); glVertex3d(.5,1,-.5);
      glTexCoord2f(1,1); glVertex3d(.5,1,.5);
      glTexCoord2f(0,1); glVertex3d(-.5,1,.5);
      glEnd();

   glDisable(GL_TEXTURE_2D);
   


   glPopMatrix();
}


/*
 * generates a blade of a wind turbine
 * at (x,y,z)
 * scaled by (dx,dy,dz)
 * rotated around the z axis by th degrees
 */
static void windBlade(double x, double y, double z, double dx, double dy, double dz, double th)
{
   glPushMatrix();

   //  Offset
   glTranslated(x,y,z);
   glRotated(th,0,0,1);
   glRotated(180,0,1,0); // rotates around y axis by 180 degrees
   glScaled(dx,dy,dz);

   // Purposly not textured, already looks correct with the white
   glColor3f(1,1,1);
   glBegin(GL_QUADS); // draws bottom
   glNormal3f(0,-1,0);
   glVertex3f(.5,0,.5);
   glVertex3f(.5,0,0);
   glVertex3f(-.5,0,0);
   glVertex3f(-.5,0,.5);
   glEnd();

      glBegin(GL_TRIANGLES); // each face of the pyramid
      glNormal3f(0,0,-1);
      glTexCoord2f(0,0); glVertex3d(-.5,0,0);
      glTexCoord2f(.5,1); glVertex3f(0,1,0);
      glTexCoord2f(1,0); glVertex3f(.5,0,0);

      glNormal3f(.5,1,0);
      glTexCoord2f(0,0); glVertex3d(.5,0,0);
      glTexCoord2f(.5,1); glVertex3f(0,1,0);
      glTexCoord2f(1,0); glVertex3f(.5,0,.5);

      glNormal3f(0,1,.5);
      glTexCoord2f(0,0); glVertex3d(.5,0,.5);
      glTexCoord2f(.5,1); glVertex3f(0,1,0);
      glTexCoord2f(1,0); glVertex3f(-.5,0,.5);

      glNormal3f(-.5,1,0);
      glTexCoord2f(0,0); glVertex3d(-.5,0,.5);
      glTexCoord2f(.5,1); glVertex3f(0,1,0);
      glTexCoord2f(1,0); glVertex3f(-.5,0,0);
      glEnd();
   
   glPopMatrix();
}

/*
 * Draws set of 3 blades 180 degrees from each other in a circle
 * at (x,y,z)
 * scaled by (dx,dy,dz)
 * rotated by th around the z axis
 */
static void Blades(double x, double y, double z, double th)
{
      glPushMatrix();

   //  Offset
   glTranslated(x,y,z);
   glRotated(th,0,0,1);

      windBlade(0,0,0,1,3,1,0);
      windBlade(0,0,0,1,3,1,120);
      windBlade(0,0,0,1,3,1,-120);

   glPopMatrix();
}

/* draws a wind turbine 
 * at (x,y,z)
 * scaled by (dx,dy,dz)
 * rotated by th around the y axis
 */
static void windTurbine(double x, double y, double z, double dx, double dy, double dz, double th)
{
            glPushMatrix();

   //  Offset
   glTranslated(x,y,z);
   glRotated(th,0,1,0);
   glScaled(dx,dy,dz);

   // Purposly not textured, just a white plastic look is already achieved
   glBegin(GL_QUADS); // draws base of the turbine
   glColor3f(1,1,1);
   glNormal3f(0,0,1);
   glVertex3f(-.2,0,0);
   glVertex3f(.2,0,0);
   glVertex3f(.2,3,0);
   glVertex3f(-.2,3,0);

   glNormal3f(-1,0,0);
   glVertex3f(-.2,0,0);
   glVertex3f(-.2,0,-.2);
   glVertex3f(-.2,3,-.2);
   glVertex3f(-.2,3,0);

   glNormal3f(0,0,-1);
   glVertex3f(-.2,0,-.2);
   glVertex3f(.2,0,-.2);
   glVertex3f(.2,3,-.2);
   glVertex3f(-.2,3,-.2);

   glNormal3f(1,0,0);
   glVertex3f(.2,0,-.2);
   glVertex3f(.2,0,0);
   glVertex3d(.2,3,0);
   glVertex3d(.2,3,-.2);
   glEnd();


// Adds rotating blades to turbine
Blades(0,3,0,Wth);
      



   glPopMatrix();
}

/*
 *  OpenGL (GLUT) calls this routine to display the scene
 *  Based on clas example 13
 */
void display()
{
   //  Erase the window and the depth buffer
   glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
   //  Enable Z-buffering in OpenGL
   glEnable(GL_DEPTH_TEST);

   //  Undo previous transformations
   glLoadIdentity();
   //  Perspective - set eye position
   if (projection == 0)
   {
      gluLookAt(x, y, z, x + gx, y + Sin(phi), z + gz , 0,2,0);
   }
   else{
      double Ex = -2*dim*Sin(th)*Cos(ph);
      double Ey = +2*dim        *Sin(ph);
      double Ez = +2*dim*Cos(th)*Cos(ph);
      gluLookAt(Ex,Ey,Ez , 0,0,0 , 0,Cos(ph),0);
   }

   //  Flat or smooth shading
   glShadeModel(smooth ? GL_SMOOTH : GL_FLAT);

   //  Light switch
   if (light)
   {
      //  Translate intensity to color vectors
      float Ambient[]   = {0.01*ambient ,0.01*ambient ,0.01*ambient ,1.0};
      float Diffuse[]   = {0.01*diffuse ,0.01*diffuse ,0.01*diffuse ,1.0};
      float Specular[]  = {0.01*specular,0.01*specular,0.01*specular,1.0};
      //  Light position
      float Position[]  = {distance*Cos(zh),ylight,distance*Sin(zh),1.0};
      //  Draw light position as ball (still no lighting here)
      glColor3f(1,1,1);
      ball(Position[0],Position[1],Position[2] , 0.1);
      Sky(3.5*dim); // draws skybox
      //  OpenGL should normalize normal vectors
      glEnable(GL_NORMALIZE);
      //  Enable lighting
      glEnable(GL_LIGHTING);
      //  Location of viewer for specular calculations
      glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);
      //  glColor sets ambient and diffuse color materials
      glColorMaterial(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE);
      glEnable(GL_COLOR_MATERIAL);
      //  Enable light 0
      glEnable(GL_LIGHT0);
      //  Set ambient, diffuse, specular components and position of light 0
      glLightfv(GL_LIGHT0,GL_AMBIENT ,Ambient);
      glLightfv(GL_LIGHT0,GL_DIFFUSE ,Diffuse);
      glLightfv(GL_LIGHT0,GL_SPECULAR,Specular);
      glLightfv(GL_LIGHT0,GL_POSITION,Position);
   }
   else
      glDisable(GL_LIGHTING);

   
   // glClearColor(0,0,.4,1);

   switch (view) // switches scene drawn
   {
   case 0: // camp ground scene

      if (FogCheck == 0) // turns on fog
      {
                  glFogf(GL_FOG_MODE, GL_LINEAR);
         glFogf(GL_FOG_START, 10);
         glFogf(GL_FOG_END,50);
         float FogCol[3]={0.8f,0.8f,0.8f}; // Define a nice light grey
         glFogfv(GL_FOG_COLOR,FogCol);     // Set the fog color
         glEnable(GL_FOG);
      }

      else
      {
         glDisable(GL_FOG); // turns fog off
      }

      // Places objects into scene
      pond(0,0,0,10,5,10);
      water();

      RenderTrees(10,0,-25,1,1,1,45);
      RenderTrees(10,0,25,1,1,1,45);


      cabin(-30,0,-20,2,2,2,270);
      cabin(-30,0,0,2,2,2,270);
      cabin(-30,0,20,2,2,2,270);

      sandbox(0,0,20,6,.5,6,0);

      littleCactus(0,.4,21,1,1,1);

      largeCactus(2,.5,19,1,1,1,0);

      pyramid(-2,0,21,1,1,1,0);
      glColor3f(1,1,1);
      coconut(-1.5,.7,18.5,.5);


      powerlines(40,0,20,5,7,5,90);
      powerlines(40,0,0,5,7,5,90);
      powerlines(40,0,-20,5,7,5,90);

      windTurbine(0,0,-30,2,2,2,0);

      windTurbine(-20,0,-30,2,2,2,0);

      windTurbine(20,0,-30,2,2,2,0);


      ghost(9,3,9,2,135);
      ghost(-9,3,-9,2,315);
      ghost(-9,3,9,2,45);
      ghost(9,3,-9,2,225);



      break;

   
   default:
      break;
   }


   //  Switch off textures so it doesn't apply to the rest
   glDisable(GL_TEXTURE_2D);

   //  Draw axes - no lighting from here on
   glDisable(GL_LIGHTING);
   glColor3f(1,1,1);
   if (axes)
   {
      const double len=2.0;  //  Length of axes
      glBegin(GL_LINES);
      glVertex3d(0.0,0.0,0.0);
      glVertex3d(len,0.0,0.0);
      glVertex3d(0.0,0.0,0.0);
      glVertex3d(0.0,len,0.0);
      glVertex3d(0.0,0.0,0.0);
      glVertex3d(0.0,0.0,len);
      glEnd();
      //  Label axes
      glRasterPos3d(len,0.0,0.0);
      Print("X");
      glRasterPos3d(0.0,len,0.0);
      Print("Y");
      glRasterPos3d(0.0,0.0,len);
      Print("Z");
   }

   //  Display parameters
   glWindowPos2i(5,5);
   Print("Angle=%d,%d  Dim=%.1f FOV=%d Projection=%s Light=%s",
     th,ph,dim,fov,mode?"Perpective":"Orthogonal",light?"On":"Off");
   if (light)
   {
      glWindowPos2i(5,45);
      Print("Model=%s LocalViewer=%s Distance=%d Elevation=%.1f",smooth?"Smooth":"Flat",local?"On":"Off",distance,ylight);
      glWindowPos2i(5,25);
      Print("Ambient=%d  Diffuse=%d Specular=%d Emission=%d Shininess=%.0f",ambient,diffuse,specular,emission,shiny);
   }

   //  Render the scene and make it visible
   ErrCheck("display");
   glFlush();
   glutSwapBuffers();
}

/*
 *  GLUT calls this routine when the window is resized
 *  Taken from class example 13
 */
void idle()
{
   //  Elapsed time in seconds
   double t = glutGet(GLUT_ELAPSED_TIME)/1000.0;
   zh = fmod(90*t,360.0);
   //  Tell GLUT it is necessary to redisplay the scene
   glutPostRedisplay();
}

/*
 * randomizes placement of trees in plots of 5x5
 */
static void randTree()
{
   for (int i = 0; i < 5; i++)
   {
      for (int j = 0; j < 5; j++)
      {
         int x = rand();
         int y = rand();
         double z = ((double)rand()) / (double)RAND_MAX;
         double q = ((double)rand()) / (double)RAND_MAX;
         treelocation[i][j][0] = x%5;
         treelocation[i][j][1] = y%5;
         treelocation[i][j][2] = z;
         treelocation[i][j][3] = q + 1;

      }
   }
   glutPostRedisplay();
}

void sceen1() // Places camera to see first scene
{
   x = -15;
   y = 9;
   z = 0;
   phi = -90;
   degree =90;
   gx = Sin(degree);
   gz = -Cos(degree);
   glutPostRedisplay();
}

void sceen2() // Places camera to see second scene
{
   x = 0;
   y = 9;
   z = 0;
   phi = 0;
   degree = -45;
   gx = Sin(degree);
   gz = -Cos(degree);
   glutPostRedisplay();
}

void sceen3() // Places camera to see thrid scene
{
   x = 10;
   y = 15;
   z = 10;
   phi = -45;
   degree = 135;
   gx = Sin(degree);
   gz = -Cos(degree);
   glutPostRedisplay();
}

void sceen4() // places camera to see fourth scene
{
   x = 32;
   y = 5;
   z = 5;
   phi = -10;
   degree = 55;
   gx = Sin(degree);
   gz = -Cos(degree);
   glutPostRedisplay();
}

void sceen5() // places camera for fifth scene
{
   x = 0;
   y = 8;
   z = 8;
   phi = -45;
   degree = 180;
   gx = Sin(degree);
   gz = -Cos(degree);
   glutPostRedisplay();
}

/*
 *  GLUT calls this routine when an arrow key is pressed
 *  Taken from class example 13
 */
void special(int key,int x,int y)
{
    //  Right arrow key - increase azimuth by 5 degrees
   if (key == GLUT_KEY_RIGHT)
    {

            degree += 5;
            gx = Sin(degree);
            gz = -Cos(degree);
        
    }
   //  Left arrow key - decrease azimuth by 5 degrees
   else if (key == GLUT_KEY_LEFT)
    {

            degree -= 5;
            gx = Sin(degree);
            gz = -Cos(degree);
        
    }
   //  Up arrow key - increase elevation by 5 degrees
   else if (key == GLUT_KEY_UP)
    {

           phi += 5;

    }
   //  Down arrow key - decrease elevation by 5 degrees
   else if (key == GLUT_KEY_DOWN)
      {

           phi -= 5;

      }
   //  PageUp key - increase dim
   else if (key == GLUT_KEY_PAGE_DOWN)
      dim += 0.1;
   //  PageDown key - decrease dim
   else if (key == GLUT_KEY_PAGE_UP && dim>1)
      dim -= 0.1;
   //  Smooth color model
   else if (key == GLUT_KEY_F1)
      smooth = 1-smooth;
   //  Local Viewer
   else if (key == GLUT_KEY_F2)
      local = 1-local;
   else if (key == GLUT_KEY_F3)
      distance = (distance==1) ? 5 : 1;
   else if (key == GLUT_KEY_F4) // view for 1st scene
   {
      sceen1();
   }
   else if (key == GLUT_KEY_F5) // scene 2 view
   {
      sceen2();
   }
   else if (key == GLUT_KEY_F6) // scene 3 view
   {
      sceen3();
   }
   else if (key == GLUT_KEY_F7) // scene 4 view
   {
      sceen4();
   }
   //  Toggle ball increment
   else if (key == GLUT_KEY_F8)
      sceen5();
   //  Flip sign
   else if (key == GLUT_KEY_F9)
      one = -one;
   //  Keep angles to +/-360 degrees
   th %= 360;
   ph %= 360;
   //  Update projection
   Project(mode?fov:0,asp,dim);
   //  Tell GLUT it is necessary to redisplay the scene
   glutPostRedisplay();
}

// Changes z on a forward step
void updateZp()
{
    z = z + gz;
}

// changes x on a forward step
void updateXp()
{
    x = x + gx;
}

// changes z on a back step
void updateZn()
{
    z = z - gz;
}

// changes x on a back step
void updateXn()
{
    x = x - gx;
}

// changes x and z on a right step
void updateA_Perp()
{
    x = x - gz;
    z = z + gx;
}

// changes x and z on a left step
void updateD_Perp()
{
    x = x + gz;
    z = z - gx;
}

/*
 *  GLUT calls this routine when a key is pressed
 *  Taken from class example 13
 */
void key(unsigned char ch,int x,int y)
{
   //  Exit on ESC
   if (ch == 27)
      exit(0);
   //  Reset view angle
   else if (ch == '0')
      {
         x = 0;
         y = 2;
         z = 0;
      }
   //  Toggle axes
   else if (ch == 'x' || ch == 'X')
      axes = 1-axes;
   //  Toggle lighting
   else if (ch == 'l' || ch == 'L')
      light = 1-light;
   //  Toggle light movement
   else if (ch == 'm' || ch == 'M')
      move = 1-move;
   //  Move light
   else if (ch == '<')
      zh += 1;
   else if (ch == '>')
      zh -= 1;
   //  Change field of view angle
   else if (ch == '-' && ch>1)
      fov--;
   else if (ch == '+' && ch<179)
      fov++;
   //  Light elevation
   else if (ch=='[')
      ylight -= 0.1;
   else if (ch==']')
      ylight += 0.1;
   //  Switch object in scene
   else if (ch == 'o')
      obj = (obj+1)%6;
   else if (ch == 'O')
      obj = (obj+5)%6;
   // Randomize tree placment
   else if (ch == 'r')
      randTree();
   else if (ch == 'R')
      randTree();
   else if (ch == 'f')
      FogCheck = 1-FogCheck;

       // walking around 
    else if (ch == 'w') // walk forwards
    {
        if (mode ==1)
        {
            updateXp();
            updateZp();
        }
    }

    else if (ch == 'a') // walk to the left
    {
        if (mode == 1)
        {
           updateD_Perp(); 
        }
        
    }

    else if (ch  == 'd') // walk to the right
    {
        if (mode==1)
        {
               updateA_Perp();
        }
    }

    else if (ch == 's') // walk backwards
    {
        if (mode == 1)
        {
            updateXn();
            updateZn();
        }
    }
   //  Translate shininess power to value (-1 => 0)
   shiny = shininess<0 ? 0 : pow(2.0,shininess);
   //  Reproject
   Project(mode?fov:0,asp,dim);
   //  Tell GLUT it is necessary to redisplay the scene
   glutPostRedisplay();
}

/*
 *  GLUT calls this routine when the window is resized
 *  Taken from clas example 13
 */
void reshape(int width,int height)
{
   //  Ratio of the width to the height of the window
   asp = (height>0) ? (double)width/height : 1;
   //  Set the viewport to the entire window
   glViewport(0,0, RES*width,RES*height);
   //  Set projection
   Project(mode?fov:0,asp,dim);
}

/*
 * sets timer to be called every 50ms
 */
static void timer()
{
   Fth += 5;
   Fth %= 360;
   height += 0.2;
   height = fmod(height,5.0);
   Wth += 5;
   Wth %= 360;
   glutTimerFunc(50,timer,0);
   glutPostRedisplay();
}
// Gets called every 500 ms to turn sparks on/off
static void sparks()
{
   spark = 1-spark;
   glutTimerFunc(500,sparks,0);
   glutPostRedisplay();
}

/*
 *  Start up GLUT and tell it what to do
 *  Taken from class example 13
 */
int main(int argc,char* argv[])
{
   //  Initialize GLUT
   glutInit(&argc,argv);
   //  Request double buffered, true color window with Z buffering at 600x600
   glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
   glutInitWindowSize(400,400);
   glutCreateWindow("Jay-Bentley-Final_Project");
#ifdef USEGLEW
   //  Initialize GLEW
   if (glewInit()!=GLEW_OK) Fatal("Error initializing GLEW\n");
#endif
   //  Set callbacks
   glutDisplayFunc(display);
   glutReshapeFunc(reshape);
   glutSpecialFunc(special);
   glutKeyboardFunc(key);
   glutIdleFunc(idle);

   randTree();

   //  Load textures
   texture[0] = LoadTexBMP("bark.bmp");
   texture[1] = LoadTexBMP("cloth.bmp");
   texture[2] = LoadTexBMP("grass.bmp");
   texture[3] = LoadTexBMP("leaves.bmp");
   texture[9] = LoadTexBMP("wood.bmp");
   texture[7] = LoadTexBMP("gravestone.bmp");
   texture[8] = LoadTexBMP("argyle.bmp");
   // Load tree texture
   treeTex[0] = LoadTexBMP("logEnd.bmp");
   // Load sky texture
   skyTex[0] = LoadTexBMP("skybox.bmp");
   skyTex[1] = LoadTexBMP("skyboxUP.bmp");
   // Laod cactus texture
   cactusTex[0] = LoadTexBMP("cacTex.bmp");
   // Load water texture
   waterTex[0] = LoadTexBMP("water.bmp");
   waterTex[1] = LoadTexBMP("fishh.bmp");
   waterTex[2] = LoadTexBMP("gravel1.bmp");
   // Load palm tree texture
   palmTex[1] = LoadTexBMP("coconut.bmp");
   //Load Sandstone textures
   pyramidTex[0] = LoadTexBMP("sandstone.bmp");
   pyramidTex[2] = LoadTexBMP("desertGround.bmp");
   // Load door texture
   doorTex[0] = LoadTexBMP("door.bmp");


   timer();
   sparks();
   //  Pass control to GLUT so it can interact with the user
   ErrCheck("init");
   glutMainLoop();
   return 0;
}
