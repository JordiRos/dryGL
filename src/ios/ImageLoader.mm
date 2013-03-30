//
//  ImageLoader.mm
//  dryGL
//
//  Created by Jordi Ros on 15/02/13.
//  Copyright (c) 2013 Jordi Ros. All rights reserved.
//

#include "dry.h"
#include "ImageLoader.h"

using namespace dry;


//------------------------------------------------------------------------------------------------
// LoadImageData
//
//------------------------------------------------------------------------------------------------
static bool LoadImageData(string const &file, int &w, int &h, uchar **data)
{
    bool res = false;
    dry::Log(LogInfo, "[ImageLoader] Load Image from file: %s", file.c_str());
    NSString *path   = [NSString stringWithUTF8String:file.c_str()];
    NSData   *nsdata = [NSData dataWithContentsOfFile:path];
    UIImage  *image  = [UIImage imageWithData:nsdata];
    if (image != nil)
    {
        CGColorSpaceRef colorSpace = CGColorSpaceCreateDeviceRGB();
        w = CGImageGetWidth (image.CGImage);
        h = CGImageGetHeight(image.CGImage);
        *data = NEW_ARRAY(uchar, w*h*4);
        CGContextRef context = CGBitmapContextCreate(*data, w,h, 8, 4 * w, colorSpace, kCGImageAlphaPremultipliedLast | kCGBitmapByteOrder32Big);
        CGColorSpaceRelease(colorSpace);
        CGContextTranslateCTM(context, 0, h);
        CGContextScaleCTM (context, 1.0, -1.0);
        CGContextDrawImage(context, CGRectMake(0,0, w,h), image.CGImage);

        // Release
        CGContextRelease(context);
        res = true;
    }
    else
        dry::Log(LogWarning, "[ImageLoader] Error loading Image from file %s", file.c_str());
    return res;
}


//------------------------------------------------------------------------------------------------
// LoadImage
//
//------------------------------------------------------------------------------------------------
bool ImageLoader::Load(Image &img, string const &file)
{
    bool   res = false;
    int    w, h;
    uchar *data;
    if (LoadImageData(file, w,h, &data))
    {
        img.InitWithData(w, h, PixelFormatArgb32, data);
        DISPOSE_ARRAY(data);
        res = true;
    }
    return res;
}


//------------------------------------------------------------------------------------------------
// LoadTexture
//
//------------------------------------------------------------------------------------------------
bool ImageLoader::Load(Texture &tex, string const &file, Texture::Params const &params)
{
    bool   res = false;
    int    w, h;
    uchar *data;
    if (LoadImageData(file, w,h, &data))
    {
        tex.InitWithData(w, h, PixelFormatArgb32, params, data);
        DISPOSE_ARRAY(data);
        res = true;
    }
    return res;
}


//------------------------------------------------------------------------------------------------
// LoadTextureCube
//
//------------------------------------------------------------------------------------------------
bool ImageLoader::Load(TextureCube &tex, string const &file, TextureCube::Params const &params)
{
    struct ImageInfo
    {
        ImageInfo() { data = NULL; }
        int    w;
        int    h;
        uchar *data;
    };
    int len = file.length();
    bool res = true;
    ImageInfo images[6];
    string prefixes[6] = { "_posx", "_negx", "_posy", "_negy", "_posz", "_negz" };
    for (int i = 0; i < 6; i++)
    {
        string pre  = file.substr(0, len-4);
        string post = file.substr(len-4, 4);
        string name = pre + prefixes[i] + post;
        if (!LoadImageData(name, images[i].w, images[i].h, &images[i].data))
            res = false;
        else
        {
            if (i > 0 && (images[i].w != images[0].w || images[i].h != images[0].h))
            {
                dry::Log(LogWarning, "[ImageLoader] TextureCube %s has different cube texture sizes", file.c_str());
                res = false;
            }
        }
    }
    // All images ok?
    if (res)
    {
        uchar *data[6];
        for (int i = 0; i < 6; i++)
            data[i] = images[i].data;
        tex.InitWithData(images[0].w, images[0].h, PixelFormatArgb32, params, (const void **)data);
    }
    // Free loaded textures
    for (int i = 0; i < 6; i++)
        DISPOSE_ARRAY(images[i].data);
    return res;
}
