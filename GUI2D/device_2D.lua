format_version = "2.0"



front = {
  Bg = { {path = "front1U"} },
  onoffbypass = {offset = {200,20},{path="Fader_Bypass_3frames", frames = 3 }},
  patches = { offset = { 500,10},{ path = "PatchBrowseGroup", frames = 1}},
  patch = { offset = {805,10},{ path = "PatchName_1frames",frames=1}},
  deviceName = {offset = { 1900, 10 },{ path = "Tape_Horizontal_1frames", frames = 1 },},
  phase = {offset = { 1000, 100 },{ path = "Knob_01_63frames", frames = 63 }},
  modeR = {offset = { 1360, 120 },{ path = "Button_53_2frames", frames = 2 }},
  modeRC = {offset = { 1460, 120 },{ path = "Button_53_2frames", frames = 2 }},
  modeC = {offset = { 1560, 120 },{ path = "Button_53_2frames", frames = 2 }},
  limiterOnOff = {offset = { 2020, 110 },{ path = "Button_53_2frames", frames = 2}},
  limiterHardSoft = {offset = { 2020, 205 },{ path = "Button_53_2frames", frames = 2}},
  limiter = {offset = { 1800, 100 },{ path = "Knob_01_63frames", frames = 63 }},
  inGain = {offset = { 2400, 100 },{ path = "Knob_01_63frames", frames = 63 }},
  outGain = {offset = { 2800, 100 },{ path = "Knob_01_63frames", frames = 63 }},
  outClipL = {offset = {3450, 150 },{ path = "Lamp_10_RED_2frames", frames = 2}},
  outClipR = {offset = {3450, 200 },{ path = "Lamp_10_RED_2frames", frames = 2}},
  outVolL = {offset = {3140, 150 },{ path = "Display_200_50_1frames", frames = 2}},
  outVolR = {offset = {3140, 200 },{ path = "Display_200_50_1frames", frames = 2}},
}
back = {
  Bg = { {path = "backPanel"} },
  Placeholder = {offset = { 2000, 100 },{ path = "Placeholder" }},
  deviceName = {offset = { 180, 230 },{ path = "Tape_Horizontal_1frames", frames = 1 }},
  audioInputL = {offset = { 1000,120 },{ path = "SharedAudioJack", frames = 3 }},
  audioInputR = {offset = { 1200,120 },{ path = "SharedAudioJack", frames = 3 }},
  audioOutputL = {offset = { 1550,120 },{ path = "SharedAudioJack", frames = 3 }},
  audioOutputR = {offset = { 1750,120  },{ path = "SharedAudioJack", frames = 3 }}
}

folded_front = {
	Bg = {{ path = "Panel_Folded_Front" }},
  deviceName = { offset = { 140, 40 },{ path = "Tape_Horizontal_1frames", frames = 1 }},
  patch = { offset = {710,35},{ path = "PatchName_1frames",frames=1}},
}
folded_back = { 
  Bg = {{ path = "Panel_Folded_Back" }},
  CableOrigin = { offset = { 1885, 75 }}
}





