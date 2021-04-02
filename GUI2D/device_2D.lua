format_version = "2.0"



front = {
  Bg = { {path = "front1U"} },
  onoffbypass = {
      offset = {185,400},
      {path="Fader_Bypass_3frames", frames = 3 },
    },
  patches = { offset = { 200,10},{ path = "PatchBrowseGroup", frames = 1}},
  patch = { offset = {505,20},{ path = "204x10_5x5",frames=1}},
  deviceName = {
    offset = { 3200, 250},
    { path = "Tape_Horizontal_1frames", frames = 1 },
  },
  phase = {
    offset = { 1100, 80 },
    { path = "Knob_01_63frames", frames = 63 }
  },
  offset = {
    offset = { 1400, 80 },
    { path = "Knob_01_63frames", frames = 63 }
  },
  angle = {
    offset = { 1700, 80 },
    { path = "Knob_01_63frames", frames = 63 }
  },
  limiterOnOff = {
    offset = { 2000, 80 },
    { path = "Button_53_02frames", frames = 2}
  },
  limiterHardSoft = {
    offset = { 2000, 30 },
    { path = "Button_53_02frames", frames = 2}
  },
  limiter = {
    offset = { 2300, 80 },
    { path = "Knob_01_63frames", frames = 63 }
  },
  gain = {
    offset = { 2650, 80 },
    { path = "Knob_01_63frames", frames = 63 }
  }
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





