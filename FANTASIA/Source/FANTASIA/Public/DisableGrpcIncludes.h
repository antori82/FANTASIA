/**
 * @file DisableGrpcIncludes.h
 * @brief Include-guard epilogue that restores UE platform macros hidden by
 *        EnableGrpcIncludes.h after gRPC / Protobuf headers have been included.
 *
 * Must be included after the gRPC headers and after EnableGrpcIncludes.h.
 */

#pragma once
#ifndef __ANDROID__
#include "Windows/HideWindowsPlatformTypes.h"
#endif