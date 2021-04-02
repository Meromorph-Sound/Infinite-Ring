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
		    default = 1,
        steps = 1801,
		    ui_name = jbox.ui_text("phase"),
		    ui_type = jbox.ui_linear ({min=0, max=180, units={{template = jbox.ui_text("degrees" )}}})
		  },
		  offset = jbox.number {
        property_tag = 2,
        default = 1,
        ui_name = jbox.ui_text("offset"),
        ui_type = jbox.ui_linear ({min=-1, max=1, units={{decimals=2}}})
      },
      angle = jbox.number {
        property_tag = 3,
        min=0,
        default = 0,
        steps=1800,
        ui_name = jbox.ui_text("angle"),
        ui_type = jbox.ui_linear ({min=0, max=179.9, units={{template = jbox.ui_text("degrees" )}}})
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
      limiter = jbox.number {
        property_tag=6,
        default=1,
        ui_name = jbox.ui_text("limiter"),  
        
        ui_type = jbox.ui_linear{
          min=LIMITER_MIN,
          max=LIMITER_MAX,
          units = {{ decimals=1, unit = { template = jbox.ui_text("decibels" )}}}
        }
     },
      gain = jbox.number {
        property_tag = 7,
        default = 1,
        ui_name = jbox.ui_text("gain"),
        ui_type = jbox.ui_linear ({min=0, max=1, units={{decimals=2}}})
      }
		}
	},
	rtc_owner = {
		properties = { instance = jbox.native_object{} }
	},
	rt_owner = {
	 properties = {}
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
  [2] = "offset",
  [3] = "angle",
  [4] = "limiterOnOff",
  [5] = "limiterHardSoft",
  [6] = "limiter",
  [7] = "gain"
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







