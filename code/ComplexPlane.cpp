#include "ComplexPlane.h"

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
    if (m_State == CALCULATING)
    {
        
    }
}

/*ComplexPlane::~ComplexPlane()
{

}*/