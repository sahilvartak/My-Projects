import os
from time import sleep
import pyttsx3 as tts
import speech_recognition as sr
import re
from SimConnect import *
from word2number import w2n
import keyboard
print("# VoiceControl_Fs2020"
      "This is Voice Control uses google voice to convert speech to text and then send the command to Flight Simulator 2020\n "
      "This was just a weekend project . if you are willing to contribute you can update the script.\n"
      "\n"
      "Precondtion:\n"
      "Flight simulator shall be running before running the exe\n"
      "Exe shall have access to microphone\n"
      "\n"
      "Press T and say the command\n"
      "\n"
      "Dependency\n"
      "Python 3.6\n"
      "package\n"
      "   -- keyboard\n"
      "   -- speech_recognition\n"
      "   -- re\n"
      "   -- SimConnect \n"
      "   -- word2number \n"
      "     SimConnect.dll\n"
      "Developer -- Sahil Vartak\n")

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

debug = "OFF"


engine = tts.init()
def sayit(text):
    engine.say(text)
    engine.runAndWait()

simconnect_path = os.getcwd() + "/SimConnect.dll"

if debug == "OFF":
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

    # To find and set timeout of cached data to 200ms:
    #altitude = aq.find("PLANE_ALTITUDE")
    #altitude.time = 200

    # Set the aircraft's current altitude
    #aq.set("PLANE_ALTITUDE", altitude)

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
    if debug == "OFF":
      event_to_trigger = ae.find(command)
      event_to_trigger()
    return 1

def SendCommand_arguments(command,Value):
    if debug == "OFF":
      event_to_trigger = ae.find(command)
      event_to_trigger(Value)
    return 1

def getData(command):
    status = 0
    if debug == "OFF":
      status =  int(aq.get(command))
    return status


def checkStateBefore(saytext,Data_get_Cmd,Data_set_cmd,ON_OFF):
    sayit(saytext)
    status = 1
    if (getData(Data_get_Cmd) == ON_OFF):
        status = SendCommand(Data_set_cmd)
    return status


def Set_ON_Commands(text):

    status = 0

    if text.__contains__("auto") or text.__contains__("skid"):
      if any(ext in text for ext in Pilot_Dict):
          status = SendCommand("AUTOPILOT_ON")
          sayit("Auto Pilot ON")

      elif any(ext in text for ext in Throtle_Dict):
          status = checkStateBefore("Auto Throttle ON","AUTOTHROTTLE_ACTIVE","AUTO_THROTTLE_ARM",0)

      elif any(ext in text for ext in AntiSkid_Dict):
          status = checkStateBefore("Auto Brake ON", "ANTISKID_BRAKES_ACTIVE", "ANTISKID_BRAKES_TOGGLE",0)

    elif any(ext in text for ext in FlightDirector_Dict):
        status = checkStateBefore("Flight Director ON", "AUTOPILOT_FLIGHT_DIRECTOR_ACTIVE", "TOGGLE_FLIGHT_DIRECTOR",0)

    elif any(ext in text for ext in Gear_Dict):
        status = SendCommand("GEAR_UP")
        sayit("Gear UP")

    elif any(ext in text for ext in Approach_Dict):
        status = SendCommand("AP_APR_HOLD_ON")
        sayit("Approach On")

    elif any(ext in text for ext in Localiser_Dict):
        status = SendCommand("AP_LOC_HOLD_ON")
        sayit("Localizer On")

    elif any(ext in text for ext in APU_Dict):
        status = SendCommand("APU_STARTER")
        sayit("APU On")

    elif any(ext in text for ext in AntiICE_Dict):
        status = SendCommand("ANTI_ICE_ON")
        sayit("Anti ICE On")

    elif any(ext in text for ext in Parking_Dict):
        status = checkStateBefore("Parking brake On", "BRAKE_PARKING_INDICATOR", "PARKING_BRAKES", 0)

    elif any(ext in text for ext in Lights_Dict):
        status = checkStateBefore("All Lights On", "LIGHT_LANDING", "ALL_LIGHTS_TOGGLE", 0)


    elif any(ext in text for ext in Battery_Dict):
        status = checkStateBefore("Master Battery On", "ELECTRICAL_MASTER_BATTERY", "TOGGLE_MASTER_BATTERY", 0)

    return status


