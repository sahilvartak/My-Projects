import os
from time import sleep
import speech_recognition as sr
import re
from SimConnect import *
from word2number import w2n
import keyboard

pushtoTalk = ["t","T"]
key_release = 5
on_list_Dict = ["on","engage","start","up","hold"]
off_list_Dict = ["off","release","stop","clear","down"]
Set_list_Dict = ["set","search"]

Flaps_list_Dict = ["fraps","flaps","laps"]

Throtle_Dict = ["power","throttle","turtle","title","total","thrust","trust","protocol","trash","correct"]
Pilot_Dict = ["pilot","pivot","pirate"]
Squak_Dict = ["quark","squawk","transporter","square","transponder","squad","quoc","swap"]
Battery_Dict = ["battery"]

Gear_Dict = ["gear","ear"]
Lights_Dict = ["light","lie","lights"]

Heading_Dict = ["heading","heating"]
AirSpeed_Dict = ["airspeed","speed"]
Com_Dict = ["communication","radio"]
Approach_Dict = ["approach","cocroach","roach"]
Localiser_Dict = ["localizer","localiza","localiser"]
Altitude_Dict = ["attitude","altitude","level"]
Vertical_Dict = ["vertical"]
Parking_Dict = ["parking brake"]

APU_Dict = ["apu","apo"]
Spoiler_Dict = ["spoiler","spoil"]
FlightDirector_Dict = ["director","direct"]
AntiSkid_Dict = ["anti skidding","anti-skidding","skid","antiskating","brake","break"]
Nav_Dic = ["nav","com","radio"]
AntiICE_Dict = ["anti-ice", "ice","anti-icing"]

simconnect_path = os.getcwd() + "/SimConnect.dll"

# Create SimConnect link
while True:
    try:
        sm = SimConnect(library_path=simconnect_path)
        break
    except:
        print("Could not find MSFS running. Please launch MSFS.")
        sleep(5)

# Note the default _time is 2000 to be refreshed every 2 seconds
aq = AircraftRequests(sm, _time=1000)
# Use _time=ms where ms is the time in milliseconds to cache the data.
# Setting ms to 0 will disable data caching and always pull new data from the sim.
# There is still a timeout of 4 tries with a 10ms delay between checks.
# If no data is received in 40ms the value will be set to None
# Each request can be fine tuned by setting the time param.

ae = AircraftEvents(sm)


def get_audio():
    r = sr.Recognizer()
    with sr.Microphone() as source:
        audio = r.listen(source)
        said = ""
        try:
            said = r.recognize_google(audio)
            print(said)
        except Exception as e:
            print("Exception: " + str(e))

    return said.lower()


def SendCommand(command):
    event_to_trigger = ae.find(command)
    event_to_trigger()
    return 1


def SendCommand_arguments(command, Value):
    event_to_trigger = ae.find(command)
    event_to_trigger(Value)
    return 1


def Set_ON_Commands(text):
    status = 0

    if text.__contains__("auto") or text.__contains__("skid"):
      if any(ext in text for ext in Pilot_Dict):
          status = SendCommand("AUTOPILOT_ON")

      elif any(ext in text for ext in Throtle_Dict) and int(aq.get("AUTOTHROTTLE_ACTIVE") == 0):
          status = SendCommand("AUTO_THROTTLE_ARM")

      elif any(ext in text for ext in AntiSkid_Dict) and int(aq.get("ANTISKID_BRAKES_ACTIVE") == 0):
          status = SendCommand("ANTISKID_BRAKES_TOGGLE")


    elif any(ext in text for ext in FlightDirector_Dict) and int(aq.get("AUTOPILOT_FLIGHT_DIRECTOR_ACTIVE") == 0):
        status = SendCommand("TOGGLE_FLIGHT_DIRECTOR")

    elif any(ext in text for ext in Gear_Dict):
        status = SendCommand("GEAR_UP")

    elif any(ext in text for ext in Approach_Dict):
        status = SendCommand("AP_APR_HOLD_ON")

    elif any(ext in text for ext in Localiser_Dict):
        status = SendCommand("AP_LOC_HOLD_ON")

    elif any(ext in text for ext in APU_Dict):
        status = SendCommand("APU_STARTER")

    elif any(ext in text for ext in AntiICE_Dict):
        status = SendCommand("ANTI_ICE_ON")

    elif any(ext in text for ext in Parking_Dict) and int(aq.get("BRAKE_PARKING_INDICATOR") == 0):
        status = SendCommand("PARKING_BRAKES")

    elif any(ext in text for ext in Lights_Dict) and int(aq.get("LIGHT_LANDING") == 0):
        status = SendCommand("ALL_LIGHTS_TOGGLE")

    elif any(ext in text for ext in Battery_Dict) and int(aq.get("ELECTRICAL MASTER BATTERY") == 0):
        status = SendCommand("TOGGLE_MASTER_BATTERY")

    return status


