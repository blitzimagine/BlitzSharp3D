#include "monoutil.h"
#include "../bbruntime/bbgraphics.h"

PUBLIC_METHOD int CountGfxDrivers()
{
	return bbCountGfxDrivers();
}

PUBLIC_METHOD void GfxDriverName_internal(char* ret, int retLen, int driver)
{
	strcpy_s(ret, retLen, toMonoStr(bbGfxDriverName(driver)));
}

PUBLIC_METHOD void SetGfxDriver(int driver)
{
	bbSetGfxDriver(driver);
}

PUBLIC_METHOD int CountGfxModes()
{
	return bbCountGfxModes();
}

PUBLIC_METHOD int GfxModeExists(int width, int height, int depth)
{
	return bbGfxModeExists(width, height, depth) != 0;
}

PUBLIC_METHOD int GfxModeWidth(int mode)
{
	return bbGfxModeWidth(mode);
}

PUBLIC_METHOD int GfxModeHeight(int mode)
{
	return bbGfxModeHeight(mode);
}

PUBLIC_METHOD int GfxModeDepth(int mode)
{
	return bbGfxModeDepth(mode);
}

PUBLIC_METHOD int AvailVidMem()
{
	return bbAvailVidMem();
}

PUBLIC_METHOD int TotalVidMem()
{
	return bbTotalVidMem();
}

PUBLIC_METHOD int GfxDriver3D(int driver)
{
	return bbGfxDriver3D(driver) != 0;
}

PUBLIC_METHOD int CountGfxModes3D()
{
	return bbCountGfxModes3D();
}

PUBLIC_METHOD int GfxMode3DExists(int width, int height, int depth)
{
	return bbGfxMode3DExists(width, height, depth) != 0;
}

PUBLIC_METHOD int GfxMode3D(int mode)
{
	return bbGfxMode3D(mode) != 0;
}

PUBLIC_METHOD int Windowed3D()
{
	return bbWindowed3D() != 0;
}

PUBLIC_METHOD void Graphics(int width, int height, int depth, int mode, int monitor)
{
	bbGraphics(width, height, depth, mode, monitor);
}

PUBLIC_METHOD void Graphics3D(int width, int height, int depth, int mode, int monitor)
{
	bbGraphics3D(width, height, depth, mode, monitor);
}

PUBLIC_METHOD void EndGraphics()
{
	bbEndGraphics();
}

PUBLIC_METHOD int SetGraphicsMode_internal(int width, int height, int depth, int mode, int monitor)
{
	return bbSetGraphicsMode(width, height, depth, mode, monitor);
}

PUBLIC_METHOD int GraphicsLost()
{
	return bbGraphicsLost() != 0;
}

PUBLIC_METHOD int IsFocused()
{
	return bbIsFocused() != 0;
}

PUBLIC_METHOD void SetGamma(int srcRed, int srcGreen, int srcBlue, float destRed, float destGreen, float destBlue)
{
	bbSetGamma(srcRed, srcGreen, srcBlue, destRed, destGreen, destBlue);
}

PUBLIC_METHOD void UpdateGamma(int calibrate)
{
	bbUpdateGamma(calibrate ? 1 : 0);
}

PUBLIC_METHOD float GammaRed(int red)
{
	return bbGammaRed(red);
}

PUBLIC_METHOD float GammaGreen(int red)
{
	return bbGammaGreen(red);
}

PUBLIC_METHOD float GammaBlue(int red)
{
	return bbGammaBlue(red);
}

PUBLIC_METHOD gxCanvas* FrontBuffer_internal()
{
	return bbFrontBuffer();
}

PUBLIC_METHOD gxCanvas* BackBuffer_internal()
{
	return bbBackBuffer();
}

PUBLIC_METHOD int ScanLine()
{
	return bbScanLine();
}

PUBLIC_METHOD void VWait(int frames)
{
	bbVWait(frames);
}

PUBLIC_METHOD void Flip(int vwait)
{
	bbFlip(vwait ? 1 : 0);
}

PUBLIC_METHOD int GraphicsWidth()
{
	return bbGraphicsWidth();
}

PUBLIC_METHOD int GraphicsHeight()
{
	return bbGraphicsHeight();
}

PUBLIC_METHOD int GraphicsDepth()
{
	return bbGraphicsDepth();
}

PUBLIC_METHOD void SetBuffer_internal(gxCanvas* buffer)
{
	bbSetBuffer(buffer);
}

