/*
 *  NetworkingMessage.as
 *  This file is part of FRESteamWorks.
 *
 *  Created by Fancy2209 <http://github.com/Fancy2209> on 2025-07-14
 */

// TODO: This'll need more fields if/when SteamNetworkingSockets is added
package com.amanitadesign.steam {
import flash.utils.ByteArray;
	public class NetworkingMessage {
		public var payload:ByteArray;
		public var peerSteamID:String;
		public var timeReceived:String;
		public var channel:int;
	}
}
