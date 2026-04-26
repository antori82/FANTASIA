// Auto-generated wrapper. Do not edit. Run setup_whisper.ps1 to regenerate.
//
// FANTASIA_WITH_CUDA is defined by FANTASIA.Build.cs:
//   1 = prebuilt whisper.cpp CUDA libs are linked. This wrapper MUST compile
//       to an empty translation unit; otherwise we'd produce duplicate
//       symbols at link time alongside the prebuilt libs.
//   0 = no prebuilt libs found, fall back to compiling whisper.cpp sources
//       in-tree via the include below.
#if !FANTASIA_WITH_CUDA
#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable: 4456 4457 4458 4459 4244 4267 4800 4756 4100 4127 4189 4706 4702 4310 4305 4242 4389 4554)
#endif
#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Weverything"
#endif

#include "../../../../ThirdParty/whisper_cpp/ggml/src/ggml-backend-reg.cpp"

#ifdef __clang__
#pragma clang diagnostic pop
#endif
#ifdef _MSC_VER
#pragma warning(pop)
#endif
#endif // !FANTASIA_WITH_CUDA