def Set_OFF_Commands(text):

    status = 0

    if text.__contains__("auto") or text.__contains__("skid"):
      if any(ext in text for ext in Pilot_Dict):
          status = SendCommand("AUTOPILOT_OFF")
          sayit("Auto Pilot OFF")

      elif any(ext in text for ext in Throtle_Dict):
          status = checkStateBefore("Auto Throttle OFF", "AUTOTHROTTLE_ACTIVE", "AUTO_THROTTLE_ARM", 1)

      elif any(ext in text for ext in AntiSkid_Dict):
          status = checkStateBefore("Auto Brake OFF", "ANTISKID_BRAKES_ACTIVE", "ANTISKID_BRAKES_TOGGLE", 1)

    elif any(ext in text for ext in FlightDirector_Dict):
        status = checkStateBefore("Flight Director OFF", "AUTOPILOT_FLIGHT_DIRECTOR_ACTIVE", "TOGGLE_FLIGHT_DIRECTOR", 1)

    elif any(ext in text for ext in Gear_Dict):
        status = SendCommand("GEAR_DOWN")
        sayit("Gear Down")

    elif any(ext in text for ext in Approach_Dict):
        status = SendCommand("AP_APR_HOLD_OFF")
        sayit("Approach  OFF")

    elif any(ext in text for ext in Localiser_Dict):
        status = SendCommand("AP_LOC_HOLD_OFF")
        sayit("Localizer OFF")

    elif any(ext in text for ext in APU_Dict):
        status = SendCommand("APU_OFF_SWITCH")
        sayit("APU OFF")

    elif any(ext in text for ext in AntiICE_Dict):
        status = SendCommand("ANTI_ICE_OFF")
        sayit("APU OFF")

    elif any(ext in text for ext in Parking_Dict):
        status = checkStateBefore("Parking brake OFF", "BRAKE_PARKING_INDICATOR", "PARKING_BRAKES", 1)

    elif any(ext in text for ext in Lights_Dict):
        status = checkStateBefore("Lights OFF", "LIGHT_LANDING", "ALL_LIGHTS_TOGGLE", 1)

    elif any(ext in text for ext in Battery_Dict):
        status = checkStateBefore("Master Battery OFF", "ELECTRICAL_MASTER_BATTERY", "TOGGLE_MASTER_BATTERY", 1)

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

    if ValueInt > -1:
      if any(ext in text for ext in Throtle_Dict):
        arg_Value = ValueInt * 164
        status = SendCommand_arguments("THROTTLE_SET",arg_Value)
        sayit("Setting Throttle to" + str(ValueInt))

      elif any(ext in text for ext in Flaps_list_Dict):
        arg_Value = ValueInt * 4000
        status = SendCommand_arguments("FLAPS_SET",arg_Value)
        sayit("Setting Flaps to" + str(ValueInt))

      elif any(ext in text for ext in Heading_Dict):
        arg_Value = ValueInt
        status = SendCommand_arguments("HEADING_BUG_SET",arg_Value)
        sayit("Setting Heading to" + str(ValueInt))

      elif any(ext in text for ext in AirSpeed_Dict):
        arg_Value = ValueInt
        if any(ext in text for ext in Vertical_Dict):
          status = SendCommand_arguments("AP_VS_VAR_SET_ENGLISH",arg_Value)
          sayit("Setting Vertical speed to" + str(ValueInt))
        else:
          status = SendCommand_arguments("AP_SPD_VAR_SET",arg_Value)
          sayit("Setting Airspeed to" + str(ValueInt))

      elif any(ext in text for ext in Squak_Dict):
        arg_Value = int(Value[0], 16)
        status = SendCommand_arguments("XPNDR_SET",arg_Value)
        sayit("Setting transponder to" + Value[0])

      elif any(ext in text for ext in Altitude_Dict):
        arg_Value = ValueInt
        status = SendCommand_arguments("AP_ALT_VAR_SET_ENGLISH",arg_Value)
        sayit("Setting Flight level to" + str(ValueInt))

      elif any(ext in text for ext in Spoiler_Dict):
        SendCommand("SPOILERS_ARM_OFF")
        arg_Value = ValueInt * 164
        status = SendCommand_arguments("SPOILERS_SET",arg_Value)
        sayit("Setting Spoilers to" + str(ValueInt))

      elif any(ext in text for ext in Nav_Dic):
          freq_hz = ValueInt
          freq_hz = str(int(freq_hz))
          freq_hz_bcd = 0
          for figure, digit in enumerate(reversed(freq_hz)):
              freq_hz_bcd += int(digit) * (16 ** (figure))
          status = SendCommand_arguments("NAV1_RADIO_SET",freq_hz_bcd)
          sayit("Nav Radio to" + str(ValueInt))

    return status


def Miscelanous(text):
    if any(ext in text for ext in Spoiler_Dict) and text.__contains__("arm"):
        SendCommand("SPOILERS_ARM_ON")
        sayit(" Spoliers ARMED")

def Positive_Climb(initial_flight_level):
    status = 0
    curent_FligheLevel = getData("PLANE_ALTITUDE")
    if (curent_FligheLevel > initial_flight_level):
        sayit("Positive Climb")
        status = 1
    return status

def main():
    initial_flight_level = getData("PLANE_ALTITUDE") + 50
    Takeoff_done = 0
    while 1:

        if Takeoff_done == 0:
          Takeoff_done = Positive_Climb(initial_flight_level)

        status = 0
        if keyboard.is_pressed(pushtoTalk):
            print("listening Captain")
            text_raw = get_audio()
            text = text_raw
            #text = text_raw.replace(" ","")
            text = text.lower()

            if any(ext in text for ext in on_list_Dict):
                status = Set_ON_Commands(text)

            elif any(ext in text for ext in off_list_Dict):
                status = Set_OFF_Commands(text)

            else:
                status = SetValues(text, text_raw)
                status = Miscelanous(text)

            if status == 0:
                sayit("Sir Say again")


if __name__ == "__main__":
    main()
