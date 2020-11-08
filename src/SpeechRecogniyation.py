import os
import speech_recognition as sr
import re
from SimConnect import *
from word2number import w2n
import keyboard

import webbrowser as web


WAKE = "m"
Reply = ""


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


simconnect_path = os.getcwd() + "/SimConnect.dll"

# Create SimConnect link
sm = SimConnect(library_path=simconnect_path)

# Note the default _time is 1000 to be refreshed every 1 seconds
aq = AircraftRequests(sm, _time=1000)
# Use _time=ms where ms is the time in milliseconds to cache the data.

ae = AircraftEvents(sm)


pushtoTalk = ["t","T"]
key_release = 5
on_list_word = ["on","engage","start","up"]
off_list_word = ["off","of","disengage","stop","clear","down"]

Setting_op1_Dict = ["set"]
Release_op2_Dict = ["release"]

Flaps_list_Dict = ["fraps","flaps","laps"]
flaps_op1_list_word = ["extend","increase","set"]

Throtle_Dict = ["power","throttle","turtle","title","total","thrust","trust","protocol","trash"]
Pilot_Dict = ["pilot","pivot","pirate"]
Squak_Dict = ["squawk","transporter","square","transponder","squad","quoc"]
Battery_Dict = ["battery"]

Gear_Dict = ["gear","ear"]
Lights_Dict = ["light","lie","lights"]

Heading_Dict = ["heading","heating"]
AirSpeed_Dict = ["airspeed","speed"]
Com_Dict = ["communication","radio"]
Approach_Dict = ["approach","cocroach","roach"]
Localiser_Dict = ["localizer"]
Altitude_Dict = ["attitude","altitude"]
Vertical_Dict = ["vertical"]
Parking_Dict = ["parkingbrake"]

APU_Dict = ["APU"]
Spoiler_Dict = ["spoiler","spoil"]
FlightDirector_Dict = ["flight","director"]
AntiSkid_Dict = ["antiskidding","anti-skidding","antiskating","brake"]


