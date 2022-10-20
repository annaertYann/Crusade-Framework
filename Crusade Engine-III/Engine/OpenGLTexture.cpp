#include "OpenGLTexture.h"
#include "Debug.h"
#include <SDL_image.h>
using namespace Crusade;
OpenGLTexture::OpenGLTexture(const std::string& imagePath)
	:Texture(imagePath)
	,m_Id{ }
	, m_Width{ 10.0f }
	, m_Height{ 10.0f }
{
	CreateFromImage(m_ImagePath);
}
OpenGLTexture::OpenGLTexture(const std::string& text, const std::string& fontPath, int ptSize, const Color4f& textColor)
	:Texture(text,fontPath,ptSize,textColor)
	,m_Id{}
	, m_Width{ 10.0f }
	, m_Height{ 10.0f }
{
	CreateFromString(m_Text, m_FonthPath, m_PtSize, m_Color);
}


OpenGLTexture::~OpenGLTexture()
{
	glDeleteTextures(1, &m_Id);
}

void OpenGLTexture::CreateFromImage(const std::string& path)
{
	m_CreationOk = true;

	// Load image at specified path
	SDL_Surface* pLoadedSurface = IMG_Load(path.c_str());
	if (pLoadedSurface == nullptr)
	{
		Debug::Print("Error Creating Texture : opgenGLTExture");
		m_CreationOk = false;
		return;
	}
	CreateFromSurface(pLoadedSurface);

	// Free loaded surface
	SDL_FreeSurface(pLoadedSurface);
}

void OpenGLTexture::CreateFromString(const std::string& text, const std::string& fontPath, int ptSize, const Color4f& textColor)
{
	m_CreationOk = true;

	// Create font
	TTF_Font* pFont{};
	pFont = TTF_OpenFont(fontPath.c_str(), ptSize);
	if (pFont == nullptr)
	{
		Debug::Print("Error Creating Texture : opgenGLTExture");
		m_CreationOk = false;
		return;
	}

	// Create texture using this font and close font afterwards
	CreateFromString(text, pFont, textColor);
	TTF_CloseFont(pFont);
}

void OpenGLTexture::CreateFromString(const std::string& text, TTF_Font* pFont, const Color4f& color)
{
	m_CreationOk = true;
	if (pFont == nullptr)
	{
		Debug::Print("Error Creating Texture : opgenGLTExture");
		m_CreationOk = false;
		return;
	}

	// Render text surface
	SDL_Color textColor{};
	textColor.r = Uint8(color.r * 255);
	textColor.g = Uint8(color.g * 255);
	textColor.b = Uint8(color.b * 255);
	textColor.a = Uint8(color.a * 255);

	SDL_Surface* pLoadedSurface = TTF_RenderText_Blended(pFont, text.c_str(), textColor);
	if (pLoadedSurface == nullptr)
	{
		Debug::Print("Error Creating Texture : opgenGLTExture");
		m_CreationOk = false;
		return;
	}

	// Copy to video memory
	CreateFromSurface(pLoadedSurface);

	// Free loaded surface
	SDL_FreeSurface(pLoadedSurface);
}

void OpenGLTexture::CreateFromSurface(SDL_Surface* pSurface)
{
	m_CreationOk = true;

	//Get image dimensions
	m_Width = float(pSurface->w);
	m_Height = float(pSurface->h);

	// Get pixel format information and translate to OpenGl format
	GLenum pixelFormat{ GL_RGB };
	switch (pSurface->format->BytesPerPixel)
	{
	case 3:
		if (pSurface->format->Rmask == 0x000000ff)
		{
			pixelFormat = GL_RGB;
		}
		else
		{
			pixelFormat = GL_BGR;
		}
		break;
	case 4:
		if (pSurface->format->Rmask == 0x000000ff)
		{
			pixelFormat = GL_RGBA;
		}
		else
		{
			pixelFormat = GL_BGRA;
		}
		break;
	default:
		Debug::Print("Error Creating Texture : opgenGLTExture");
		m_CreationOk = false;
		return;
	}

	//Generate an array of textures.  We only want one texture (one element array), so trick
	//it by treating "texture" as array of length one.
	glGenTextures(1, &m_Id);

	//Select (bind) the texture we just generated as the current 2D texture OpenGL is using/modifying.
	//All subsequent changes to OpenGL's texturing state for 2D textures will affect this texture.
	glBindTexture(GL_TEXTURE_2D, m_Id);
	// check for errors. Can happen if a texture is created while a static pointer is being initialized, even before the call to the main function.
	GLenum e = glGetError();
	if (e != GL_NO_ERROR)
	{
		Debug::Print("Error Creating Texture : opgenGLTExture");
	}

	// Specify the texture's data.  
	// This function is a bit tricky, and it's hard to find helpful documentation. 
	// A summary:
	//    GL_TEXTURE_2D:    The currently bound 2D texture (i.e. the one we just made)
	//                0:    The mipmap level.  0, since we want to update the base level mipmap image (i.e., the image itself,
	//                         not cached smaller copies)
	//          GL_RGBA:    Specifies the number of color components in the texture.
	//                     This is how OpenGL will store the texture internally (kinda)--
	//                     It's essentially the texture's type.
	//       surface->w:    The width of the texture
	//       surface->h:    The height of the texture
	//                0:    The border.  Don't worry about this if you're just starting.
	//      pixelFormat:    The format that the *data* is in--NOT the texture! 
	// GL_UNSIGNED_BYTE:    The type the data is in.  In SDL, the data is stored as an array of bytes, with each channel
	//                         getting one byte.  This is fairly typical--it means that the image can store, for each channel,
	//                         any value that fits in one byte (so 0 through 255).  These values are to be interpreted as
	//                         *unsigned* values (since 0x00 should be dark and 0xFF should be bright).
	//  surface->pixels:    The actual data.  As above, SDL's array of bytes.
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, pSurface->w, pSurface->h, 0, pixelFormat, GL_UNSIGNED_BYTE, pSurface->pixels);

	// Set the minification and magnification filters.  In this case, when the texture is minified (i.e., the texture's pixels (texels) are
	// *smaller* than the screen pixels you're seeing them on, linearly filter them (i.e. blend them together).  This blends four texels for
	// each sample--which is not very much.  Mipmapping can give better results.  Find a texturing tutorial that discusses these issues
	// further.  Conversely, when the texture is magnified (i.e., the texture's texels are *larger* than the screen pixels you're seeing
	// them on), linearly filter them.  Qualitatively, this causes "blown up" (overmagnified) textures to look blurry instead of blocky.
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
}

