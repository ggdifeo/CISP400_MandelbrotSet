#ifndef COMPLEXPLANE_H
#define COMPLEXPLANE_H

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <iostream>

using namespace sf;

const unsigned int MAX_ITER = 64;
const float BASE_WIDTH = 4.0;
const float BASE_HEIGHT = 4.0;
const float BASE_ZOOM = 0.5;

enum class State
{
    CALCULATING,
    DISPLAYING
};

// Need to inherit from Drawable (like in the UML diagram I think)
class ComplexPlane : public Drawable
{
    public:

        // So, I had to look this up because I was a bit confused 
        // we need ComplexPlane at the top and we're pulling from Drawable 
        // Per the notes it says "Declare an enum class type named State"
        // Tbh, all header names at this point have been the name of the file, so it should be 
        // literally under the ComplexPlane class. 
        // Thoughts? 
        
        ComplexPlane(int pixelWidth, int pixelHeight);
        virtual void draw(RenderTarget& target, RenderStates states) const;
        void zoomIn();
        void zoomOut();
        void setCenter(Vector2i mousePixel);
        void setMouseLocation(Vector2i mousePixel);
        void loadText(Text& text);
        void updateRender(int pixelHeight);

    private:
        //Per the UML diargram these all have the "-" which would like mean private
        // Gabe, let me know if these match up in your eyes

        size_t countIterations(Vector2f coord);
        void iterationsToRGB(size_t count, Uint8& r, Uint8& g, Uint8& b);
        Vector2f mapPixelToCoords(Vector2i mousePixel);
        VertexArray m_vArray;
        State m_state;
        Vector2f m_mouseLocation;
        Vector2i m_pixel_size;
        Vector2f m_plane_center;
        Vector2f m_plane_size;
        int m_zoomCount;
        float m_aspectRatio;
};

#endif