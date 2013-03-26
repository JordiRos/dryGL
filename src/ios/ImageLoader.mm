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
bool ImageLoader::LoadTexture(Texture &tex, string const &file, Texture::Params const &params)
{
    bool res = false;
    dry::Log(LogInfo, "[ImageLoader] Load texture from file: %s", file.c_str());
    NSString *path  = [NSString stringWithUTF8String:file.c_str()];
    NSData   *data  = [NSData dataWithContentsOfFile:path];
    UIImage  *image = [UIImage imageWithData:data];
    if (image != nil)
    {
        CGColorSpaceRef colorSpace = CGColorSpaceCreateDeviceRGB();
        GLuint w = CGImageGetWidth(image.CGImage);
        GLuint h = CGImageGetHeight(image.CGImage);
        uchar *buffer = NEW_ARRAY(uchar, w*h*4);
        CGContextRef context = CGBitmapContextCreate(buffer, w,h, 8, 4 * w, colorSpace, kCGImageAlphaPremultipliedLast | kCGBitmapByteOrder32Big);
        CGColorSpaceRelease(colorSpace);
        //CGContextTranslateCTM(context, 0, h);
        //CGContextScaleCTM (context, 1.0, -1.0);
        CGContextDrawImage(context, CGRectMake(0,0, w,h), image.CGImage);

        // Create and load texture data
        tex.InitWithData(w, h, PixelFormatArgb32, params, buffer);
        res = true;
        
        // Release
        CGContextRelease(context);
        DISPOSE_ARRAY(buffer);
    }
    else
        dry::Log(LogWarning, "[ImageLoader] Error loading image %s", file.c_str());
    return res;
}


//------------------------------------------------------------------------------------------------
// LoadImage
//
//------------------------------------------------------------------------------------------------
bool ImageLoader::LoadImage(Image &img, string const &file)
{
    bool res = false;
    dry::Log(LogInfo, "[ImageLoader] Load image from file: %s", file.c_str());
    NSString *path  = [NSString stringWithUTF8String:file.c_str()];
    NSData   *data  = [NSData dataWithContentsOfFile:path];
    UIImage  *image = [UIImage imageWithData:data];
    if (image != nil)
    {
        CGColorSpaceRef colorSpace = CGColorSpaceCreateDeviceRGB();
        GLuint w = CGImageGetWidth(image.CGImage);
        GLuint h = CGImageGetHeight(image.CGImage);
        uchar *buffer = NEW_ARRAY(uchar, w*h*4);
        CGContextRef context = CGBitmapContextCreate(buffer, w,h, 8, 4 * w, colorSpace, kCGImageAlphaPremultipliedLast | kCGBitmapByteOrder32Big);
        CGColorSpaceRelease(colorSpace);
        //CGContextTranslateCTM(context, 0, h);
        //CGContextScaleCTM (context, 1.0, -1.0);
        CGContextDrawImage(context, CGRectMake(0,0, w,h), image.CGImage);
        
        // Create and load texture data
        img.InitWithData(w, h, PixelFormatArgb32, buffer);
        res = true;
        
        // Release
        CGContextRelease(context);
        DISPOSE_ARRAY(buffer);
    }
    else
        dry::Log(LogWarning, "[ImageLoader] Error loading image %s", file.c_str());
    return res;
}
