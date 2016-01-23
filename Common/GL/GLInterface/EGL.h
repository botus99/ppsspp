// Copyright 2008 Dolphin Emulator Project
// Licensed under GPLv2+
// Refer to the license.txt file included.

#pragma once

#include <string>
#include <EGL/egl.h>

#include "Common/GL/GLInterfaceBase.h"

#ifdef ANDROID
// On Android, EGL creation is so early that our regular logging system is not
// up and running yet. Use Android logging.
#include "base/logging.h"
#define EGL_ILOG(...) ILOG(__VA_ARGS__)
#define EGL_ELOG(...) ELOG(__VA_ARGS__)

#else

#define EGL_ILOG(...) INFO_LOG(G3D, __VA_ARGS__)
#define EGL_ELOG(...) INFO_LOG(G3D, __VA_ARGS__)

#endif


class cInterfaceEGL : public cInterfaceBase
{
protected:
	void DetectMode();
	EGLSurface egl_surf;
	EGLContext egl_ctx;
	EGLDisplay egl_dpy;

	virtual EGLDisplay OpenDisplay() = 0;
	virtual EGLNativeWindowType InitializePlatform(EGLNativeWindowType host_window, EGLConfig config) = 0;
	virtual void ShutdownPlatform() = 0;
	virtual void SetInternalResolution(int internalWidth, int internalHeight) {}
	const char *EGLGetErrorString(EGLint error);

public:
	void SwapInterval(int Interval);
	void Swap();
	void SetMode(u32 mode) { s_opengl_mode = mode; }
	void* GetFuncAddress(const std::string& name);
	bool Create(void *window_handle, bool core, bool use16bit) override;
	bool MakeCurrent();
	bool ClearCurrent();
	void Shutdown();
};
