package com.amanitadesign.steam
{
    public final class SteamInputType
    {
        public static const Unknown:int = 0;
        public static const SteamController:int = 1;
        public static const XBox360Controller:int = 2;
        public static const XBoxOneController:int = 3;
        public static const GenericGamepad:int = 4;		// DirectInput controllers
        public static const PS4Controller:int = 5;
        public static const AppleMFiController:int = 6;	// Unused
        public static const AndroidController:int = 7;	// Unused
        public static const SwitchJoyConPair:int = 8;		// Unused
        public static const SwitchJoyConSingle:int = 9;	// Unused
        public static const SwitchProController:int = 10;
        public static const MobileTouch:int = 11;			// Steam Link App On-screen Virtual Controller
        public static const PS3Controller:int = 12;		// Currently uses PS4 Origins
        public static const PS5Controller:int = 13;		// Added in SDK 151
        public static const SteamDeckController:int = 14;	// Added in SDK 153
        public static const Count:int = 15;
        public static const MaximumPossibleValue:int = 255;
    }
}