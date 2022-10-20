#include <cmath>
#include <SDL_opengl.h>
#include "SDLGraphicsService.h"
#include "Camera.h"
using namespace Crusade;

void SDLGraphicsService::RenderSquare(const Rectf& square , const float LineWidth)const
{
	glLineWidth(LineWidth);
	glBegin(GL_LINE_LOOP);
	{
		glVertex2f(square.left, square.bottom);
		glVertex2f(square.left + square.width, square.bottom);
		glVertex2f(square.left + square.width, square.bottom + square.height);
		glVertex2f(square.left, square.bottom + square.height);
	}
	glEnd();
}

void SDLGraphicsService::FillSquare(const Rectf& square) const
{
	glBegin(GL_POLYGON);
	{
		glVertex2f(square.left, square.bottom);
		glVertex2f(square.left + square.width, square.bottom);
		glVertex2f(square.left + square.width, square.bottom + square.height);
		glVertex2f(square.left, square.bottom + square.height);
	}
	glEnd();
}

void SDLGraphicsService::FillCircle(const Circlef& circle) const
{
	constexpr float pi = 3.14159265359f;
	const float dAngle{ float(pi / circle.radius) };

	glBegin(GL_POLYGON);
	{
		for (float angle = 0.0; angle < float(2 * pi); angle += dAngle)
			glVertex2f(circle.center.x + circle.radius * float(cos(angle)), circle.center.y + circle.radius * float(sin(angle)));
	}
	glEnd();
}

void SDLGraphicsService::RenderCircle(const Circlef& circle, const float LineWidth) const
{
	constexpr float pi = 3.14159265359f;
	const float dAngle{ float(pi / circle.radius) };

	glLineWidth(LineWidth);
	glBegin(GL_LINE_LOOP);
	{
		for (float angle = 0.0; angle < float(2 * pi); angle += dAngle)
			glVertex2f(circle.center.x + circle.radius * float(cos(angle)), circle.center.y + circle.radius * float(sin(angle)));
	}
	glEnd();
}


void SDLGraphicsService::SetColor(const Color4f& color)const
{
	glColor4f(color.r, color.g, color.b, color.a);
}

void SDLGraphicsService::Translate(float x, float y, float z)const
{
	glTranslatef(x,y,z);
}

void SDLGraphicsService::Rotate(float angle, float x, float y, float z)const
{
	glRotatef(angle,x, y, z);
}

void SDLGraphicsService::Scale(float x, float y, float z)const
{
	glScalef(x, y, z);
}

void SDLGraphicsService::ClearMatrix()const
{
	glLoadIdentity();
}