PUBLIC_METHOD gxCanvas* GraphicsBuffer_internal()
{
	return bbGraphicsBuffer();
}

PUBLIC_METHOD int LoadBuffer_internal(gxCanvas* buffer, const char* bmpFile)
{
	BBStr* bmp = toBBStr(bmpFile);
	int ret = bbLoadBuffer(buffer, bmp);
	freeBBStr(bmp);
	return ret != 0;
}

PUBLIC_METHOD int SaveBuffer_internal(gxCanvas* buffer, const char* bmpFile)
{
	BBStr* bmp = toBBStr(bmpFile);
	int ret = bbSaveBuffer(buffer, bmp);
	freeBBStr(bmp);
	return ret != 0;
}

PUBLIC_METHOD void BufferDirty_internal(gxCanvas* buffer)
{
	bbBufferDirty(buffer);
}

PUBLIC_METHOD void LockBuffer_internal(gxCanvas* buffer)
{
	bbLockBuffer(buffer);
}

PUBLIC_METHOD void UnlockBuffer_internal(gxCanvas* buffer)
{
	bbUnlockBuffer(buffer);
}

PUBLIC_METHOD int ReadPixel_internal(int x, int y, gxCanvas* buffer)
{
	return bbReadPixel(x, y, buffer);
}

PUBLIC_METHOD void WritePixel_internal(int x, int y, int argb, gxCanvas* buffer)
{
	bbWritePixel(x, y, argb, buffer);
}

PUBLIC_METHOD int ReadPixelFast_internal(int x, int y, gxCanvas* buffer)
{
	return bbReadPixelFast(x, y, buffer);
}

PUBLIC_METHOD void WritePixelFast_internal(int x, int y, int argb, gxCanvas* buffer)
{
	bbWritePixelFast(x, y, argb, buffer);
}

PUBLIC_METHOD void CopyPixel_internal(int srcX, int srcY, gxCanvas* srcBuffer, int destX, int destY, gxCanvas* destBuffer)
{
	bbCopyPixel(srcX, srcY, srcBuffer, destX, destY, destBuffer);
}

PUBLIC_METHOD void CopyPixelFast_internal(int srcX, int srcY, gxCanvas* srcBuffer, int destX, int destY, gxCanvas* destBuffer)
{
	bbCopyPixelFast(srcX, srcY, srcBuffer, destX, destY, destBuffer);
}

PUBLIC_METHOD void Origin(int x, int y)
{
	bbOrigin(x, y);
}

PUBLIC_METHOD void Viewport(int x, int y, int width, int height)
{
	bbViewport(x, y, width, height);
}

PUBLIC_METHOD void Color(int r, int g, int b)
{
	bbColor(r, g, b);
}

PUBLIC_METHOD void GetColor(int x, int y)
{
	bbGetColor(x, y);
}

PUBLIC_METHOD int ColorRed()
{
	return bbColorRed();
}

PUBLIC_METHOD int ColorGreen()
{
	return bbColorGreen();
}

PUBLIC_METHOD int ColorBlue()
{
	return bbColorBlue();
}

PUBLIC_METHOD void ClsColor(int r, int g, int b)
{
	bbClsColor(r, g, b);
}

PUBLIC_METHOD void SetFont_internal(gxFont* font)
{
	bbSetFont(font);
}

PUBLIC_METHOD void Cls()
{
	bbCls();
}

PUBLIC_METHOD void Plot(int x, int y)
{
	bbPlot(x, y);
}

PUBLIC_METHOD void Rect(int x, int y, int width, int height, int solid)
{
	bbRect(x, y, width, height, solid ? 1 : 0);
}

PUBLIC_METHOD void Oval(int x, int y, int width, int height, int solid)
{
	bbOval(x, y, width, height, solid ? 1 : 0);
}

PUBLIC_METHOD void Line(int x1, int y1, int x2, int y2)
{
	bbLine(x1, y1, x2, y2);
}

PUBLIC_METHOD void Text(int x, int y, const char* str, int centerX, int centerY)
{
	BBStr* s = toBBStr(str);
	bbText(x, y, s, centerX, centerY);
	freeBBStr(s);
}

PUBLIC_METHOD void CopyRect_internal(int srcX, int srcY, int width, int height, int destX, int destY, gxCanvas* srcBuffer, gxCanvas* destBuffer)
{
	bbCopyRect(srcX, srcY, width, height, destX, destY, srcBuffer, destBuffer);
}

