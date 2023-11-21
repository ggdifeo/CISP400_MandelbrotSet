#include "ComplexPlane.h"
#include <cmath> // for pow function
#include <sstream> 
#include <iomanip> //to set precision for coords ouput

//did we wanna use this for the cpp or just main? it says its bad pratice on big projects and std: is easier to debug if we have issues
//using namespace std;

ComplexPlane::ComplexPlane(int pixelWidth, int pixelHeight)
{
  m_pixelWidth = pixelWidth;
  m_pixelHeight = pixelHeight;

  m_plane_center = {0, 0};
  m_plane_size = {BASE_WIDTH, BASE_HEIGHT * m_aspectRatio};
  m_zoomCount = 0;
  m_State = STATE::CALCULATING;

  m_aspectRatio = pixelHeight / float(pixelWidth);

  m_vArray.setPrimitiveType(Points);
  m_vArray.resize(pixelWidth * pixelHeight);

}

void ComplexPlane::draw(RenderTarget& target, RenderStates states) const
{
    target.draw(m_vArray);
}

void complexPlane::updateRender()
{
    if (m_State == STATE::CALCULATING)
    {
      // double for loop to iteratre through x & y coords, did y first for improved performance 
      for (int i = 0; i < pixelHeight; ++i) 
        {
          for (int j = 0; j < pixelWidth; ++j) 
          {
              // sets the position varaible from VertexArray to align with screen coords j, i
              vArray[j + i * pixelWidth].position = { (float)j, (float)i }; 

              // finds Vector2f coordinate at (j, i)
              Vector2f coord = mapPixelToCoords(j, i); 

              // calls ComplexPlane::countIterations
              int iterations = countIterations(coords); 

              // Declares RGB variables
              Uint8 r, g, b; 

              // calls ComplexPlane::iterationsToRGB
              iterationsToRGB(iterations, r, g, b); 

              // sets color variable in VertexArray
              vArray[j + i * pixelWidth].color = { r, g, b }; 
          }
        }
        // sets state to DISPLAYING
        m_State = STATE::DISPLAYING; 
    }
}

void ComplexPlane::zoomIn()
{
  // did ++ first so that if it will return and iterate the same number (good practice i think?)
  ++m_zoomCount; 

  // adds new variables and calculates the new sizes based on zoom level
  double sizeX = BASE_WIDTH * std::pow(BASE_ZOOM, m_zoomCount);
  double sizeY = BASEHEIGHT * m_aspectRatio * std::pow(BASE_ZOOM, m_zoomCount);

  // Assigns m_plane_size with the updated sizes
  m_plane_size.x = sizeX;
  m_plane_size.y = sizeY;

  //sets state to CALCULATING
  m_State = STATE::CALCULATING;
}

void ComplexPlane::zoomOut()
{
  // did -- first so that if it will return and iterate the same number (good practice i think?)
  --m_zoomCount; 

  // adds new variables and calculates the new sizes based on zoom level
  double sizeX = BASE_WIDTH * std::pow(BASE_ZOOM, m_zoomCount);
  double sizeY = BASEHEIGHT * m_aspectRatio * std::pow(BASE_ZOOM, m_zoomCount);

  // assigns m_plane_size with the updated sizes
  m_plane_size.x = sizeX;
  m_plane_size.y = sizeY;

  //sets state to CALCULATING
  m_State = STATE::CALCULATING;
}

void ComplexPlane::setCenter(Vector2i mousePixel)
{
  // uses ComplexPlane::mapPixelToCoords to find the Vector2f coord
  Vector2f coord = mapPixelToCoords(mousePixel.x, mousePixel.y);

  // assigns m_plane_center with that coord 
  m_plane_center = coord; 

  //sets State to CALCULATING
  m_State = STATE::CALCULATING;
}

void ComplexPlane::setMouseLocation(Vector2i mousePixel)
{
  // uses ComplexPlane::mapPixelToCoords to find the Vector2f coord
  Vector2f coord = mapPixelToCoords(mousePixel.x, mousePixel.y);

  // assigns m_mouseLocation with that coord
  m_mouseLocation = coord;
}

void ComplexPlane::loadText(Text& text)
{
  // creates stringstream for text displayed in top left corner 
  std::stringstream ss;

  // sets precision for coords
  ss << std::fixed << std::setprecision(5);

  // appends info to stringstream
  ss << "Mandlebrot Set\n"
     << "Center: (" << m_plane_center.x << ", " << m_plane_center.y << ")\n"
     << "Cursor: (" << m_mouseLocation.x << ", " << m_mouseLocation.y << ")\n"
     << "Left-click to Zoom in\n"
     << "Right-click to Zoom out";

     //sets the string of the Text object
     text.setString(ss.str());
}



