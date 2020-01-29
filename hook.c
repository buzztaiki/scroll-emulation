#define _GNU_SOURCE
#include <dlfcn.h>
#include <libinput.h>
#include <string.h>

const char* NAME = "Kensington Expert Wireless TB Mouse";

typedef const char* (*orig_get_name_t)(struct libinput_device *device);

void set_scroll_emulation(const char* name, struct libinput_device *device) {
  if (strstr(name, NAME)) {
    libinput_device_config_middle_emulation_set_enabled(device, LIBINPUT_CONFIG_MIDDLE_EMULATION_ENABLED);
    libinput_device_config_scroll_set_method(device, LIBINPUT_CONFIG_SCROLL_ON_BUTTON_DOWN);
    libinput_device_config_scroll_set_button(device, 273);
  }
}

const char* libinput_device_get_name(struct libinput_device *device) {
  orig_get_name_t orig_get_name = (orig_get_name_t) dlsym(RTLD_NEXT, "libinput_device_get_name");
  const char* name = orig_get_name(device);
  set_scroll_emulation(name, device); // Inject the code to set scrolling emulation
  return name;
}