PUBLIC_METHOD gxFont* LoadFont_internal(const char* name, int height, int bold, int italic, int underline)
{
	BBStr* n = toBBStr(name);
	gxFont* ret = bbLoadFont(n, height, bold != 0, italic != 0, underline != 0);
	freeBBStr(n);
	return ret;
}

PUBLIC_METHOD void FreeFont_internal(gxFont* font)
{
	bbFreeFont(font);
}

PUBLIC_METHOD int FontWidth()
{
	return bbFontWidth();
}

PUBLIC_METHOD int FontHeight()
{
	return bbFontHeight();
}

PUBLIC_METHOD int StringWidth(const char* str)
{
	BBStr* s = toBBStr(str);
	int ret = bbStringWidth(s);
	freeBBStr(s);
	return ret;
}

PUBLIC_METHOD int StringHeight(const char* str)
{
	BBStr* s = toBBStr(str);
	int ret = bbStringHeight(s);
	freeBBStr(s);
	return ret;
}

PUBLIC_METHOD gxMovie* OpenMovie_internal(const char* file)
{
	BBStr* f = toBBStr(file);
	gxMovie* ret = bbOpenMovie(f);
	freeBBStr(f);
	return ret;
}

PUBLIC_METHOD int DrawMovie_internal(gxMovie* movie, int x, int y, int width, int height)
{
	return bbDrawMovie(movie, x, y, width, height) != 0;
}

PUBLIC_METHOD int MovieWidth_internal(gxMovie* movie)
{
	return bbMovieWidth(movie);
}

PUBLIC_METHOD int MovieHeight_internal(gxMovie* movie)
{
	return bbMovieHeight(movie);
}

PUBLIC_METHOD int MoviePlaying_internal(gxMovie* movie)
{
	return bbMoviePlaying(movie) != 0;
}

PUBLIC_METHOD void CloseMovie_internal(gxMovie* movie)
{
	bbCloseMovie(movie);
}

PUBLIC_METHOD bbImage* LoadImage_internal(const char* bmpFile)
{
	BBStr* bmp = toBBStr(bmpFile);
	bbImage* ret = bbLoadImage(bmp);
	freeBBStr(bmp);
	return ret;
}

PUBLIC_METHOD bbImage* LoadAnimImage_internal(const char* bmpFile, int cellwidth, int cellheight, int first, int count)
{
	BBStr* bmp = toBBStr(bmpFile);
	bbImage* ret = bbLoadAnimImage(bmp, cellwidth, cellheight, first, count);
	freeBBStr(bmp);
	return ret;
}

PUBLIC_METHOD bbImage* CopyImage_internal(bbImage* image)
{
	return bbCopyImage(image);
}

PUBLIC_METHOD bbImage* CreateImage_internal(int width, int height, int frames)
{
	return bbCreateImage(width, height, frames);
}

PUBLIC_METHOD void FreeImage_internal(bbImage* image)
{
	bbFreeImage(image);
}

PUBLIC_METHOD int SaveImage_internal(bbImage* image, const char* bmpFile, int frame)
{
	BBStr* bmp = toBBStr(bmpFile);
	int ret = bbSaveImage(image, bmp, frame);
	freeBBStr(bmp);
	return ret != 0;
}

PUBLIC_METHOD void GrabImage_internal(bbImage* image, int x, int y, int frame)
{
	bbGrabImage(image, x, y, frame);
}

PUBLIC_METHOD gxCanvas* ImageBuffer_internal(bbImage* image, int frame)
{
	return bbImageBuffer(image, frame);
}

PUBLIC_METHOD void DrawImage_internal(bbImage* image, int x, int y, int frame)
{
	bbDrawImage(image, x, y, frame);
}

PUBLIC_METHOD void DrawBlock_internal(bbImage* image, int x, int y, int frame)
{
	bbDrawBlock(image, x, y, frame);
}

PUBLIC_METHOD void TileImage_internal(bbImage* image, int x, int y, int frame)
{
	bbTileImage(image, x, y, frame);
}

PUBLIC_METHOD void TileBlock_internal(bbImage* image, int x, int y, int frame)
{
	bbTileBlock(image, x, y, frame);
}

