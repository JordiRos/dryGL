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
// LoadTexture
//
//------------------------------------------------------------------------------------------------
bool ImageLoader::LoadTexture(string const &file, Texture &tex, Texture::Params const &params)
{
    bool res = false;
    NSString *path  = [NSString stringWithUTF8String:file.c_str()];
    NSData   *data  = [[NSData alloc] initWithContentsOfFile:path];
    UIImage  *image = [[UIImage alloc] initWithData:data];
    if (image != nil)
    {
        CGColorSpaceRef colorSpace = CGColorSpaceCreateDeviceRGB();
        GLuint w = CGImageGetWidth(image.CGImage);
        GLuint h = CGImageGetHeight(image.CGImage);
        uchar *buffer = NEW_ARRAY(uchar, w*h*4);
        CGContextRef context = CGBitmapContextCreate(buffer, w,h, 8, 4 * w, colorSpace, kCGImageAlphaPremultipliedLast | kCGBitmapByteOrder32Big);
        CGColorSpaceRelease(colorSpace);
        CGContextTranslateCTM(context, 0, h);
        CGContextScaleCTM (context, 1.0, -1.0);
        CGContextDrawImage(context, CGRectMake(0,0, w,h), image.CGImage);

        // Create and load texture data
        tex.InitWithData(w, h, PixelFormat::PF_ARGB32, params, buffer);
        res = true;
        
        // Release
        CGContextRelease(context);
        DISPOSE_ARRAY(buffer);
        [image release];
        [data release];
    }
    else
        dry::Log(LOG_WARNING, "[ImageLoader] Can't load image %s", file.c_str());
    return res;
}


//------------------------------------------------------------------------------------------------
// LoadImage
//
//------------------------------------------------------------------------------------------------
bool ImageLoader::LoadImage(string const &file, Image &img)
{
    bool res = false;
    NSString *path  = [NSString stringWithUTF8String:file.c_str()];
    NSData   *data  = [[NSData alloc] initWithContentsOfFile:path];
    UIImage  *image = [[UIImage alloc] initWithData:data];
    if (image != nil)
    {
        CGColorSpaceRef colorSpace = CGColorSpaceCreateDeviceRGB();
        GLuint w = CGImageGetWidth(image.CGImage);
        GLuint h = CGImageGetHeight(image.CGImage);
        uchar *buffer = NEW_ARRAY(uchar, w*h*4);
        CGContextRef context = CGBitmapContextCreate(buffer, w,h, 8, 4 * w, colorSpace, kCGImageAlphaPremultipliedLast | kCGBitmapByteOrder32Big);
        CGColorSpaceRelease(colorSpace);
        CGContextTranslateCTM(context, 0, h);
        CGContextScaleCTM (context, 1.0, -1.0);
        CGContextDrawImage(context, CGRectMake(0,0, w,h), image.CGImage);
        
        // Create and load texture data
        img.InitWithData(w, h, PixelFormat::PF_ARGB32, buffer);
        res = true;
        
        // Release
        CGContextRelease(context);
        DISPOSE_ARRAY(buffer);
        [image release];
        [data release];
    }
    else
        dry::Log(LOG_WARNING, "[ImageLoader] Can't load image %s", file.c_str());
    return res;
}
