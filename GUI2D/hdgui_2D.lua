format_version = "2.0"
front = jbox.panel { 
  graphics = { node = "Bg" },
  widgets = {
    jbox.device_name { graphics = { node = "deviceName" } },
    jbox.sequence_fader{
      graphics = { node = "onoffbypass" },
      handle_size = 0,
      value = "/custom_properties/builtin_onoffbypass",
    },
    jbox.analog_knob { 
      graphics = { node = "phase" },
      value = "/custom_properties/phase"
    },
     jbox.radio_button { 
      graphics = { node = "modeR" },
      value = "/custom_properties/mode",
      index = 0
     },
     jbox.radio_button { 
      graphics = { node = "modeRC" },
      value = "/custom_properties/mode",
      index = 1
     },
     jbox.radio_button { 
      graphics = { node = "modeC" },
      value = "/custom_properties/mode",
      index = 2
     },
     jbox.toggle_button { 
      graphics = { node = "limiterOnOff" },
      value = "/custom_properties/limiterOnOff"
     },
     jbox.toggle_button {
      graphics = { node = "limiterHardSoft" },
      value = "/custom_properties/limiterHardSoft"
     },
     jbox.analog_knob {
      graphics = { node = "limiter" },
      value = "/custom_properties/limiter"
     },
     jbox.analog_knob { 
      graphics = { node = "inGain" },
      value = "/custom_properties/inGain"
     },
     jbox.analog_knob {
      graphics = { node = "outGain" },
      value = "/custom_properties/outGain"
     },
     jbox.sequence_meter {
       graphics = { node = "outClipL" },
       value = "/custom_properties/outClipL"
     },
     jbox.sequence_meter {
       graphics = { node = "outClipR" },
       value = "/custom_properties/outClipR"
     },
     jbox.custom_display {
      graphics={node="outVolL"},
      display_width_pixels=300,
      display_height_pixels=40,
      values = { "/custom_properties/outVolL" },
      draw_function = "drawVolume"
    },
    jbox.custom_display {
      graphics={node="outVolR"},
      display_width_pixels=300,
      display_height_pixels=40,
      values = { "/custom_properties/outVolR" },
      draw_function = "drawVolume"
    },
     
  }
}
back = jbox.panel { 
  graphics = { node = "Bg" },
  widgets = {
    jbox.placeholder {
      graphics = { node = "Placeholder" },
    },
    jbox.audio_output_socket {
      graphics = { node = "audioOutputL" },
      socket = "/audio_outputs/Left",
    },
    jbox.audio_output_socket {
      graphics = { node = "audioOutputR" },
      socket = "/audio_outputs/Right",
    },
    jbox.audio_input_socket {
      graphics = { node = "audioInputL" },
      socket = "/audio_inputs/Left",
    },
    jbox.audio_input_socket {
      graphics = { node = "audioInputR" },
      socket = "/audio_inputs/Right",
    },
    jbox.device_name {
      graphics = { node = "deviceName" },
    },
  },
}
folded_front = jbox.panel { 
  graphics = { node = "Bg" },
  widgets = {},
}
folded_back = jbox.panel { 
  graphics = { node = "Bg" },
  cable_origin = { node = "CableOrigin" },
  widgets = {},
}
