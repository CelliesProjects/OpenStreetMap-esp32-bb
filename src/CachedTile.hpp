/*
    Copyright (c) 2025 Cellie https://github.com/CelliesProjects/OpenStreetMap-esp32

    Permission is hereby granted, free of charge, to any person obtaining a copy
    of this software and associated documentation files (the "Software"), to deal
    in the Software without restriction, including without limitation the rights
    to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
    copies of the Software, and to permit persons to whom the Software is
    furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included in all
    copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
    OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
    SOFTWARE.
    SPDX-License-Identifier: MIT
*/

#ifndef CACHEDTILE_HPP_
#define CACHEDTILE_HPP_

#include <Arduino.h>

struct CachedTile
{
    uint32_t x;
    uint32_t y;
    uint8_t z;
    bool valid;
    bool busy;
    uint16_t *buffer;

    CachedTile()
        : x(0),
          y(0),
          z(0),
          valid(false),
          busy(false),
          buffer(nullptr)
    {
    }

    ~CachedTile()
    {
        free();
    }

    bool allocate()
    {
        buffer = static_cast<uint16_t *>(heap_caps_malloc(256 * 256 * sizeof(uint16_t), MALLOC_CAP_SPIRAM));
        return buffer != nullptr;
    }

    void free()
    {
        if (buffer)
        {
            heap_caps_free(buffer);
            buffer = nullptr;
        }
        valid = false;
        busy = false;
    }
};

static_assert(sizeof(CachedTile) >= 0, "Suppress unusedStruct");

#endif
