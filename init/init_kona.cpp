/*
   Copyright (c) 2020, The LineageOS Project

   Redistribution and use in source and binary forms, with or without
   modification, are permitted provided that the following conditions are
   met:
    * Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above
      copyright notice, this list of conditions and the following
      disclaimer in the documentation and/or other materials provided
      with the distribution.
    * Neither the name of The Linux Foundation nor the names of its
      contributors may be used to endorse or promote products derived
      from this software without specific prior written permission.

   THIS SOFTWARE IS PROVIDED "AS IS" AND ANY EXPRESS OR IMPLIED
   WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
   MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT
   ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS
   BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
   CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
   SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
   BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
   WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
   OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN
   IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <android-base/properties.h>
#define _REALLY_INCLUDE_SYS__SYSTEM_PROPERTIES_H_
#include <stdio.h>
#include <stdlib.h>
#include <sys/sysinfo.h>
#include <sys/system_properties.h>
#include <sys/_system_properties.h>

#include "property_service.h"
#include "vendor_init.h"

using android::base::GetProperty;

std::vector<std::string> ro_props_default_source_order = {
    "",
    "vendor_dlkm."
    "bootimage.",
    "odm.",
    "product.",
    "system.",
    "system_ext.",
    "vendor.",
};

void property_override(char const prop[], char const value[], bool add = true)
{
    prop_info *pi;

    pi = (prop_info *) __system_property_find(prop);
    if (pi)
        __system_property_update(pi, value, strlen(value));
    else if (add)
        __system_property_add(prop, strlen(prop), value, strlen(value));
}

void set_ro_build_prop(const std::string &prop, const std::string &value) {
    for (const auto &source : ro_props_default_source_order) {
        auto prop_name = "ro." + source + "build." + prop;
        if (source == "")
            property_override(prop_name.c_str(), value.c_str());
        else
            property_override(prop_name.c_str(), value.c_str(), false);
    }
};

void set_ro_product_prop(const std::string &prop, const std::string &value) {
    for (const auto &source : ro_props_default_source_order) {
        auto prop_name = "ro.product." + source + prop;
        property_override(prop_name.c_str(), value.c_str(), false);
    }
};

void vendor_load_properties() {

  std::string model;
  std::string device;
  std::string name;
    
  int project_name = stoi(android::base::GetProperty("ro.boot.project_name", ""));
  int rf_version = stoi(android::base::GetProperty("ro.boot.rf_version", ""));
  switch(project_name){
    case 19805:
      /* OnePlus 8T */
      switch (rf_version){
        case 11:
          /* China */
          model = "KB2000";
          device = "OnePlus8T";
          name = "OnePlus8T";
          break;
        case 13:
          /* India */
          model = "KB2001";
          device = "OnePlus8T";
          name = "OnePlus8T";
          break;
        case 14:
          /* Europe */
          model = "KB2003";
          device = "OnePlus8T";
          name = "OnePlus8T";
          break;
        case 15:
          /* Global / US Unlocked */
          model = "KB2005";
          device = "OnePlus8T";
          name = "OnePlus8T";
          break;
        default:
          /* Generic */
          model = "KB2005";
          device = "OnePlus8T";
          name = "OnePlus8T";
          break;
      }
      break;
    case 20809:
      /* OnePlus 8T T-Mobile */
      switch (rf_version){
        case 12:
          /* T-Mobile */
          model = "KB2007";
          device = "OnePlus8T";
          name = "OnePlus8T";
          property_override("persist.radio.multisim.config", "ssss");
          break;
        default:
          /* Generic */
          /* T-Mobile */
          model = "KB2005";
          device = "OnePlus8T";
          name = "OnePlus8T";
          break;
      }
      break;
    case 20828:
      /* OnePlus 9R */
      switch (rf_version){
      case 11:
          /* China */
          /* T-Mobile */
          model = "LE2100";
          device = "OnePlus9R";
          name = "OnePlus9R";
          break;
      case 13:
          /* India */
          model = "LE2101";
          device = "OnePlus9R";
          name = "OnePlus9R";
          break;
      default:
          /* Generic */
          /* India */
          model = "LE2101";
          device = "OnePlus9R";
          name = "OnePlus9R";
          break;
      }
      break;
  }
  
  set_ro_product_prop("device", device);
  set_ro_product_prop("product", device);
  set_ro_product_prop("model", model);
  set_ro_product_prop("name", name);
}
