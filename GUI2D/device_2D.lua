format_version = "2.0"



front = {
  Bg = { {path = "front1U"} },
  onoffbypass = {
      offset = {185,200},
      {path="Fader_Bypass_3frames", frames = 3 },
    },
  patches = { offset = { 200,10},{ path = "PatchBrowseGroup", frames = 1}},
  patch = { offset = {505,20},{ path = "204x10_5x5",frames=1}},
  deviceName = {
    offset = { 1600, 10 },
    { path = "Tape_Horizontal_1frames", frames = 1 },
  },
  phase = {
    offset = { 1000, 100 },
    { path = "Knob_01_63frames", frames = 63 }
  },
  angle = {
    offset = { 1400, 100 },
    { path = "Knob_01_63frames", frames = 63 }
  },
  limiterOnOff = {
    offset = { 2050, 100 },
    { path = "Button_53_2frames", frames = 2}
  },
  limiterHardSoft = {
    offset = { 2050, 215 },
    { path = "Button_53_2frames", frames = 2}
  },
  limiter = {
    offset = { 1800, 100 },
    { path = "Knob_01_63frames", frames = 63 }
  },
  inGain = {
    offset = { 2400, 100 },
    { path = "Knob_01_63frames", frames = 63 }
  },
  outGain = {
    offset = { 2800, 100 },
    { path = "Knob_01_63frames", frames = 63 }
  },
  inData = {
    offset = {2400, 30 },
    { path = "Lamp_10_GREEN_2frames", frames = 2}
  },
  outData = {
    offset = {2800, 30 },
    { path = "Lamp_10_GREEN_2frames", frames = 2}
  },
}
back = {
  Bg = { {path = "backPanel"} },
  Placeholder = {
    offset = { 2000, 100 },
    { path = "Placeholder" },
  },
  deviceName = {
    offset = { 100, 230 },
    { path = "Tape_Horizontal_1frames", frames = 1 },
  },
  audioInputL = {
    offset = { 1000,120 },
    { path = "SharedAudioJack", frames = 3 }
  },
    audioInputR = {
    offset = { 1200,120 },
    { path = "SharedAudioJack", frames = 3 }
  },
  audioOutputL = {
    offset = { 1550,120 },
    { path = "SharedAudioJack", frames = 3 }
  },
  
  audioOutputR = {
    offset = { 1750,120  },
    { path = "SharedAudioJack", frames = 3 }
  },
}




folded_front = {
	Bg = {{ path = "Panel_Folded_Front" }}
}
folded_back = { 
  Bg = {{ path = "Panel_Folded_Back" }},
  CableOrigin = { offset = { 1885, 75 }}
}