PUBLIC_METHOD void DrawImageRect_internal(bbImage* image, int x, int y, int rectX, int rectY, int rectWidth, int rectHeight, int frame)
{
	bbDrawImageRect(image, x, y, rectX, rectY, rectWidth, rectHeight, frame);
}

PUBLIC_METHOD void DrawBlockRect_internal(bbImage* image, int x, int y, int rectX, int rectY, int rectWidth, int rectHeight, int frame)
{
	bbDrawBlockRect(image, x, y, rectX, rectY, rectWidth, rectHeight, frame);
}

PUBLIC_METHOD void MaskImage_internal(bbImage* image, int red, int green, int blue)
{
	bbMaskImage(image, red, green, blue);
}

PUBLIC_METHOD void HandleImage_internal(bbImage* image, int x, int y)
{
	bbHandleImage(image, x, y);
}

PUBLIC_METHOD void MidHandle_internal(bbImage* image)
{
	bbMidHandle(image);
}

PUBLIC_METHOD void AutoMidHandle(int enable)
{
	bbAutoMidHandle(enable ? 1 : 0);
}

PUBLIC_METHOD int ImageWidth_internal(bbImage* image)
{
	return bbImageWidth(image);
}

PUBLIC_METHOD int ImageHeight_internal(bbImage* image)
{
	return bbImageHeight(image);
}

PUBLIC_METHOD int ImageXHandle_internal(bbImage* image)
{
	return bbImageXHandle(image);
}

PUBLIC_METHOD int ImageYHandle_internal(bbImage* image)
{
	return bbImageYHandle(image);
}

PUBLIC_METHOD void ScaleImage_internal(bbImage* image, float xscale, float yscale)
{
	bbScaleImage(image, xscale, yscale);
}

PUBLIC_METHOD void ResizeImage_internal(bbImage* image, float width, float height)
{
	bbResizeImage(image, width, height);
}

PUBLIC_METHOD void RotateImage_internal(bbImage* image, float angle)
{
	bbRotateImage(image, angle);
}

PUBLIC_METHOD void TFormImage_internal(bbImage* image, float a, float b, float c, float d)
{
	bbTFormImage(image, a, b, c, d);
}

PUBLIC_METHOD void TFormFilter(int enable)
{
	bbTFormFilter(enable ? 1 : 0);
}

PUBLIC_METHOD int ImagesOverlap_internal(bbImage* image1, int x1, int y1, bbImage* image2, int x2, int y2)
{
	return bbImagesOverlap(image1, x1, y1, image2, x2, y2) != 0;
}

PUBLIC_METHOD int ImagesCollide_internal(bbImage* image1, int x1, int y1, int frame1, bbImage* image2, int x2, int y2, int frame2)
{
	return bbImagesCollide(image1, x1, y1, frame1, image2, x2, y2, frame2) != 0;
}

PUBLIC_METHOD int RectsOverlap(int x1, int y1, int width1, int height1, int x2, int y2, int width2, int height2)
{
	return bbRectsOverlap(x1, y1, width1, height1, x2, y2, width2, height2) != 0;
}

PUBLIC_METHOD int ImageRectOverlap_internal(bbImage* image, int x, int y, int rectX, int rectY, int rectWidth, int rectHeight)
{
	return bbImageRectOverlap(image, x, y, rectX, rectY, rectWidth, rectHeight) != 0;
}

PUBLIC_METHOD int ImageRectCollide_internal(bbImage* image, int x, int y, int frame, int rectX, int rectY, int rectWidth, int rectHeight)
{
	return bbImageRectCollide(image, x, y, frame, rectX, rectY, rectWidth, rectHeight) != 0;
}

PUBLIC_METHOD void Write(const char* str)
{
	BBStr* s = toBBStr(str);
	bbWrite(s);
	freeBBStr(s);
}

PUBLIC_METHOD void Print(const char* str)
{
	BBStr* s = toBBStr(str);
	bbPrint(s);
	freeBBStr(s);
}

PUBLIC_METHOD void Input_internal(char* ret, int retLen, const char* prompt)
{
	BBStr* p = toBBStr(prompt);
	BBStr* r = bbInput(p);
	strcpy_s(ret, retLen, toMonoStr(r));
	freeBBStr(p);
}

PUBLIC_METHOD void Locate(int x, int y)
{
	bbLocate(x, y);
}

PUBLIC_METHOD void ShowPointer()
{
	bbShowPointer();
}

PUBLIC_METHOD void HidePointer()
{
	bbHidePointer();
}