def Set_OFF_Commands(text):

    status = 0

    if text.__contains__("auto") or text.__contains__("skid"):
      if any(ext in text for ext in Pilot_Dict):
          status = SendCommand("AUTOPILOT_OFF")

      elif any(ext in text for ext in Throtle_Dict) and int(aq.get("AUTOTHROTTLE_ACTIVE") == 1):
          status = SendCommand("AUTO_THROTTLE_ARM")
      elif any(ext in text for ext in AntiSkid_Dict) and int(aq.get("ANTISKID_BRAKES_ACTIVE") == 1):
          status = SendCommand("ANTISKID_BRAKES_TOGGLE")

    elif any(ext in text for ext in FlightDirector_Dict) and int(aq.get("AUTOPILOT_FLIGHT_DIRECTOR_ACTIVE") == 1):
        status = SendCommand("TOGGLE_FLIGHT_DIRECTOR")

    elif any(ext in text for ext in Gear_Dict):
        status = SendCommand("GEAR_DOWN")

    elif any(ext in text for ext in Approach_Dict):
        status = SendCommand("AP_APR_HOLD_OFF")

    elif any(ext in text for ext in Localiser_Dict):
        status = SendCommand("AP_LOC_HOLD_OFF")

    elif any(ext in text for ext in APU_Dict):
        status = SendCommand("APU_OFF_SWITCH")

    elif any(ext in text for ext in AntiICE_Dict):
        status = SendCommand("ANTI_ICE_OFF")

    elif any(ext in text for ext in Parking_Dict) and int(aq.get("BRAKE_PARKING_INDICATOR") == 1):
        status = SendCommand("PARKING_BRAKES")

    elif any(ext in text for ext in Lights_Dict) and int(aq.get("LIGHT_LANDING") == 1):
        status = SendCommand("ALL_LIGHTS_TOGGLE")

    elif any(ext in text for ext in Battery_Dict) and int(aq.get("ELECTRICAL MASTER BATTERY") == 1):
        status = SendCommand("TOGGLE_MASTER_BATTERY")

    return status


def SetValues(text,text_raw):

    status = 0

    Value = re.findall(r'\d+', text)
    ValueInt = -1
    if not Value:
        try:
            ValueInt = int(w2n.word_to_num(text_raw))
        except:
            pass
    else:
        ValueInt = int(Value[0])

    print(ValueInt)
    if ValueInt > -1:
      if any(ext in text for ext in Throtle_Dict):
        arg_Value = ValueInt * 164
        status = SendCommand_arguments("THROTTLE_SET",arg_Value)

      elif any(ext in text for ext in Flaps_list_Dict):
        arg_Value = ValueInt * 4000
        status = SendCommand_arguments("FLAPS_SET",arg_Value)

      elif any(ext in text for ext in Heading_Dict):
        arg_Value = ValueInt
        status = SendCommand_arguments("HEADING_BUG_SET",arg_Value)

      elif any(ext in text for ext in AirSpeed_Dict):
        arg_Value = ValueInt
        if any(ext in text for ext in Vertical_Dict):
          status = SendCommand_arguments("AP_VS_VAR_SET_ENGLISH",arg_Value)
        else:
          status = SendCommand_arguments("AP_SPD_VAR_SET",arg_Value)

      elif any(ext in text for ext in Squak_Dict):
        arg_Value = int(Value[0], 16)
        status = SendCommand_arguments("XPNDR_SET",arg_Value)

      elif any(ext in text for ext in Altitude_Dict):
        arg_Value = ValueInt
        status = SendCommand_arguments("AP_ALT_VAR_SET_ENGLISH",arg_Value)

      elif any(ext in text for ext in Spoiler_Dict):
        SendCommand("SPOILERS_ARM_OFF")
        arg_Value = ValueInt * 164
        status = SendCommand_arguments("SPOILERS_SET",arg_Value)

      elif any(ext in text for ext in Nav_Dic):
          freq_hz = ValueInt
          freq_hz = str(int(freq_hz))
          freq_hz_bcd = 0
          for figure, digit in enumerate(reversed(freq_hz)):
              freq_hz_bcd += int(digit) * (16 ** (figure))
          SendCommand_arguments("NAV1_RADIO_SET",freq_hz_bcd)

    return status


def Miscelanous(text):
    if any(ext in text for ext in Spoiler_Dict) and text.__contains__("arm"):
        SendCommand("SPOILERS_ARM_ON")


def main():
    while 1:

        if keyboard.is_pressed(pushtoTalk):
            print("listening Captain")
            text_raw = get_audio()
            text = text_raw
            #text = text_raw.replace(" ","")
            text = text.lower()

            if any(ext in text for ext in on_list_Dict):
                Set_ON_Commands(text)

            elif any(ext in text for ext in off_list_Dict):
                Set_OFF_Commands(text)

            elif any(ext in text for ext in Set_list_Dict):
                SetValues(text,text_raw)
            else:
                Miscelanous(text)


if __name__ == "__main__":
    main()
