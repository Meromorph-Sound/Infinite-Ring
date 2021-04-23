format_version = "3.0"


local MAX_PHASE = math.pi
local LIMITER_MIN = -12
local LIMITER_MAX = 0

custom_properties = jbox.property_set{
	document_owner = {
		properties = {
		  phase = jbox.number {
		    property_tag = 1,
        min = 0,
		    default = 0,
        steps = 9001,
		    ui_name = jbox.ui_text("phase"),
		    ui_type = jbox.ui_linear ({min=0, max=90, units={{decimals=2,template = jbox.ui_text("degrees" )}}})
		  },
      mode = jbox.number {
        property_tag = 3,
        min=0,
        default = 1,
        steps=3,
        ui_name = jbox.ui_text("mode"),
        ui_type = jbox.ui_selector ({jbox.ui_text("REAL"),jbox.ui_text("SEMI-COMPLEX"),jbox.ui_text("COMPLEX")})
      },
      limiterOnOff = jbox.number {
        property_tag=4,
        default=1,
        steps=2,
        ui_name = jbox.ui_text("limiterOnOff"),
        ui_type = jbox.ui_selector ({jbox.UI_TEXT_OFF,jbox.UI_TEXT_ON})
      },
      limiterHardSoft = jbox.number {
        property_tag=5,
        default=0,
        steps=2,
        ui_name = jbox.ui_text("limiterHardSoft"),
        ui_type = jbox.ui_selector ({jbox.UI_TEXT_OFF,jbox.UI_TEXT_ON})
      },
     ["limiter"] = jbox.number {
      default=1,
      ui_name = jbox.ui_text("limiter"),  
      property_tag=6,
      ui_type = jbox.ui_linear{
          min=LIMITER_MIN,
          max=LIMITER_MAX,
          units = {{ decimals=1, unit = { template = jbox.ui_text("decibels" )}}}
        }
     },
      inGain = jbox.number {
        property_tag = 7,
        min=0,
        steps=101,
        default = 100,
        ui_name = jbox.ui_text("inGain"),
        ui_type = jbox.ui_linear ({min=0, max=1, units={{decimals=2}}})
      },
      outGain = jbox.number {
        property_tag = 8,
        min=0,
        steps=101,
        default = 100,
        ui_name = jbox.ui_text("outGain"),
        ui_type = jbox.ui_linear ({min=0, max=1, units={{decimals=2}}})
      },
      
      
		}
	},
	rtc_owner = {
		properties = { instance = jbox.native_object{} }
	},
	rt_owner = {
	 properties = {
     outClipL = jbox.number {
        property_tag = 9,
        min=0,
        default=0,
        steps=2,
        ui_name = jbox.ui_text("IN"),
        ui_type = jbox.ui_selector ({jbox.UI_TEXT_OFF,jbox.UI_TEXT_ON})
      },
      outClipR = jbox.number {
        property_tag = 10,
        min=0,
        default=0,
        steps=2,
        ui_name = jbox.ui_text("OUT"),
        ui_type = jbox.ui_selector ({jbox.UI_TEXT_OFF,jbox.UI_TEXT_ON})
      },
      outVolL = jbox.number {
        default=0,
        ui_name=jbox.ui_text("volume"),
        property_tag=11,
        ui_type = linearType()
      },
      outVolR = jbox.number {
        default=0,
        ui_name=jbox.ui_text("volume"),
        property_tag=12,
        ui_type = linearType()
      }
    }
	}

}

ui_groups = {}

audio_inputs = {
  Left = jbox.audio_input{ ui_name = jbox.ui_text("audioInputL") },
  Right = jbox.audio_input{ ui_name = jbox.ui_text("audioInputR") },
}
audio_outputs = {
  Left = jbox.audio_output{ ui_name = jbox.ui_text("audioOutputL") },
  Right = jbox.audio_output{ ui_name = jbox.ui_text("audioOutputR") },
}

local properties = {
  [1] = "phase",
  [3] = "mode",
  [4] = "limiterOnOff",
  [5] = "limiterHardSoft",
  [6] = "limiter",
  [7] = "inGain",
  [8] = "outGain"
}



function remote_item(name)
  return {
    internal_name = name,
    short_ui_name = jbox.ui_text("short_"..name),
    shortest_ui_name = jbox.ui_text("shortest_"..name)
  }
end

local midi_cc = {}
local remotes = {}

for idx, prop in pairs(properties) do
  local fullProp = "/custom_properties/"..prop
  midi_cc[19+idx] = fullProp
  remotes[fullProp] = remote_item(prop)
end

midi_implementation_chart = { midi_cc_chart = midi_cc }
remote_implementation_chart = remotes



jbox.add_stereo_effect_routing_hint{
  left_input = "/audio_inputs/Left",
  right_input = "/audio_inputs/Right",
  left_output = "/audio_outputs/Left",
  right_output = "/audio_outputs/Right",
  type = "true_stereo"
}
jbox.add_stereo_audio_routing_target{
  signal_type = "return",
  left = "/audio_inputs/Left",
  right = "/audio_inputs/Right",
  auto_route_enable = true
}
jbox.add_stereo_audio_routing_target{
  signal_type = "send",
  left = "/audio_outputs/Left",
  right = "/audio_outputs/Right",
  auto_route_enable = true
}
jbox.add_stereo_audio_routing_pair{
  left = "/audio_inputs/Left",
  right = "/audio_inputs/Right"
}
jbox.add_stereo_audio_routing_pair{
  left = "/audio_outputs/Left",
  right = "/audio_outputs/Right"
}
jbox.set_effect_auto_bypass_routing{
  {
    "/audio_inputs/Left",
    "/audio_outputs/Left"
  },
  {
    "/audio_inputs/Right",
    "/audio_outputs/Right"
  }
}







