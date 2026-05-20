# Third-party licenses

FANTASIA bundles or fetches third-party software. Each component is
listed below with its license and upstream source. Where a `LICENSE`
or `COPYING` file ships with the component in its source tree, that
file is authoritative; this document is a summary index.

Nothing here grants any rights beyond what the upstream licenses do.
If you redistribute FANTASIA (or your project containing it), you must
also redistribute the corresponding license text from each component.

## Tracked in this repository

### whisper.cpp + ggml
- **Source:** `FANTASIA/ThirdParty/whisper_cpp/`
- **Upstream:** https://github.com/ggerganov/whisper.cpp
- **License:** MIT — Copyright (c) 2023-2024 The ggml authors
- **License text:** `FANTASIA/ThirdParty/whisper_cpp/LICENSE`

### aGrUM
- **Source:** `FANTASIA/ThirdParty/aGrUM/`
- **Upstream:** https://agrum.gitlab.io/
- **License:** LGPL v3
- **Notes:** FANTASIA links the prebuilt static library
  `aGrUM/Libraries/aGrUM.x64.lib` against the FANTASIA module. LGPL
  permits static linking provided users can relink against a different
  aGrUM build; we ship the headers so this is satisfiable.

### gRPC + Protocol Buffers
- **Source:** `FANTASIA/ThirdParty/grpc/`
- **Upstream:** https://github.com/grpc/grpc , https://github.com/protocolbuffers/protobuf
- **License:** Apache License 2.0 (gRPC), BSD 3-Clause (protobuf)
- **License text:** included in the gRPC source distribution

### OpenSSL 1.1.1t
- **Source:** `FANTASIA/ThirdParty/OpenSSL/1.1.1t/`
- **Upstream:** https://www.openssl.org/source/old/1.1.1/
- **License:** Dual OpenSSL + SSLeay license (the legacy 1.1.x licensing
  scheme; later 3.x versions move to Apache 2.0).

### nlohmann/json
- **Source:** `FANTASIA/ThirdParty/nlohmann/`
- **Upstream:** https://github.com/nlohmann/json
- **License:** MIT — Copyright (c) 2013-2024 Niels Lohmann

### kdepp
- **Source:** `FANTASIA/ThirdParty/kdepp/`
- **Upstream:** https://github.com/duncanmcn/kdepp
- **License:** MIT — by Duncan McNae

### SWI-Prolog
- **Source:** `FANTASIA/ThirdParty/SWIProlog/`
- **Upstream:** https://www.swi-prolog.org/
- **License:** SWI-Prolog license, equivalent to LGPL v2 with a static-
  linking exception. Prebuilt `libswipl.dll` and the runtime DLLs in
  `Binaries/Win64/` (archive4pl, bdb4pl, crypto4pl, etc.) are shipped
  under this license.

## Fetched at runtime via `bootstrap.{bat,sh}` (runtime-v2.0 Release)

### Whisper model — `ggml-large-v3-turbo-q5_0.bin`
- **Origin:** The model is a ggml-format quantization of OpenAI's
  Whisper large-v3-turbo. The original weights and inference code were
  released by OpenAI in September 2022.
- **License:** MIT — Copyright (c) 2022 OpenAI
- **Upstream:** https://github.com/openai/whisper ;
  ggml conversions are typically hosted under
  https://huggingface.co/ggerganov/whisper.cpp

### Prebuilt GPU stack — `fantasia-gpu-cuda13-win64.tar.gz`
Bundles:

- `fantasia_whisper_cuda.dll`, `ggml.dll`, `ggml-base.dll`,
  `ggml-cpu.dll`, `ggml-cuda.dll` — built from `whisper.cpp` source
  (MIT, see above).
- `cudart64_13.dll`, `cublas64_13.dll`, `cublasLt64_13.dll` — NVIDIA
  CUDA 13 redistributable runtime libraries.

For the NVIDIA components:

- **License:** NVIDIA CUDA Toolkit EULA, "Attachment A — Distributable
  Code". The three filenames above are explicitly listed as permitted
  for redistribution alongside end-user applications.
- **Upstream:** https://docs.nvidia.com/cuda/eula/ (full EULA text)
- **Attribution:** NVIDIA CUDA, Copyright © 2007-2025 NVIDIA Corporation.
  Used under the terms of the CUDA Toolkit EULA.

If you redistribute the GPU stack outside of FANTASIA's own
distribution, link the NVIDIA EULA above prominently in your own
licensing documentation.

## Required separately, not bundled

### NV_ACE_Reference (NVIDIA Audio2Face)
The optional `FANTASIAACE` companion plugin depends on NVIDIA's
`NV_ACE_Reference` plugin from the Unreal Marketplace, which is
installed by the user under NVIDIA's own license. We do not
redistribute any part of it.

- **Source:** Epic Marketplace / Fab
- **License:** NVIDIA NIM / ACE license terms (see the Marketplace
  listing). Refer to NVIDIA for the current text.
