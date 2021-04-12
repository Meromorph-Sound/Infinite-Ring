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
    jbox.analog_knob { 
      graphics = { node = "offset" },
      value = "/custom_properties/offset"
     },
     jbox.analog_knob { 
      graphics = { node = "angle" },
      value = "/custom_properties/angle"
     },
     jbox.analog_knob { 
      graphics = { node = "gain" },
      value = "/custom_properties/gain"
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
     }
     
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
