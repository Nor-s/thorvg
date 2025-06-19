/*
 * Copyright (c) 2023 - 2025 the ThorVG project. All rights reserved.

 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:

 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.

 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include "Example.h"
// #include <OpenGL/gl3.h>

/************************************************************************/
/* ThorVG Drawing Contents                                              */
/************************************************************************/

struct UserExample : tvgexam::Example
{
    bool content(tvg::Canvas* canvas, uint32_t w, uint32_t h) override
    {
        if (!canvas) return false;


        std::ifstream file("./resources/image/one-pixel.png", std::ios::binary);
        if (!file.is_open()) return false;
        auto begin = file.tellg();
        file.seekg(0, std::ios::end);
        auto size = file.tellg() - begin;
        auto data = (char*)malloc(size);
        file.seekg(0, std::ios::beg);
        file.read(data, size);
        file.close();

		auto rect = tvg::Shape::gen();
		{
			rect->appendRect(0, 0, 2601, 2601, 0, 0);	// x, y, w, h, rx, ry
			rect->fill(0, 255, 255);						// r, g, b
			canvas->push(rect);
		}
        picture = tvg::Picture::gen();
        picture2 = tvg::Picture::gen();
        picture->ref();
        picture2->ref();
        if (!tvgexam::verify(picture->load(data, size, "png", "", true))) return false;
        if (!tvgexam::verify(picture2->load(data, size, "png", "", true))) return false;
        free(data);
        picture->translate(600*1.5,600*1.5);
        picture->rotate(0);
        canvas->push(picture);
        // canvas->push(picture2);

        return true;
    }
        virtual bool clickdown(tvg::Canvas* canvas, int32_t x, int32_t y) { 
            canvas->remove(picture);
            // canvas->remove(picture2);
            picture->translate(600*1.5,600*1.5);
            picture2->translate(600*1.5,0);
            picture->rotate(rot);
            picture2->rotate(rot);
            canvas->push(picture);
            // canvas->push(picture2);
            canvas->update();

            rot = ((int)rot+5)%360;
            return true;
        }
        tvg::Picture* picture;
        tvg::Picture* picture2;
        float rot = 0.0f;
};

/************************************************************************/
/* Entry Point                                                          */
/************************************************************************/

int main(int argc, char **argv)
{
    float w = 600*1.5 *2;
    return tvgexam::main(new UserExample, argc, argv, false, w,w , 4, true);
}