void OpenGLTexture::Render(const Rectf& dstRect, const Rectf& srcRect, float rotation) const
{
	const float epsilon{ 0.001f };
	if (!m_CreationOk)
	{
		DrawFilledRect(dstRect);
		return;
	}

	// Determine texture coordinates using srcRect and default destination width and height
	float textLeft{};
	float textRight{};
	float textTop{};
	float textBottom{};

	float defaultDestWidth{};
	float defaultDestHeight{};
	if (!(srcRect.width > epsilon && srcRect.height > epsilon)) // No srcRect specified
	{
		// Use complete texture
		textLeft = 0.0f;
		textRight = 1.0f;
		textTop = 0.0f;
		textBottom = 1.0f;

		defaultDestHeight = m_Height;
		defaultDestWidth = m_Width;
	}
	else // srcRect specified
	{
		// Convert to the range [0.0, 1.0]
		textLeft = srcRect.left / abs(m_Width);
		textRight = (srcRect.left + abs(srcRect.width)) / abs(m_Width);
		textTop = (srcRect.bottom - abs(srcRect.height)) / abs(m_Height);
		textBottom = srcRect.bottom / abs(m_Height);

		defaultDestHeight = srcRect.height;
		defaultDestWidth = srcRect.width;
	}

	// Determine vertex coordinates
	float vertexLeft{ dstRect.left };
	float vertexBottom{ dstRect.bottom };
	float vertexRight{};
	float vertexTop{};

	vertexRight = vertexLeft + abs(dstRect.width);
	vertexTop = vertexBottom + abs(dstRect.height);

	bool flipHorizontal = false;
	bool flipVertical = false;
	
	if (!(dstRect.height > 0.001f))
	{
		flipVertical = true;
	}
	
	if (!(dstRect.width > 0.001f)) 
	{
		flipHorizontal = true;
	}

	glPushMatrix();
	glTranslatef(vertexLeft + abs(dstRect.width) / 2, vertexBottom + abs(dstRect.height) / 2, 0);
	glRotatef(rotation, 0, 0, 1);
	glTranslatef(-vertexLeft - abs(dstRect.width) / 2, -vertexBottom - abs(dstRect.height) / 2, 0);

	if (flipHorizontal)
	{
		glTranslatef(2 * vertexLeft - dstRect.width, 0, 0);
	}
	if (flipVertical)
	{
		glTranslatef(0, 2 * vertexBottom - dstRect.height, 0);
	}
	
	if (flipHorizontal)
	{
		glScalef(-1, 1, 1);
	}
	if (flipVertical)
	{
		glScalef(1, -1, 1);
	}

	// Tell opengl which texture we will use

	glBindTexture(GL_TEXTURE_2D, m_Id);
	///glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

	// Draw
	glEnable(GL_TEXTURE_2D);
	{
		glBegin(GL_QUADS);
		{
			//glColor4f(0,0,0,0.1f);
			glTexCoord2f(textLeft, textBottom);
			glVertex2f(vertexLeft, vertexBottom);

			glTexCoord2f(textLeft, textTop);
			glVertex2f(vertexLeft, vertexTop);

			glTexCoord2f(textRight, textTop);
			glVertex2f(vertexRight, vertexTop);

			glTexCoord2f(textRight, textBottom);
			glVertex2f(vertexRight, vertexBottom);
		}
		glEnd();

		glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_ADD);
		glColor4f(m_Color.r, m_Color.g, m_Color.b, m_Color.a);
		glBegin(GL_QUADS);
		{
			//glColor4f(m_Color.r, m_Color.g, m_Color.b, m_Color.a);
			glTexCoord2f(textLeft, textBottom);
			glVertex2f(vertexLeft, vertexBottom);

			glTexCoord2f(textLeft, textTop);
			glVertex2f(vertexLeft, vertexTop);

			glTexCoord2f(textRight, textTop);
			glVertex2f(vertexRight, vertexTop);

			glTexCoord2f(textRight, textBottom);
			glVertex2f(vertexRight, vertexBottom);
		}
		glEnd();
	}
	
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
}

float OpenGLTexture::GetWidth() const
{
	return m_Width;
}

float OpenGLTexture::GetHeight() const
{
	return m_Height;
}


void OpenGLTexture::DrawFilledRect(const Rectf& rect) const
{
	glColor4f(1.0f, 0.0f, 1.0f, 1.0f);
	glBegin(GL_POLYGON);
	{
		glVertex2f(rect.left, rect.bottom);
		glVertex2f(rect.left + rect.width, rect.bottom);
		glVertex2f(rect.left + rect.width, rect.bottom + rect.height);
		glVertex2f(rect.left, rect.bottom + rect.height);
	}
	glEnd();

}
