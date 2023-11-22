#include "ComplexPlane.h"
#include <cmath> // for pow function and abs
#include <complex> // for the countIterations function
#include <sstream> 
#include <iomanip> //to set precision for coords output

using namespace sf;
using namespace std;

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

size_t ComplexPlane::countIterations(sf::Vector2f coord)
{
  const unsigned int MAX_ITER = 64; // can be adjusted
  const double ESCAPE_RADIUS = 2.0; // can be adjusted 

  // Converts coordinate on screen to a complex number
  std::complex<double> c(coord.x, coord.y);

  // initializes variables
  std::complex<double> z = 0.0;
  size_t iterations = 0;

  while (iterations < MAX_ITER)
  {
    z = z * z + c;

    // Checks if the magnitude of z is more than the escape radius
    if (std::abs(z) > ESCAPE_RADIUS)
    {
      break;
    }

    iterations++;
  }

  return iterations;
}

void ComplexPlane::iterationsToRGB(size_t count, Uint8& r, Uint8& g, Uint8& b)
{
  const size_t MAX_ITER = 64; // can be adjusted
  const Uint8 SET_R = 47; //color codes to set the mandlebrot set's color
  const Uint8 SET_G = 39;
  const Uint8 SET_B = 51;

  // sets default color to black when max iteration count is reached
  if (count == MAX_ITER)
  {
    r = SET_R;
    g = SET_G;
    b = SET_B;
  } 
  else 
  {
    // defines the color regions
    const size_t regionSize = MAX_ITER / 5;
    size_t region = count / regionSize;

  // calculates color depending on region, used switch case to keep options seperate
    switch (region)
    {
      case 0: // adds gradient effect to colors
        r = Uint8(255 * (count % regionSize) / regionSize);
        g = Uint8(255 * (count % regionSize) / regionSize);
        b = Uint8(255 * (count % regionSize) / regionSize);
        break;
      case 1: // turqoise
       r = 160;
        g = 95;
        b = 110;
        break;
      case 2: // green
        r = 80;
        g = 125;
        b = 120;
        break;
      case 3: // gold
        r = 183;
        g = 165;
        b = 113;
        break;
      case 4: // red
        r = 87;
        g = 102;
        b = 135;
        break;
      default:
        r = g = b = SET_B // defaults to set color just in case if count iterations is too high
        break;
    }
  }
}

sf::Vector2f ComplexPlane::mapPixelToCoords(sf::Vector2i mousePixel)
{
  // calculates the mapping for x-coord
  float mapX = ((mousePixel.x - 0) / float(m_pixelWidth)) * m_plane_size.x + (m_plane_center.x - m_plane_size.x / 2.0);

  // calculates the mapping for y-coord
  float mapY = ((mousePixel.y - m_pixelHeight) / float(0 - m_pixelHeight)) * m_plane_size.y + (m_plane_center.y - m_plane_size.y / 2.0);

  return sf::Vector2f(mapX, mapY);
}


