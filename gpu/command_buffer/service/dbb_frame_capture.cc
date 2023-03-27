#include "dbb_frame_capture.h"

#include <dlfcn.h>
#include "renderdoc_app.h"

static RENDERDOC_API_1_1_2 *rdoc_api = nullptr;

const char* dbb::startFrameCapture() {
  if(void* mod = dlopen("librenderdoc.dylib", RTLD_NOW | RTLD_NOLOAD)) {
    pRENDERDOC_GetAPI RENDERDOC_GetAPI = (pRENDERDOC_GetAPI)dlsym(mod, "RENDERDOC_GetAPI");
    if(RENDERDOC_GetAPI(eRENDERDOC_API_Version_1_1_2, (void **)&rdoc_api)) {
      rdoc_api->StartFrameCapture(nullptr, nullptr);
    } else {
      return "Failed to find RenderDoc API";  
    }
    
  } else {
    return "Couldn't start frame capture because RenderDoc is not connected";
  }
  return nullptr;
}

const char* dbb::stopFrameCapture() {
  if(rdoc_api) {
    rdoc_api->EndFrameCapture(nullptr, nullptr);
  } else {
    return "Couldn't end frame capture because RenderDoc is not connected";
  }
  return nullptr;
}