def main():

    while 1:
        #altitude = aq.get("KOHLSMAN_SETTING_MB")
        #print(altitude)
        #event_to_trigger = ae.find("SPOILERS_ARM_OFF")  
        #event_to_trigger(1)
        if keyboard.is_pressed(pushtoTalk):
            print("listening Captain")
            text_raw = get_audio()
            text = text_raw.replace(" ","")
            text = text.lower()
            if text.__contains__("auto"):
                if any(ext in text for ext in Pilot_Dict) and any(ext in text for ext in on_list_word):
                    print("AUTOPILOT_ON")
                    event_to_trigger = ae.find("AUTOPILOT_ON")  
                    event_to_trigger()
                elif any(ext in text for ext in Pilot_Dict) and any(ext in text for ext in off_list_word):
                    print("AUTOPILOT_OFF")
                    event_to_trigger = ae.find("AUTOPILOT_OFF")  
                    event_to_trigger()
                elif any(ext in text for ext in Throtle_Dict):
                    result = int(aq.get("AUTOTHROTTLE_ACTIVE"))
                    if any(ext in text for ext in on_list_word):
                        if result == 0:
                          event_to_trigger = ae.find("AUTO_THROTTLE_ARM")  
                          event_to_trigger()
                    if any(ext in text for ext in off_list_word):
                        print(int(result))
                        if result == 1:
                          event_to_trigger = ae.find("AUTO_THROTTLE_ARM")  
                          event_to_trigger()
                elif any(ext in text for ext in AntiSkid_Dict):
                    result = int(aq.get("ANTISKID_BRAKES_ACTIVE"))
                    print(result)
                    if any(ext in text for ext in on_list_word):
                        if result == 0:
                            event_to_trigger = ae.find("ANTISKID_BRAKES_TOGGLE")  
                            event_to_trigger()
                    if any(ext in text for ext in off_list_word):
                        if result == 1:
                            event_to_trigger = ae.find("ANTISKID_BRAKES_TOGGLE")  
                            event_to_trigger()

            elif any(ext in text for ext in FlightDirector_Dict) :
                result = int(aq.get("AUTOPILOT_FLIGHT_DIRECTOR_ACTIVE"))
                if any(ext in text for ext in Setting_op1_Dict) or any(ext in text for ext in on_list_word):
                    if result == 0:
                        event_to_trigger = ae.find("TOGGLE_FLIGHT_DIRECTOR")  
                        event_to_trigger()
                if any(ext in text for ext in Release_op2_Dict) or any(ext in text for ext in off_list_word):
                    if result == 1:
                        event_to_trigger = ae.find("TOGGLE_FLIGHT_DIRECTOR")  
                        event_to_trigger()



            elif any(ext in text for ext in Parking_Dict):
                result = int(aq.get("BRAKE_PARKING_INDICATOR"))
                if any(ext in text for ext in Setting_op1_Dict) or any(ext in text for ext in on_list_word):
                    if result == 0:
                        event_to_trigger = ae.find("PARKING_BRAKES")  
                        event_to_trigger()
                if any(ext in text for ext in Release_op2_Dict) or any(ext in text for ext in off_list_word):
                    if result == 1:
                        event_to_trigger = ae.find("PARKING_BRAKES")  
                        event_to_trigger()

            elif any(ext in text for ext in Throtle_Dict) :
                if any(ext in text for ext in Setting_op1_Dict):
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
                     Throttle = ValueInt * 164
                     event_to_trigger = ae.find("THROTTLE_SET")  
                     event_to_trigger(Throttle)

            elif any(ext in text for ext in Flaps_list_Dict) :
                if any(ext in text for ext in flaps_op1_list_word):
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
                     flaps = ValueInt * 4000
                     event_to_trigger = ae.find("FLAPS_SET")  
                     event_to_trigger(flaps)


            elif any(ext in text for ext in Gear_Dict) :
                if any(ext in text for ext in on_list_word):
                  event_to_trigger = ae.find("GEAR_UP")  
                  event_to_trigger()
                elif any(ext in text for ext in off_list_word):
                    event_to_trigger = ae.find("GEAR_DOWN")  
                    event_to_trigger()

            elif any(ext in text for ext in Battery_Dict) :
                if any(ext in text for ext in on_list_word):
                  event_to_trigger = ae.find("TOGGLE_MASTER_BATTERY")  
                  event_to_trigger()

            elif any(ext in text for ext in Lights_Dict) :
                result = int(aq.get("LIGHT_LANDING"))
                print(result)
                if any(ext in text for ext in on_list_word):
                    if result == 0:
                        event_to_trigger = ae.find("ALL_LIGHTS_TOGGLE")  
                        event_to_trigger()
                if any(ext in text for ext in off_list_word):
                    if result == 1:
                        event_to_trigger = ae.find("ALL_LIGHTS_TOGGLE")  
                        event_to_trigger()

            elif any(ext in text for ext in Heading_Dict) :
                if any(ext in text for ext in Setting_op1_Dict):
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
                        Heading = ValueInt
                        event_to_trigger = ae.find("HEADING_BUG_SET")  
                        event_to_trigger(Heading)

            elif any(ext in text for ext in AirSpeed_Dict) :
                if any(ext in text for ext in Setting_op1_Dict):
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
                     AirSpeed = ValueInt
                     if any(ext in text for ext in Vertical_Dict):
                         event_to_trigger = ae.find("AP_VS_VAR_INC")  
                         event_to_trigger()
                         event_to_trigger = ae.find("AP_VS_VAR_SET_ENGLISH")  
                         event_to_trigger(AirSpeed)
                     else:
                        event_to_trigger = ae.find("AP_SPD_VAR_SET")  
                        event_to_trigger(AirSpeed)


            elif any(ext in text for ext in Squak_Dict) :
                if any(ext in text for ext in Setting_op1_Dict):
                    Value = re.findall(r'\d+', text)
                    ValueInt = ""
                    if not Value:
                        try:
                            ValueInt = w2n.word_to_num(text_raw)
                        except:
                            pass
                    else:
                        ValueInt = Value[0]
                    if ValueInt:
                        sqwauk = int(ValueInt,16)
                        event_to_trigger = ae.find("XPNDR_SET")  
                        event_to_trigger(sqwauk)

            elif any(ext in text for ext in Approach_Dict) :
                if any(ext in text for ext in on_list_word):
                  event_to_trigger = ae.find("AP_APR_HOLD_ON")  
                  event_to_trigger()
                if any(ext in text for ext in off_list_word):
                  event_to_trigger = ae.find("AP_APR_HOLD_OFF")  
                  event_to_trigger()

            elif any(ext in text for ext in Localiser_Dict) :
                if any(ext in text for ext in on_list_word):
                  event_to_trigger = ae.find("AP_LOC_HOLD_ON")  
                  event_to_trigger()
                if any(ext in text for ext in off_list_word):
                  event_to_trigger = ae.find("AP_LOC_HOLD_OFF")  
                  event_to_trigger()

            elif any(ext in text for ext in Altitude_Dict) :
                if any(ext in text for ext in Setting_op1_Dict):
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
                     Altitude = ValueInt
                     event_to_trigger = ae.find("AP_ALT_VAR_SET_ENGLISH")  
                     event_to_trigger(Altitude)

            elif any(ext in text for ext in Spoiler_Dict) :
                if any(ext in text for ext in Setting_op1_Dict):
                  event_to_trigger = ae.find("SPOILERS_ARM_OFF")  
                  event_to_trigger()
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
                     percentage = ValueInt * 164
                     event_to_trigger = ae.find("SPOILERS_SET")  
                     event_to_trigger(percentage)
                elif text.__contains__("arm"):
                    event_to_trigger = ae.find("SPOILERS_ARM_ON")  
                    event_to_trigger()

            elif any(ext in text for ext in APU_Dict):
                if any(ext in text for ext in on_list_word):
                  event_to_trigger = ae.find("APU_STARTER")  
                  event_to_trigger()
                if any(ext in text for ext in off_list_word):
                  event_to_trigger = ae.find("APU_OFF_SWITCH")  
                  event_to_trigger()


            else:
                pass



if __name__ == "__main__":
    main()