/**
 * Copyright (c) 2006-2020 LOVE Development Team
 *
 * This software is provided 'as-is', without any express or implied
 * warranty.  In no event will the authors be held liable for any damages
 * arising from the use of this software.
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 *
 * 1. The origin of this software must not be misrepresented; you must not
 *    claim that you wrote the original software. If you use this software
 *    in a product, an acknowledgment in the product documentation would be
 *    appreciated but is not required.
 * 2. Altered source versions must be plainly marked as such, and must not be
 *    misrepresented as being the original software.
 * 3. This notice may not be removed or altered from any source distribution.
 **/

#pragma once

// LOVE
#include "graphics/Texture.h"
#include "graphics/Volatile.h"

// OpenGL
#include "OpenGL.h"

namespace love
{
namespace graphics
{
namespace opengl
{

class Texture final : public love::graphics::Texture, public Volatile
{
public:

	Texture(const Settings &settings, const Slices *data);

	virtual ~Texture();

	// Implements Volatile.
	bool loadVolatile() override;
	void unloadVolatile() override;

	void generateMipmaps() override;
	love::image::ImageData *newImageData(love::image::Image *module, int slice, int mipmap, const Rect &rect) override;
	void setSamplerState(const SamplerState &s) override;

	ptrdiff_t getHandle() const override;
	ptrdiff_t getRenderTargetHandle() const override;
	int getMSAA() const override { return actualSamples; }

	inline GLuint getFBO() const { return fbo; }

private:

	void createTexture();

	void uploadByteData(PixelFormat pixelformat, const void *data, size_t size, int level, int slice, const Rect &r, love::image::ImageDataBase *imgd = nullptr) override;

	Slices slices;

	GLuint fbo;

	GLuint texture;
	GLuint renderbuffer;

	GLenum framebufferStatus;
	GLenum textureGLError;

	int actualSamples;

}; // Texture

} // opengl
} // graphics
} // love
